#include "../include/liste.h"
#include "../include/feuille.h"
#include "../include/cellule.h"
#include "../include/formule.h"
#include <stdio.h>

void printInt(void *ptr){
    int * ptrInt=(int*) ptr;
    printf("%d", *ptrInt);
    printf("\n");
}
int main(){
//  // Créer une liste vide
//     node_t *l = list_create();

//     // Ajouter des éléments en tête
//     int a = 1, b = 2, c = 3, d = 4;
//     l = list_insert(l, &a);
//     l = list_insert(l, &b);
//     l = list_insert(l, &c);  // liste: 3 -> 2 -> 1
//     printf("Liste après insert en tête: ");
//     list_print(l, printInt);
//     printf("\n");

//     //  Ajouter un élément en queue
//     l = list_append(l, &d); // liste: 3 -> 2 -> 1 -> 4
//     printf("Liste après append en queue: ");
//     list_print(l, printInt);
//     printf("\n");

//     // Tester list_remove (supprimer le milieu)
//     l = list_remove(l, &b); // supprime 2, liste: 3 -> 1 -> 4
//     printf("Liste après remove b: ");
//     list_print(l, printInt);
//     printf("\n");

//     // Supprimer la tête
//     l = list_headRemove(l); // supprime 3, liste: 1 -> 4
//     printf("Liste après headRemove: ");
//     list_print(l, printInt);
//     printf("\n");

//     //  Tester list_getData et list_setData

//     printf("Valeur du premier noeud: %d \n ", *(int*)list_get_data(l)); // affiche 1 );
    
 


//     int newVal = 99;
//     list_set_data(l, &newVal); // change 1 en 99
//     printf("Liste après setData: ");
//     list_print(l, printInt);
//     printf("\n");

//     //  Parcourir avec list_next
//     printf("Parcours avec list_next: ");
//     node_t *tmp = l;
//     while(tmp != NULL) {
//         printInt(tmp->data);
//         tmp = list_next(tmp);
//     }
//     printf("\n");

//     //  Supprimer tous les noeuds
//     while(l != NULL) {
//         l = list_headRemove(l);
//     }
//     printf("Liste après suppression complète: ");
//     list_print(l, printInt);
//     printf("\n");

//     list_destroy(l);
//     printf("\n");
  printf("=== Initialisation de la feuille ===\n");
    s_feuille f;
    init_feuille(&f, "Test", 26, 26);
    printf("Feuille initialisée : %s, %d lignes x %d colonnes\n\n",
           f.nom, f.lignes, f.colonnes);

    // --- Test 1 : cellule avec valeur simple ---
    printf("=== Test 1 : cellule A1 avec valeur simple ===\n");
    s_cell *A1 = init_cell();
    cell_setStr(A1, "10", &f);
    feuille_setCell(&f, A1, "A1");
    printf("A1 = %.2f (attendu: 10.0)\n\n", A1->value);

    printf("=== Test 1-- echec : cellule A1 avec valeur simple ===\n");
    s_cell *A2 = init_cell();
    cell_setStr(A2, "10dcdsb", &f);
    feuille_setCell(&f, A2, "A2");
 

    
    // --- Test 2 : cellule avec formule valide ---
    printf("=== Test 2 : cellule B2 avec formule '=A1+5' ===\n");
    s_cell *B2 = init_cell();
    cell_setStr(B2, "=A1+5", &f);
    feuille_setCell(&f, B2, "B2");
    printf("B2 = %.2f (attendu: 15.0)\n\n", B2->value);

    // --- Test 3 : cellule avec référence vide ---
    printf("=== Test 3 : cellule D4 avec référence vide '=' ===\n");
    s_cell *D4 = init_cell();
    cell_setStr(D4, "=", &f);
    feuille_setCell(&f, D4, "D4");
    printf("D4 = %.2f (attendu: 0.0, erreur: référence vide)\n\n", D4->value);

    // --- Test 4 : cellule avec texte ---
    printf("=== Test 4 : cellule F6 avec texte 'Hello' ===\n");
    s_cell *F6 = init_cell();
    cell_setStr(F6, "Hello", &f);
    feuille_setCell(&f, F6, "F6");
    

    // --- Test 5 : cellule avec formule utilisant une cellule non existante ---
    printf("=== Test 5 : cellule E5 avec formule '=Z1+3' ===\n");
    s_cell *E5 = init_cell();
    cell_setStr(E5, "=Z1+3", &f);
    feuille_setCell(&f, E5, "E5");
    printf("E5 = %.2f (attendu: 3.0 si Z1 vide, message d'erreur attendu)\n\n", E5->value);

    
}
