#ifndef _TOKEN_H_
#define _TOKEN_H_

#include "liste.h"
#include "cellule.h"
typedef struct cell s_cell;  //pour compil

typedef struct token{
    enum{VALUE,REF,OPERATOR} type;
    union{
        double cst; //==value
        s_cell * ref; //==ref
        void(*operator)(my_stack_t * eval); //==operator
    }value;

}s_token;

void clear_tokens(s_cell *c);
#endif 