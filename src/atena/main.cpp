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


#include "callegro.h"
#include "cjogo.h"

int main(int argc, char *argv[])
{

	allegro_init();
	install_timer();
	install_mouse();
	install_keyboard();
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);

	set_uformat(U_ASCII);
	alfont_init();
	alfont_text_mode(-1);
/*
	
	set_color_depth(16);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 320, 240, 0, 0);


	
	fonte = alfont_load_font("dat/lucon.ttf");
	alfont_set_font_size(fonte, 18);

	GADados dados;
	dados.Abrir("dat/aliens/indice.txt");
	blit(dados.Bitmap(0), screen, 0, 0, 0, 0, 100, 100);
	alfont_textout_aa(screen, fonte, "Puta merda isto é um teste", 10, 10, makecol(255,255,0));

	readkey();

	dados.Fechar();
	alfont_destroy_font(fonte);

/**/

/**/
	remove("log.txt");

	CJogo atena;

	atena.Iniciar();
	atena.Executar();
	atena.Finalizar();

/**/
	alfont_exit();
	allegro_exit();

	return 0;

} END_OF_MAIN();
