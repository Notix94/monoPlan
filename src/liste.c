#include "../include/liste.h"
// node_t *head = NULL;

node_t *list_create(void){
    return NULL;  // la liste est vide, head = NULL
}
//prochain noeud
node_t *list_next(node_t *node){
    if(node == NULL) return NULL;//pas de de prochain
    return node->next;
}
//return noeud du params
void *list_get_data(const node_t * node){
    if(node==NULL) {
        return NULL;
   }
   
    return node->data;
}

//modif le noeud du params
void list_set_data(node_t * node, void * data){

 if (node != NULL) {
        node->data = data;
    }
}
//print list
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

//ajt noeud fin de list && return tete 
node_t * list_append(node_t * head, void * data){
    node_t *n1 = malloc(sizeof(node_t));
    if(!n1) return head; //creat fail

    n1->data = data;
    n1->next = NULL; 

    if (head == NULL)//si la liste est empty
        return n1;

    node_t *tmp = head; 
    while(tmp->next !=NULL){//va jusqu'a la fin ou next == null
        tmp = tmp->next;
    }
    tmp->next = n1;////n1 placé a la fin
    return head;
}

//sup premiere instance qui a la value data
//return head
node_t * list_remove(node_t * head, void *data){
    node_t *tmp =head;
    node_t *prev; // previus

    //si head->data == data
if(tmp != NULL &&tmp->data == data){
    head = tmp->next;
    free(tmp);
    return head;
}
//compare jusqu a la queu si n->data == data
while(tmp!=NULL && tmp->data !=data){
    prev = tmp;//avance previus
    tmp = tmp->next;//tmp == proch noeud a compar
}
//si tmp arrive a la fin sans trv data
if(tmp==NULL){
    return head;
}
prev->next = tmp->next;//on relie le prev (1) au next (3)
free(tmp); 
return head;
}

node_t * list_headRemove(node_t * head){
    if(head==NULL)return NULL;
    //surpimme la tete de list
    node_t *temp=head;
    head = head->next; // le node 2 devient head
    free(temp);
    //retourne la nouvelle tete
    return head;

}

 void list_destroy(node_t * head){
	if(head==NULL)return;
 // destruction d’une liste
	node_t *temp=head;
	while(temp!=NULL){//parcourt Chaine
		node_t *next=temp->next; //save le next
		free(temp);//free la memory pointee
		temp=next; // pointe proch noeud
	}
}
int list_contains(node_t *head, void *data) {
    node_t *n = head;

    while(n) {
        if(list_get_data(n) == data) {
            return 1; // trouvé
        }
        n = list_next(n);
    }
    return 0; // pas trouvé
}