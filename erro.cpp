 /*------------------------------------------------------------*
 *  erro.cpp - Manipulacao de erros
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: terça-feira, 4 de setembro de 2001
*
*  
*
*------------------------------------------------------------*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "erro.h"

void ErroX(char *arquivo, int linha, char *s1, char *s2)
{
	FILE *f;

	f = fopen("erro.txt", "a");
	
	fprintf(f, "Erro critico:\n");
	fprintf(f, "%s: %d: %s", arquivo, linha, s1);
	
	if (s2)
		fprintf(f, " (%s)", s2);

	fprintf(f, "\n");
	
	fclose(f);
	exit(EXIT_FAILURE);
}