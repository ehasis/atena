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
	rect(    bmp, x,   y,   x + l,                   y + 8, makecol(255,255,255));
	rectfill(bmp, x,   y,   x + l - 1,               y + 7, makecol(0,0,0));
	rectfill(bmp, x+1, y+1, x + ((percent*100)/l)-1, y + 7, makecol(255,(percent*255)/100,0));
}

void escrever(BITMAP *bmp, const char *str, int x, int y, int cor)
{
	textout(bmp, font, str, x+1,   y+1,  makecol(0,0,0));
	textout(bmp, font, str, x, y,cor);
}