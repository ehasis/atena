 /*------------------------------------------------------------*
 *  cconstrucao.cpp - Implementacao da Classe CConstrucao
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: domingo, 27 de janeiro de 2002
*
*
*
*------------------------------------------------------------*/


#include "cconstrucao.h"
#include "construcoes.h"
#include "erro.h"

//------------------------------------------------------------
void CConstrucao::Iniciar(TObjeto &obj)
{
	IniciarInimigo(obj);

	m_quadro	= 0;
	m_atirar	= 1;
	m_ativo		= 1;
	m_status	= eInimigoNormal;
	m_atirar	= 1;
}

//------------------------------------------------------------
void CConstrucao::Finalizar()
{
	FinalizarInimigo();
}

//------------------------------------------------------------
void CConstrucao::Atualizar(TRect &area, CObjetoAvancado * const alvo)
{
	if(m_subtipo == eConstrucao_04)
	{
		if(m_atirar >= 500)
		{
			m_armas.Obter().Atirar(alvo);
			m_atirar = 0;
		}
		m_atirar += rand() % 11;
		m_quadro = m_quadro == 2 ? 0 : m_quadro + 1;
	}

	if(m_status == eInimigoExplosao)
	{
		m_quadro++;
		if (m_quadro == 9)
		{
			m_status = eInimigoInativo;
		}
	}
	m_armas.Atualizar(area, alvo);
}


//------------------------------------------------------------
void CConstrucao::Desenhar(CTela &tela, int x_real, int y_real)
{
	switch(m_status)
	{
		case eInimigoNormal:
			tela.MaskedBlit(m_bitmap, eCamadaObjetos, m_quadro * m_largura, 0, m_x - x_real, m_y - y_real, m_largura, m_altura);
			break;

		case eInimigoExplosao:
			DesenharExplosao(tela, x_real, y_real, m_x + (m_largura/2), m_y + (m_altura/2), (m_quadro * 3) + (m_largura / 2), m_largura);
			break;
	}
	m_armas.Desenhar(tela, x_real, y_real);
}