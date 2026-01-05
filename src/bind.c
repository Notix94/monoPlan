#include "../include/bind.h"
#include "../include/feuille.h"
#include "../include/formule.h"
#include <ctype.h>

// Tableau global des liaisons [ligne][colonne]
s_bind *liaisons[NBCOL][NBLIG] = {{NULL}};

// Variable globale pour la barre de formule
GtkWidget *entry_formule_global = NULL;

// Variable globale pour la feuille
extern s_feuille feuille_globale;

// Recherche une liaison par cellule
s_bind *bindLookupByCell(s_cell *cell) {
    for (int col = 0; col < NBCOL; col++) {
        for (int lig = 0; lig < NBLIG; lig++) {
            if (liaisons[col][lig] && liaisons[col][lig]->cell == cell) {
                return liaisons[col][lig];
            }
        }
    }
    return NULL;
}

// Recherche une liaison par position
s_bind *bindLookupByPos(int colonne, int ligne) {
    if (colonne >= 0 && colonne < NBCOL && ligne >= 0 && ligne < NBLIG) {
        return liaisons[colonne][ligne];
    }
    return NULL;
}

// Mettre à jour l'affichage d'une cellule
void update_cell_display(s_bind *bind) {
    if (!bind || !bind->case_widget) return;
    
    // Si la cellule contient une formule, afficher le résultat
    if (bind->cell->t[0] == '=') {
        char buffer[64];
        snprintf(buffer, sizeof(buffer), "%.2f", bind->cell->value);
        gtk_entry_set_text(GTK_ENTRY(bind->case_widget), buffer);
    } else {
        // Sinon afficher le contenu brut
        gtk_entry_set_text(GTK_ENTRY(bind->case_widget), bind->cell->t);
    }
}

// Mettre à jour l'affichage de tous les dépendants
void update_dependents_display(s_cell *cell) {
    if (!cell || !cell->cells) return;
    
    node_t *n = cell->cells;
    while (n) {
        s_cell *dep = list_get_data(n);
        s_bind *bind = bindLookupByCell(dep);
        if (bind) {
            update_cell_display(bind);
        }
        // Récursif pour les dépendants des dépendants
        update_dependents_display(dep);
        n = list_next(n);
    }
}

// Callback quand on valide une cellule (touche Entrée)
void callback_validation(GtkEntry *entry, gpointer user_data) {
    s_bind *bind = (s_bind *)user_data;
    const gchar *texte = gtk_entry_get_text(entry);
    
    printf("[CALLBACK] Validation cellule [%d][%d] : '%s'\n", 
           bind->ligne, bind->colonne, texte);
    
    // Mettre à jour le modèle de la cellule
    cell_setStr(bind->cell, texte, &feuille_globale);
    
    // Mettre à jour l'affichage de cette cellule
    update_cell_display(bind);
    
    // Mettre à jour l'affichage de tous les dépendants
    update_dependents_display(bind->cell);
    
    printf("Valeur calculée : %.2f\n", bind->cell->value);
}

// Callback quand une cellule reçoit le focus
gboolean callback_focus_in(GtkWidget *widget, GdkEventFocus *event, gpointer user_data) {
    s_bind *bind = (s_bind *)user_data;
    
    // Afficher la formule brute dans la barre de formule
    if (entry_formule_global) {
        gtk_entry_set_text(GTK_ENTRY(entry_formule_global), bind->cell->t);
    }
    
    // Afficher la formule dans la cellule elle-même
    gtk_entry_set_text(GTK_ENTRY(widget), bind->cell->t);
    
    (void)event;

    return FALSE;
}

// Créer toutes les cellules de la grille
void creer_cellules(GtkWidget *grid, s_feuille *feuille) {
    // Créer une cellule vide en haut à gauche
    GtkWidget *corner = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), corner, 0, 0, 1, 1);
    
    // Créer les en-têtes de colonnes (A, B, C, ...)
    for (int col = 0; col < NBCOL; col++) {
        GtkWidget *label = gtk_label_new(NULL);
        char col_name[3];
        col_name[0] = 'A' + col;
        col_name[1] = '\0';
        gtk_label_set_text(GTK_LABEL(label), col_name);
        gtk_widget_set_size_request(label, 80, -1);
        gtk_grid_attach(GTK_GRID(grid), label, col + 1, 0, 1, 1);
    }
    
    // Créer les en-têtes de lignes (1, 2, 3, ...)
    for (int lig = 0; lig < NBLIG; lig++) {
        GtkWidget *label = gtk_label_new(NULL);
        char row_name[4];
        snprintf(row_name, sizeof(row_name), "%d", lig + 1);
        gtk_label_set_text(GTK_LABEL(label), row_name);
        gtk_widget_set_size_request(label, 30, -1);
        gtk_grid_attach(GTK_GRID(grid), label, 0, lig + 1, 1, 1);
    }
    
    // Créer toutes les cellules
    for (int col = 0; col < NBCOL; col++) {
        for (int lig = 0; lig < NBLIG; lig++) {
            // Créer la structure bind
            s_bind *bind = malloc(sizeof(s_bind));
            bind->ligne = lig;
            bind->colonne = col;
            
            // Créer le widget GtkEntry
            bind->case_widget = gtk_entry_new();
            gtk_entry_set_width_chars(GTK_ENTRY(bind->case_widget), 10);
            gtk_widget_set_size_request(bind->case_widget, 80, -1);
            gtk_entry_set_text(GTK_ENTRY(bind->case_widget), "");
            
            // Créer ou récupérer le modèle de cellule
            if (feuille->tab[lig][col] == NULL) {
                bind->cell = init_cell();
                feuille->tab[lig][col] = bind->cell;
            } else {
                bind->cell = feuille->tab[lig][col];
            }
            
            // Connecter les callbacks
            g_signal_connect(bind->case_widget, "activate",
                           G_CALLBACK(callback_validation), bind);
            g_signal_connect(bind->case_widget, "focus-in-event",
                           G_CALLBACK(callback_focus_in), bind);
            
            // Ajouter au grid (décalage de +1 pour les en-têtes)
            gtk_grid_attach(GTK_GRID(grid), bind->case_widget, 
                          col + 1, lig + 1, 1, 1);
            
            // Enregistrer la liaison
            liaisons[col][lig] = bind;
        }
    }
}