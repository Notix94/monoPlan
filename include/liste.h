
#ifndef _LISTE_H_
#define _LISTE_H_
#include "stdio.h"
typedef struct node{
    void *data;//pointeur vers les données(int char...)
    struct node *next;//vers prochain node
}node_t;
void list_print(node_t * head, void (*fct) (void*));
node_t *list_create(void);
node_t *list_insert(node_t *head,void *data);


#endif