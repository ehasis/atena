 /*------------------------------------------------------------*
 *  cbotao.cpp - Implementacao da Classe CBotao
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: sábado, 23 de fevereiro de 2002
*
*
*
*------------------------------------------------------------*/

#include "cbotao.h"


//------------------------------------------------------------
void CBotao::Iniciar(char * nome_arquivo_dat, const char * nome_botao, int mouse_botao, int (* acao)(), int x, int y)
{
	m_dat_botao = load_datafile_object(nome_arquivo_dat, nome_botao);

	if(!m_dat_botao)
	{
		Erro("Código do erro:", "0700");
	}

	m_mouse_botao	= mouse_botao;
	m_acao			= acao;
	m_x				= x;
	m_y				= y;
	m_largura		= ((BITMAP *) m_dat_botao[0].dat)->w / 2;
	m_altura		= ((BITMAP *) m_dat_botao[0].dat)->h;
	m_ativo			= false;
	m_visivel		= true;
}


//------------------------------------------------------------
int CBotao::Atualizar(int mouse_x, int mouse_y)
{
	if(m_ativo
	&& (!m_mouse_botao || mouse_b & m_mouse_botao)
	&& ChecarColisao(mouse_x, mouse_y))
	{
		if(m_acao)
		{
			(* m_acao)();
			rest(100);
		}
		return 1;
	}
	return 0;
}


//------------------------------------------------------------
void CBotao::Desenhar(CTela & tela, ECamada camada)
{
	if(m_visivel)
	{
		tela.Blit((BITMAP *) m_dat_botao[0].dat, camada, m_largura * m_ativo, 0, m_x, m_y, m_largura, m_altura);
	}
}


//------------------------------------------------------------
void CBotao::Finalizar()
{
	unload_datafile_object(m_dat_botao);
}


