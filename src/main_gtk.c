#include <gtk/gtk.h>
#include "../include/feuille.h"
#include "../include/cellule.h"
#include "../include/bind.h"

// Variable globale pour la feuille
s_feuille feuille_globale;

// Variable globale pour la barre de formule (déclarée dans bind.c)
extern GtkWidget *entry_formule_global;

// Callback pour le menu Quitter
void on_menu_quitter_activate(GtkMenuItem *menuitem, gpointer user_data) {
    (void)menuitem;
    (void)user_data;
    gtk_main_quit();
}

// Callback pour le menu À propos
void on_menu_apropos_activate(GtkMenuItem *menuitem, gpointer user_data) {
    (void)menuitem;
    (void)user_data;
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "MonoPlan - Tableur simple\nJalon 4 - Interface GTK+\n\nUtilisez les cellules comme dans Excel.\nExemple de formule : =A1 B2 +");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    
    // Initialiser la feuille de calcul
    init_feuille(&feuille_globale, "Feuille1", NBLIG, NBCOL);
    
    // Créer la fenêtre principale
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "MonoPlan - Tableur");
    gtk_window_set_default_size(GTK_WINDOW(window), 1200, 700);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // Box vertical principal
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    
    // === BARRE DE MENU ===
    GtkWidget *menubar = gtk_menu_bar_new();
    
    // Menu Fichier
    GtkWidget *menu_fichier = gtk_menu_new();
    GtkWidget *menuitem_fichier = gtk_menu_item_new_with_label("Fichier");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem_fichier), menu_fichier);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menuitem_fichier);
    
    GtkWidget *menuitem_quitter = gtk_menu_item_new_with_label("Quitter");
    g_signal_connect(menuitem_quitter, "activate", 
                    G_CALLBACK(on_menu_quitter_activate), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_fichier), menuitem_quitter);
    
    // Menu Aide
    GtkWidget *menu_aide = gtk_menu_new();
    GtkWidget *menuitem_aide = gtk_menu_item_new_with_label("Aide");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem_aide), menu_aide);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menuitem_aide);
    
    GtkWidget *menuitem_apropos = gtk_menu_item_new_with_label("À propos");
    g_signal_connect(menuitem_apropos, "activate", 
                    G_CALLBACK(on_menu_apropos_activate), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_aide), menuitem_apropos);
    
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);
    
    // === BARRE DE FORMULE ===
    GtkWidget *hbox_formule = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox_formule, FALSE, FALSE, 5);
    
    GtkWidget *label_formule = gtk_label_new("Formule:");
    gtk_box_pack_start(GTK_BOX(hbox_formule), label_formule, FALSE, FALSE, 5);
    
    entry_formule_global = gtk_entry_new();
    gtk_editable_set_editable(GTK_EDITABLE(entry_formule_global), FALSE);
    gtk_box_pack_start(GTK_BOX(hbox_formule), entry_formule_global, TRUE, TRUE, 5);
    
    // === ZONE DE CELLULES ===
    GtkWidget *scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled),
                                   GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled, TRUE, TRUE, 0);
    
    // Grille pour les cellules
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 1);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 1);
    gtk_container_add(GTK_CONTAINER(scrolled), grid);
    
    // Créer toutes les cellules (26 colonnes x 50 lignes)
    printf("Création de la grille : %d colonnes x %d lignes\n", NBCOL, NBLIG);
    creer_cellules(grid, &feuille_globale);
    
    // Afficher tout
    gtk_widget_show_all(window);
    
    printf("Interface GTK+ prête. Fenêtre affichée.\n");
    
    // Lancer la boucle principale GTK
    gtk_main();
    
    return 0;
}