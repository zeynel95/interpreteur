
#include <stdio.h>
#include <stdlib.h>
#include "type_ast.h"
#include "ast_construction.h"
#include "table_symbole.h"

int val_bool(Ast A, table_symbole t);

void aff_operateur(TypeOperateur op){
	switch (op) {
		case N_PLUS:
			printf("+") ;
			break;
		case N_MOINS:
			printf("-") ;
			break;
		case N_MUL:
			printf("*") ;
			break;
		case N_DIV:
			printf("/") ;
			break;
	} 
}

void afficher_ast(Ast expr) {
	if(expr == NULL) return;
	switch (expr->nature) {
               case OPERATION:
                        printf("(");
                        afficher_ast(expr->gauche);
                        aff_operateur(expr->operateur) ;
                        afficher_ast(expr->droite);
                        printf(")");
			break ;
               case VALEUR:
                  	printf("%f", expr->valeur);
			break ;
				case CHAINE:
                  	printf("%s", expr->chaine);
			break ;
	}
}

float evaluation(Ast expr, table_symbole t) {
      float vg, vd;
	  int val;
	  switch (expr->nature)
	  {
	  case VALEUR:
		  return expr->valeur;
	  case OPERATION:
	  	vg = evaluation(expr->gauche, t);
		vd = evaluation(expr->droite, t);
		switch (expr->operateur)
		{
		case N_PLUS:
			return vg + vd;
		case N_MOINS:
			return vg - vd;
		case N_MUL:
		 return vg * vd;
		case N_DIV:
		 return vg / vd;
		default:
			break;
		}
	  case CHAINE:
	  	if(chercher(expr->chaine, &val, t))
			return (float)val;
		else{
			printf("\nvariable existe pas\n");
			exit(1);
		}
	  default:
		  break;
	  }
      return -1.0 ;
}

void interpreter_aff(Ast A, table_symbole t){
	symbole s = cree_symbole(A->gauche->chaine, (int)evaluation(A->droite, t));
	ajouter_symbole(s, t);
}

void interpreter_lire(Ast A, table_symbole t){
	int val;
	printf("\nlire : ");
	scanf("%d",&val);
	symbole s = cree_symbole(A->gauche->chaine, val);
	ajouter_symbole(s, t);
}

void interpreter_ecrire(Ast A, table_symbole t){
	printf("\necrire : %d\n", (int)evaluation(A->gauche, t));
}

void interpreter_if(Ast A, table_symbole t){
	switch (A->gauche->operateur)
	{
	case N_INF:
		evaluation(A->gauche->gauche, t) < evaluation(A->gauche->droite, t) ? interpreter(A->bis, t) : interpreter(A->droite, t);
		break;
	case N_INFEG:
		evaluation(A->gauche->gauche, t) <= evaluation(A->gauche->droite, t) ? interpreter(A->bis, t) : interpreter(A->droite, t);
		break;
	case N_SUP:
		evaluation(A->gauche->gauche, t) > evaluation(A->gauche->droite, t) ? interpreter(A->bis, t) : interpreter(A->droite, t);
		break;
	case N_SUPEG:
		evaluation(A->gauche->gauche, t) >= evaluation(A->gauche->droite, t) ? interpreter(A->bis, t) : interpreter(A->droite, t);
		break;
	case N_EG:
		evaluation(A->gauche->gauche, t) == evaluation(A->gauche->droite, t) ? interpreter(A->bis, t) : interpreter(A->droite, t);
		break;
	case N_DIF:
		evaluation(A->gauche->gauche, t) != evaluation(A->gauche->droite, t) ? interpreter(A->bis, t) : interpreter(A->droite, t);
		break;
	default:
		break;
	}
}

int val_bool(Ast A, table_symbole t){
	switch (A->operateur)
	{
	case N_INF:
		if (evaluation(A->gauche, t) < evaluation(A->droite, t)) return 1;
		else return 0;
		break;
	case N_INFEG:
		if (evaluation(A->gauche, t) <= evaluation(A->droite, t)) return 1;
		else return 0;
		break;
	case N_SUP:
		if (evaluation(A->gauche, t) > evaluation(A->droite, t)) return 1;
		else return 0;
		break;
	case N_SUPEG:
		if (evaluation(A->gauche, t) >= evaluation(A->droite, t)) return 1;
		else return 0;
		break;
	case N_EG:
		if (evaluation(A->gauche, t) == evaluation(A->droite, t)) return 1;
		else return 0;
		break;
	case N_DIF:
		if (evaluation(A->gauche, t) != evaluation(A->droite, t)) return 1;
		else return 0;
		break;
	default:
		break;
	}
}

void interpreter(Ast A, table_symbole t){
	switch (A->operateur)
	{
	case N_SEPINST:
		interpreter(A->gauche, t);
		interpreter(A->droite, t);
		break;
	case N_AFF:
		interpreter_aff(A, t);
		break;
	case N_LIRE:
		interpreter_lire(A, t);
		break;
	case N_ECRIRE:
		interpreter_ecrire(A, t);
		break;
	case N_IF:
		interpreter_if(A, t);
		break;
	case N_WHILE:
		while (val_bool(A->gauche, t))
		{
			interpreter(A->droite, t);
		}
		break;
	default:
		break;
	}
}

