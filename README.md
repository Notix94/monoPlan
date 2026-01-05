ajout, apres rendu final
Jalon 3:
-ajout tableau predecesseurs cellule.h
- initialisation de preds[] dans init_cell cellule.c
- ajout func recalc_dependents permettant le recalcul si un predecesseurs a sa value modif et appeler dans cell_set cellule.c
- collect_all_preds permet de recup les predecesseurs d'une cellule et les placer dans le tab preds cellule.c

  cell->preds=list_append(cell->preds,ref_cell); dans token create appeler dans parse formule (formule.c)





Jalon 4:
-modification du make pour compiler et executer le GTK
-creation fichier bind.h
avec definition de la structure s_bind
  position de la cellule dans la feuille 
  pointeur vers le widget GTK
  pointeur vers le modele interne de la cellule

declaration du tableau global
  stoke toute les association de widget - cellule

declaration fonction de recherche 
  bindLookupByCell() trouve le widget associé à une cellule
  bindLookupByPos() trouve la liaison par coordonnées (colonne, ligne)

Déclaration des fonctions d'interface 
  creer_cellules() crée la grille de 26×50 cellules
  update_cell_display() met à jour l'affichage d'une cellule
  update_dependents_display() met à jour l'affichage des dépendants
  callback_validation() gère la validation d'une cellule (touche Entrée)
  callback_focus_in() gère le focus sur une cellule

-creation bind.c
Implémentation du tableau global liaisons
Initialisation à NULL
Implémentation de bindLookupByCell(s_cell *cell)
Parcourt le tableau liaisons pour trouver la liaison correspondante
Retourne NULL si non trouvée
Implémentation de bindLookupByPos(int colonne, int ligne)
Implémentation de update_cell_display(s_bind *bind)
  Affiche la valeur calculée si formule (commence par '=')
  Affiche le contenu brut sinon

Implémentation de update_dependents_display(s_cell *cell)
Implémentation de callback_validation(GtkEntry *entry, gpointer user_data)
Appelle cell_setStr() pour mettre à jour le modèle
Implémentation de callback_focus_in(GtkWidget *widget, ...)
  Affiche la formule brute dans la barre de formule en haut
  Affiche la formule dans la cellule elle-même (pas la valeur calculée)

Implémentation de creer_cellules(GtkWidget *grid, s_feuille *feuille)

-Création main_gtk.c

Déclaration de la variable globale s_feuille feuille_globale
  Accessible depuis bind.c via extern

Implémentation de on_menu_quitter_activate()
  Callback pour quitter l'application (menu Fichier → Quitter)
  Appelle gtk_main_quit()

Implémentation de on_menu_apropos_activate()
  Callback pour afficher la boîte "À propos" (menu Aide → À propos)
  Affiche un message d'information avec instructions d'utilisation

Implémentation de main(int argc, char *argv[])
  Crée la fenêtre principale (GtkWindow) 1200×700 pixels
  Crée une boîte verticale (GtkBox) pour organiser les éléments
  Crée la barre de menu 
    Menu "Fichier" avec "Quitter"
    Menu "Aide" avec "À propos"

Crée la barre de formule 
  Label "Formule:"
  GtkEntry non éditable pour afficher la formule de la cellule sélectionnée

Crée la zone de cellules 
  GtkScrolledWindow pour permettre le défilement
  GtkGrid pour organiser les cellules en grille
  Appelle creer_cellules() pour générer toutes les cellules

Affiche la fenêtre avec gtk_widget_show_all()
