
#include "../include/formule.h"
#define MAX_CELL_LENGTH 256


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

//analyser la formule
int parse_formule(s_cell *cell, s_feuille *f){
    clear_tokens(cell);

    if(cell->t[0] != '='){   // nombre ou texte
        char *end;
        double val = strtod(cell->t,&end); // end pointe premier cara non convertible

        if(*end=='\0'){ //si tout chaine de cell a ete convert alors..
            cell->value=val; 
            return 0; 
        }

        printf("[INFO] Texte détecté → valeur=0\n");
        cell->value=0;
       
            //recalculer les dépendants
            // recalculate_dependents(cell, f);

        return 0;
    }
    
    //== formule 
   tokenCreate(cell,f);

    cell->value = eval_cell(cell,f);
    //recalculer les dépendants après calcul de la formule
    // recalculate_dependents(cell, f);
    return 0;
}


//cree token, stock dans tok[] de cell
//
int tokenCreate(s_cell *cell, s_feuille *f){
     //tab des tokens
    char *expr=cell->t;
    if(expr[0] == '=') expr++; // ignore le '='
    char *tok=strtok(expr," \t");//separe en token chaque mot [B22,1,5,+]

    while(tok){
        s_token *t = malloc(sizeof(s_token));

        if(isdigit(tok[0])){             // valeur
            t->type=VALUE;
            t->value.cst=atof(tok);//tok.val en float
        }
        else if(isalpha(tok[0])){        // référence EX: A12
          int col = 0, row = 0,  i = 0;

        // Calculer la colonne (lettres)
        while (isalpha(tok[i])) {
            char letter = tok[i];         
            int value = letter - 'A' + 1; // A=1, B=2, ..., Z=26
            col = col * 26 + value;        // conversion en base 26
            i++;                           // passer au caractère suivant
        }

        row=atoi(tok+i);// atoi prend la partie restante de la chaîne
        // VÉRIFICATION DES LIMITES
        if(row < 1 || row > f->lignes || col < 1 || col > f->colonnes) {
            printf("[ERREUR] Référence %s hors limites (row=%d, col=%d)\n", tok, row, col);
            free(t);
            tok = strtok(NULL, " \t"); // passer au token suivant
            continue;  // sauter ce token invalide
        }

        
        //sinon c'est une ref d'une cell
        t->type=REF;

        s_cell *ref_cell = f->tab[row-1][col-1];//recup pos de la ref

        // Si la cellule n'existe pas, l'initialiser
        if(ref_cell == NULL) {
        ref_cell = init_cell();
        f->tab[row-1][col-1] = ref_cell;//on place la cell dans la f
        printf("[INFO] Cellule %s (row=%d, col=%d) n'existait pas → initialisée à 0\n", tok, row, col);
        }

        t->value.ref = ref_cell;

        // Enregistrer que 'cell' dépend de 'ref_cell' //B depend de A
        ref_cell->cells = list_append(ref_cell->cells, cell);
        cell->preds=list_append(cell->preds,ref_cell);
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
    return 0;  
}


//calculer la valeur finale d’une cellule
double eval_cell(s_cell *cell, s_feuille *feuille){
    // Si pas de tokens, c'est une valeur simple = retourner directement
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
