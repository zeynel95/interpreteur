#ifndef __TYPE_AST__
#define __TYPE_AST__ 

typedef enum {OPERATION, VALEUR, CHAINE} TypeAst ;
typedef enum {N_PLUS, N_MUL, N_MOINS, N_DIV, N_SEPINST, N_AFF, N_LIRE, N_ECRIRE,  N_SUP,  N_SUPEG,  N_INF,  N_INFEG,  N_EG,  N_DIF, N_IF, N_WHILE} TypeOperateur ;

typedef struct noeud { 
	TypeAst nature ;
	TypeOperateur operateur ;
	struct noeud *gauche, *droite, *bis;
    float valeur ;
	char chaine[20];
} NoeudAst ;

typedef NoeudAst *Ast ;

#endif  
