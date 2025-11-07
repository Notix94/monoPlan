#include "../include/liste.h"
// node_t *head = NULL;
void list_print(node_t * head, void (*fct) (void*));
node_t *list_create(void){
    return NULL;  // la liste est vide, head = NULL
}
node_t *list_insert(node_t *head,void *data){
    node_t *n1 = malloc(sizeof(node_t));
    if(!n1) return head; // échec allocation
    n1->data = data;    
    n1->next = head; 
    head = n1;
    return head;
};