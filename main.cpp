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
*   - Inserido a chamada à install_mouse na procedure Iniciar;
*
*  Henrique em 22/01/2002
*   - Tratamento para aceitar diversos tipos de resolucao
*
*  Henrique em 08/02/2002
*   - Incluido Log em modo Console
*
*  Henrique em 23/02/2002
*   - Convertido para POO e encapsulado tudo dentro de CJogo
*
*------------------------------------------------------------*/

#include <stdio.h>
#include <allegro.h>
#include "cjogo.h"

int main(int argc, char *argv[])
{
	
	install_allegro(SYSTEM_AUTODETECT, &errno, atexit);
	install_keyboard();
	install_timer();
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	install_mouse();
	set_uformat(U_ASCII); 

	CJogo atena;
	
	remove("log.txt");

	atena.Iniciar();
	atena.Executar();
	atena.Desligar();

/*	CEfeito efeitos;
	BITMAP *bmp;
	
	//allegro_init();
	//set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0);
	install_keyboard();
	install_timer();
	install_mouse();
	show_mouse(screen);

	bmp = create_bitmap(LARGURA_TELA, ALTURA_TELA);

    //InitGraphics();
	efeitos.IniciarExplosao();
	for(;;)
	{
		efeitos.DesenharExplosao(bmp, 100, 100);
		blit(bmp, screen, 0, 0, 0, 0, LARGURA_TELA, ALTURA_TELA);

		if(key[KEY_K])
		{			
			efeitos.KaBoom(LARGURA_TELA/2, ALTURA_TELA/2);
			//KaBoom(100, 100);
		   	
		}
		else if(key[KEY_ESC]) break;
    }
	*/
	allegro_exit();
	
	return 0;

} END_OF_MAIN();