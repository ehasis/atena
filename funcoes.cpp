 /*------------------------------------------------------------*
 *  funcoes.cpp - Funcoes Genericas
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: sexta-feira, 21 de setembro de 2001
*
*
*------------------------------------------------------------*/


#include "funcoes.h"

static unsigned int cor_mascara = 0xF7DEF7DE;
static unsigned int pixel_baixo_mascara = 0x08210821;

#define INTERPOLAR(A, B) ((((A & cor_mascara) >> 1) + ((B & cor_mascara) >> 1) + (A & B & pixel_baixo_mascara)))


void barra_progresso_atena(CTela & tela, int x, int y, int l, int percent)
{
	tela.Rect(eCamadaEfeitos, x,   y,   x + l,                   y + 8, makecol(255,255,255));
	tela.RectFill(eCamadaEfeitos, x,   y,   x + l - 1,               y + 7, makecol(0,0,0));
	tela.RectFill(eCamadaEfeitos, x+1, y+1, x + ((percent*l)/100)-1, y + 7, makecol(255,(percent*255)/100,0));
}

void barra_progresso_atena2(CTela & tela, int x, int y, int l, int percent)
{
	tela.RectFill(eCamadaEfeitos, x, y, x + l,                 y + 4, makecol(0,0,0));
	tela.RectFill(eCamadaEfeitos, x, y, x + ((percent*l)/100), y + 4, makecol(255,(percent*255)/100,0));
}

void barra_progresso_zeus(CTela & tela, int x1, int y1, int x2, int y2, int maximo, int valor_anterior, int valor_atual, int cor)
{
	int pos;

	if(((valor_atual / ((maximo / 100) + 1))) == 1 || (valor_atual / ((maximo / 100) + 1)) != (valor_anterior / ((maximo / 100) + 1)))
	{
		pos = valor_atual / ((maximo / 100) + 1);
		tela.Rect(eCamadaEfeitos, x1, y1, x2, y2, makecol(255, 255, 255));
		tela.RectFill(eCamadaEfeitos, x1 + 1,   y1 + 1,   x2 - 1, y2 - 1, makecol(0, 0, 0));
		tela.RectFill(eCamadaEfeitos, x1 + 1, y1 + 1, x1 + (((x2 - x1) / 100) * pos), y2 - 1, cor);
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


void SuavizarBitmap(BITMAP *bmp)
{
	int y, x;
	char *linha;
	unsigned short *slinha;


	if (bitmap_color_depth(bmp) != 16)
	{
		return;
	}

	linha = (char *)malloc(sizeof(short) * (bmp->w + 2));

	if (!linha)
	{
		return;
	}

	acquire_bitmap(bmp);


	for (y = 0; y < bmp->h; y++)
	{
        unsigned int cor1, cor2, cor3, d;
        int endereco_linha;

		bmp_select(bmp);
		endereco_linha = bmp_read_line(bmp, y);

		for (x = 0; x < (int)(bmp->w * sizeof(short)); x += sizeof(long))
		{
			*((unsigned long *) &linha[x]) = bmp_read32(endereco_linha + x);
        }

        slinha = (unsigned short *)linha;

		bmp_select(bmp);

		d = bmp_write_line(bmp, y);

		for (x = 0; x < bmp->w - 2; x += 2)
		{
			unsigned int produto;
			cor1 = slinha[x];
			cor2 = slinha[x + 1];
			cor3 = slinha[x + 2];
			produto = (INTERPOLAR(cor2, cor3) << 16 | INTERPOLAR(cor2, cor1));

			bmp_write32(d, produto);
			d += sizeof(int);
		}
	}
	bmp_unwrite_line(bmp);
	release_bitmap(bmp);

	free(linha);

	return;
}
