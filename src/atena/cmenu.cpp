 /*------------------------------------------------------------*
 *  cmenu.cpp - Classe para criacao de Menus
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quinta-feira, 19 de julho de 2001
*
*
*------------------------------------------------------------*/

#include "cmenu.h"
#include "atena.h"

//------------------------------------------------------------
// CLASSE CMenuH
//------------------------------------------------------------


//------------------------------------------------------------
// Constructors
CMenuH::CMenuH()
{
	m_x 		= 0;
	m_y			= 0;
	m_fonte		= font;
	m_cor_texto	= makecol(255,255,255);
	m_cor_selecao	= makecol(255,255,0);
	m_num_itens	= 0;
	m_pos_atual	= 0;
	m_alinhamento	= eAlinharEsquerda;
	m_cp_screen	= create_bitmap(SCREEN_W, SCREEN_H);
	m_bmp_menu	= create_bitmap(SCREEN_W, SCREEN_H);
}

//------------------------------------------------------------
CMenuH::CMenuH(FONT * fonte, int cor_texto, int cor_selecao)
{
	m_x 			= 0;
	m_y			= 0;
	m_fonte		= fonte;
	m_cor_texto	= cor_texto;
	m_cor_selecao	= cor_selecao;
	m_num_itens	= 0;
	m_pos_atual	= 0;
	m_alinhamento = eAlinharEsquerda;
	m_cp_screen	= create_bitmap(SCREEN_W, SCREEN_H);
	m_bmp_menu	= create_bitmap(SCREEN_W, SCREEN_H);
}

//------------------------------------------------------------
CMenuH::CMenuH(FONT * fonte, int cor_texto, int cor_selecao, int x, int y)
{
	m_x 			= x;
	m_y			= y;
	m_fonte		= fonte;
	m_cor_texto	= cor_texto;
	m_cor_selecao	= cor_selecao;
	m_num_itens	= 0;
	m_pos_atual	= 0;
	m_alinhamento	= eAlinharEsquerda;
	m_cp_screen	= create_bitmap(SCREEN_W, SCREEN_H);
	m_bmp_menu	= create_bitmap(SCREEN_W, SCREEN_H);
}


//------------------------------------------------------------
// Destructor
CMenuH::~CMenuH()
{
	destroy_bitmap(m_cp_screen);
	destroy_bitmap(m_bmp_menu);
}

//------------------------------------------------------------
// Adiciona um novo m_item ao menu
void CMenuH::Adicionar(const char * texto)
{
	sprintf(m_item[m_num_itens++], texto);
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
	blit(screen, m_cp_screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	do {
		for (i = 0; i < m_num_itens; i++)
		{
			Escrever(screen, m_item[i], i, (m_pos_atual == i ? m_cor_selecao : m_cor_texto));
		}

		tecla = readkey() >> 8;
		switch (tecla)
		{
			case KEY_UP:
				m_pos_atual--;
				break;

			case KEY_DOWN:
				m_pos_atual++;
				break;

			case KEY_ESC:
				retorno = -1;
				sair = 1;
				break;

			case KEY_ENTER:
				retorno = m_pos_atual;
				sair = 1;
				break;
		}

		if (m_pos_atual < 0) m_pos_atual = m_num_itens - 1;
		if (m_pos_atual >= m_num_itens) m_pos_atual = 0;

	} while (!sair);

	//Retorna o estado origina da m_tela
	blit(m_cp_screen, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	return retorno;
}

//------------------------------------------------------------
// Escreve o texto no bitmap como parametro
void CMenuH::Escrever(BITMAP * bmp, const char * texto, int linha, int cor)
{
	int aux_linha = (linha * m_fonte->height) + (font->height / 3);
	switch (m_alinhamento)
	{
		case eAlinharEsquerda:
			textout(bmp, m_fonte, texto, m_x, m_y + aux_linha , cor);
			break;

		case eAlinharDireita:
			textout_right(bmp, m_fonte, texto, m_x, m_y + aux_linha, cor);
			break;

		case eAlinharCentro:
			textout_centre(bmp, m_fonte, texto, m_x, m_y + aux_linha, cor);
			break;
	}
}

//------------------------------------------------------------
void CMenuH::SetarAlinhamento(EAlinhamentoMenu alinhamento)
{
	m_alinhamento = alinhamento;
}

//------------------------------------------------------------
void CMenuH::SetarFonte(FONT * fonte)
{
	m_fonte = fonte;
}

//------------------------------------------------------------
void CMenuH::SetarCorTexto(int cor_texto)
{
	m_cor_texto = cor_texto;
}

//------------------------------------------------------------
void CMenuH::SetarCorSelecao(int cor_selecao)
{
	m_cor_selecao = cor_selecao;
}

//------------------------------------------------------------
void CMenuH::SetarX(int x)
{
	m_x = x;
}

//------------------------------------------------------------
void CMenuH::SetarY(int y)
{
	m_y = y;
}

//------------------------------------------------------------
void CMenuH::SetarTexto(int indice, const char * texto)
{
	if (indice >= 0 && indice < m_num_itens)
	{
		sprintf(m_item[indice], texto);
	}
}

//------------------------------------------------------------
void CMenuH::SetarNumeroItens(int numero_itens)
{
	m_num_itens = numero_itens;
}
