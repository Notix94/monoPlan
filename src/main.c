#include "../include/liste.h"
#include <stdio.h>

void printInt(void *ptr){
    int * ptrInt=(int*) ptr;
    printf("%d", *ptrInt);
    printf("\n");
}
int main(){
 // Créer une liste vide
    node_t *l = list_create();

    // Ajouter des éléments en tête
    int a = 1, b = 2, c = 3, d = 4;
    l = list_insert(l, &a);
    l = list_insert(l, &b);
    l = list_insert(l, &c);  // liste: 3 -> 2 -> 1
    printf("Liste après insert en tête: ");
    list_print(l, printInt);
    printf("\n");

    //  Ajouter un élément en queue
    l = list_append(l, &d); // liste: 3 -> 2 -> 1 -> 4
    printf("Liste après append en queue: ");
    list_print(l, printInt);
    printf("\n");

    // Tester list_remove (supprimer le milieu)
    l = list_remove(l, &b); // supprime 2, liste: 3 -> 1 -> 4
    printf("Liste après remove b: ");
    list_print(l, printInt);
    printf("\n");

    // Supprimer la tête
    l = list_headRemove(l); // supprime 3, liste: 1 -> 4
    printf("Liste après headRemove: ");
    list_print(l, printInt);
    printf("\n");

    //  Tester list_getData et list_setData
    printf("Valeur du premier noeud: %d \n ", *(int*)list_get_data(l)); // affiche 1 );
    
 

    int newVal = 99;
    list_set_data(l, &newVal); // change 1 en 99
    printf("Liste après setData: ");
    list_print(l, printInt);
    printf("\n");

    //  Parcourir avec list_next
    printf("Parcours avec list_next: ");
    node_t *tmp = l;
    while(tmp != NULL) {
        printInt(tmp->data);
        tmp = list_next(tmp);
    }
    printf("\n");

    //  Supprimer tous les noeuds
    while(l != NULL) {
        l = list_headRemove(l);
    }
    printf("Liste après suppression complète: ");
    list_print(l, printInt);
    printf("\n");

    list_destroy(l);
    printf("\n");

}
