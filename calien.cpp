 /*------------------------------------------------------------*
 *  calien.cpp - Implementação da Classe de alien
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: terça-feira, 13 de dezembro de 2001
*
*
*------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro.h>
#include <math.h>
#include "aliens.h"
#include "calien.h"
#include "erro.h"

//------------------------------------------------------------
// Membros static
DATAFILE *CAlien::m_dat_arquivo = NULL;
int CAlien::m_num_aliens = 0;


//------------------------------------------------------------
void CAlien::CarregarArquivoDados(DATAFILE * dat_arquivo)
{
	Log("CAlien::CarregarArquivoDados();");
	if(m_dat_arquivo) DescarregarArquivoDados();
	m_dat_arquivo = dat_arquivo;
}


//------------------------------------------------------------
void CAlien::DescarregarArquivoDados()
{
	Log("CAlien::DescarregarArquivoDados();");
	unload_datafile(m_dat_arquivo);
	m_dat_arquivo = NULL;
}


//------------------------------------------------------------
// Construtor
CAlien::CAlien()
{
	m_p_alien = NULL;
}


//------------------------------------------------------------
void CAlien::Iniciar(int tipo, int x, int y)
{
	Log("CAlien::Iniciar();");

	m_tipo		= tipo;
	m_x			= x;
	m_y			= y;
	m_dir_x     = 0;
	m_dir_y	    = 1;
	m_quadro	= 0;
	m_ativo     = 0;	// Atena = 0 / Zeus = 1
	m_visivel	= 0;	// Atena = 0 / Zeus = 1
	m_atirar    = rand() % 2;
	m_status    = eAlienNormal;
	m_angulo	= 0;
	m_tempo		= 0;
	m_flag_x	= (rand() % 2) * -2 + 1;
	m_flag_y	= (rand() % 2) * -2 + 1;
	m_dir_r		= 0;
	m_objeto	= eAlien;
	m_pos_sombra= 40;

	switch(m_tipo)
	{
		case eAlien_01:
			m_largura   = 47;
			m_altura    = 31;
			m_energia	= 1;
			m_velocidade= 4;
			m_dir_x		= 1;
			m_angulo	= 0;
			break;

		case eAlien_02:
			m_largura    = 50;
			m_altura     = 50;
			m_energia	 = 2;
			m_velocidade = 5;
			break;

		case eAlien_03:
			m_largura    = 52;
			m_altura     = 48;
			m_energia	 = 3;
			m_velocidade = 6;
			break;

		case eAlien_04:
			m_largura    = 65;
			m_altura     = 106;
			m_energia	 = 4;
			m_velocidade = 7;
			break;

		case eAlien_05:
			m_largura    = 41;
			m_altura     = 38;
			m_energia	 = 1;
			m_velocidade = 8;
			break;

		case eAlien_06:
			m_largura    = 40;
			m_altura     = 40;
			m_energia	   = 2;
			m_velocidade = 5;
			break;

		case eAlien_07:
			m_largura    = 98;
			m_altura     = 73;
			m_energia	 = 10;
			m_velocidade = 6;
			break;
	}
	m_energia *= 2;
}


//------------------------------------------------------------
void CAlien::Adicionar(int tipo, int x, int y)
{
	Log("CAlien::Adicionar();");
	CAlien *aux;

    for(aux = this; aux->m_p_alien; aux = aux->m_p_alien);

	aux->m_p_alien = new CAlien;
	if(!aux->m_p_alien)
	{
		Erro("Código do erro:", "0000");
	}
	aux->m_p_alien->Iniciar(tipo, x, y);
	m_num_aliens++;
}


//------------------------------------------------------------
void CAlien::Atualizar(TRect area, CObjetoAvancado * const alvo)
{
	Log("CAlien::Atualizar();");
	if (m_status != eAlienExplosao && m_status != eAlienInativo)
	{
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

					if(!(m_tempo % 10))
						m_tiros.Adicionar(eTiroFogo, m_x + (m_largura / 2), m_y + m_altura, alvo);
					
					
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
			m_tiros.Adicionar((ETiro) (rand() % 2), m_x + (m_largura / 2), m_y + m_altura, alvo);
			m_atirar = 0;
		}	
	}
	else if(m_status == eAlienAtingido)
	{
		m_status = eAlienNormal;
	}
	else if(m_status == eAlienExplosao)
	{
		m_quadro++;
		if (m_quadro == 10)
		{
			m_status = eAlienInativo;
		}
	}
	m_tiros.AtualizarTodos(area, alvo);
}


//------------------------------------------------------------
void CAlien::AtualizarTodos(TRect area, CObjetoAvancado * const alvo)
{
	Log("");
	Log("[INICIO]:CAlien::AtualizarTodos();");
	CAlien *aux;

	for(aux = m_p_alien; aux; aux = aux->m_p_alien)
	{
		if((aux->ChecarColisaoSombra(area)
		&& aux->m_status != eAlienExplosao
		&& aux->m_status != eAlienInativo))
		{
			aux->Atualizar(area, alvo);
			if(!aux->m_ativo)
			{
				aux->m_ativo = 1;
				aux->m_visivel = 1;
			}
		}
		else if(aux->m_tiros.VerificarExisteTiros())
		{
			aux->Atualizar(area, alvo);
			aux->m_visivel = 0;
		}
		else
		{
			if(aux->m_ativo) aux->m_status = eAlienInativo;
			aux->m_ativo   = 0;
			aux->m_visivel = 0;
		}
	}
	Log("[FIM]: CAlien::AtualizarTodos();");
	Log("");
}


//------------------------------------------------------------
void CAlien::Desenhar(CTela & tela, int x_real, int y_real)
{
	switch(m_status)
	{
		case eAlienNormal:
		case eAlienAtingido:

			//tela.MaskedBlit((BITMAP *)m_dat_arquivo[(m_tipo * 2) + 1].dat, eCamadaObjetos, quadro * (largura / 1.5), 0, x - x_real + 50, y  - y_real + 50, (largura / 1.5), (altura / 1.5));
			//tela.MaskedBlit((BITMAP *)m_dat_arquivo[(m_tipo * 2)].dat, eCamadaObjetos, quadro * largura, 0, x - x_real, y  - y_real, largura, altura);
			tela.RotateSprite(eCamadaObjetos, (BITMAP *)m_dat_arquivo[(m_tipo * 2) + 1].dat, m_x - x_real + m_pos_sombra, m_y  - y_real + m_pos_sombra, itofix(m_angulo));
 			tela.RotateSprite(eCamadaObjetos, (BITMAP *)m_dat_arquivo[(m_tipo * 2)].dat, m_x - x_real, m_y - y_real, itofix(m_angulo));
			break;

		case eAlienExplosao:
			DesenharExplosao(tela, x_real, y_real, m_x + (m_largura/2), m_y + (m_altura/2), (m_quadro * 3) + (m_largura / 2), 500);
			break;
	}
	m_tiros.DesenharTodos(tela, x_real, y_real);
}


//------------------------------------------------------------
void CAlien::DesenharTodos(CTela & tela, int x_real, int y_real)
{
	Log("[INICIO]:CAlien::DesenharTodos();");
	CAlien *aux;

	for(aux = m_p_alien; aux; aux = aux->m_p_alien)
	{
		if(aux->m_ativo)
		{
			aux->Desenhar(tela, x_real, y_real);
		}
	}
	Log("[FIM]:CAlien::DesenharTodos();");
}


//------------------------------------------------------------
void CAlien::Finalizar()
{
	Log("");
	Log("[INICIO]:CAlien::Finalizar();");

	CAlien *aux, *del;

	for(aux = m_p_alien; aux;)
	{
		del = aux;
		aux = aux->m_p_alien;
		del->m_tiros.Finalizar();
		delete del;
		m_num_aliens--;
	}
	m_p_alien = NULL;

	Log("[FIM]:CAlien::Finalizar();");
	Log("");
}


//------------------------------------------------------------
int CAlien::ObterTipo()
{
	return m_tipo;
}


//------------------------------------------------------------
void CAlien::SalvarAlien(char * fase)
{
	CAlien *aux;
	TObjeto alien;
	FILE *m_arquivo;

	if((m_arquivo = fopen(fase, "rb+")) != NULL)
	{
		alien.m_tipo = eAlien;
		fseek(m_arquivo, 0, SEEK_END);
		for(aux = m_p_alien; aux; aux = aux->m_p_alien)
		{
			alien.subtipo = aux->ObterTipo();
			alien.x = aux->ObterX();
			alien.y = aux->ObterY();
			fwrite(&alien, sizeof(TObjeto), 1, m_arquivo);
		}
	}
    fclose(m_arquivo);
}


//------------------------------------------------------------
void CAlien::Excluir(int tipo, int x, int y)
{
	CAlien *aux, *del;

	for(aux = this; aux->m_p_alien;)
	{
		if(aux->m_p_alien->ObterTipo() == tipo
		&& aux->m_p_alien->ObterX()    == x
		&& aux->m_p_alien->ObterY()    == y)
		{
			del = aux->m_p_alien;
			aux->m_p_alien = aux->m_p_alien->m_p_alien;
			delete del;
			m_num_aliens--;
		}
		else
		{
			aux = aux->m_p_alien;
		}
	}
}

void CAlien::Excluir(int x1, int y1, int x2, int y2)
{
	CAlien *aux, *del;

	for(aux = this; aux->m_p_alien;)
	{
		if(aux->m_p_alien->ChecarColisao(x1, y1, x2, y2))
		{
			del = aux->m_p_alien;
			aux->m_p_alien = aux->m_p_alien->m_p_alien;
			delete del;
			m_num_aliens--;
		}
		else
		{
			aux = aux->m_p_alien;
		}
	}
}


//------------------------------------------------------------
int CAlien::ChecarColisaoAliens(int x1, int y1, int x2, int y2)
{
	CAlien *aux;

	for(aux = m_p_alien; aux; aux = aux->m_p_alien)
	{
		if(aux->ChecarColisao(x1, y1, x2, y2))
		{
			return 1;
		}
	}
	return 0;
}

int CAlien::ChecarColisaoAliens(TRect ret)
{
	CAlien *aux;

	for(aux = m_p_alien; aux; aux = aux->m_p_alien)
	{
		if(aux->ChecarColisao(ret))
		{
			return 1;
		}
	}
	return 0;
}


int CAlien::ChecarColisaoAliens()
{
	CAlien *aux;

	for(aux = m_p_alien; aux; aux = aux->m_p_alien)
	{
		if(aux->ChecarColisao(m_x, m_y, m_x + m_largura, m_y + m_altura))
		{
			return 1;
		}
	}
	return 0;
}


//------------------------------------------------------------
void CAlien::Sonorizar()
{
	if(m_status == eAlienExplosao
	&& m_quadro == 0)
	{
		play_sample((SAMPLE *)m_dat_arquivo[WAV_ALIEN_EXPLOSAO].dat, 128, 128, 1000, 0);
	}
	m_tiros.SonorizarTodos();
}


//------------------------------------------------------------
void CAlien::SonorizarTodos()
{
	CAlien *aux;

	for(aux = m_p_alien; aux; aux = aux->m_p_alien)
	{
		if(aux->m_ativo)
		{
			aux->Sonorizar();
		}
	}
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
int CAlien::ObterEnergia()
{
	return m_energia;
}


//------------------------------------------------------------
void CAlien::DecEnergia(int decremento)
{
	m_energia -= decremento;

	if(m_energia == 0)
	{
		m_status = eAlienExplosao;
		m_quadro = 0;
	}
}


//------------------------------------------------------------
CTiro *CAlien::ObterTiros()
{
	return &m_tiros;
}

//------------------------------------------------------------
CObjetoAvancado *CAlien::ObterMaisProximo(int x, int y)
{
	CAlien *aux;
	int menor_distancia = 999;
	int distancia;
	CObjetoAvancado *obj;

	obj = NULL;
	if(m_p_alien)
	{
		for(aux = m_p_alien; aux; aux = aux->m_p_alien)
		{
			if(aux->m_visivel)
			{
				distancia = sqrt(pow(x - aux->m_x, 2) + pow(y - aux->m_y, 2));
				if(distancia < menor_distancia)
				{
					menor_distancia = distancia;
					obj = aux->RetornarObjetoAvancado();
				}
			}
		}
	}
	return obj;
}


//------------------------------------------------------------
int CAlien::ChecarColisaoSombra(TRect area)
{
	if ((m_x + m_largura + m_pos_sombra < area.x1)
	||  (m_y + m_altura  + m_pos_sombra < area.y1)
	||  (m_x           > area.x2)
	||  (m_y           > area.y2))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}