// src/formule.c
#include "../include/formule.h"
#include "../include/token.h"
#include "../include/liste.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CELL_LENGTH 256

// // Recalcule une cellule et tous ses dépendants récursivement
// void recalculate_dependents(s_cell *cell, s_feuille *feuille) {
//     if(!cell || !cell->cells) return;
    
//     node_t *n = cell->cells;
//     while(n) {
//         s_cell *dependent = list_get_data(n);
        
//         // Recalculer la valeur du dépendant
//         if(dependent->tokens) {  // Si c'est une formule
//             dependent->value = eval_cell(dependent, feuille);
//             printf("[RECALC] Cellule recalculée → valeur=%.2f\n", dependent->value);
            
//             // Recalculer récursivement ses propres dépendants
//             recalculate_dependents(dependent, feuille);
//         }
        
//         n = list_next(n);
//     }
// }

/* opérateurs implémentés comme fonctions agissant sur la pile */
// adition
void op_add(my_stack_t *stack){
    double b = STACK_POP(stack,double);
    double a = STACK_POP(stack,double);
    STACK_PUSH(stack,a+b,double);
}
// soustraction
void op_sub(my_stack_t *stack){
    double b = STACK_POP(stack,double);
    double a = STACK_POP(stack,double);
    STACK_PUSH(stack,a-b,double);
}
// multiplication
void op_mul(my_stack_t *stack){
    double b = STACK_POP(stack,double);
    double a = STACK_POP(stack,double);
    STACK_PUSH(stack,a*b,double);
}
// division
void op_div(my_stack_t *stack){
    double b = STACK_POP(stack,double);
    double a = STACK_POP(stack,double);
    STACK_PUSH(stack,(b!=0)? a/b : 0.0,double);
}


int parse_formule(s_cell *cell, s_feuille *f)
{
    clear_tokens(cell);

    if(cell->t[0] != '='){   // nombre ou texte
        char *end;
        double v = strtod(cell->t,&end);
        if(*end=='\0'){ cell->value=v; return 0; }
        printf("[INFO] Texte détecté → valeur=0\n");
        cell->value=0;
       
            //recalculer les dépendants
            // recalculate_dependents(cell, f);

        return 0;
    }
    char *expr=cell->t+1;
    char *tok=strtok(expr," \t");

    while(tok){
        s_token *t = malloc(sizeof(s_token));

        if(isdigit(tok[0])){             // valeur
            t->type=VALUE;
            t->value.cst=atof(tok);
        }
       else if(isalpha(tok[0])){        // référence EX: A12
            int col=0,row=0,i=0;
            while(isalpha(tok[i])) col=col*26+(tok[i++]&31);
            row=atoi(tok+i);
           // VÉRIFICATION DES LIMITES
    if(row < 1 || row > f->lignes || col < 1 || col > f->colonnes) {
        printf("[ERREUR] Référence %s hors limites (row=%d, col=%d)\n", tok, row, col);
        free(t);
        continue;  // sauter ce token invalide
    }
    
    t->type=REF;
    
            s_cell *ref_cell = f->tab[row-1][col-1];
    
        // Si la cellule n'existe pas, l'initialiser
        if(ref_cell == NULL) {
            ref_cell = init_cell();
            ref_cell->value = 0.0;
            f->tab[row-1][col-1] = ref_cell;
            printf("[INFO] Cellule %s (row=%d, col=%d) n'existait pas → initialisée à 0\n", tok, row, col);
        }
    
            t->value.ref = ref_cell;
    
    // Enregistrer que 'cell' dépend de 'ref_cell'
    ref_cell->cells = list_append(ref_cell->cells, cell);
}
        else{                             // opérateur
            t->type=OPERATOR;
            t->value.operator =
                tok[0]=='+'? op_add :
                tok[0]=='-'? op_sub :
                tok[0]=='*'? op_mul :
                tok[0]=='/'? op_div : NULL;
        }

        cell->tokens = list_append(cell->tokens,t);
        tok=strtok(NULL," \t");
    }

    cell->value = eval_cell(cell,f);
    //recalculer les dépendants après calcul de la formule
    // recalculate_dependents(cell, f);
    return 0;
}



double eval_cell(s_cell *cell, s_feuille *feuille){
    // Si pas de tokens, c'est une valeur simple → retourner directement
    if(!cell->tokens) {
        printf("[DEBUG] Cellule sans tokens, retour valeur directe: %.2f\n", cell->value);
        return cell->value;
    }
    
    my_stack_t *stack = STACK_CREATE(32,double);
    node_t *n = cell->tokens;

    while(n){
        s_token *t = n->data;
        switch(t->type){
            case VALUE:
                STACK_PUSH(stack, t->value.cst, double);
                break;

            case REF:
                STACK_PUSH(stack, eval_cell(t->value.ref, feuille), double);
                break;

            case OPERATOR:
                t->value.operator(stack);
                break;
        }
        n = n->next;
    }

    return STACK_POP(stack,double);
}
