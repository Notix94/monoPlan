ajout, apres rendu final
Jalon 3:
-ajout tableau predecesseurs cellule.h
- initialisation de preds[] dans init_cell cellule.c
- ajout func recalc_dependents permettant le recalcul si un predecesseurs a sa value modif et appeler dans cell_set cellule.c
- collect_all_preds permet de recup les predecesseurs d'une cellule et les placer dans le tab preds cellule.c

  cell->preds=list_append(cell->preds,ref_cell); dans token create appeler dans parse formule (formule.c)