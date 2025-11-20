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
void list_set_data(node_t * node, void * data){

 if (node != NULL) {
        node->data = data;
    }
}

void list_print(node_t * head, void (*fct) (void*)){
    printf("\n");
    node_t *ptr = head;
    while(ptr){
        (*fct) (list_get_data(ptr));
        ptr =list_next(ptr);
    }
}

//cree et insert nouv node en tete
node_t *list_insert(node_t *head,void *data){
    node_t *n1 = malloc(sizeof(node_t));
    if(!n1) return head; // échec allocation
    n1->data = data;    
    n1->next = head; 
    head = n1;
    return head;
};


node_t * list_append(node_t * head, void * data){
    node_t *n1 = malloc(sizeof(node_t));
    if(!n1) return head;

    n1->data = data;
    n1->next = NULL;

    if (head == NULL)//si la liste est empty
        return n1;

    node_t *tmp = head;
    while(tmp->next !=NULL){
        tmp = tmp->next;
    }
    tmp->next = n1;
    return head;
}
//sup premiere instance qui a la value data
//return head
node_t * list_remove(node_t * head, void *data){
    node_t *tmp =head;
    node_t *prev;
    //si head->data == data
if(tmp != NULL &&tmp->data == data){
head = tmp->next;
free(tmp);
return head;
}
while(tmp!=NULL && tmp->data !=data){
    prev = tmp;
    tmp = tmp->next;//tmp == node a supr
}
//si tmp arrive a la fin sans trv data
if(tmp==NULL){
    return head;
}
prev->next = tmp->next;
free(tmp);
return head;
}
node_t * list_headRemove(node_t * head){
    if(head==NULL)return NULL;
    //surpimme la tete de list
    node_t *temp=head;
    head = head->next;
    free(temp);
    //retourne la nouvelle tete
    return head;

}