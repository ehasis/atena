 /*------------------------------------------------------------*
 *  carmas.cpp - Implementação da Classe para armas
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
GADados CArma::m_dat_arquivo;


//------------------------------------------------------------
void CArma::CarregarArquivoDados(const char *arquivo)
{
	m_dat_arquivo.Abrir(arquivo);
}


//------------------------------------------------------------
void CArma::DescarregarArquivoDados()
{
	m_dat_arquivo.Fechar();
}


//------------------------------------------------------------
// Construtor
CArma::CArma()
{
}


//------------------------------------------------------------
void CArma::Iniciar(int tipo, int x, int y)
{
	m_tipo		= tipo;
	m_x			= x;
	m_y			= y;
	m_flag_x	= x;
	m_flag_y	= y;
	m_status	= eArmaNormal;
	m_quadro	= 0;
	m_ativo     = 1;
	m_visivel	= 1;

	switch(m_tipo)
	{
		case eArmaCanhao:
			m_energia = 25;
			m_largura = 15;
			m_altura = 16;
			m_tipo_tiro = eTiroLaserVermelho;
			break;

		case eArmaEscudo:
			m_energia = 50;
			m_largura = 30;
			m_altura = 10;
			m_tipo_tiro = eTiroLaserVermelho;
			break;

		case eArmaInvisivel:
			m_energia = 25;
			m_largura = 30;
			m_altura = 10;
			m_tipo_tiro = eTiroFogo;
			break;

		case eArmaNave:
			m_energia = 25;
			m_largura = 0;
			m_altura = 0;
			m_tipo_tiro = eTiroLaserVermelho;
			break;

	}
}

//------------------------------------------------------------
void CArma::Finalizar()
{
	m_tiros.Finalizar();
}

//------------------------------------------------------------
void CArma::Desenhar(CTela &tela, int x_real, int y_real)
{
	switch(m_status)
	{
		case eArmaNormal:
			tela.MaskedBlit(m_dat_arquivo.Bitmap((m_tipo * 2) + 1), eCamadaEfeitos, m_quadro * m_largura, 0, m_x - x_real + 40, m_y - y_real + 40, m_largura, m_altura);
			tela.MaskedBlit(m_dat_arquivo.Bitmap((m_tipo * 2)), eCamadaEfeitos, m_quadro * m_largura, 0, m_x - x_real, m_y - y_real, m_largura, m_altura);

			if(m_tipo == eArmaCanhao)
			{
				if(m_turbina)
					DesenharExplosao(tela, x_real, y_real, m_x + (m_largura/2) - 1, m_y + m_altura, 3, 5);
				else
					DesenharExplosao(tela, x_real, y_real, m_x + (m_largura/2) - 1, m_y + m_altura, 1, 5);
			}
			break;

		case eArmaExplosao:
			DesenharExplosao(tela, x_real, y_real, m_x + (m_largura/2), m_y + (m_altura/2), (m_quadro * 3) + (m_largura / 2), m_largura);
			break;
	}
	m_tiros.Desenhar(tela, x_real, y_real);
}


//------------------------------------------------------------
void CArma::Atualizar(TRect &area, CObjetoAvancado * const alvo)
{

	m_turbina = 0;
	if(m_tiros.MoverPrimeiro())
	{
		do
		{
			if(m_tiros.Obter().ObterStatus() == eTiroInativo)
			{
				m_tiros.Remover();
				m_tiros.MoverAnterior();
			}
		} while(m_tiros.MoverProximo());

		m_tiros.Atualizar(area, alvo);
	}

	switch(m_tipo)
	{

		case eArmaCanhao:
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
			break;
	}

	if(m_status != eArmaInativa)
	{
		if(m_quadro == 10) m_status = eArmaInativa;
		else if(m_status == eArmaExplosao) m_quadro++;
		else if(m_energia <= 0) m_status = eArmaExplosao;
	}
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
void CArma::SetarTipoTiro(ETiro tipo_tiro)
{
	m_tipo_tiro = tipo_tiro;
}
