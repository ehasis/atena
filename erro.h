 /*------------------------------------------------------------*
 *  erro.h - Cabecalho para manipulacao de erro
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: terça-feira, 4 de setembro de 2001
*
*  Alteracoes:
*  Diego Giacomelli em 20/12/2001
*   - Implementação da procedure LogX;
*
*------------------------------------------------------------*/

#ifndef erro_h_incluido
#define erro_h_incluido

void ErroX(char *arquivo, int linha, char *s1, char *s2);
#define Erro(a, b) ErroX(__FILE__, __LINE__, a, b)

void LogX(char *arquivo, int linha, char *texto);
#define Log(a) LogX(__FILE__, __LINE__, a)
#endif