 /*------------------------------------------------------------*
 *  main.c - Função Principal
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: segunda-feira, 03 de setembro de 2001
*
*  Contém a execucao das funcoes de inicializacao
*
*  Alterações:
*
*  Diego Giacomelli em 06/11/2001
*  - Inserido a chamada à install_mouse na procedure Iniciar;
*
*  Henrique em 22/01/2002
*  - Tratamento para aceitar diversos tipos de resolucao
*
*------------------------------------------------------------*/

#include <stdio.h>
#include <allegro.h>
#include "jogo.h"
#include "erro.h"
#include "vglobal.h"

/* ----- EM TESTE
volatile int contador;
void Temporizador()
{
	contador++;

} END_OF_FUNCTION(Temporizador);
/**/

static void checar_arquivo(const char *nome)
{
	char str[80];
	if (!exists(nome))
	{
		sprintf(str, "Arquivo [%s] nao encontrado.", nome);
		allegro_message(str);
		Erro(str, 0);
	}
}

/* Inicializacao Geral */
static void Iniciar()
{
	int modo_tela;
	int resolucao_x, resolucao_y;

	install_allegro(SYSTEM_AUTODETECT, &errno, atexit);
	install_keyboard();
	install_timer();
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	install_mouse();
	//install_joystick(JOY_TYPE_AUTODETECT);


	/* ----- EM TESTE
	LOCK_VARIABLE(contador);
	LOCK_FUNCTION(Temporizador);

	install_int_ex(Temporizador, BPS_TO_TIMER(60));
	/**/

	checar_arquivo("atena.ini");
	checar_arquivo("atena.dat");
	checar_arquivo("nave.dat");
	checar_arquivo("aliens.dat");
	checar_arquivo("tiros.dat");

	set_config_file("atena.ini");

	// definicao do modo de video
	switch(get_config_int("video", "modo", 1))
	{
		case  1: modo_tela = GFX_AUTODETECT_FULLSCREEN; break;
		case  2: modo_tela = GFX_AUTODETECT_WINDOWED; break;
		case  3: modo_tela = GFX_DIRECTX; break;
		case  4: modo_tela = GFX_DIRECTX_OVL; break;
		case  5: modo_tela = GFX_DIRECTX_WIN; break;
		case  6: modo_tela = GFX_DIRECTX_SAFE; break;
		case  7: modo_tela = GFX_DIRECTX_SOFT; break;
		case  8: modo_tela = GFX_DIRECTX_ACCEL; break;
		case  9: modo_tela = GFX_GDI; break;
		case 10: modo_tela = GFX_SAFE; break;
		default: modo_tela = GFX_AUTODETECT;
	}

	// definicao da resolucao
	switch (get_config_int("video", "resolucao", 1))
	{
		case 0:	 resolucao_x=320; resolucao_y=240; break;
		case 2:	 resolucao_x=800; resolucao_y=600; break;
		default: resolucao_x=640; resolucao_y=480;
	}

	set_color_depth(16);
	if (set_gfx_mode(modo_tela, resolucao_x, resolucao_y, 0, 0) < 0)
		Erro("Nao foi possivel definir o modo grafico", allegro_error);

}

/* Execucao das rotinas do jogo */
static void Executar()
{
	IniciarJogo();
	ExecutarJogo();
	DesligarJogo();
}

/* Finalizacao Geral */
static void Desligar()
{
	allegro_exit();
}

/* Funcao de entrada */
int main(int argc, char *argv[])
{

	Iniciar();
	Executar();
	Desligar();

	return TRUE;

}
#ifndef DJGPP
	END_OF_MAIN();
#endif


/*******************************************************************/