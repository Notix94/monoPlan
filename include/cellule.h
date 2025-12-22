
#ifndef _CELL_H_
#define _CELL_H_
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stack.h"
#include "token.h"
#include "feuille.h"
#include "formule.h"

#define MAX_CELL_LENGTH 256

typedef struct feuille s_feuille;  // pour connaitre node a la compil
typedef struct cell{
    char t [MAX_CELL_LENGTH]; //champ cell
    double value; //0.0 si pas calculable
    node_t *preds;            // liste des prédécesseurs 
    node_t * tokens;
    node_t * cells; //dependts

    
}s_cell;
s_cell *init_cell();
void cell_setStr(s_cell *c, const char *t, s_feuille *f);
void collect_all_preds(s_cell *c, node_t **acc);
void recalc_dependents(s_cell *cell, s_feuille *f);
#endif 