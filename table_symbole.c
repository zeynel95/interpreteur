#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table_symbole.h"

void ajouter_symbole(symbole s, table_symbole t){
    int i = 0;
    while (strcmp(t[i].nom,"\0") != 0 && strcmp(t[i].nom,s.nom) != 0)
    {   
        i++;
    }
    //t[i].nom = s.nom;
    strcpy(t[i].nom, s.nom);
    t[i].val = s.val;
}

symbole cree_symbole(char* nom, int val){
    symbole s;
    strcpy(s.nom, nom);
    s.val = val;
    return s;
}

void afficher_table(table_symbole t){
    printf("\n**********************\n");
    printf("*   nom   |   val   *\n");
    int i = 0;
    while (strcmp(t[i].nom,"\0") != 0)
    {   
        printf("*    %s    |    %d    *\n", t[i].nom, t[i].val);
        i++;
    }
    printf("**********************\n");
}

void init_table(table_symbole t,int taille_table){
    for (int i = 0; i < taille_table; i++)
    {
        //t[i].nom = "\0";
        strcpy(t[i].nom, "\0");
        t[i].val = 0;
    }
}

int chercher(char* var, int* v, table_symbole t){
    int i = 0;
    while (strcmp(t[i].nom,"\0") != 0)
    {   
        if (!strcmp(t[i].nom, var))
        {
            *v = t[i].val;
            return 1;
        }
        i++;
    }
    return 0;
}