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

/* Inicializacao Geral */
static void Iniciar()
{
	install_allegro(SYSTEM_AUTODETECT, &errno, atexit);
	install_keyboard();
	install_timer();
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	set_config_file("atena.ini");
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