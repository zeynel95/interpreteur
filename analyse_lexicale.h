/* ------------------------------------------------------------------------
-- paquetage machine_lexemes
--
-- analyse lexicale d'une expression arithmetique
--
-- P.Habraken - 18/01/2010
--
-- 2 aout 2006 - PH :
-- remplacement record a champs variants par record "plat"
------------------------------------------------------------------------ */

   typedef enum {
	  ERREUR_CAR,   // caractere incorrect
	  CHIFFRE,			// chiffre
     LETTRE,			// caractere       
	  SYMBOLE,			// symbole,
	  OPERATEUR,	   // operateur,
      C_FIN_SEQUENCE // caractere de fin de sequence     
   } Nature_Caractere ;

   typedef enum {
      PARO,             // (
      PARF,             // )
      ENTIER,           // sequence de chiffres
      FLOAT,            // floattant
      PLUS,             // +
      MOINS,            // -
      MUL,              // *
      DIV,              // /
      IDF,              // identificateur
      AFF,              // = (symbole d'affectation)
      SEPAFF,           // \n (separateur d'affectation)
      LIRE,             //lire
      ECRIRE,           //ecrire
      IF,               //if
      FI,               // fin if
      THEN,             //then
      ELSE,             //else
      INF,              //inferieur
      INFEG,            //inferieur ou egale
      SUP,              //superieur
      SUPEG,            //superieur ou egale
      EG,               //egale
      DIFF,             //different
      WHILE,            //tan que
      DO,               //faire
      DONE,             //fin tant que
      FIN_SEQUENCE,     // pseudo lexeme ajoute en fin de sequence
    } Nature_Lexeme ;


   typedef struct { 
      Nature_Lexeme nature;    // nature du lexeme
      unsigned int ligne;           // numero de ligne
      unsigned int colonne;         // numero de colonne
      char chaine[256];           // chaine de caracteres
      float valeur;          // valeur d'un entier
   } Lexeme ; 

   void afficher(Lexeme l);

   void demarrer(char *nom_fichier);
   // e.i. : indifferent
   // e.f. : la sequence de lexemes est lue dans le fichier designe par
   //        nom_fichier
   //        fin_de_sequence <=> lexeme_courant.nature = FIN_SEQUENCE
   //        (non fin_de_sequence) => lexeme courant est le premier
   //        lexeme de la sequence
   //        l'exception Erreur_Lexicale est levee en cas d'erreur

   void avancer();
   // pre-condition : la machine sequentielle est demarree
   // e.i. : on pose i = rang du lexeme_courant :
   //        (non fin_de_sequence)
   //        et (non lexeme_courant.nature = FIN_SEQUENCE)
   // e.f. : fin_de_sequence <=> lexeme_courant.nature = FIN_SEQUENCE
   //        (non fin_de_sequence) => lexeme_courant est le lexeme i+1
   //        l'exception Erreur_Lexicale est levee en cas d'erreur

   Lexeme lexeme_courant();
   // pre-condition : la machine sequentielle est demarree
   // lexeme_courant est :
   // . le pseudo lexeme FIN_SEQUENCE si fin_de_sequence
   // . le pseudo lexeme ERREUR si une erreur a ete detectee
   // . le lexeme de rang i sinon

   int fin_de_sequence();
   // pre-condition : la machine sequentielle est demarree
   // fin_de_sequence vaut :
   // . vrai si tous les lexemes de la sequence ont ete reconnus
   // . faux sinon

   void arreter();
   // e.i. : la machine sequentielle est demarree
   // e.f. : la machine sequentielle est arretee
