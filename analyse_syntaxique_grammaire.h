/* -------------------
-- paquetage syntaxique
-- analyse syntaxique d'une expression
--------------------------------*/



#include "analyse_lexicale.h"
#include "ast_construction.h"
#include "ast_parcours.h"

int rec_eaep(float* val);

int rec_op(Nature_Lexeme* op);

float evaluer(float vald, Nature_Lexeme op, float valg);

int rec_eag(Ast *A);

int rec_seq_terme(Ast *A);

int Rec_suite_seq_terme(Ast Ag, Ast *A);

int Rec_suite_seq_facteur(Ast Ag, Ast *A);

int Rec_terme(Ast *A);

int Rec_seq_facteur(Ast *A);

int Rec_facteur(Ast *A);

int Rec_op1(TypeOperateur *Op);

int Rec_op2(TypeOperateur *Op);

int Rec_aff(table_symbole t);

int Rec_seq_aff(table_symbole t);

int Rec_pgm(Ast* A);

int Rec_seq_inst(Ast* A);

int Rec_suite_seq_inst(Ast A1, Ast* A);

int Rec_inst(Ast* A);

int Rec_condition(Ast* A);