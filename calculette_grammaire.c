

/* Exemple d'utilisation de l'analyse lexicale : 
    Affichage d'une sequence de lexemes            */

#include <stdio.h>
#include <stdlib.h>

#include "analyse_syntaxique_grammaire.h"

#include "ast_parcours.h"


int main (int argc, char *argv[]) {
    switch (argc) {
        case 1:
            // demarre l'analyse lexicale sur stdin
            demarrer ("") ; 
            break ;
        case 2:
            // demarre l'analyse lexicale sur le fichier transmis en argument
            demarrer (argv[1]) ; 
            break ;
        default:
            printf("nombre d'arguments incorrects !\n");
            exit(1) ;
    } ;
   
    // float resultat;
    // analyse recursive de grammaire
    // float res;
    int taille_table = 100;
    table_symbole t = malloc(sizeof(symbole)*taille_table);
    init_table(t, taille_table);
    //int res_error = Rec_seq_aff(t);
    Ast A;
    int res_error = Rec_pgm(&A);
    if(res_error == 0 || !fin_de_sequence()){
        // ERROR
        printf("Mauvaise syntaxe, lexemme \n");
        afficher(lexeme_courant());
        printf("\n");
        return 0;

    } 
    else{
        afficher_ast(A);
        printf("\nBonne syntax !! \n");
        interpreter(A, t);
        afficher_table(t);
        //float res = evaluation(A);
        //printf("resultat: %f\n", res);
    }

    //printf("res: %f\n", res);

    arreter() ; // termine l'analyse lexicale
    return 0 ;
}
