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
#include <string.h>
#include "funcoes.h"
#include <stdio.h>


void barra_progresso_atena(BITMAP *bmp, int x, int y, int l, int percent)
{
	rect(    bmp, x,   y,   x + l,                   y + 8, makecol(255,255,255));
	rectfill(bmp, x,   y,   x + l - 1,               y + 7, makecol(0,0,0));
	rectfill(bmp, x+1, y+1, x + ((percent*l)/100)-1, y + 7, makecol(255,(percent*255)/100,0));
}

void barra_progresso_atena2(BITMAP *bmp, int x, int y, int l, int percent)
{
	rectfill(bmp, x, y, x + l,                 y + 4, makecol(0,0,0));
	rectfill(bmp, x, y, x + ((percent*l)/100), y + 4, makecol(255,(percent*255)/100,0));
}

void barra_progresso_zeus(BITMAP *bmp, int x1, int y1, int x2, int y2, int maximo, int valor_anterior, int valor_atual, int cor)
{
	int pos;

	if(((valor_atual / ((maximo / 100) + 1))) == 1 || (valor_atual / ((maximo / 100) + 1)) != (valor_anterior / ((maximo / 100) + 1)))
	{
		pos = valor_atual / ((maximo / 100) + 1);
		rect(bmp, x1, y1, x2, y2, makecol(255, 255, 255));
		rectfill(bmp, x1 + 1,   y1 + 1,   x2 - 1, y2 - 1, makecol(0, 0, 0));
		rectfill(bmp, x1 + 1, y1 + 1, x1 + (((x2 - x1) / 100) * pos), y2 - 1, cor);
	}
}

void escrever(BITMAP *bmp, const char *str, int x, int y, int cor)
{
	textout(bmp, font, str, x+1,   y+1,  makecol(0,0,0));
	textout(bmp, font, str, x, y,cor);
}

void escrever(BITMAP *bmp, const char *str, int x, int y, int cor, int cor_sombra)
{
	textout(bmp, font, str, x+1,   y+1,  cor_sombra);
	textout(bmp, font, str, x, y,cor);
}