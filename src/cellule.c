#include "../include/cellule.h"

s_cell *init_cell(){

    s_cell *c = malloc(sizeof(s_cell));
    if(!c) return NULL;
    c->t[0] = '\0';
    c->value = 0.0;
    c->tokens = NULL;
    c->cells = NULL;
    c->preds = NULL;
  
    return c;
}
void recalc_dependents(s_cell *cell, s_feuille *f) {
    if (!cell || !cell->cells) return;

    node_t *n = cell->cells;
    while (n) {
        s_cell *succ = list_get_data(n);

        // Recalculer la valeur du successeur
        succ->value = eval_cell(succ, f);
        printf("[RECALC] %s → %.2f\n", succ->t, succ->value);

        // Recalculer récursivement ses propres successeurs
        recalc_dependents(succ, f);

        n = list_next(n);
    }
}
// assigner une chaine a la cellule et analyser la formule
void cell_setStr(s_cell *c, const char *t, s_feuille *f){
    // 1. copier le texte
    strcpy(c->t, t);


    // 2. supprimer anciens tokens
    clear_tokens(c);

    // 3. analyser la formule
    parse_formule(c,f);   // construit c->tokens
    recalc_dependents(c, f);

}


void collect_all_preds(s_cell *cell, node_t **visited) {

    node_t *n = cell->preds;

    while(n) {
        s_cell *p = list_get_data(n);

        // si déjà vu alors skip
        if(list_contains(*visited, p)) {
            n = list_next(n);
            continue;
        }

        // ajouter p à visited
        *visited = list_append(*visited, p);

        // descendre dans les preds de p
        collect_all_preds(p, visited);

        n = list_next(n);
    }
}
