 /*------------------------------------------------------------*
 *  cmenu.cpp - Classe para criacao de Menus
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quinta-feira, 19 de julho de 2001
*
*  
*
*
*------------------------------------------------------------*/

#include <string.h>
#include <allegro.h>
#include "cmenu.h"
#include "atena.h"

/* Constructor */
CMenuH::CMenuH(FONT *_fonte, int _cor_texto, int _cor_selecao)
{
	fonte		= _fonte;
	cor_texto	= _cor_texto;
	cor_selecao = _cor_selecao;
	cp_screen	= create_bitmap(SCREEN_W, SCREEN_H);
	bmp_menu	= create_bitmap(SCREEN_W, SCREEN_H);
	num_itens	= 0;
	pos_atual	= 0;
}

/* Destructor */
CMenuH::~CMenuH()
{
	destroy_bitmap(cp_screen);
	destroy_bitmap(bmp_menu);
}

/* Adiciona um novo item ao menu */
void CMenuH::Adicionar(const char *texto)
{
	num_itens++;
	strcpy(menu[num_itens - 1], texto);
}

int CMenuH::Executar()
{
	int sair = 0;
	int ret, ch, i;

	//Limpa o buffer de teclas pressionadas
	//rest(50);
	clear_keybuf();
	text_mode(-1);

	//Copia da Tela
	blit(screen, cp_screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	do {
		for (i = 0; i < num_itens; i++)
		{
			if (pos_atual == i)
				textout_centre(screen, fonte, menu[i], SCREEN_W/2, (i * 36) + 200, cor_selecao);
			else
				textout_centre(screen, fonte, menu[i], SCREEN_W/2, (i * 36) + 200, cor_texto);
		}

		ch = readkey() >> 8;
		switch (ch)
		{
		case KEY_UP:
			pos_atual--;
			break;
		
		case KEY_DOWN:
			pos_atual++;
			break;
		
		case KEY_ESC:
			ret = -1;
			sair = 1;
			break;
		
		case KEY_ENTER:
			ret = pos_atual;
			sair = 1;
			break;
		}

		if (pos_atual < 0) pos_atual = num_itens - 1;
		if (pos_atual >= num_itens) pos_atual = 0;
	} while (!sair);

	//Retorna o estado origina da tela
	blit(cp_screen, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	return ret;
}