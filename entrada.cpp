 /*------------------------------------------------------------*
 *  entrada.cpp - Manipulacao de Entradas
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quarta-feira, 5 de setembro de 2001
*
*  
*
*------------------------------------------------------------*/

#include <allegro.h>

#include "entrada.h"
#include "vglobal.h"
#include "erro.h"
#include "centrada.h"

struct TEntrada entrada1;
struct TEntrada entrada2;

void IniciarEntrada()
{
	entrada1.x = 0;
	entrada1.y = 0;
	entrada1.a = 0;
	entrada1.b = 0;
	entrada1.c = 0;

	entrada2.x = 0;
	entrada2.y = 0;
	entrada2.a = 0;
	entrada2.b = 0;
	entrada2.c = 0;
	
	while (joy[0].flags & JOYFLAG_CALIBRATE) 
		if (calibrate_joystick(0) != 0)
			Erro("Erro ao calibrar o controle", 0);
}

void DesligarEntrada()
{
	//Implementar
}

void AtualizarEntrada()
{
	int x = 0, y = 0, a = 0, b = 0, c = 0;
	
	if (key[KEY_ESC]) final_jogo = 1;

	/* Leitura das Teclas */
	if (key[KEY_UP])		y--;
	if (key[KEY_DOWN])		y++;
	if (key[KEY_LEFT])		x--;
	if (key[KEY_RIGHT])		x++;
	if (key[KEY_SPACE])		a = 1;
	if (key[KEY_MINUS_PAD]) b = 1; 
	if (key[KEY_PLUS_PAD])  c = 1; 

	/*
	poll_joystick();
	
	if (joy_up)			y--;
	if (joy_down)		y++;
	if (joy_left)		x--;
	if (joy_right)		x++;
	if (joy_b1)			a = 1;
	/**/
	
	//Atualizacao da estrutura
	entrada1.x = x;
	entrada1.y = y;
	entrada1.a = a;
	entrada1.b = b;
	entrada1.c = c;
	
}
