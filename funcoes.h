 /*------------------------------------------------------------*
 *  funcoes.h - Cabecalho com as Funcoes Genericas
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: sexta-feira, 21 de setembro de 2001
*
*  Alterações:
*  Diego Giacomelli em 04/11/2001
*   - Alterado o nome da procedure barra_progresso para
*     barra_progresso_atena;
*   - Implementação da procedure barra_progresso_zeus;
*
*  Henrique em 02/02/2002
*   - Implementação da função SuavizarBitmap()
*
*
*------------------------------------------------------------*/

#ifndef funcoes_h_incluido
#define funcoes_h_incluido

#include "ctela.h"

void barra_progresso_atena(CTela &_tela, int x, int y, int l, int percent);
void barra_progresso_atena2(CTela &_tela, int x, int y, int l, int percent);
void barra_progresso_zeus(CTela &_tela, int x1, int y1, int x2, int y2, int maximo, int valor_anterior, int valor_atual, int cor);
void escrever(BITMAP *bmp, const char *str, int x, int y, int cor);
void escrever(BITMAP *bmp, const char *str, int x, int y, int cor, int cor_sombra);
void SuavizarBitmap(BITMAP *bmp);

#endif