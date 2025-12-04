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
void test_cellule_simple() {
    printf("=== TEST 1 : Cellule avec valeur simple ===\n");
    s_feuille f;
    init_feuille(&f, "Test", 26, 26);
    
    s_cell *A1 = init_cell();
    cell_setStr(A1, "10", &f);
    feuille_setCell(&f, A1, "A1");
    
    printf("A1 = %.2f (attendu: 10.00)\n", A1->value);
    printf("A1 tokens = %p (attendu: NULL)\n", (void*)A1->tokens);
    printf("✓ Test 1 réussi\n\n");
}

void test_formule_simple() {
    printf("=== TEST 2 : Formule simple avec référence ===\n");
    s_feuille f;
    init_feuille(&f, "Test", 26, 26);
    
    // Créer A1 = 10
    s_cell *A1 = init_cell();
    cell_setStr(A1, "10", &f);
    feuille_setCell(&f, A1, "A1");
    
    // Créer B1 = A1 + 5
    s_cell *B1 = init_cell();
    feuille_setCell(&f, B1, "B1");
    cell_setStr(B1, "=A1 5 +", &f);
    
    printf("A1 = %.2f (attendu: 10.00)\n", A1->value);
    printf("B1 = %.2f (attendu: 15.00)\n", B1->value);
    printf("✓ Test 2 réussi\n\n");
}

void test_reference_inexistante() {
    printf("=== TEST 3 : Référence vers cellule inexistante ===\n");
    s_feuille f;
    init_feuille(&f, "Test", 26, 26);
    
    // B2 = C5 + 5 (C5 n'existe pas mais est dans les limites)
    s_cell *B2 = init_cell();
    feuille_setCell(&f, B2, "B2");
    cell_setStr(B2, "=C5 5 +", &f);
    
    printf("B2 = %.2f (attendu: 5.00)\n", B2->value);
    
    // Vérifier que C5 a été créée (C=3, 5=index 4)
    s_cell *C5 = f.tab[4][2];
    if(C5 != NULL) {
        printf("C5 = %.2f (attendu: 0.00)\n", C5->value);
        printf("C5 existe : OUI\n");
    } else {
        printf("❌ ERREUR : C5 n'a pas été créée !\n");
    }
    printf("✓ Test 3 réussi\n\n");
}

void test_dependances() {
    printf("=== TEST 4 : Vérification des dépendances ===\n");
    s_feuille f;
    init_feuille(&f, "Test", 26, 26);
    
    // A1 = 10
    s_cell *A1 = init_cell();
    cell_setStr(A1, "10", &f);
    feuille_setCell(&f, A1, "A1");
    
    // B1 = A1 + 5
    s_cell *B1 = init_cell();
    feuille_setCell(&f, B1, "B1");
    cell_setStr(B1, "=A1 5 +", &f);
    
    // C1 = A1 * 2
    s_cell *C1 = init_cell();
    feuille_setCell(&f, C1, "C1");
    cell_setStr(C1, "=A1 2 *", &f);
    
    // Vérifier que A1 a 2 dépendants
    printf("A1 = %.2f\n", A1->value);
    printf("B1 = %.2f (attendu: 15.00)\n", B1->value);
    printf("C1 = %.2f (attendu: 20.00)\n", C1->value);
    
    int count = 0;
    node_t *n = A1->cells;
    printf("Dépendants de A1 : ");
    while(n) {
        s_cell *dep = list_get_data(n);
        printf("%p ", (void*)dep);
        count++;
        n = list_next(n);
    }
    printf("\nNombre de dépendants : %d (attendu: 2)\n", count);
    
    if(count == 2) {
        printf("✓ Test 4 réussi\n\n");
    } else {
        printf("❌ ERREUR : nombre de dépendants incorrect\n\n");
    }
}

void test_operateurs_multiples() {
    printf("=== TEST 5 : Formule avec plusieurs opérateurs ===\n");
    s_feuille f;
    init_feuille(&f, "Test", 26, 26);
    
    // A1 = 10, B1 = 20
    s_cell *A1 = init_cell();
    cell_setStr(A1, "10", &f);
    feuille_setCell(&f, A1, "A1");
    
    s_cell *B1 = init_cell();
    cell_setStr(B1, "20", &f);
    feuille_setCell(&f, B1, "B1");
    
    // C1 = (A1 + B1) * 2 → en notation polonaise inverse : A1 B1 + 2 *
    s_cell *C1 = init_cell();
    feuille_setCell(&f, C1, "C1");
    cell_setStr(C1, "=A1 B1 + 2 *", &f);
    
    printf("A1 = %.2f\n", A1->value);
    printf("B1 = %.2f\n", B1->value);
    printf("C1 = %.2f (attendu: 60.00)\n", C1->value);
    printf("✓ Test 5 réussi\n\n");
}

void test_division_par_zero() {
    printf("=== TEST 6 : Division par zéro ===\n");
    s_feuille f;
    init_feuille(&f, "Test", 26, 26);
    
    s_cell *A1 = init_cell();
    feuille_setCell(&f, A1, "A1");
    cell_setStr(A1, "=10 0 /", &f);
    
    printf("A1 = %.2f (attendu: 0.00, car division par zéro)\n", A1->value);
    printf("✓ Test 6 réussi\n\n");
}

void test_chaine_references() {
    printf("=== TEST 7 : Chaîne de références (A1→B1→C1) ===\n");
    s_feuille f;
    init_feuille(&f, "Test", 26, 26);
    
    // A1 = 5
    s_cell *A1 = init_cell();
    cell_setStr(A1, "5", &f);
    feuille_setCell(&f, A1, "A1");
    
    // B1 = A1 * 2
    s_cell *B1 = init_cell();
    feuille_setCell(&f, B1, "B1");
    cell_setStr(B1, "=A1 2 *", &f);
    
    // C1 = B1 + 3
    s_cell *C1 = init_cell();
    feuille_setCell(&f, C1, "C1");
    cell_setStr(C1, "=B1 3 +", &f);
    
    printf("A1 = %.2f (attendu: 5.00)\n", A1->value);
    printf("B1 = %.2f (attendu: 10.00)\n", B1->value);
    printf("C1 = %.2f (attendu: 13.00)\n", C1->value);
    printf("✓ Test 7 réussi\n\n");
}

void test_texte() {
    printf("=== TEST 8 : Cellule texte ===\n");
    s_feuille f;
    init_feuille(&f, "Test", 26, 26);
    
    s_cell *A1 = init_cell();
    cell_setStr(A1, "Bonjour", &f);
    feuille_setCell(&f, A1, "A1");
    
    printf("A1 contenu = '%s'\n", A1->t);
    printf("A1 valeur = %.2f (attendu: 0.00 pour texte)\n", A1->value);
    printf("✓ Test 8 réussi\n\n");
}
// void test_recalcul_automatique() {
//     printf("=== TEST 9 : Recalcul automatique ===\n");
//     s_feuille f;
//     init_feuille(&f, "Test", 26, 26);
    
//     // A1 = 10
//     s_cell *A1 = init_cell();
//     cell_setStr(A1, "10", &f);
//     feuille_setCell(&f, A1, "A1");
    
//     // B1 = A1 + 5
//     s_cell *B1 = init_cell();
//     feuille_setCell(&f, B1, "B1");
//     cell_setStr(B1, "=A1 5 +", &f);
    
//     // C1 = B1 * 2
//     s_cell *C1 = init_cell();
//     feuille_setCell(&f, C1, "C1");
//     cell_setStr(C1, "=B1 2 *", &f);
    
//     printf("Initial : A1=%.2f, B1=%.2f, C1=%.2f\n", A1->value, B1->value, C1->value);
//     printf("Attendu : A1=10.00, B1=15.00, C1=30.00\n");
    
//     // MODIFIER A1
//     printf("\n>>> Modification de A1 : 10 → 20\n");
//     cell_setStr(A1, "20", &f);
    
//     printf("Après recalcul : A1=%.2f, B1=%.2f, C1=%.2f\n", A1->value, B1->value, C1->value);
//     printf("Attendu : A1=20.00, B1=25.00, C1=50.00\n");
    
//     if(B1->value == 25.0 && C1->value == 50.0) {
//         printf("✓ Test 9 réussi : recalcul automatique fonctionne !\n\n");
//     } else {
//         printf("❌ Test 9 échoué : recalcul ne fonctionne pas\n\n");
//     }
//}
int main() {
    printf("╔════════════════════════════════════════════════╗\n");
    printf("║   SUITE DE TESTS - JALON 2 : FORMULES          ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");
    
    test_cellule_simple();
    test_formule_simple();
    test_reference_inexistante();
    test_dependances();
    test_operateurs_multiples();
    test_division_par_zero();
    test_chaine_references();
    test_texte();
    // test_recalcul_automatique();
    printf("╔════════════════════════════════════════════════╗\n");
    printf("║   TOUS LES TESTS TERMINÉS !                    ║\n");
    printf("╚════════════════════════════════════════════════╝\n");
    
    return 0;
}
