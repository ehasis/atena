 /*------------------------------------------------------------*
 *  funcoes.h - Cabecalho com as Funcoes Genericas
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: sexta-feira, 21 de setembro de 2001
*
*  Alterações:
*  Diego Giacomelli em 04/11/2001
*  	- Alterado o nome da procedure barra_progresso para
*	  barra_progresso_atena;
*   - Implementação da procedure barra_progresso_zeus;
*
*
*------------------------------------------------------------*/

#ifndef funcoes_h_incluido
#define funcoes_h_incluido

void barra_progresso_atena(BITMAP *bmp, int x, int y, int l, int percent);
void barra_progresso_atena2(BITMAP *bmp, int x, int y, int l, int percent);
void barra_progresso_zeus(BITMAP *bmp, int x1, int y1, int x2, int y2, int maximo, int valor_anterior, int valor_atual, int cor);
void escrever(BITMAP *bmp, const char *str, int x, int y, int cor);
void escrever(BITMAP *bmp, const char *str, int x, int y, int cor, int cor_sombra);
void InserirBarra(char string[]);

#endif