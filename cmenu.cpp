 /*------------------------------------------------------------*
 *  cmenu.cpp - Classe para criacao de Menus
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quinta-feira, 19 de julho de 2001
*
*  Henrique em 21/02/2002
*   - Vide cmenu.h
*
*
*------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <allegro.h>
#include "cmenu.h"
#include "atena.h"

//------------------------------------------------------------
// Constructors
CMenuH::CMenuH()
{
	x 			= 0;
	y			= 0;
	fonte		= font;
	cor_texto	= makecol(255,255,255);
	cor_selecao	= makecol(255,255,0);
	num_itens	= 0;
	pos_atual	= 0;
	alinhamento	= eAlinharEsquerda;
	cp_screen	= create_bitmap(SCREEN_W, SCREEN_H);
	bmp_menu	= create_bitmap(SCREEN_W, SCREEN_H);
}

//------------------------------------------------------------
CMenuH::CMenuH(FONT *_fonte, int _cor_texto, int _cor_selecao)
{
	x 			= 0;
	y			= 0;
	fonte		= _fonte;
	cor_texto	= _cor_texto;
	cor_selecao	= _cor_selecao;
	num_itens	= 0;
	pos_atual	= 0;
	alinhamento = eAlinharEsquerda;
	cp_screen	= create_bitmap(SCREEN_W, SCREEN_H);
	bmp_menu	= create_bitmap(SCREEN_W, SCREEN_H);
}

//------------------------------------------------------------
CMenuH::CMenuH(FONT *_fonte, int _cor_texto, int _cor_selecao, int _x, int _y)
{
	x 			= _x;
	y			= _y;
	fonte		= _fonte;
	cor_texto	= _cor_texto;
	cor_selecao	= _cor_selecao;
	num_itens	= 0;
	pos_atual	= 0;
	alinhamento	= eAlinharEsquerda;
	cp_screen	= create_bitmap(SCREEN_W, SCREEN_H);
	bmp_menu	= create_bitmap(SCREEN_W, SCREEN_H);
}


//------------------------------------------------------------
// Destructor
CMenuH::~CMenuH()
{
	destroy_bitmap(cp_screen);
	destroy_bitmap(bmp_menu);
}

//------------------------------------------------------------
// Adiciona um novo item ao menu
void CMenuH::Adicionar(const char *_texto)
{
	num_itens++;
	strcpy(menu[num_itens - 1], _texto);
}

//------------------------------------------------------------
// Exibe o menu e aguarda entrada do usuario
int CMenuH::Executar()
{
	int sair = 0;
	int retorno = -1;
	int tecla, i;

	//Limpa o buffer de teclas pressionadas
	//rest(50);
	clear_keybuf();
	text_mode(-1);

	//Copia da Tela
	blit(screen, cp_screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	do {
		for (i = 0; i < num_itens; i++)
		{
			Escrever(screen, menu[i], i, (pos_atual == i ? cor_selecao : cor_texto));
		}

		tecla = readkey() >> 8;
		switch (tecla)
		{
			case KEY_UP:
				pos_atual--;
				break;

			case KEY_DOWN:
				pos_atual++;
				break;

			case KEY_ESC:
				retorno = -1;
				sair = 1;
				break;

			case KEY_ENTER:
				retorno = pos_atual;
				sair = 1;
				break;
		}

		if (pos_atual < 0) pos_atual = num_itens - 1;
		if (pos_atual >= num_itens) pos_atual = 0;

	} while (!sair);

	//Retorna o estado origina da tela
	blit(cp_screen, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	return retorno;
}

//------------------------------------------------------------
// Escreve o texto no bitmap como parametro
void CMenuH::Escrever(BITMAP *_bmp, char *_texto, int _linha, int _cor)
{
	int linha = (_linha * fonte->height) + (font->height / 3);
	switch (alinhamento)
	{
		case eAlinharEsquerda:
			textout(_bmp, fonte, _texto, x, y + linha , _cor);
			break;

		case eAlinharDireita:
			textout_right(_bmp, fonte, _texto, x, y + linha, _cor);
			break;

		case eAlinharCentro:
			textout_centre(_bmp, fonte, _texto, x, y + linha, _cor);
			break;
	}
}

//------------------------------------------------------------
void CMenuH::SetarAlinhamento(EAlinhamentoMenu _alinhamento)
{
	alinhamento = _alinhamento;
}

//------------------------------------------------------------
void CMenuH::SetarFonte(FONT *_fonte)
{
	fonte = _fonte;
}

//------------------------------------------------------------
void CMenuH::SetarCorTexto(int _cor_texto)
{
	cor_texto = _cor_texto;
}

//------------------------------------------------------------
void CMenuH::SetarCorSelecao(int _cor_selecao)
{
	cor_selecao = _cor_selecao;
}

//------------------------------------------------------------
void CMenuH::SetarX(int _x)
{
	x = _x;
}

//------------------------------------------------------------
void CMenuH::SetarY(int _y)
{
	y = _y;
}

//------------------------------------------------------------
void CMenuH::SetarTexto(int _indice, const char *_texto)
{
	if (_indice >= 0 && _indice < num_itens)
	{
		sprintf(menu[_indice], _texto);
	}
}

//------------------------------------------------------------
void CMenuH::SetarNumeroItens(int _numero_itens)
{
	num_itens = _numero_itens;
}