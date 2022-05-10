#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "table_symbole.h"

int main(int argc, char** argv){
    int taille_table = 100;
    table_symbole t = malloc(sizeof(symbole)*taille_table);
    init_table(t, taille_table);
    ajouter_symbole(cree_symbole("w", 4), t);
    afficher_table(t);
    ajouter_symbole(cree_symbole("x", 3), t);
    afficher_table(t);
    ajouter_symbole(cree_symbole("y", 2), t);
    afficher_table(t);
    ajouter_symbole(cree_symbole("z", 1), t);
    afficher_table(t);
    ajouter_symbole(cree_symbole("x", 9), t);
    afficher_table(t);
}