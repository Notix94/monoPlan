// src/formule.c
#include "../include/formule.h"
#include "../include/token.h"
#include "../include/liste.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CELL_LENGTH 256

/* opérateurs implémentés comme fonctions agissant sur la pile */
void op_add(my_stack_t *stack){
    double b = STACK_POP(stack,double);
    double a = STACK_POP(stack,double);
    STACK_PUSH(stack,a+b,double);
}
void op_sub(my_stack_t *stack){
    double b = STACK_POP(stack,double);
    double a = STACK_POP(stack,double);
    STACK_PUSH(stack,a-b,double);
}
void op_mul(my_stack_t *stack){
    double b = STACK_POP(stack,double);
    double a = STACK_POP(stack,double);
    STACK_PUSH(stack,a*b,double);
}
void op_div(my_stack_t *stack){
    double b = STACK_POP(stack,double);
    double a = STACK_POP(stack,double);
    STACK_PUSH(stack,(b!=0)? a/b : 0.0,double);
}

int parse_formule(s_cell *cell, s_feuille *feuille){
    if(!cell || !feuille) return -1;

    clear_tokens(cell); // vide les anciens jetons
    char *s = cell->t;

    if(!s || s[0] != '='){
        // vérifier si c'est un nombre complet
        char *endptr = NULL;
        double val = strtod(s, &endptr);
        if(endptr != s && *endptr == '\0'){
            cell->value = val;
            return 0;
        }
        // sinon texte (pas d'erreur)
        printf("Info : cellule contient du texte ('%s'), valeur = 0.0\n", s ? s : "");
        cell->value = 0.0;
        return 0;
    }

    s++; // skip '='

    // Lecture de la référence (ex: A1 ou AA12)
    char ref_str[32] = {0};
    int i = 0;
    while(s[i] && isalpha((unsigned char)s[i]) && i < (int)sizeof(ref_str)-1){
        ref_str[i] = s[i];
        i++;
    }
    // lire chiffres
    int j = 0;
    char rowbuf[16] = {0};
    while(s[i] && isdigit((unsigned char)s[i]) && j < (int)sizeof(rowbuf)-1){
        rowbuf[j++] = s[i++];
    }
    ref_str[i] = '\0';

    if(ref_str[0] == '\0' || rowbuf[0] == '\0'){
        printf("Erreur: référence vide ou mal formée\n");
        cell->value = 0.0;
        return 0;
    }

    // calcul index colonne (supporte AA, AB...)
    int col = 0;
    for(int k = 0; ref_str[k]; ++k){
        col = col * 26 + (toupper((unsigned char)ref_str[k]) - 'A' + 1);
    }
    col -= 1; // 0-based
    int row = atoi(rowbuf) - 1;

    if(row < 0 || row >= feuille->lignes || col < 0 || col >= feuille->colonnes){
        printf("Erreur: référence hors limites %s%s\n", ref_str, rowbuf);
        cell->value = 0.0;
        return 0;
    }

    s_cell *refCell = feuille->tab[row][col];

    /* Initialiser la liste de tokens si nécessaire (head pointer) */
    cell->tokens = list_create(); // retourne node_t* (NULL ou head). adapte selon ton impl
    if(!cell->tokens) {
        // si list_create retourne NULL pour liste vide, on laisse NULL et on utilisera list_append which should handle it
        cell->tokens = NULL;
    }

    /* Jeton REF : on stocke le pointeur vers la cellule référencée (peut être NULL) */
    s_token *tok_ref = malloc(sizeof(s_token));
    if(!tok_ref) return -1;
    tok_ref->type = REF;
    tok_ref->value.ref = refCell;
    cell->tokens = list_append(cell->tokens, tok_ref);

    /* skip whitespace */
    while(s[i] && isspace((unsigned char)s[i])) i++;

    /* opérateur attendu */
    char op = '\0';
    if(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/'){
        op = s[i++];
    }

    while(s[i] && isspace((unsigned char)s[i])) i++;

    if(op != '\0' && s[i]){
        /* valeur constante après l'opérateur */
        double val = atof(s + i);

        s_token *tok_val = malloc(sizeof(s_token));
        if(!tok_val) return -1;
        tok_val->type = VALUE;
        tok_val->value.cst = val;
        cell->tokens = list_append(cell->tokens, tok_val);

        s_token *tok_op = malloc(sizeof(s_token));
        if(!tok_op) return -1;
        tok_op->type = OPERATOR;
        switch(op){
            case '+': tok_op->value.operator = op_add; break;
            case '-': tok_op->value.operator = op_sub; break;
            case '*': tok_op->value.operator = op_mul; break;
            case '/': tok_op->value.operator = op_div; break;
            default: tok_op->value.operator = NULL; break;
        }
        cell->tokens = list_append(cell->tokens, tok_op);
    }

    /* On évalue la cellule immédiatement (optionnel) */
    return eval_cell(cell, feuille);
}

double eval_cell(s_cell *cell, s_feuille *feuille){
    if(!cell || !feuille) return 0.0;

    /* Si pas de tokens -> soit valeur déjà calculée (nombre) soit texte */
    if(cell->tokens == NULL){
        return cell->value;
    }

    my_stack_t *stack = STACK_CREATE(32, double); // taille configurable
    node_t *node = cell->tokens;
    while(node){
        s_token *t = (s_token*) node->data;
        if(!t){
            node = node->next;
            continue;
        }
        switch(t->type){
            case VALUE:
                STACK_PUSH(stack, t->value.cst, double);
                break;
            case REF: {
                double v = 0.0;
                if(t->value.ref) v = eval_cell(t->value.ref, feuille);
                STACK_PUSH(stack, v, double);
                break;
            }
            case OPERATOR:
                if(t->value.operator) t->value.operator(stack);
                break;
        }
        node = node->next;
    }

    cell->value = STACK_POP(stack, double);
    STACK_REMOVE(stack);
    return cell->value;
}
