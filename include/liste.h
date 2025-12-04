
#ifndef _LISTE_H_
#define _LISTE_H_
#include "stdio.h"
#include "stdlib.h"
typedef struct node {
    void *data;//pointeur vers les données(int char...)
    struct node *next;//vers prochain node
}node_t;
void list_print(node_t * head, void (*fct) (void*));
node_t *list_create(void);
node_t *list_insert(node_t *head,void *data);
node_t *list_next(node_t *head);
void *list_get_data(const node_t * node);
void list_set_data(node_t * node, void * data);
node_t * list_append(node_t * head, void * data);
node_t * list_remove(node_t * head, void *data);
node_t * list_headRemove(node_t * head);
void list_destroy(node_t * head);

#endif