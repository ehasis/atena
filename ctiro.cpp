 /*------------------------------------------------------------*
 *  ctiro.cpp - Implementação da Classe de tiro
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: terça-feira, 13 de janeiro de 2002
*
*
*------------------------------------------------------------*/

#include "erro.h"
#include "ctiro.h"


//------------------------------------------------------------
// Membros static
DATAFILE *CTiro::m_dat_arquivo = NULL;


//------------------------------------------------------------
void CTiro::CarregarArquivoDados(DATAFILE * dat_arquivo)
{
	Log("CTiro::CarregarArquivoDados();");
	if(m_dat_arquivo) DescarregarArquivoDados();
	m_dat_arquivo = dat_arquivo;
}


//------------------------------------------------------------
void CTiro::DescarregarArquivoDados()
{
	Log("CTiro::DescarregarArquivoDados();");
	unload_datafile(m_dat_arquivo);
	m_dat_arquivo = NULL;
}

//------------------------------------------------------------
// Construtor
CTiro::CTiro()
{

}


//------------------------------------------------------------
void CTiro::Iniciar(ETiro tipo, int x, int y, CObjetoAvancado * const alvo)
{
	m_tipo = tipo;
	m_x	= x;
	m_y	= y;
	m_alvo = alvo;
	m_dir_x = 0;
	m_dir_y	= 0;
	m_flag_x = 0;
	m_flag_y = 0;
	m_cont = 0;
	m_quadro = 0;
	m_tocar_som	= 1;
	m_status = eTiroNormal;
	m_ativo	= 1;
	m_visivel = 1;
	m_tipo_objeto = eTiro;

	switch(m_tipo)
	{
		// Tiro alien
		case eTiroCerra:
			m_largura = 18;
			m_altura  = 16;
			m_dir_x	= 0;
			m_dir_y	= 1;
			m_velocidade = 4;
			break;

		case eTiroBola:
			m_largura = 5;
			m_altura  = 5;
			m_cont    = 5;
			m_dir_x   = 1;
			m_dir_y	= 1;
			m_velocidade = 2;
			break;

		// Tiro nave
		case eTiroLaserVermelho:
			m_largura = 10;
			m_altura  = 50;
			m_velocidade = 100;
			break;

		case eTiroLaserVerde:
			m_largura = 72;
			m_altura  = 100;
			m_velocidade = 100;
			break;

		case eTiroFogoTeleguiado:
			m_largura = 10;
			m_altura  = 8;
			m_velocidade = 25;
			break;

		// Tiro construcao
		case eTiroFogo:
			m_largura = 10;
			m_altura  = 8;
			m_dir_x	= 0;
			m_dir_y	= 0;
			m_velocidade = 3;
			break;

	}
	m_x = x - (m_largura / 2);
}


//------------------------------------------------------------
void CTiro::Atualizar(TRect area, CObjetoAvancado * const alvo)
{
	area.y1 += ObterAltura() * 2;	// Não permite que o tiro colida com objetos que 
								 	// ainda não entraram na tela
	
	if(ChecarColisao(area)
	&& m_status != eTiroExplosao
	&& m_status != eTiroInativo)
	{
		switch(m_tipo)
		{
	    	case eTiroCerra:
				if(!m_dir_x)
				{
					if(m_alvo->ObterX() != m_x)
					{
						m_dir_x = m_alvo->ObterX() >= m_x ? 1 : -1;
					}
				}

				m_x += m_dir_x * m_velocidade;
				m_y += m_dir_y * m_velocidade;
				m_quadro = m_quadro == 3 ? 0 : m_quadro + 1;
				break;

			case eTiroBola:
				if(m_cont == 5)
				{
					m_dir_x = m_dir_x * -1;
					m_cont = 0;
				}

				m_cont++;
				m_x += m_dir_x * m_velocidade * 2;
       			m_y += m_dir_y * m_velocidade;
				break;

			case eTiroLaserVermelho:
			case eTiroLaserVerde:
				m_y += -1 * m_velocidade;
				break;

			case eTiroFogoTeleguiado:
				if(!m_alvo || !m_alvo->ObterVisivel())
				{
					m_alvo = alvo;
					m_dir_y = -1;
				}

				if(m_alvo)
				{
					// Coordenada x
					if(m_alvo->ChecarColisaoX(m_x,  m_x + m_largura))
					{
						m_dir_x = 0;
					}
					else if(m_x > m_alvo->ObterX())
					{
						m_dir_x = -1;
					}
					else
					{
						m_dir_x = 1;
					}

					// Coordenada y
					if(m_alvo->ChecarColisaoY(m_y,  m_y + m_altura))
					{
						m_dir_y = 0;
					}
					else if(m_y > m_alvo->ObterY())
					{
						m_dir_y = -1;
					}
					else
					{
						m_dir_y = 1;
					}
				}

				m_x += m_dir_x * m_velocidade;
				m_y += m_dir_y * m_velocidade;

				m_quadro = m_quadro == 2 ? 0 : m_quadro + 1;
				break;

			case eTiroFogo:
				if(!m_dir_x)
				{
					if(m_alvo->ObterX() != m_x)
					{
						m_dir_x = m_alvo->ObterX() >= m_x ? 1 : -1;
					}
					if(m_alvo->ObterY() != m_y)
					{
						m_dir_y = m_alvo->ObterY() >= m_y ? 1 : -1;
					}
				}

				m_x += m_dir_x * m_velocidade;
				m_y += m_dir_y * m_velocidade;
				m_quadro = m_quadro == 2 ? 0 : m_quadro + 1;
				break;
		}
	}
	else
	{
		if(m_visivel)
		{
			m_visivel = 0;
			m_quadro = 0;
		}
		if(m_status == eTiroExplosao)
		{
			m_quadro++;
			if (m_quadro == 5)
			{
				m_status = eTiroInativo;
				m_ativo  = 0;
			}
		}
		else
		{
			m_status = eTiroInativo;
			m_ativo  = 0;
		}
	}
}


//------------------------------------------------------------
void CTiro::Desenhar(CTela & tela, int x_real, int y_real)
{

	switch(m_status)
	{
		case eTiroNormal:
			tela.MaskedBlit((BITMAP *)m_dat_arquivo[m_tipo * 2].dat, eCamadaEfeitos, m_largura * m_quadro, 0, m_x - x_real, m_y - y_real, m_largura, m_altura);
			//DesenharExplosao(tela, x_real, y_real, m_x + (m_largura/2), m_y + (m_altura/2), (m_quadro * 3) + (m_largura / 2), m_largura);
			
			if (m_tipo == eTiroFogo)
				m_explosoes.IniciarExplosao(m_x - x_real + (m_largura / 2), m_y - y_real + (m_altura / 2), 3, 10);
			
			break;

		case eTiroExplosao:
			DesenharExplosao(tela, x_real, y_real, m_x + (m_largura/2), m_y + (m_altura/2), (m_quadro * 3) + (m_largura / 2), m_largura);
			break;
	}
}


//------------------------------------------------------------
void CTiro::Sonorizar()
{
	if(m_tocar_som && m_status == eTiroNormal)
	{
		stop_sample((SAMPLE *)m_dat_arquivo[(m_tipo * 2) + 1].dat);
		play_sample((SAMPLE *)m_dat_arquivo[(m_tipo * 2) + 1].dat, 100, 128, 1000, 0);
		m_tocar_som = 0;
	}
	else if(m_status == eTiroExplosao)
	{
		//play_sample((SAMPLE *)m_dat_arquivo[WAV_TIRO_EXPLOSAO].dat, 100, 128, 1000, 0);
	}
}


//------------------------------------------------------------
void CTiro::SetarStatus(EStatusTiro status)
{
	m_status = status;
}


//------------------------------------------------------------
EStatusTiro CTiro::ObterStatus()
{
	return m_status;
}



//------------------------------------------------------------
void CTiro::Finalizar()
{
}


