#ifndef _FORMULE_H_
#define _FORMULE_H_

#include "feuille.h" 
#include "token.h"
#include "stack.h"
#include "cellule.h"
// Analyse la chaîne de la cellule et construit les tokens
int parse_formule(s_cell *cell, s_feuille *feuille);
double eval_cell(s_cell *cell, s_feuille *feuille);
#endif 