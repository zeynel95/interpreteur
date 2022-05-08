#ifndef __AST_PARCOURS__
#define __AST_PARCOURS__

#include "table_symbole.h"

void afficher_ast(Ast expr) ;
// affiche l'arbre abstrait de l'expression arithmetique expr

float evaluation(Ast expr, table_symbole t) ;
// calcule la valeur de l'expression arithmetique expr
// FONCTION A COMPLETER !

void interpreter_aff(Ast A, table_symbole t);

void interpreter_lire(Ast A, table_symbole t);

void interpreter_ecrire(Ast A, table_symbole t);

void interpreter_if(Ast A, table_symbole t);

void interpreter(Ast A, table_symbole t);

void interpreter(Ast A, table_symbole t);

#endif

