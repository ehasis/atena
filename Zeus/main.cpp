#include <stdio.h>
#include <allegro.h>
#include "..\erro.h"
#include "zeus.h"


/* Inicializacao Geral */
static void Iniciar()
{
	int modo_tela;

	install_allegro(SYSTEM_AUTODETECT, &errno, atexit);
	install_keyboard();
	install_timer();
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	install_mouse();
	set_config_file("zeus.ini");

	/* definicao do modo de video */
	if (get_config_int("video", "modo", 1) == 1)
		modo_tela = GFX_AUTODETECT;
	else
		
		modo_tela = GFX_DIRECTX_WIN;

	set_color_depth(16);
	
	if (set_gfx_mode(modo_tela, 640, 480, 0, 0) < 0)
		Erro("Nao foi possivel definir o modo grafico", allegro_error);

	CLog::Iniciar();
	CLog::SetarVisivel(get_config_int("jogo", "console", 0));
}

/* Execucao das rotinas do jogo */
static void Executar()
{
	Log("Iniciando Zeus ...");
	IniciarZeus();
	Log("Zeus iniciado.");

	Log("Executando Zeus ...");
	ExecutarZeus();
	Log("Zeus executado.");

	Log("Desligando Zeus ...");
	DesligarZeus();
}


/* Finalizacao Geral */
static void Desligar()
{
	CLog::Desligar();
	allegro_exit();
}

int main(int argc, char *argv[])
{
	remove("log.txt");

	Iniciar();
	Executar();
	Desligar();


	return TRUE;

}

#ifndef DJGPP
	END_OF_MAIN();
#endif