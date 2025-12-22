#ifndef _FORMULE_H_
#define _FORMULE_H_

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "feuille.h" 
#include "token.h"
#include "stack.h"
#include "cellule.h"
typedef struct cell s_cell;
typedef struct feuille s_feuille;
// Analyse la chaîne de la cellule et construit les tokens
int parse_formule(s_cell *cell, s_feuille *feuille);
double eval_cell(s_cell *cell, s_feuille *feuille);
int tokenCreate(s_cell *cell, s_feuille *f);
#endif 