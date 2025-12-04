#include "../include/formule.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CELL_LENGTH 256

int parse_formule(s_cell *cell, s_feuille *feuille){
 char *s = cell->t;

if(s[0] != '='){
    //verif si c'est un nombre
    int isNumber = 1;
    int i = 0;
    //si nbr negatif
    if(s[0] == '-' && isdigit(s[1])){
        i = 1;
    }
    //parcourt le tableau
    for(; s[i]!='\0'; i++){
        //si autre chose que chiffre et point
        if (!isdigit(s[i]) && s[i] != '.') {
            isNumber = 0;
            break;
        }
    }
    if(isNumber){
        cell->value =atof(s);//convert chaine en double
        return 0;
    }
    // sinon c'est juste du texte
   printf("Info : cellule contient du texte ('%s'), valeur = 0.0\n \n", s);          // pas numérique
    return 0;
}
return eval_cell(cell,feuille);

}
double eval_cell(s_cell *cell, s_feuille *feuille) {
    if (!cell || !feuille) return 0;

    char *s = cell->t;

    if (!s || s[0] != '=') {
        cell->value = atof(s); // pas une formule
        return cell->value;
    }

    s++; // skip '='

    // 1) lecture de la référence (ex: A1)
    char ref_str[16] = {0};
    int i = 0;
    while (isalnum((unsigned char)s[i]) && i < 15) {
        ref_str[i] = s[i];
        i++;
    }
    ref_str[i] = '\0';

    if (ref_str[0] == '\0') {
        printf("Erreur: référence vide\n");
        cell->value = 0;
        return 0;
    }

    // calcul index ligne/colonne
    int col = toupper(ref_str[0]) - 'A';
    int row = atoi(ref_str + 1) - 1;

    if (row < 0 || row >= feuille->lignes || col < 0 || col >= feuille->colonnes) {
        printf("Erreur: référence hors limites %s\n", ref_str);
        cell->value = 0;
        return 0;
    }

    // récupère la cellule référencée
    s_cell *refCell = feuille->tab[row][col];
    double base_val = (refCell) ? eval_cell(refCell, feuille) : 0;

    // 2) création pile et empilement de la valeur de la référence
    my_stack_t *stack = STACK_CREATE(10, double);
    STACK_PUSH(stack, base_val, double);

    // 3) lecture de l'opérateur et de la valeur
    char op = '\0';
    while (s[i] && isspace((unsigned char)s[i])) i++;
    if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
        op = s[i++];
    }

    while (s[i] && isspace((unsigned char)s[i])) i++;

    double val = 0;
    if (op && s[i]) {
        val = atof(s + i);
        STACK_PUSH(stack, val, double);
    }

    // 4) dépile et calcule
    double b = STACK_POP(stack, double);
    double a = STACK_POP(stack, double);
    double result = 0;

    switch (op) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/': result = (b != 0) ? a / b : 0; break;
        default: result = a; break;
    }

    cell->value = result;
    STACK_REMOVE(stack);
    return result;
}
