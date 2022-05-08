
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lecture_caracteres.h"
#include "analyse_syntaxique_grammaire.h"

int natureop_vers_typeop(TypeOperateur* op);

// 0 si faux, 1 si correcte syntaxe
int rec_eaep(float* val){
    switch(lexeme_courant().nature){
        case FLOAT:
        case ENTIER:
            *val = lexeme_courant().valeur;
            avancer();
            // return 1;
            break;
        case PARO:
            avancer();
            float valg;
            rec_eaep(&valg);
            
            Nature_Lexeme op;
            if(rec_op(&op) != 1) {
                // on gere l'erreur
                return 0;
            }
            
            float vald;
            rec_eaep(&vald);
            
            *val = evaluer(valg, op, vald);

            if(lexeme_courant().nature == PARF){
                avancer();
            }else{
                return 0;
            }
            
            break;
        default:
            return 0;
    };
    return 1;
};
// 0 si faux, 1 si correcte
int rec_op(Nature_Lexeme* op){
    switch(lexeme_courant().nature){
        case PLUS:
        case MOINS:
        case MUL:
        case DIV:
            *op = lexeme_courant().nature;
            avancer();
            return 1;
        default:
            return 0;
    }
};

float evaluer(float vald, Nature_Lexeme op, float valg){
    switch(op){
        case PLUS:
            return vald + valg;
        case MOINS:
            return vald - valg;
        case DIV:
            return vald / valg;
        case MUL:
            return vald * valg;
        default:
            // pass
            return 0.0;
    }
}

int rec_eag(Ast *A){
    return rec_seq_terme(A);
}

int rec_seq_terme(Ast *A){
    int err = 1;
    Ast A1 = NULL;
    err *= Rec_terme(&A1);
    err *= Rec_suite_seq_terme(A1, A);
    return err;
}

int Rec_suite_seq_terme(Ast Ag, Ast *A){
    int err = 1;
    Ast Ad = NULL, A1 = NULL;
    TypeOperateur Op;
    switch (lexeme_courant().nature){
        case PLUS:
        case MOINS:
            err *= Rec_op1(&Op);
            err *= Rec_terme(&Ad);
            A1 = creer_operation(Op, Ag, Ad);
            err *= Rec_suite_seq_terme(A1, A);
            break;
        
        default:
            *A = Ag;
            break;
    }
    return err;
}

int Rec_suite_seq_facteur(Ast Ag, Ast *A){
    int err = 1;
    Ast Ad = NULL, A1 = NULL;
    TypeOperateur Op;
    switch (lexeme_courant().nature){
        case MUL:
        case DIV:
            err *= Rec_op2(&Op);
            err *= Rec_terme(&Ad);
            A1 = creer_operation(Op, Ag, Ad);
            err *= Rec_suite_seq_terme(A1, A);
            break;
        
        default:
            *A = Ag;
            break;
    }
    return err;
}

int Rec_terme(Ast *A){
    return Rec_seq_facteur(A);
}

int Rec_seq_facteur(Ast *A){
    Ast Ag = NULL;
    int err = 1;
    err *= Rec_facteur(&Ag);
    err *= Rec_suite_seq_facteur(Ag, A);
    return err;
}

int Rec_facteur(Ast *A){
    switch (lexeme_courant().nature){
        case ENTIER:
        case FLOAT:
            *A = creer_valeur(lexeme_courant().valeur);
            avancer();
            break;
        case PARO:
            avancer();
            rec_eag(A);
            if (lexeme_courant().nature == PARF)
            {
                avancer();
            }
            else return 0;
            break;
        case IDF:
            *A = creer_idf(lexeme_courant().chaine);
            avancer();
            break;
        default:
            return 0;
    }
    return 1;
}

int Rec_op1(TypeOperateur *Op){
    switch (lexeme_courant().nature){
        case PLUS:
            *Op = N_PLUS;
            avancer();
            return 1;
        case MOINS:
            *Op = N_MOINS;
            avancer();    
            return 1;

        default:
            return 0;
    }
}

int Rec_op2(TypeOperateur *Op){
    switch (lexeme_courant().nature){
        case MUL:
            *Op = N_MUL;
            avancer();    
            return 1;
        case DIV:
            *Op = N_DIV;
            avancer();    
            return 1;        
        default:
            return 0;
    }
}

int Rec_aff(table_symbole t){
    symbole s;
    if (lexeme_courant().nature == IDF)
    {
        strcpy(s.nom, lexeme_courant().chaine);
        avancer();
        if (lexeme_courant().nature == AFF)
        {
            avancer();
            Ast A;
            if (rec_eag(&A))
            {
                s.val = (int)evaluation(A, t);
                ajouter_symbole(s, t);
                if (lexeme_courant().nature == SEPAFF)
                {
                    avancer();
                    return 1;
                }
                
            }
            
        }
        
    }
    return 0;
}

int Rec_seq_aff(table_symbole t){
    if (lexeme_courant().nature == FIN_SEQUENCE)
    {
        return 1;
    }
    else
    {
        if (Rec_aff(t))
        {
            if(Rec_seq_aff(t))
            {
                return 1;
            }
        }
    }
    return 0;
}

int Rec_pgm(Ast* A){
    int err = Rec_seq_inst(A);
    return err;
}

int Rec_seq_inst(Ast* A){
    Ast A1;
    int err = Rec_inst(&A1);
    err *= Rec_suite_seq_inst(A1, A);
    return err;
}

int Rec_suite_seq_inst(Ast A1, Ast* A){
    if (lexeme_courant().nature == SEPAFF)
    {
        avancer();
        Ast A2;
        int err = Rec_seq_inst(&A2);
        *A = creer_seq_inst(A1, A2);
        return err;
    }
    else
    {
        *A = A1;
        return 1;
    }
    
}

int Rec_inst(Ast* A){
    Ast Ag, Ad;
    if (lexeme_courant().nature == IDF)
    {
        Ag = creer_idf(lexeme_courant().chaine);
        avancer();
        if (lexeme_courant().nature == AFF)
        {
            avancer();
            int err = rec_eag(&Ad);
            *A = creer_aff(Ag, Ad);
            return err;
        }
        else return 0;
        
    }
    if (lexeme_courant().nature == LIRE)
    {
        avancer();
        if (lexeme_courant().nature == PARO)
        {
            avancer();
            if (lexeme_courant().nature == IDF)
            {
                Ag = creer_idf(lexeme_courant().chaine);
                avancer();
                if (lexeme_courant().nature == PARF)
                {
                    avancer();
                    *A = creer_lire(Ag);
                    return 1;
                }
                else return 0;
            }
            else return 0;
        }
        else return 0;
    }
    if (lexeme_courant().nature == ECRIRE)
    {
        avancer();
        if (lexeme_courant().nature == PARO)
        {
            avancer();
            int err = rec_eag(&Ag);
            *A = creer_ecrire(Ag);
            if (lexeme_courant().nature == PARF)
            {
                avancer();
                return err;
            }
            else return 0;
        }
        else return 0;
    }
    if (lexeme_courant().nature == IF)
    {
        Ast Ag, Ad, Abis;
        int err = 1;
        avancer();
        err *= Rec_condition(&Ag);
        if (lexeme_courant().nature == THEN)
        {
            avancer();
            err *= Rec_seq_inst(&Abis);
            if (lexeme_courant().nature == ELSE)
            {
                avancer();
                err *= Rec_seq_inst(&Ad);
                if (lexeme_courant().nature == FI)
                {
                    *A = creer_if(Ag, Ad, Abis);
                    avancer();
                    return 1;
                }
                else return 0;
            }
            else return 0;
        }
        else return 0;
    }
    if (lexeme_courant().nature == WHILE)
    {
        Ast Ag, Ad;
        int err = 1;
        avancer();
        err *= Rec_condition(&Ag);
        if (lexeme_courant().nature == DO)
        {
            avancer();
            err *= Rec_seq_inst(&Ad);
            if (lexeme_courant().nature == DONE)
            {
                *A = creer_operation(N_WHILE, Ag, Ad);
                avancer();
                return err;
            }
            
        }
        
    }
    
    else return 0;
}

int Rec_condition(Ast* A){
    Ast Ag, Ad;
    rec_eag(&Ag);
    TypeOperateur op; 
    int err = natureop_vers_typeop(&op);
    avancer();
    rec_eag(&Ad);
    *A = creer_operation(op, Ag, Ad);    
    return err;
}

int natureop_vers_typeop(TypeOperateur* op){
    switch (lexeme_courant().nature)
    {
    case INF:
        *op = N_INF;
        return 1;
    case INFEG:
        *op = N_INFEG;
        return 1;
    case SUP:
        *op = N_SUP;
        return 1;
    case SUPEG:
        *op = N_SUPEG;
        return 1;
    case EG:
        *op = N_EG;
        return 1;
    case DIFF:
        *op = N_DIF;
        return 1;
    default:
        return 0;
    }
}