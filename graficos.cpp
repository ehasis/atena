 /*------------------------------------------------------------*
 *  graficos.cpp - Motor Grafico
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quarta-feira, 5 de setembro de 2001
*
*  Henrique em 22/01/2002
*  - Modificado AtualizarGraficos() para utilizar stretch
*    se a resolucao nao for 640x480
*
*------------------------------------------------------------*/

#include <allegro.h>
#include "graficos.h"
#include "objgraf.h"

static BITMAP *bmp_buffer;
static int executar_vsync;

/* Inicializacao do motor grafico */
void IniciarGraficos()
{
	set_trans_blender(0, 0, 0, 96);
	bmp_buffer = create_system_bitmap(640, 480);
	clear(screen);
	executar_vsync = get_config_int("video", "vsyc", 1);
}

/* Desligamento do motor grafico */
void DesligarGraficos()
{
	//Destruicao do motor
	destroy_bitmap(bmp_buffer);
}

/* Atualizacao dos graficos */
void AtualizarGraficos()
{
	DesenharObjetos(bmp_buffer);
	
	if (executar_vsync)
		vsync();
	
	if (SCREEN_W == 640)
		blit(bmp_buffer, screen, 0, 0, 0, 0, 640, 480);
	else
		stretch_blit(bmp_buffer, screen, 0, 0, 640, 480, 0, 0, SCREEN_W, SCREEN_H);
}