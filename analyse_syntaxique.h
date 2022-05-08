/* -------------------
-- paquetage syntaxique
-- analyse syntaxique d'une expression
--------------------------------*/

#include "analyse_lexicale.h"


typedef enum {E_INIT, E_ENTIER, E_SYMBOLE, E_ERREUR} Etat_Automate_Syntax;

Etat_Automate_Syntax analyser(Etat_Automate_Syntax etat, Nature_Lexeme *last_lex, float* res);

int is_final(Etat_Automate_Syntax etat);

