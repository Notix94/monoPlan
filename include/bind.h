#ifndef _BIND_H_
#define _BIND_H_

#include <gtk/gtk.h>
#include "cellule.h"
#include "feuille.h"

// Structure de liaison entre widget GTK et modèle de cellule
typedef struct bind {
    int ligne, colonne;           // Position dans la feuille
    GtkWidget *case_widget;       // Widget GTK (GtkEntry)
    s_cell *cell;                 // Modèle interne de la cellule
} s_bind;

// Tableau global des liaisons [colonne][ligne]
extern s_bind *liaisons[NBCOL][NBLIG];

// Variable globale pour la barre de formule
extern GtkWidget *entry_formule_global;

// Fonctions de recherche de liaison
s_bind *bindLookupByCell(s_cell *cell);
s_bind *bindLookupByPos(int colonne, int ligne);

// Fonction de création des cellules
void creer_cellules(GtkWidget *grid, s_feuille *feuille);

// Fonctions de mise à jour de l'affichage
void update_cell_display(s_bind *bind);
void update_dependents_display(s_cell *cell);

// Callbacks
void callback_validation(GtkEntry *entry, gpointer user_data);
gboolean callback_focus_in(GtkWidget *widget, GdkEventFocus *event, gpointer user_data);

#endif