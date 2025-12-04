
#ifndef _CELL_H_
#define _CELL_H_
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stack.h"
#include "token.h"
#define MAX_CELL_LENGTH 256
typedef struct cell s_cell;   // forward declaration si besoin
typedef struct feuille s_feuille;  // <<-- ici, permet d'utiliser s_feuille* sans inclure feuille.h
typedef struct cell{
    char t [MAX_CELL_LENGTH]; //champ cell
    double value; //0.0 si pas calculable
    
    node_t * tokens;
    node_t * cells;
    
}s_cell;
s_cell *init_cell();
void cell_setStr(s_cell *c, const char *t, s_feuille *f);

#endif 