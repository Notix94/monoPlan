#include "../include/liste.h"
// node_t *head = NULL;

node_t *list_create(void){
    return NULL;  // la liste est vide, head = NULL
}
node_t *list_next(node_t *node){
    if(node == NULL) return NULL;//pas de de prochain
    return node->next;
}

void *list_get_data(const node_t * node){
    if(node==NULL) return NULL;
    return node->data;
}


void list_print(node_t * head, void (*fct) (void*)){
    node_t *ptr = head;
    while(ptr){
        (*fct) (list_get_data(ptr));
        ptr =list_next(ptr);
    }
}


node_t *list_insert(node_t *head,void *data){
    node_t *n1 = malloc(sizeof(node_t));
    if(!n1) return head; // échec allocation
    n1->data = data;    
    n1->next = head; 
    head = n1;
    return head;
};

node_t * list_headRemove(node_t * head){
    if(head==NULL)return NULL;
    //surpimme la tete de list
    node_t *temp=head;
    head = head->next;
    free(temp);
    //retourne la nouvelle tete
    return head;
}