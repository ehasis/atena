 /*------------------------------------------------------------*
 *  graficos.cpp - Motor Grafico
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quarta-feira, 5 de setembro de 2001
*
*  
*
*------------------------------------------------------------*/

#include <allegro.h>

#include "graficos.h"
#include "objgraf.h"
#include "erro.h"

BITMAP *bmp_buffer;

/* Inicializacao do motor grafico */
void IniciarGraficos()
{
	//if (set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0) < 0)
	if (set_gfx_mode(GFX_DIRECTX_WIN, 640, 480, 0, 0) < 0)
		Erro("Nao foi possivel definir o modo grafico", allegro_error);	

	bmp_buffer = create_bitmap(640, 480);
	clear(screen);
}

/* Desligamento do motor grafico */
void DesligarGraficos()
{
	//Destruicao do motor
	fade_out(5);
	destroy_bitmap(bmp_buffer);
}

/* Atualizacao dos graficos */
void AtualizarGraficos()
{
	vsync();
	DesenharObjetos(bmp_buffer);
	blit(bmp_buffer, screen, 0, 0, 0, 0, 640, 480);
}