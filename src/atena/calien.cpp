 /*------------------------------------------------------------*
 *  calien.cpp - Implementação da Classe de alien
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: terça-feira, 13 de dezembro de 2001
*
*
*------------------------------------------------------------*/

#include <time.h>
#include "calien.h"
#include "erro.h"

CAlien::CAlien()
{
	m_sombra = NULL;
}

CAlien::~CAlien()
{
//	Finalizar();
}


//------------------------------------------------------------
void CAlien::Iniciar(TObjeto &obj)
{
	register int x, y;

	//Inicializa a classe base
	CInimigo::Iniciar(obj);

	//m_sombra= load_bmp(tmp_arquivo, NULL);
	m_sombra = create_bitmap(m_largura / 2, m_altura / 2);
	stretch_blit(m_bitmap, m_sombra, 0, 0, m_bitmap->w, m_bitmap->h, 0, 0, m_sombra->w, m_sombra->h);
	for (x = 0; x < m_sombra->w; x++)
	{
		for (y = 0; y < m_sombra->h; y++)
		{
			if (_getpixel16(m_sombra, x, y) != COR_ROSA)
				_putpixel16(m_sombra, x, y, COR_PRETA);
		}
	}

	m_dir_x     = 0;
	m_dir_y	    = 1;

	m_atirar    = rand() % 2;
	m_flag_x	= (rand() % 2) * -2 + 1;
	m_flag_y	= (rand() % 2) * -2 + 1;
	m_dir_r		= 0;
	m_pos_sombra= 40;


	switch(m_subtipo)
	{
		case eAlien_01:
			m_dir_x		= 1;
			m_angulo	= 0;
			break;
	}
	m_energia += 2;
}

//------------------------------------------------------------
void CAlien::Finalizar()
{
	if (m_sombra != NULL)
	{
		destroy_bitmap(m_sombra);
		m_sombra = NULL;
	}
	CInimigo::Finalizar();
}

//------------------------------------------------------------
void CAlien::Atualizar(TRect &area, CObjetoAvancado * const alvo)
{
	if (m_ativo)
	{
		TRect area_alien;

		area_alien.x1 = area.x1 - ObterLargura();
		area_alien.y1 = area.y1 - ObterAltura();
		area_alien.x2 = area.x2 + ObterLargura();
		area_alien.y2 = area.y2 + ObterAltura();

		if(m_status != eInimigoExplosao
		&& m_status != eInimigoInativo
		&& ChecarColisao(area_alien))
		{
			if(!m_visivel)
			{
				m_visivel = 1;
			}

			switch(m_subtipo)
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
			if(m_status == eInimigoAtingido)
				m_status = eInimigoNormal;
		}
		else
		{
			if(m_visivel)
				m_visivel = 0;

			if(m_status == eInimigoExplosao)
			{
				m_quadro++;
				if (m_quadro == 10)
				{
					m_status = eInimigoInativo;
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
			case eInimigoNormal:
			case eInimigoAtingido:
				//sombra
				tela.RotateSprite(eCamadaObjetos, m_sombra, m_x - x_real + m_pos_sombra, m_y  - y_real + m_pos_sombra, itofix(m_angulo));
				
				//alien
				tela.RotateSprite(eCamadaObjetos, m_bitmap, m_x - x_real, m_y - y_real, itofix(m_angulo));
 				
				break;

			case eInimigoExplosao:
				DesenharExplosao(tela, x_real, y_real, m_x + (m_largura/2), m_y + (m_altura/2), m_quadro  + (m_largura / 2), m_largura/2);
				break;
		}
	}
	m_armas.Desenhar(tela, x_real, y_real);
}