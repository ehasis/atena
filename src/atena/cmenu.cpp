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
	m_x 			= 0;
	m_y				= 0;
	m_fonte			= NULL;
	m_cor_texto		= makecol(255,255,255);
	m_cor_selecao	= makecol(255,255,0);
	m_num_itens		= 0;
	m_pos_atual		= 0;
	m_alinhamento	= eAlinharEsquerda;
	m_cp_screen		= create_bitmap(SCREEN_W, SCREEN_H);
	m_bmp_menu		= create_bitmap(SCREEN_W, SCREEN_H);
}

//------------------------------------------------------------
// Destructor
CMenuH::~CMenuH()
{
	m_fonte = NULL;
	destroy_bitmap(m_cp_screen);
	destroy_bitmap(m_bmp_menu);
}

//------------------------------------------------------------
// Adiciona um novo m_item ao menu
CMenuH& CMenuH::Adicionar(const char * texto)
{
	sprintf(m_item[m_num_itens++], texto);
	return *this;
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
	alfont_text_mode(-1);

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
	int aux_linha = (linha * alfont_get_font_height(m_fonte)) + (alfont_get_font_height(m_fonte) / 3);
	switch (m_alinhamento)
	{
		case eAlinharEsquerda:
			alfont_textout(bmp, m_fonte, texto, m_x, m_y + aux_linha , cor);
			break;

		case eAlinharDireita:
			alfont_textout_right(bmp, m_fonte, texto, m_x, m_y + aux_linha, cor);
			break;

		case eAlinharCentro:
			alfont_textout_centre(bmp, m_fonte, texto, m_x, m_y + aux_linha, cor);
			break;
	}
}

//------------------------------------------------------------
CMenuH& CMenuH::SetarAlinhamento(EAlinhamentoMenu alinhamento)
{
	m_alinhamento = alinhamento;
	return *this;
}

//------------------------------------------------------------
CMenuH& CMenuH::SetarFonte(ALFONT_FONT *fonte)
{
	m_fonte = fonte;
	return *this;
}

//------------------------------------------------------------
CMenuH& CMenuH::SetarTamanhoFonte(int tamanho)
{
	alfont_set_font_size(m_fonte, tamanho);
	return *this;
}

//------------------------------------------------------------
CMenuH& CMenuH::SetarCorTexto(int cor_texto)
{
	m_cor_texto = cor_texto;
	return *this;
}

//------------------------------------------------------------
CMenuH& CMenuH::SetarCorSelecao(int cor_selecao)
{
	m_cor_selecao = cor_selecao;
	return *this;
}

//------------------------------------------------------------
CMenuH& CMenuH::SetarX(int x)
{
	m_x = x;
	return *this;
}

//------------------------------------------------------------
CMenuH& CMenuH::SetarY(int y)
{
	m_y = y;
	return *this;
}

//------------------------------------------------------------
CMenuH& CMenuH::SetarTexto(int indice, const char * texto)
{
	if (indice >= 0 && indice < m_num_itens)
	{
		sprintf(m_item[indice], texto);
	}
	return *this;
}

//------------------------------------------------------------
CMenuH& CMenuH::SetarNumeroItens(int numero_itens)
{
	m_num_itens = numero_itens;
	return *this;
}
