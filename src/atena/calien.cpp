 /*------------------------------------------------------------*
 *  calien.cpp - Implementação da Classe de alien
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: terça-feira, 13 de dezembro de 2001
*
*
*------------------------------------------------------------*/

#include <time.h>
#include "aliens.h"
#include "calien.h"
#include "erro.h"

//------------------------------------------------------------
// Membros static
GADados CAlien::m_dat_arquivo;
//int CAlien::m_num_aliens = 0;


//------------------------------------------------------------
void CAlien::CarregarArquivoDados(const char *arquivo)
{
	Log("CAlien::CarregarArquivoDados();");
	m_dat_arquivo.Abrir(arquivo);
}


//------------------------------------------------------------
void CAlien::DescarregarArquivoDados()
{
	m_dat_arquivo.Fechar();
}



//------------------------------------------------------------
// Construtor
CAlien::CAlien()
{
}


//------------------------------------------------------------
void CAlien::Iniciar(int tipo, int x, int y)
{
	m_tipo		= tipo;
	m_x			= x;
	m_y			= y;
	m_dir_x     = 0;
	m_dir_y	    = 1;
	m_quadro	= 0;

//#ifdef ZEUS // Atena = 0 / Zeus = 1
	m_ativo     = 1;	
	m_visivel	= 1;
//#else
//	m_ativo     = 0;
//	m_visivel	= 0;
//#endif

	m_atirar    = rand() % 2;
	m_status    = eAlienNormal;
	m_angulo	= 0;
	m_tempo		= 0;
	m_flag_x	= (rand() % 2) * -2 + 1;
	m_flag_y	= (rand() % 2) * -2 + 1;
	m_dir_r		= 0;
	m_tipo_objeto= eAlien;
	m_pos_sombra= 40;

	m_largura   = m_dat_arquivo.Bitmap((m_tipo * 2))->w;
	m_altura    = m_dat_arquivo.Bitmap((m_tipo * 2))->h;


	switch(m_tipo)
	{
		case eAlien_01:
			m_energia	= 1;
			m_velocidade= 2;
			m_dir_x		= 1;
			m_angulo	= 0;
			break;

		case eAlien_02:
			m_energia	 = 2;
			m_velocidade = 3;
			break;

		case eAlien_03:
			m_energia	 = 3;
			m_velocidade = 3;
			break;

		case eAlien_04:
			m_energia	 = 2;
			m_velocidade = 3;
			break;

		case eAlien_05:
			m_energia	 = 1;
			m_velocidade = 4;
			break;

		case eAlien_06:
			m_energia	 = 2;
			m_velocidade = 3;
			break;

		case eAlien_07:
			m_energia	 = 6;
			m_velocidade = 3;
			break;
	}
	m_energia *= 2;

	m_armas.Adicionar();
	m_armas.Obter().Iniciar(eArmaInvisivel, m_x, m_y);
}


//------------------------------------------------------------
void CAlien::Atualizar(TRect area, CObjetoAvancado * const alvo)
{
	if (m_ativo)
	{
	TRect area_alien;

	area_alien.x1 = area.x1 - ObterLargura();
	area_alien.y1 = area.y1 - ObterAltura();
	area_alien.x2 = area.x2 + ObterLargura();
	area_alien.y2 = area.y2 + ObterAltura();

	if(ChecarColisao(area_alien)
	&& m_status != eAlienExplosao
	&& m_status != eAlienInativo)
	{
		if(!m_ativo)
		{
			m_ativo = 1;
			m_visivel = 1;
		}
		switch(m_tipo)
		{
			case eAlien_01:
				if(m_x <= (m_largura * 2))
				{
					m_dir_x = 1;
					m_angulo = 0;
				}
				else if(m_x > SCREEN_W - (m_largura * 2))
				{
					m_dir_x = -1;
					m_angulo = 0;
				}
				if(abs(m_angulo) <= 30)
				{
					m_angulo -= m_dir_x * 2;
				}
				break;

			case eAlien_02:
			case eAlien_03:
				//quadro = quadro < 2 ?quadro + 1 :0;
				if(m_tempo > 20)
				{
					if(abs(m_angulo) <= 20) m_angulo -= m_dir_x * 4;
				}
				else if(m_tempo == 20)
				{
					m_dir_x = m_flag_x;
				}
				break;

			case eAlien_04:
				if(m_tempo > 15)
				{
					if(!ChecarColisaoX(310, 330))
					{
						m_dir_x = 320 >= m_x ? 1 : -1;
						m_dir_r = m_dir_x;
					}
					else if(m_dir_x)
					{
						m_dir_r = m_dir_x * -1;
						m_angulo -= m_dir_r * 2;
						m_dir_x = 0;
					}
					if(m_angulo >= -20
					&& m_angulo <=  20
					&& (m_dir_x != 0 || m_angulo != 0))
					{
						m_angulo -= m_dir_r * 2;
					}
				}
				else if(m_tempo == 15)
				{
					if(!ChecarColisaoX(310, 330))
					{
						m_dir_x = 320 >= m_x ? 1 : -1;
						m_dir_r = m_dir_x;
					}
					else m_dir_x = 0;
				}
				break;

			case eAlien_06:
				if(!alvo->ChecarColisaoX(m_x, m_x + m_largura) && alvo->ObterY() > m_y)
				{
					m_dir_x = alvo->ObterX() >= m_x ? 1 : -1;
					m_dir_r = m_dir_x;
				}
				else if(m_dir_x)
				{
					m_dir_r = m_dir_x * -1;
					m_angulo -= m_dir_r * 4;
					m_dir_x = 0;
				}
				if(m_angulo >= -20
				&& m_angulo <=  20
				&& (m_dir_x != 0 || m_angulo != 0))
				{
					m_angulo -= m_dir_r * 4;
				}
				break;

			case eAlien_07:
				if(m_tempo >= 15)
				{
					m_dir_y = 0;
					if(!(m_tempo % 50))
						m_armas.Obter().Atirar(alvo);

					if (m_tempo >= 50)
					{
						if(abs(m_angulo) < 100)
						{
							m_dir_x = m_flag_x;
							m_dir_y = 1;
							m_angulo += 5 * m_flag_x * -1;
						}
						else
						{
							m_dir_x = m_flag_x;
							m_dir_y = -2;
						}
					}
				}

				break;
		}
		m_tempo++;
		m_x += m_dir_x * m_velocidade;
		m_y += m_dir_y * m_velocidade;

		if(m_atirar && m_tempo >= 20 + 5 * m_flag_x)
		{
			m_armas.Obter().Atirar(alvo);
			m_atirar = 0;
		}
		if(m_status == eAlienAtingido)
			m_status = eAlienNormal;
	}
	else
	{
		if(m_visivel)
			m_visivel = 0;

		if(m_status == eAlienExplosao)
		{
			m_quadro++;
			if (m_quadro == 10)
			{
				m_status = eAlienInativo;
				m_ativo   = 0;
			}
		}
	}
	}
	m_armas.Obter().SetarXY(m_x, m_y);
	m_armas.Atualizar(area, alvo);
}


//------------------------------------------------------------
void CAlien::Desenhar(CTela & tela, int x_real, int y_real)
{

	if (m_ativo)
	{	
		switch(m_status)
		{
			case eAlienNormal:
			case eAlienAtingido:
				//tela.MaskedBlit((BITMAP *)m_dat_arquivo[(m_tipo * 2) + 1].dat, eCamadaObjetos, quadro * (largura / 1.5), 0, x - x_real + 50, y  - y_real + 50, (largura / 1.5), (altura / 1.5));
				//tela.MaskedBlit((BITMAP *)m_dat_arquivo[(m_tipo * 2)].dat, eCamadaObjetos, quadro * largura, 0, x - x_real, y  - y_real, largura, altura);
				tela.RotateSprite(eCamadaObjetos, m_dat_arquivo.Bitmap((m_tipo * 2) + 1), m_x - x_real + m_pos_sombra, m_y  - y_real + m_pos_sombra, itofix(m_angulo));
 				tela.RotateSprite(eCamadaObjetos, m_dat_arquivo.Bitmap((m_tipo * 2)), m_x - x_real, m_y - y_real, itofix(m_angulo));
				break;

			case eAlienExplosao:
				DesenharExplosao(tela, x_real, y_real, m_x + (m_largura/2), m_y + (m_altura/2), m_quadro  + (m_largura / 2), m_largura/2);
				//m_explosao.InserirSprite((BITMAP *)m_dat_arquivo[(m_tipo * 2)].dat,  m_x - x_real, m_y - y_real);
				break;
		}
	}
	m_armas.Desenhar(tela, x_real, y_real);
}

//------------------------------------------------------------
void CAlien::Finalizar()
{
	m_armas.Finalizar();
}


//------------------------------------------------------------
int CAlien::ObterTipo()
{
	return m_tipo;
}


//------------------------------------------------------------
void CAlien::Sonorizar()
{
	if(m_status == eAlienExplosao
	&& m_quadro == 0)
	{
		play_sample(m_dat_arquivo.Sample(WAV_ALIEN_EXPLOSAO), 128, 128, 1000, 0);
	}
	m_armas.Sonorizar();
}


//------------------------------------------------------------
void CAlien::SetarStatus(EStatusAlien status)
{
	m_status = status;
}


//------------------------------------------------------------
EStatusAlien CAlien::ObterStatus()
{
	return m_status;
}


//------------------------------------------------------------
void CAlien::DecEnergia(int decremento)
{
	m_energia -= decremento;

	if(m_energia <= 0)
	{
		m_status = eAlienExplosao;
		m_quadro = 0;
	}
}


//------------------------------------------------------------
CColecaoAvancada< CArma > & CAlien::ObterArmas()
{
	return m_armas;
}


//------------------------------------------------------------
bool CAlien::Colidir(TRect area, int energia)
{
	if(ChecarColisao(area)
	&& m_status != eAlienInativo
	&& m_status != eAlienExplosao)
	{
		DecEnergia(energia);
		return true;
	}
	return false;
}
