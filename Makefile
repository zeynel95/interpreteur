all:  calculette calculette_grammaire test_lexeme test_symbole

essai_ast: ast_construction.o  ast_parcours.o  essai_ast.o  
	gcc -g -Wall -o essai_ast ast_construction.o  ast_parcours.o  essai_ast.o

ast_construction.o: ast_construction.c type_ast.h
	gcc -g -Wall -c ast_construction.c

ast_parcours.o: ast_parcours.c type_ast.h ast_construction.h table_symbole.h
	gcc -g -Wall -c ast_parcours.c

essai_ast.o: essai_ast.c  ast_construction.h  ast_parcours.h  type_ast.h
	gcc -g -Wall -c essai_ast.c

test_lexeme: analyse_lexicale.o  lecture_caracteres.o  test_lexeme.o
	gcc -g -Wall -o test_lexeme analyse_lexicale.o  lecture_caracteres.o  test_lexeme.o

calculette: analyse_syntaxique.o analyse_lexicale.o lecture_caracteres.o calculette.o
	gcc -g -Wall -o calculette analyse_syntaxique.o analyse_lexicale.o  lecture_caracteres.o calculette.o
	
calculette_grammaire: analyse_syntaxique_grammaire.o analyse_lexicale.o lecture_caracteres.o calculette_grammaire.o ast_parcours.o ast_construction.o table_symbole.o
	gcc -g -Wall -o calculette_grammaire analyse_syntaxique_grammaire.o analyse_lexicale.o  lecture_caracteres.o calculette_grammaire.o ast_parcours.o ast_construction.o table_symbole.o

analyse_syntaxique_grammaire.o: analyse_syntaxique_grammaire.c analyse_syntaxique_grammaire.h analyse_lexicale.h lecture_caracteres.h type_ast.h ast_construction.h table_symbole.h
	gcc -g -Wall -c analyse_syntaxique_grammaire.c

analyse_syntaxique.o: analyse_syntaxique.c analyse_syntaxique.h analyse_lexicale.h lecture_caracteres.h
	gcc -g -Wall -c analyse_syntaxique.c

analyse_lexicale.o: analyse_lexicale.c analyse_lexicale.h lecture_caracteres.h
	gcc -g -Wall -c analyse_lexicale.c

lecture_caracteres.o: lecture_caracteres.h lecture_caracteres.c
	gcc -g -Wall -c lecture_caracteres.c

test_lexeme.o: analyse_lexicale.h
	gcc -g -Wall -c test_lexeme.c

calculette.o : analyse_syntaxique.h analyse_lexicale.h
	gcc -g -Wall -c calculette.c

calculette_grammaire.o : analyse_syntaxique_grammaire.h analyse_lexicale.h type_ast.h ast_parcours.h
	gcc -g -Wall -c calculette_grammaire.c

table_symbole.o : table_symbole.c table_symbole.h
	gcc -g -Wall -c table_symbole.c

test_symbole.o : test_symbole.c table_symbole.h
	gcc -g -Wall -c test_symbole.c

test_symbole : test_symbole.o table_symbole.o
	gcc -g -Wall -o test_symbole test_symbole.o table_symbole.o

clean:
	rm -f *.o essai_ast calculette calculette_grammaire test_lexeme test_symbole

