
#ifndef __AST_CONSTRUCTION__
#define __AST_CONSTRUCTION__

#include "type_ast.h"

Ast creer_operation(TypeOperateur opr , Ast opde_gauche , Ast opde_droit) ;
// renvoie un arbre abstrait de nature OPERATEUR,  d'operateur opr 
// et ayant opde_gauche et opde_droit pour fils gauche et droit

Ast creer_valeur(float val) ; 
// renvoie un arbre abstrait "feuille", de nature OPERATION  
// et de valeur val

Ast creer_seq_inst(Ast opde_gauche , Ast opde_droit);

Ast creer_idf(char* val);

Ast creer_aff(Ast opde_gauche , Ast opde_droit);

Ast creer_lire(Ast opde_gauche);

Ast creer_ecrire(Ast opde_gauche);

Ast creer_if(Ast opde_gauche, Ast opde_droit, Ast opde_bis);

#endif
