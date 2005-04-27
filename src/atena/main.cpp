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

	remove("log.txt");

	CJogo* atena = new CJogo();

	atena->Iniciar();
	atena->Executar();
	atena->Finalizar();

	delete atena;

	alfont_exit();
	allegro_exit();

	return 0;

} END_OF_MAIN();
