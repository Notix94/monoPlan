#include "../include/token.h"

void clear_tokens(s_cell *c){
    if(c->tokens){
        list_destroy(c->tokens);
        c->tokens = NULL;
    }

}