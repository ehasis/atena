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

static BITMAP *bmp_buffer;

/* Inicializacao do motor grafico */
void IniciarGraficos()
{
	set_trans_blender(0, 0, 0, 128);
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
	DesenharObjetos(bmp_buffer);
	vsync();
	blit(bmp_buffer, screen, 0, 0, 0, 0, 640, 480);
}