 /*------------------------------------------------------------*
 *  cveiculo.h - Implementação da Classe para veículos
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: terça-feira, 09 de julho de 2002
*
*  Alterações:
*
*------------------------------------------------------------*/


#include "cveiculo.h"


//------------------------------------------------------------
// Membros static
GADados CVeiculo::m_dat_arquivo;


//------------------------------------------------------------
void CVeiculo::CarregarArquivoDados(const char *arquivo)
{
	Log("CVeiculo::CarregarArquivoDados();");
	m_dat_arquivo.Abrir(arquivo);
}


//------------------------------------------------------------
void CVeiculo::DescarregarArquivoDados()
{
	Log("CVeiculo::DescarregarArquivoDados();");
	m_dat_arquivo.Fechar();
}


//------------------------------------------------------------
// Construtor
CVeiculo::CVeiculo()
{
}


//------------------------------------------------------------
void CVeiculo::Iniciar(int tipo, int x, int y)
{
	m_tipo	 = tipo;
	m_x		 = x;
	m_y		 = y;
	m_flag_x	= (rand() % 2) * -2 + 1;
	m_flag_y	= (rand() % 2) * -2 + 1;
	m_tipo_objeto = eVeiculo;
	m_status = eVeiculoNormal;
	m_quadro = 0;
	m_tempo = 0;
	m_velocidade = 1;
	m_dir_x     = 0;
	m_dir_y	    = 1;
	m_angulo = 0;
	switch(m_tipo)
	{
		case eVeiculoCarro:
			m_energia = 20;
			m_largura = 70;
			m_altura = 105;
			break;

		case eVeiculoTanque:
			m_energia = 50;
			m_largura = 30;
			m_altura = 10;
			break;
	}
	
	m_armas.Adicionar();
	m_armas.Obter().Iniciar(eArmaInvisivel, m_x, m_y);
	
}


//------------------------------------------------------------
void CVeiculo::Desenhar(CTela &tela, int x_real, int y_real)
{
	//Log("[INICIO]:CVeiculo::Desenhar();");

	switch(m_status)
	{
		case eVeiculoNormal:
			//m_tela.RotateSprite(eCamadaObjetos, (BITMAP *)m_dat_arquivo[(m_tipo)].dat, 0, 0, 0);
			//m_tela.MaskedBlit((BITMAP *) m_dat_arquivo[(m_tipo * 2) + 1].dat, eCamadaObjetos, m_quadro * m_largura, 0, m_x - x_real + 5, m_y - y_real + 5, m_largura, m_altura);
			tela.RotateSprite(eCamadaObjetos, m_dat_arquivo.Bitmap(m_tipo * 2), m_x - x_real, m_y - y_real, itofix(m_angulo));
			//m_tela.MaskedBlit((BITMAP *) m_dat_arquivo[(m_tipo * 2)].dat, eCamadaObjetos, m_quadro * m_largura, 0, m_x - x_real, m_y - y_real, m_largura, m_altura);

			break;
			
		case eVeiculoExplosao:
			DesenharExplosaoRadial(x_real, y_real, m_x + (m_largura / 2), m_y + (m_altura / 2), (m_quadro * 3) + (m_largura / 2));
	  		break;
	}
	m_armas.Desenhar(tela, x_real, y_real);
	Log("[FIM]:CVeiculo::Desenhar();");
}



//------------------------------------------------------------
void CVeiculo::Atualizar(TRect area, CObjetoAvancado * const alvo)
{
	
	if(ChecarColisao(area) || m_armas.Obter().ObterTiros().ObterQuantidade())
	{
		if(!m_ativo)
		{
			m_ativo = 1;
			m_visivel = 1;
		}
		if(m_tempo >= 15)
		{
			m_dir_y = 0;
			if(!(m_tempo % 200))
				m_armas.Obter().Atirar(alvo);
									
			if (m_tempo >= 50)
			{
				if(abs(m_angulo) < 50)
					m_angulo += m_flag_x;
				else
				{
					m_dir_x = - 2 * m_flag_x;
					m_dir_y = 1;
				}
			}	
		}
		m_tempo++;
		m_x += m_dir_x * m_velocidade;
		m_y += m_dir_y * m_velocidade;

	
		if(m_status != eVeiculoInativo)
		{	
			if(m_quadro == 10) m_status = eVeiculoInativo;
			else if(m_status == eVeiculoExplosao) m_quadro++;
			else if(m_energia <= 0) m_status = eVeiculoExplosao;
		}
		m_armas.Obter().SetarXY(m_x, m_y);
		m_armas.Atualizar(area, alvo);
	}
}


//------------------------------------------------------------
void CVeiculo::Sonorizar()
{
	m_armas.Sonorizar();
}


//------------------------------------------------------------
void CVeiculo::Finalizar()
{
	m_armas.Finalizar();
}


//------------------------------------------------------------
int CVeiculo::ObterTipo()
{
	return m_tipo;
}


//------------------------------------------------------------
void CVeiculo::SetarStatus(EStatusVeiculo status)
{
	m_status = status;
}


//------------------------------------------------------------
EStatusVeiculo CVeiculo::ObterStatus()
{	
	return m_status;
}


//------------------------------------------------------------
CColecaoAvancada< CArma > & CVeiculo::ObterArmas()
{
	return m_armas;
}


//------------------------------------------------------------
bool CVeiculo::Colidir(TRect area, int energia)
{
	if(ChecarColisao(area)
	&& m_status != eVeiculoInativo
	&& m_status != eVeiculoExplosao)
	{
		DecEnergia(energia);
		return true;
	}
	return false;
}
