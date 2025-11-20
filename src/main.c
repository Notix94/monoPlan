#include "../include/liste.h"
#include <stdio.h>

void printInt(void *ptr){
    int * ptrInt=(int*) ptr;
    printf("%d", *ptrInt);
}
int main(){
    node_t *l = list_create();
    int a = 1, b = 0;
    l= list_insert(l,&a);
    l=list_insert(l, &b);
    list_print(l,&printInt);
    printf("\n");

    l=list_headRemove(l);
    list_print(l,&printInt);
    printf("\n");
}
