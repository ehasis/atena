 /*------------------------------------------------------------*
 *  main.c - Função Principal
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: segunda-feira, 03 de setembro de 2001
*
*  Contém a execucao das funcoes de inicializacao
*
*  11/07/2001
*  - 
*
*------------------------------------------------------------*/

#include <allegro.h>
#include "jogo.h"
#include "erro.h"

/* Inicializacao Geral */
static void Iniciar()
{
	int modo_tela;

	install_allegro(SYSTEM_AUTODETECT, &errno, atexit);
	install_keyboard();
	install_timer();
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	set_config_file("atena.ini");

	// definicao do modo de video
	if (get_config_int("video", "modo", 1) == 1)
		modo_tela = GFX_AUTODETECT;
	else
		modo_tela = GFX_DIRECTX_WIN;

	set_color_depth(16);
	
	if (set_gfx_mode(modo_tela, 640, 480, 0, 0) < 0)
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