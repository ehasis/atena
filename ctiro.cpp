 /*------------------------------------------------------------*
 *  ctiro.cpp - Implementação da Classe de tiro
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: terça-feira, 13 de janeiro de 2002
*
*
*------------------------------------------------------------*/


#include <stdio.h>
#include <allegro.h>
#include "erro.h"
#include "ctiro.h"
#include <math.h>


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
	m_p_tiro = NULL;
}


//------------------------------------------------------------
void CTiro::Iniciar(ETiro tipo, int x, int y, CObjetoAvancado * const alvo)
{
	m_tipo		= tipo;
	m_x			= x;
	m_y			= y;
	m_alvo		= alvo;
	m_dir_x		= 0;
	m_dir_y		= 0;
	m_flag_x		= 0;
	m_flag_y		= 0;
	m_cont		= 0;
	m_quadro		= 0;
	m_tocar_som	= 1;
	m_status		= eTiroNormal;
	m_ativo		= 1;
	m_visivel	= 1;
	m_objeto	= eTiro;

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
			m_velocidade = 4;
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
			m_velocidade = 4;
			break;

	}
	m_x = x - (m_largura / 2);
}



//------------------------------------------------------------
void CTiro::Adicionar(ETiro tipo, int x, int y, CObjetoAvancado * const alvo)
{
	CTiro *aux;

    for(aux = this; aux->m_p_tiro; aux = aux->m_p_tiro);

	aux->m_p_tiro = new CTiro;
	/*
	if(!aux->m_p_tiro)
	{
		Erro("Código do erro:", "0500");
	}
	*/
	aux->m_p_tiro->Iniciar(tipo, x, y, alvo);
}


//------------------------------------------------------------
void CTiro::Atualizar(CObjetoAvancado * const alvo)
{
	Log("CTiro::Atualizar();");
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


//------------------------------------------------------------
void CTiro::AtualizarTodos(TRect area, CObjetoAvancado * const alvo)
{
	Log("CTiro::AtualizarTodos();");
	CTiro *aux, *del;

	for(aux = this; aux->m_p_tiro;)
	{
		if(aux->m_p_tiro->ChecarColisao(area)
		&& aux->m_p_tiro->m_status != eTiroExplosao	)
		{
			aux->m_p_tiro->Atualizar(alvo);
			aux->m_p_tiro->m_ativo = 1;
			aux = aux->m_p_tiro;
		}
		else
		{
			del = aux->m_p_tiro;
			aux->m_p_tiro = aux->m_p_tiro->m_p_tiro;
			delete del;
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
			
			break;

		case eTiroExplosao:
			DesenharExplosao(tela, x_real, y_real, m_x + (m_largura/2), m_y + (m_altura/2), (m_quadro * 3) + (m_largura / 2), 250);
		break;
	}
}


//------------------------------------------------------------
void CTiro::DesenharTodos(CTela & tela, int x_real, int y_real)
{
	Log("[INICIO]:CTiro::DesenharTodos();");
	CTiro *aux;

	for(aux = m_p_tiro; aux; aux = aux->m_p_tiro)
	{
		if(aux->m_ativo)
		{
			aux->Desenhar(tela, x_real, y_real);
		}
	}
	Log("[FIM]:CTiro::DesenharTodos();");
}


//------------------------------------------------------------
int CTiro::VerificarExisteTiros()
{
	if(m_p_tiro) return 1;
	return 0;
}


//------------------------------------------------------------
int CTiro::ChecarColisaoTiros(TRect obj)
{
	CTiro *aux;

	for(aux = m_p_tiro; aux; aux = aux->m_p_tiro)
	{
		if(aux->ChecarColisao(obj))
		{
			return 1;
		}
	}
	return 0;
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
		play_sample((SAMPLE *)m_dat_arquivo[WAV_TIRO_EXPLOSAO].dat, 100, 128, 1000, 0);
	}
}


//------------------------------------------------------------
void CTiro::SonorizarTodos()
{
	CTiro *aux;

	for(aux = m_p_tiro; aux; aux = aux->m_p_tiro)
	{
		if(aux->m_ativo)
		{
			aux->Sonorizar();
		}
	}
}


//------------------------------------------------------------
void CTiro::SetarStatus(EStatusTiro status)
{
	m_status = status;
}

//------------------------------------------------------------
void CTiro::Finalizar()
{
	Log("CTiro::Finalizar();");

	CTiro *aux, *del;

	for(aux = m_p_tiro; aux;)
	{
		del = aux;
		aux = aux->m_p_tiro;
		delete del;
	}
	m_p_tiro = NULL;
}


//------------------------------------------------------------
CObjetoAvancado *CTiro::ObterMaisProximo(int x, int y)
{
	CTiro *aux;
	int menor_distancia = 999;
	int distancia;
	CObjetoAvancado *obj;

	obj = NULL;
	if(m_p_tiro)
	{
		for(aux = m_p_tiro; aux; aux = aux->m_p_tiro)
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
