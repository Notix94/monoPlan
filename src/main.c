#include "../include/liste.h"
#include <stdio.h>

void printInt(void *ptr){
    int * ptrInt=(int*) ptr;
    printf("%d", *ptrInt);
}
int main(){

    // node_t *l = list_create();
    // int a = 0,  b = 1, c = 2 ,d =3 ;
    // l= list_insert(l,&a);
    // l=list_insert(l, &b);
    // l=list_insert(l, &c);
    // l=list_insert(l, &d);
    // list_print(l,&printInt);
    // list_remove(l, &b);
    //  list_print(l,&printInt);

//      node_t *l = NULL;
//      int x = 42;  
// l = list_remove(l, &x);  // doit juste retourner NULL sans crash
// list_print(l,&printInt);

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
