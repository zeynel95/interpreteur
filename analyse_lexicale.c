/* ------------------------------------------------------------------------
-- paquetage analyse_lexicale
--
-- analyse lexicale d'une expression arithmetique
--
-- J-P. Peyrin, G. Serasset (version initiale) : janvier 1999
-- P.Habraken - 18/01/2010
--
-- 10 juin 2006 - PH :
-- remplacement record a champs variants par record "plat"
-- remplacement traitement iteratif par automate
--
-- Aout 2016 - LM : version C
------------------------------------------------------------------------ */

#include <string.h>
#include <stdlib.h> 
#include <stdio.h> 

#include "lecture_caracteres.h"
#include "analyse_lexicale.h"

   /* --------------------------------------------------------------------- */


/* Les variables et fonctions locales au module */

   Lexeme lexeme_en_cours ;	/* le lexeme courant */

   void ajouter_caractere (char *s, char c);
   Nature_Caractere nature_caractere (char c);
   int est_separateur(char c ) ;
   int est_chiffre(char c ) ;
   int est_symbole(char c ) ;
   int est_operateur(char c ) ;
   int est_lettre(char c);
   void reconnaitre_lexeme();

   /* --------------------------------------------------------------------- */

   void demarrer(char *nom_fichier) {
      demarrer_car(nom_fichier);
      avancer();
   }

   /* --------------------------------------------------------------------- */

   void avancer() {
      reconnaitre_lexeme();
   } 

   /* --------------------------------------------------------------------- */

   Lexeme lexeme_courant() {
      return lexeme_en_cours;
   } 

   /* --------------------------------------------------------------------- */

   int fin_de_sequence() {
      return lexeme_en_cours.nature == FIN_SEQUENCE;
   }

   /* --------------------------------------------------------------------- */

   void arreter() {
      arreter_car() ;
   }

   /* --------------------------------------------------------------------- */


   // reconnaissance d'un nouveau lexeme
   // etat initial : le caractere courant est soit separateur 
   //                soit le 1er caractere d'un lexeme
   // etat final : 
   //       - un nouveau lexeme est reconnu dans lexeme_en_cours
   //       - le caractere courant est soit la fin de fichier, 
   //		soit un separateur,  soit le 1er caractere d'un lexeme

   void reconnaitre_lexeme() {
      typedef enum {E_INIT, E_ENTIER, E_FLOAT, E_IDF, E_OP, E_FIN} Etat_Automate ;
      Etat_Automate etat=E_INIT;

     // on commence par lire et ignorer les separateurs
     while (est_separateur(caractere_courant())) {
        	avancer_car() ;
     } ;

     lexeme_en_cours.chaine[0] = '\0' ;

      float ordre = 10.0;

     // on utilise ensuite un automate pour reconnaitre et construire le prochain lexeme

    while (etat != E_FIN) {

	    switch (etat) {

		  case E_INIT: // etat initial

			switch(nature_caractere(caractere_courant())) {

				case C_FIN_SEQUENCE: 
             		lexeme_en_cours.nature = FIN_SEQUENCE;
                	etat = E_FIN;
					break ;


				case CHIFFRE: 
		     		lexeme_en_cours.nature = ENTIER;
                	lexeme_en_cours.ligne = numero_ligne();
                	lexeme_en_cours.colonne = numero_colonne();
		     		ajouter_caractere (lexeme_en_cours.chaine, caractere_courant()) ;
               		lexeme_en_cours.valeur = caractere_courant() - '0';
               		etat = E_ENTIER;
		   			avancer_car() ;
					break ;

				case SYMBOLE: 
		       		lexeme_en_cours.ligne = numero_ligne();
               		lexeme_en_cours.colonne = numero_colonne();
		       		ajouter_caractere (lexeme_en_cours.chaine, caractere_courant()) ;
               		switch (caractere_courant()) {
               		   case '+':
                           lexeme_en_cours.nature = PLUS;
                           etat = E_FIN;
                           break;
               		   case '-':
                           lexeme_en_cours.nature = MOINS;
                           etat = E_FIN;
                           break;
               		   case '*':
                           lexeme_en_cours.nature = MUL;
                           etat = E_FIN;
                           break;
                        case '/':
                           lexeme_en_cours.nature = DIV;
                           etat = E_FIN;
                           break;
                        case '.':
                           lexeme_en_cours.nature = FLOAT;
                           etat = E_FIN;
                           break;
                        case '(':
                           lexeme_en_cours.nature = PARO;
                           etat = E_FIN;
                           break;
                        case ')':
                           lexeme_en_cours.nature = PARF;
                           etat = E_FIN;
                           break;
                        case '=':
                           lexeme_en_cours.nature = AFF;
                           etat = E_OP;
                           break;
                        case ';':
                           lexeme_en_cours.nature = SEPAFF;
                           etat = E_FIN;
                           break;
		       		      default:
                           printf("\nLe caractere courant a l'erreur est : %d\n", caractere_courant());
                           printf("Erreur_Lexicale") ;
                           exit(0) ;
				 	} ;
		   			avancer_car() ;
					break ;
            
            case LETTRE:
               lexeme_en_cours.nature = IDF;
               lexeme_en_cours.ligne = numero_ligne();
             	lexeme_en_cours.colonne = numero_colonne();
		     		ajouter_caractere (lexeme_en_cours.chaine, caractere_courant()) ;
         		etat = E_IDF;
	   			avancer_car() ;
               break;
            case OPERATEUR:
		      	lexeme_en_cours.ligne = numero_ligne();
         		lexeme_en_cours.colonne = numero_colonne();
	       		ajouter_caractere (lexeme_en_cours.chaine, caractere_courant()) ;
               switch (caractere_courant()){
                  case '>':
                     lexeme_en_cours.nature = SUP;
                     etat = E_OP;
                     break;
                  case '<':
                     lexeme_en_cours.nature = INF;
                     etat = E_OP;
                     break;
                  case '!':
                     lexeme_en_cours.nature = DIFF;
                     etat = E_OP;
                     break;
                  default:
                     printf("\nLe caractere courant a l'erreur est : %d\n", caractere_courant());
                     printf("Erreur_Lexicale") ;
                     exit(0) ;
               }
               avancer_car();
               break;
				default:
                 printf("\nLe caractere courant a l'erreur est : %d\n", caractere_courant());
		           printf("Erreur_Lexicale\n") ;
		           exit(0) ;
		} ;
		break ;

		case E_ENTIER:  // reconnaissance d'un entier
			switch(nature_caractere(caractere_courant())) {
			    case CHIFFRE:
		  			ajouter_caractere (lexeme_en_cours.chaine, caractere_courant()) ;
                  			lexeme_en_cours.valeur = lexeme_en_cours.valeur * 10.0 + caractere_courant() - '0';
                  	etat = E_ENTIER;
                  	avancer_car ();
					break ;
             case SYMBOLE:
         		switch (caractere_courant()){
                  case '.':
		      	    ajouter_caractere (lexeme_en_cours.chaine, caractere_courant()) ;
                   lexeme_en_cours.nature = FLOAT;
                   etat = E_FLOAT;
                   avancer_car ();
                   break;
                  default:
                   etat = E_FIN;
               }
               break;
			   default:
                  	etat = E_FIN;
          	} ;
            break;

      case E_FLOAT:
         switch(nature_caractere(caractere_courant())) {
			    case CHIFFRE:   
		  			ajouter_caractere (lexeme_en_cours.chaine, caractere_courant()) ;
               lexeme_en_cours.valeur += (caractere_courant()-'0') / ordre;
               ordre *= 10.0;
               etat = E_FLOAT;
               avancer_car ();
               break;
             default:
               etat = E_FIN;
         }
      
      case E_IDF:  // reconnaissance d'un entier
			switch(nature_caractere(caractere_courant())) {
			   case CHIFFRE:
            case LETTRE:
		  			ajouter_caractere (lexeme_en_cours.chaine, caractere_courant()) ;
               etat = E_IDF;
            	avancer_car ();
					break ;
			   default:
                     if (!strcmp(lexeme_en_cours.chaine, "ecrire"))
                     {
                        lexeme_en_cours.nature = ECRIRE;
                     }
                     if (!strcmp(lexeme_en_cours.chaine, "lire"))
                     {
                        lexeme_en_cours.nature = LIRE;
                     }
                     if (!strcmp(lexeme_en_cours.chaine, "if"))
                     {
                        lexeme_en_cours.nature = IF;
                     }
                     if (!strcmp(lexeme_en_cours.chaine, "fi"))
                     {
                        lexeme_en_cours.nature = FI;
                     }
                     if (!strcmp(lexeme_en_cours.chaine, "then"))
                     {
                        lexeme_en_cours.nature = THEN;
                     }
                     if (!strcmp(lexeme_en_cours.chaine, "else"))
                     {
                        lexeme_en_cours.nature = ELSE;
                     }
                     if (!strcmp(lexeme_en_cours.chaine, "while"))
                     {
                        lexeme_en_cours.nature = WHILE;
                     }
                     if (!strcmp(lexeme_en_cours.chaine, "do"))
                     {
                        lexeme_en_cours.nature = DO;
                     }
                     if (!strcmp(lexeme_en_cours.chaine, "done"))
                     {
                        lexeme_en_cours.nature = DONE;
                     }
                     etat = E_FIN;
          	} ;
            break;
      case E_OP:
         if (caractere_courant() == '=')
         {
            ajouter_caractere (lexeme_en_cours.chaine, caractere_courant()) ;
            switch (lexeme_en_cours.nature)
            {
            case INF:
               lexeme_en_cours.nature = INFEG;
               etat = E_FIN;
               break;
            case SUP:
               lexeme_en_cours.nature = SUPEG;
               etat = E_FIN;
               break;
            case DIFF:
               etat = E_FIN;
               break;
            case AFF:
               lexeme_en_cours.nature = EG;
               etat = E_FIN;
               break;
            default:
               break;
            }
            avancer_car();
         }
         else
         {
            if (lexeme_en_cours.nature == DIFF)
            {
               printf("\nLe caractere courant a l'erreur est : %d\n", caractere_courant());
		         printf("Erreur_Lexicale\n") ;
	            exit(0) ;
            }
            else etat = E_FIN;
            
         }
         
	   case E_FIN:  // etat final
		break ;
	    
	  } ; // fin du switch(etat)
	} ; // fin du while (etat != fin)
   }

   /* --------------------------------------------------------------------- */

   // cette fonction ajoute le caractere c a la fin de la chaine s 
   // (la chaine s est donc modifiee)
 
   void ajouter_caractere (char *s, char c) {
	int l ;
	
	l = strlen(s) ;
	s[l] = c ;
	s[l+1] = '\0' ;
   } ;

   /* --------------------------------------------------------------------- */

   Nature_Caractere nature_caractere (char c) {
	   if (fin_de_sequence_car(c)) return C_FIN_SEQUENCE;
	   if (est_chiffre(c)) return CHIFFRE;
	   if (est_symbole(c)) return SYMBOLE;
      if (est_lettre(c)) return LETTRE;
      if (est_operateur(c)) return OPERATEUR;
	   return ERREUR_CAR ;
   }
   /* --------------------------------------------------------------------- */

   // vaut vrai ssi c designe un caractere separateur
   int est_separateur(char c) { 
      return c == ' ' || c == '\t' || c == '\n' || c == '\r' ;
   }

   /* --------------------------------------------------------------------- */

   // vaut vrai ssi c designe un caractere chiffre
   int est_chiffre(char c) {
      return c >= '0' && c <= '9' ;
   }

   /* --------------------------------------------------------------------- */

   // vaut vrai ssi c designe un caractere chiffre
   int est_lettre(char c) {
      return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ;
   }

   /* --------------------------------------------------------------------- */

   // vaut vrai ssi c designe un caractere correspondant a un symbole arithmetique
   int est_symbole(char c)  {
      switch (c) {
      case '+':  
	 	case '-':  
	 	case '*':
	 	case '/':
      case '.':
      case '(':
      case ')':
      case '=':
      case ';':
            return 1;

        default:
            return 0;
      } 
   }
   
   int est_operateur(char c){
      switch (c)
      {
      case '<':
      case '>':
      case '!':   
         return 1;
      default:
         return 0;
      }
   }

   /* --------------------------------------------------------------------- */

   // renvoie la chaine de caracteres correspondant a la nature du lexeme
   char *Nature_vers_Chaine (Nature_Lexeme nature) {
	switch (nature) {
		case ENTIER: return "ENTIER" ;
      case FLOAT : return "FLOAT";
		case PLUS: return "PLUS" ;
      case MOINS: return "MOINS" ;            
      case MUL: return "MUL" ;
      case DIV: return "DIV" ;
      case PARO: return "PARO";
      case PARF: return "PARF";
      case AFF: return "AFF";
      case SEPAFF: return "SEPAFF";
      case IDF: return "IDF";
      case LIRE: return "LIRE";
      case ECRIRE: return "ECRIRE";
      case IF : return "IF";
      case THEN : return "THEN";
      case ELSE : return "ELSE";
      case SUP : return "SUP";
      case SUPEG : return "SUPEG";
      case INF : return "INF";
      case INFEG : return "INFEG";
      case EG : return "EG";
      case DIFF : return "DIFF";
      case FIN_SEQUENCE: return "FIN_SEQUENCE" ;     
      default: return "ERREUR" ;            
	} ;
   } 

   /* --------------------------------------------------------------------- */

   // affiche a l'ecran le lexeme l
   void afficher(Lexeme l) {

      switch (l.nature) {
         case FIN_SEQUENCE: 
            break;
         default: 
            printf("(ligne %d, ", l.ligne);
            printf("colonne %d) : ",l.colonne);
	    printf("[") ;
            printf("nature = %s", Nature_vers_Chaine(l.nature)) ;
            printf(", chaine = %s, ", l.chaine) ;
            switch(l.nature) {
                 case ENTIER:
                 case FLOAT:
                      printf("valeur = %f", l.valeur);
                 default:
                      break;
            } ;
	    printf("]") ;
	} ;
   }

   /* --------------------------------------------------------------------- */

