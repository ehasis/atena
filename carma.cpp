 /*------------------------------------------------------------*
 *  carmas.h - Implementação da Classe para armas
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: quarta-feira, 27 de fevereiro de 2002
*
*  Alterações:
*
*------------------------------------------------------------*/


#include "carma.h"


//------------------------------------------------------------
// Membros static
DATAFILE *CArma::m_dat_arquivo = NULL;


//------------------------------------------------------------
void CArma::CarregarArquivoDados(DATAFILE * dat_arquivo)
{
	Log("CArma::CarregarArquivoDados();");
	if(m_dat_arquivo) DescarregarArquivoDados();
	m_dat_arquivo = dat_arquivo;
	if (!m_dat_arquivo) Erro("Código do erro:", "0801");
}


//------------------------------------------------------------
void CArma::DescarregarArquivoDados()
{
	Log("CArma::DescarregarArquivoDados();");
	unload_datafile(m_dat_arquivo);
	m_dat_arquivo = NULL;
}


//------------------------------------------------------------
// Construtor
CArma::CArma()
{
}


//------------------------------------------------------------
void CArma::Iniciar(int tipo, int x, int y)
{
	m_tipo	 = tipo;
	m_x		 = x;
	m_y		 = y;
	m_flag_x = 0;//x;
	m_flag_y = 0;//y;
	m_objeto = (EObjeto) m_tipo;
	m_status = eArmaNormal;
	m_quadro = 0;
	
	switch(m_tipo)
	{
		case eArmaCanhao:
			m_energia = 25;
			m_largura = 30;
			m_altura = 32
				;
			break;

		case eArmaEscudo:
			m_energia = 50;
			m_largura = 30;
			m_altura = 10;
			break;
	}
}


//------------------------------------------------------------
void CArma::Desenhar(CTela &m_tela, int x_real, int y_real)
{
	Log("[INICIO]:CArma::Desenhar();");

	switch(m_status)
	{
		case eArmaNormal:
			//m_tela.RotateSprite(eCamadaObjetos, (BITMAP *)m_dat_arquivo[(m_tipo)].dat, 0, 0, 0);
			m_tela.Blit((BITMAP *) m_dat_arquivo[(m_tipo * 2) + 1].dat, eCamadaEfeitos, m_quadro * m_largura, 0, m_x - x_real + 40, m_y - y_real + 40, m_largura, m_altura);
			m_tela.Blit((BITMAP *) m_dat_arquivo[(m_tipo * 2)].dat, eCamadaEfeitos, m_quadro * m_largura, 0, m_x - x_real, m_y - y_real, m_largura, m_altura);

			break;

		case eArmaExplosao:
			DesenharExplosao(m_tela, m_x - x_real, m_y - y_real, m_x + (m_largura/2), m_y + (m_altura/2), (m_quadro * 3) + (m_largura / 2), 250);
			break;
	}
	m_tiros.DesenharTodos(m_tela, x_real, y_real);
	Log("[FIM]:CArma::Desenhar();");
}



//------------------------------------------------------------
void CArma::Atualizar(TRect area, CObjetoAvancado * const alvo)
{
	m_tiros.AtualizarTodos(area, alvo);
	
	// Movimentação horizontal
	/*
	if(m_flag_x < 15)
	{
		m_flag_x++;
		m_x++;
	}
	else if(m_flag_x < 30)
	{
		m_flag_x++;
		m_x--;
	}
	else
		m_flag_x = 0;
	/**/

	if(m_tipo == eArmaCanhao)
	{	
		// Movimentação vertical
		if(m_flag_y < 15)
		{
			m_flag_y++;
			m_y++;
		}
		else if(m_flag_y < 30)
		{
			m_flag_y++;
			m_y--;
		}
		else
			m_flag_y = 0;
	
		//m_quadro = m_quadro == 2 ? 0 : m_quadro + 1;
	}
	/**/

	if(m_status != eArmaInativa)
	{
		if(m_quadro == 10) m_status = eArmaInativa;
		else if(m_status == eArmaExplosao) m_quadro++;
		else if(m_energia <= 0) m_status = eArmaExplosao;
	}

	
}


//------------------------------------------------------------
void CArma::Sonorizar()
{
	m_tiros.SonorizarTodos();
}


//------------------------------------------------------------
void CArma::Finalizar()
{
	m_tiros.Finalizar();
}


//------------------------------------------------------------
void CArma::Atirar(CObjetoAvancado * const alvo)
{
	if(m_status != eArmaExplosao && m_status != eArmaInativa)
		m_tiros.Adicionar(eTiroLaserVermelho,  m_x + (m_largura / 2), m_y, alvo);
}


//------------------------------------------------------------
int CArma::ObterTipo()
{
	return m_tipo;
}


//------------------------------------------------------------
void CArma::SetarStatus(EStatusArma status)
{
	m_status = status;
}


//------------------------------------------------------------
EStatusArma CArma::ObterStatus()
{	
	return m_status;
}


//------------------------------------------------------------
CTiro & CArma::ObterTiros()
{
	return m_tiros;
}


