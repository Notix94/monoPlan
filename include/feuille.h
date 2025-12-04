
#ifndef _FEUILLE_H_
#define _FEUILLE_H_

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "token.h"
#include "cellule.h"
#define MAX_FEUILLE_LENGTH 256
#define NBLIG 26
#define NBCOL 50

typedef struct feuille{
    char nom [MAX_FEUILLE_LENGTH];
    int lignes;
    int colonnes;
    s_cell *tab[NBLIG][NBCOL] ;

}s_feuille;

void init_feuille(s_feuille *f, char *nom, int lignes, int colonnes);
void feuille_setCell(s_feuille *f,s_cell *c, char *pos);
#endif 