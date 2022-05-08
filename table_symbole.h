/*
    MODULE QUI GERE LES VARIABLES ET LEURS VALEURS
*/


//************************************************

/*
    TYPE STRUCTUREE NOM DE LA VARIABLE AVEC SA VALEUR
*/

typedef struct
{
    char nom[100];
    int val;
} symbole;

// tableau qui va contenir toute nos variables avec leur valeurs

typedef symbole* table_symbole;

//**************************************************


/*
    Signature des fonction liee a la table des symbole
*/

// ajoute le symbole et le met a jour si il existe deja

void ajouter_symbole(symbole s, table_symbole t);

symbole cree_symbole(char* nom, int val);

void afficher_table(table_symbole t);

void init_table(table_symbole t, int taille_table);

int chercher(char* var, int* v, table_symbole t);

