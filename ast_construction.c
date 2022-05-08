#include <stdlib.h>
#include <stdio.h> 
#include <string.h>

#include "type_ast.h"

Ast creer_operation(TypeOperateur opr , Ast opde_gauche , Ast opde_droit) 
{
      Ast expr ;
      expr = (Ast) malloc (sizeof(NoeudAst));
      expr->nature = OPERATION;
      expr->operateur = opr;
      if (opde_gauche == NULL){
         printf("ERREUR_EXPRESSION gauche null\n") ;
         exit(1) ;

      }else if(opde_droit == NULL) {
      
         printf("ERREUR_EXPRESSION droit null\n") ;
	   exit(1) ;
      } else {
         expr->gauche = opde_gauche;
         expr->droite = opde_droit;
      } ;
      return expr ;
}

Ast creer_valeur(float val) { 
      Ast expr ;
      expr = (Ast) malloc (sizeof(NoeudAst));
      expr->nature = VALEUR;
      expr->valeur = val;
      return expr ;
}

Ast creer_idf(char* val) { 
      Ast expr ;
      expr = (Ast) malloc (sizeof(NoeudAst));
      expr->nature = CHAINE;
      strcpy(expr->chaine, val);
      return expr ;
}


Ast creer_seq_inst(Ast opde_gauche , Ast opde_droit) 
{
      Ast expr ;
      expr = (Ast) malloc (sizeof(NoeudAst));
      expr->nature = OPERATION;
      expr->operateur = N_SEPINST;
      if (opde_gauche == NULL){
         printf("ERREUR_EXPRESSION gauche null\n") ;
         exit(1) ;

      }else if(opde_droit == NULL) {
      
         printf("ERREUR_EXPRESSION droit null\n") ;
	   exit(1) ;
      } else {
         expr->gauche = opde_gauche;
         expr->droite = opde_droit;
      } ;
      return expr ;
}

Ast creer_aff(Ast opde_gauche , Ast opde_droit) 
{
      Ast expr ;
      expr = (Ast) malloc (sizeof(NoeudAst));
      expr->nature = OPERATION;
      expr->operateur = N_AFF;
      if (opde_gauche == NULL){
         printf("ERREUR_EXPRESSION gauche null\n") ;
         exit(1) ;

      }else if(opde_droit == NULL) {
      
         printf("ERREUR_EXPRESSION droit null\n") ;
	   exit(1) ;
      } else {
         expr->gauche = opde_gauche;
         expr->droite = opde_droit;
      } ;
      return expr ;
}

Ast creer_lire(Ast opde_gauche) 
{
      Ast expr ;
      expr = (Ast) malloc (sizeof(NoeudAst));
      expr->nature = OPERATION;
      expr->operateur = N_LIRE;
      if (opde_gauche == NULL){
         printf("ERREUR_EXPRESSION gauche null\n") ;
         exit(1) ;

      } 
      else {
         expr->gauche = opde_gauche;
      } ;
      return expr ;
}

Ast creer_ecrire(Ast opde_gauche) 
{
      Ast expr ;
      expr = (Ast) malloc (sizeof(NoeudAst));
      expr->nature = OPERATION;
      expr->operateur = N_ECRIRE;
      if (opde_gauche == NULL){
         printf("ERREUR_EXPRESSION gauche null\n") ;
         exit(1) ;

      } 
      else {
         expr->gauche = opde_gauche;
      } ;
      return expr ;
}

Ast creer_if(Ast opde_gauche, Ast opde_droit,Ast opde_bis){
   Ast expr;
   expr = (Ast) malloc (sizeof(NoeudAst));
   expr->nature = OPERATION;
   expr->operateur = N_IF;
   if (opde_gauche == NULL){
         printf("ERREUR_EXPRESSION gauche null\n") ;
         exit(1) ;

      }
   else if (opde_droit == NULL){
         printf("ERREUR_EXPRESSION gauche null\n") ;
         exit(1) ;

      }
   else if (opde_bis == NULL){
         printf("ERREUR_EXPRESSION gauche null\n") ;
         exit(1) ;

      }
   else {
      expr->bis = opde_bis;
      expr->gauche = opde_gauche;
      expr->droite = opde_droit;
   }
}