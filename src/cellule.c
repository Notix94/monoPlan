#include "../include/cellule.h"
#include "../include/formule.h"
#include "../include/feuille.h"
s_cell *init_cell(){

    s_cell *c = malloc(sizeof(s_cell));
    if(!c) return NULL;
    c->t[0] = '\0';
    c->value = 0.0;
    c->tokens = NULL;
    c->cells = NULL;
    return c;
}

void cell_setStr(s_cell *c, const char *t, s_feuille *f){
    // 1. copier le texte
    strcpy(c->t, t);


    // 2. supprimer anciens tokens
    clear_tokens(c);

    // 3. analyser la formule
    parse_formule(c,f);   // construit c->tokens


}
