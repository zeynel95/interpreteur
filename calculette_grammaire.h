
/* -------------------
-- paquetage syntaxique
-- analyse syntaxique d'une expression utilisant une grammaire
--------------------------------*/


#include "analyse_lexicale.h"


int rec_eaep(float* val);

// reconnait l'operateur
// on avance a l'autre lexemme
int rec_op();

float evaluer(float vald, Nature_Lexeme op, float valg);