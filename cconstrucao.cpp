 /*------------------------------------------------------------*
 *  cconstrucao.cpp - Implementacao da Classe CConstrucao
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: domingo, 27 de janeiro de 2002
*
*
*
*------------------------------------------------------------*/


#include "erro.h"
#include "cconstrucao.h"
#include "construcoes.h"


//------------------------------------------------------------
// Membros static
DATAFILE *CConstrucao::m_dat_arquivo = NULL;


//------------------------------------------------------------
void CConstrucao::CarregarArquivoDados(DATAFILE * dat_arquivo)
{
	Log("CConstrucao::CarregarArquivoDados();");
	if(m_dat_arquivo) DescarregarArquivoDados();
	m_dat_arquivo = dat_arquivo;
}


//------------------------------------------------------------
void CConstrucao::DescarregarArquivoDados()
{
	Log("CConstrucao::DescarregarArquivoDados();");
	unload_datafile(m_dat_arquivo);
	m_dat_arquivo = NULL;
}



//------------------------------------------------------------
// Construtor
CConstrucao::CConstrucao()
{

}


//------------------------------------------------------------
void CConstrucao::Iniciar(int tipo, int x, int y)
{
	m_x	= x;
	m_y	= y;
	m_tipo = tipo;
	m_quadro = 0;
	m_atirar = 1;
	m_ativo	= 1;
	m_status = eConstrucaoNormal;
	m_atirar = 1;
	m_tipo_objeto = eConstrucao;

	switch(m_tipo)
	{
		case eConstrucao_01:
			m_largura   = 128;
			m_altura    = 128;
			m_energia	= 1;
			break;

		case eConstrucao_02:
			m_largura   = 161;
			m_altura    = 161;
			m_energia	= 2;
			break;

		case eConstrucao_03:
			m_largura   = 102;
			m_altura    = 103;
			m_energia	= 2;
			break;

		case eConstrucao_04:
			m_largura   = 62;
			m_altura    = 67;
			m_energia	= 2;
			break;

		case eConstrucao_05:
			m_largura   = 132;
			m_altura    = 132;
			m_energia	= 2;
			break;

		case eConstrucao_06:
			m_largura   = 111;
			m_altura    = 97;
			m_energia	= 2;
			break;
	}
	m_armas.Adicionar();
	m_armas.Obter().Iniciar(eArmaInvisivel, m_x, m_y);
}


//------------------------------------------------------------
void CConstrucao::Atualizar(TRect area, CObjetoAvancado * const alvo)
{
	if(m_tipo == eConstrucao_04)
	{
		if(m_atirar >= 500)
		{
			m_armas.Obter().Atirar(alvo);
			m_atirar = 0;
		}
		m_atirar += rand() % 11;
		m_quadro = m_quadro == 2 ? 0 : m_quadro + 1;
	}

	if(m_status == eConstrucaoExplosao)
	{
		m_quadro++;
		if (m_quadro == 9)
		{
			m_status = eConstrucaoInativo;
		}
	}
	//m_armas.Obter().SetarXY(m_x, m_y);
	m_armas.Atualizar(area, alvo);
}


//------------------------------------------------------------
void CConstrucao::Desenhar(CTela & tela, int x_real, int y_real)
{
	switch(m_status)
	{
		case eConstrucaoNormal:
			tela.MaskedBlit((BITMAP *)m_dat_arquivo[m_tipo].dat, eCamadaObjetos, m_quadro * m_largura, 0, m_x - x_real, m_y - y_real, m_largura, m_altura);
			break;

		case eConstrucaoExplosao:
			DesenharExplosao(tela, x_real, y_real, m_x + (m_largura/2), m_y + (m_altura/2), (m_quadro * 3) + (m_largura / 2), m_largura);
			//tela.Blit((BITMAP *)m_dat_arquivo[_CONSTRUCAO_EXPLOSAO].dat, eCamadaObjetos, m_quadro * 50, 0, m_x - x_real, m_y - y_real, 50, 50);
			break;
	}
	m_armas.Desenhar(tela, x_real, y_real);
}


//------------------------------------------------------------
void CConstrucao::Finalizar()
{
	m_armas.Finalizar();
}


//------------------------------------------------------------
int CConstrucao::ObterTipo()
{
	return m_tipo;
}


//------------------------------------------------------------
void CConstrucao::Sonorizar()
{
	if(m_status == eConstrucaoExplosao
	&& m_quadro == 0)
	{
		play_sample((SAMPLE *)m_dat_arquivo[_WAV_CONSTRUCAO_EXPLOSAO].dat, 128, 128, 1000, 0);
	}
	m_armas.Sonorizar();
}


//------------------------------------------------------------
void CConstrucao::SetarStatus(EStatusConstrucao status)
{
	m_status = status;
}


//------------------------------------------------------------
EStatusConstrucao CConstrucao::ObterStatus()
{
	return m_status;
}


//------------------------------------------------------------
int CConstrucao::ObterEnergia()
{
	return m_energia;
}


//------------------------------------------------------------
void CConstrucao::DecEnergia(int decremento)
{
	m_energia -= decremento;

	if(m_energia == 0)
	{
		m_status = eConstrucaoExplosao;
		m_quadro = 0;
	}
}


//------------------------------------------------------------
CColecaoAvancada< CArma > & CConstrucao::ObterArmas()
{
	return m_armas;
}