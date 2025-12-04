#include "../include/feuille.h"
#include <string.h>
#include <ctype.h>
void init_feuille(s_feuille *f, char *nom, int lignes, int colonnes){
    strcpy(f->nom, nom);

    f->lignes = (lignes > NBLIG) ? NBLIG : lignes;
    f->colonnes = (colonnes > NBCOL) ? NBCOL : colonnes;

    for(int i = 0; i < f->lignes; i++){
        for(int j = 0; j < f->colonnes; j++){
            f->tab[i][j] = NULL;
        }
    }
}
void feuille_setCell(s_feuille *f,s_cell *c, char *pos){
    char c1 ;
    int c2 ;
    if(sscanf(pos,"%c%2d", &c1, &c2) !=2){
        printf("Position invalide !\n");
        return;
    }
    int col = toupper(c1)-'A';
   int ligne = c2 - 1;

    if(ligne< 0 ||ligne >= f->lignes || col < 0 || col >= f->colonnes){
        printf("Position hors limites !\n");
        return; 
    }

     f->tab[ligne][col] = c;
}