 /*------------------------------------------------------------*
 *  funcoes.cpp - Funcoes Genericas
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: sexta-feira, 21 de setembro de 2001
*
*  
*
*------------------------------------------------------------*/

#include <allegro.h>
#include "funcoes.h"

void barra_progresso(BITMAP *bmp, int x, int y, int l, int percent)
{
	rectfill(bmp, x+1, y+1, x+l+1, y + 9, 10);
	rectfill(bmp, x, y, x + ((percent*100)/l), y + 8, 49);
	rect(bmp, x, y, x+l, y + 8, 255);
}
