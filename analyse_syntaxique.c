#include <stdio.h>
#include <stdlib.h>
#include "lecture_caracteres.h"
#include "analyse_syntaxique.h"

int is_final(Etat_Automate_Syntax etat){return etat == E_ENTIER;}


Etat_Automate_Syntax analyser(Etat_Automate_Syntax etat, Nature_Lexeme *last_lex, float *res){

    while (etat != E_ERREUR)
    {
        switch (etat)
        {
            case E_INIT:
                switch (lexeme_courant().nature)
                {
                    case FLOAT:
                    case ENTIER:
                        *res = *res + lexeme_courant().valeur;
                        return E_ENTIER;
                        break;
                    
                    default:
                        return E_ERREUR;
                        break;
                }
                break;
            case E_ENTIER:
                switch (lexeme_courant().nature)
                {
                    case PLUS :
                        *last_lex = PLUS;
                        return E_SYMBOLE;
                        break;
                    case MOINS :
                        *last_lex = MOINS;
                        return E_SYMBOLE;
                        break;
                    case MUL :
                        *last_lex = MUL;
                        return E_SYMBOLE;
                        break;
                    case DIV :
                        *last_lex = DIV;
                        return E_SYMBOLE;
                        break;
                    
                    default:
                        return E_ERREUR;
                        break;
                }
                break;
            
            case E_SYMBOLE:
                switch (lexeme_courant().nature)
                {
                    case FLOAT:
                    case ENTIER:
                        switch (*last_lex)
                        {
                        case PLUS:
                            *res = *res + lexeme_courant().valeur;
                            break;
                        case MOINS:
                            *res = *res - lexeme_courant().valeur;
                            break;
                        case MUL:
                            *res = *res * lexeme_courant().valeur;
                            break;
                        case DIV:
                            *res = *res / lexeme_courant().valeur;
                            break;
                        default:
                            break;
                        }
                        return E_ENTIER;
                        break;
                    
                    default:
                        return E_ERREUR;
                        break;
                }
                break;
            case E_ERREUR :
                return E_ERREUR;
                break;
            default:
                break;
            }
        }
        return etat;
} 