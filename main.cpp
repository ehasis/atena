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

#include <iostream>
#include <stdio.h>
#include <allegro.h>
#include "cjogo.h"
#include "ccolecao.h"
#include "ccolecaoavancada.h"

int main(int argc, char *argv[])
{
	char buf[80], c[5];

	install_allegro(SYSTEM_AUTODETECT, &errno, atexit);
	install_keyboard();
	install_timer();
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	install_mouse();

	CJogo atena;
	
	remove("log.txt");

	atena.Iniciar();
	atena.Executar();
	atena.Desligar();
/*
	CColecao< char > texto;
	texto.AdicionarFim('1');
	texto.AdicionarFim('2');
	texto.AdicionarFim('3');
	texto.AdicionarFim('4');
	texto.AdicionarFim('5');
	
	texto.RemoverTodos();
	texto.AdicionarFim('0');
	texto.MoverUltimo();
	c[0] = texto.Obter();
	c[1] = texto.Obter();
	c[2] = texto.Obter();
	c[3] = texto.Obter();
	c[4] = texto.Obter();
	
	
	texto.Adicionar('6', 2);
	texto.Adicionar('7', 4);
	texto.Adicionar('8', 6);
	texto.Adicionar('9', 8);
	texto.Adicionar('10', 10);
	texto.Adicionar('11', 1);
	texto.Adicionar('1');
	texto.Adicionar('2');
	texto.Adicionar('3');
	texto.Adicionar('4');
	texto.Adicionar('5');
	texto.AdicionarFim('1');
	texto.AdicionarFim('2');
	texto.AdicionarFim('3');
	texto.AdicionarFim('4');
	texto.AdicionarFim('5');

	
	sprintf(buf, "%c%c%c%c%c", c[0], c[1], c[2], c[3], c[4]);
	escrever(screen, buf, 50, 50, makecol(255, 0, 0));
	rest(2000);
/**/	
	allegro_exit();
	
	return 0;

} END_OF_MAIN();