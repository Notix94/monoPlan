#include "../include/feuille.h"
#include <string.h>
#include <ctype.h>
void init_feuille(s_feuille *f, char *nom, int lignes, int colonnes){
    strcpy(f->nom, nom);

    //si lignes et col sup a limite
    f->lignes = (lignes > NBLIG) ? NBLIG : lignes;
    f->colonnes = (colonnes > NBCOL) ? NBCOL : colonnes;

    //init les cases a NULL
    for(int i = 0; i < f->lignes; i++){
        for(int j = 0; j < f->colonnes; j++){
            f->tab[i][j] = NULL;
        }
    }
}
//cellule deja existante a ajouter
void feuille_setCell(s_feuille *f,s_cell *c, char *pos){
    char c1 ;
    int c2 ;
    //si BB22 invalid si B22 valide
    if(sscanf(pos,"%c%2d", &c1, &c2) !=2){
        printf("Position invalide !\n");
        return;
    }
    int col = toupper(c1)-'A';
   int ligne = c2 - 1;
    //si hors limite avec converrt ASCII
    if(ligne< 0 ||ligne >= f->lignes || col < 0 || col >= f->colonnes){
        printf("Position hors limites !\n");
        return; 
    }

     f->tab[ligne][col] = c;
}