 /*------------------------------------------------------------*
 *  main.c - Função Principal
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: sexta-feira, 19 de outubro de 2001
*
*  Contém a execucao das funcoes de inicializacao
*
*------------------------------------------------------------*/

#include <stdio.h>
#include <allegro.h>
#include "ceditor.h"

int main(int argc, char *argv[])
{
	install_allegro(SYSTEM_AUTODETECT, &errno, atexit);
	install_keyboard();
	//install_timer();
	//install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	install_mouse();

	CEditor zeus;

	remove("log.txt");
	
	Log("zeus.Iniciar();");
	zeus.Iniciar();
	Log("zeus.Executar();");
	zeus.Executar();
	Log("zeus.Finalizar();");
	zeus.Finalizar();

	Log("allegro_exit(); 1");
	allegro_exit();
	Log("allegro_exit(); 2");
	return 0;

} END_OF_MAIN();
