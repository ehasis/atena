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
*  Henrique Andreassy em 02/02/2002
*   - Implementação da função SuavizarBitmap()
*
*  Diego Giacomelli em 13/02/2002
*   - Alterados as procedures de barras de progresso para
*     aceitar CTela;
*
*  Henrique Andreassy em 23/07/2002
*	- Modificado barra_status_* para pintar somente quando 
*	  a porcentagem for maior que zero
*
*------------------------------------------------------------*/

#ifndef funcoes_h_incluido
#define funcoes_h_incluido

#include "callegro.h"
#include "ctela.h"

void barra_progresso_atena(CTela & tela, int x, int y, int l, int percent);
void barra_progresso_atena2(CTela & tela, int x, int y, int l, int percent);
void barra_progresso_zeus(CTela & tela, int x1, int y1, int x2, int y2, int maximo, int valor_anterior, int valor_atual, int cor);
void escrever(BITMAP *bmp, const char *str, int x, int y, int cor);
void escrever(BITMAP *bmp, const char *str, int x, int y, int cor, int cor_sombra);
void SuavizarBitmap(BITMAP *bmp);

#endif

