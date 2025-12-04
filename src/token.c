#include "../include/token.h"

//liberer token
//token avec ref si b2 modif depend plus de A1
void clear_tokens(s_cell *c){
    if(!c) return;
    
    // Libérer les tokens
    if(c->tokens) {
        node_t *actuel = c->tokens;
        while(actuel) {
            s_token *t = list_get_data(actuel);
            
            // Retirer 'c' de la liste des dépendants de la cellule référencée
            if(t->type == REF && t->value.ref) {
                t->value.ref->cells = list_remove(t->value.ref->cells, c);
            }
            
            free(t);
            actuel = list_next(actuel);
        }
        list_destroy(c->tokens);
        c->tokens = NULL;
    }
}