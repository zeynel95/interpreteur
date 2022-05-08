
/* Exemple d'utilisation de l'analyse lexicale : 
    Affichage d'une sequence de lexemes            */

#include <stdio.h>
#include <stdlib.h>

#include "analyse_syntaxique.h"


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
   Etat_Automate_Syntax etat = E_INIT;
   float res = 0.0;
   Nature_Lexeme last_lex ;
   while (! fin_de_sequence()) { 
        etat = analyser(etat, &last_lex, &res); 
        avancer();
   } ;
   is_final(etat) ? printf("\nlexpression est correct et le resultat est %f\n", res) : printf("\nlexpression nest pas correct\n");
   arreter() ; // termine l'analyse lexicale
   return 0 ;
}
