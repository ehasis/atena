 /*------------------------------------------------------------*
 *  ctiro.h - Classe CTiro
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: terça-feira, 13 de janeiro de 2002
*
*  Diego Giacomelli em 13/02/2002
*   - Alterado os métodos Desenhar e DesenharTodos para aceitar
*     CTela e posicionamento relativo;
*
*  Diego Giacomelli em 24/02/2002
*   - Incluido membro de dados m_velocidade;
*
*  Diego Giacomelli em 05/03/2002
*   - Alterada herância para CObjetoAvancado;
*
*  Diego Giacomelli em 01/05/2002
*   - Inserido o método ObterMaisProximo;
*
*  Diego Giacomelli em 23/06/2002
*   - Renomeado ETiroTipo para ETiro
*
*  Diego Giacomelli em 20/06/2002
*	- Alterada toda a classe para ser utilizada com CColecaoAvancada;
*	- Implementado método ObterStatus;
*------------------------------------------------------------*/

#ifndef ctiro_h_incluido
#define ctiro_h_incluido

#include "callegro.h"

#include "cobjeto.h"
#include "tiros.h"

typedef enum
{
	eTiroCerra,
	eTiroBola,
	eTiroLaserVermelho,
	eTiroLaserVerde,
	eTiroFogoTeleguiado,
	eTiroFogo
} ETiro;


typedef enum
{
	eTiroNormal,
	eTiroExplosao,
	eTiroInativo
} EStatusTiro;

//------------------------------------------------------------
// Classe para as tiros
class CTiro : public CObjetoAvancado
{
public:
	static void CarregarArquivoDados(const char *arquivo);
	static void DescarregarArquivoDados();

public:
	CTiro();
	void Iniciar(ETiro tipo, int x, int y, CObjetoAvancado * const alvo);
	void Atualizar(TRect &area, CObjetoAvancado * const alvo);
	void Desenhar(CTela &tela, int x_real, int y_real);
	void Sonorizar();
	void SetarStatus(EStatusTiro status);
	EStatusTiro ObterStatus();
	void Finalizar();
	
	
private:
	int m_tocar_som;
	int m_dir_x;
	int m_dir_y;
	int m_flag_x;
	int m_flag_y;
	int m_cont;
	int m_velocidade;

	ETiro m_tipo;
	EStatusTiro m_status;
	CObjetoAvancado *m_alvo;
	static GADados m_dat_arquivo;
};


//------------------------------------------------------------
inline void CTiro::Iniciar(ETiro tipo, int x, int y, CObjetoAvancado * const alvo)
{
	m_tipo		= tipo;
	m_x			= x;
	m_y			= y;
	m_alvo		= alvo;
	m_dir_x		= 0;
	m_dir_y		= 0;
	m_flag_x	= 0;
	m_flag_y	= 0;
	m_cont		= 0;
	m_quadro	= 0;
	m_tocar_som	= 1;
	m_status	= eTiroNormal;
	m_ativo		= 1;
	m_visivel	= 1;
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
			m_largura = 17;
			m_altura  = 17;
			m_velocidade = 50;
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
inline void CTiro::Atualizar(TRect &area, CObjetoAvancado * const alvo)
{
	int area_y1_ant = area.y1;

	area.y1 += m_altura * 2;	// Não permite que o tiro colida com objetos que 
								 	// ainda não entraram na tela
	
	if(m_status != eTiroExplosao
	&& m_status != eTiroInativo
	&& ChecarColisao(area))
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
				m_cont++;
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
	area.y1 = area_y1_ant;
}


//------------------------------------------------------------
inline void CTiro::Desenhar(CTela &tela, int x_real, int y_real)
{

	switch(m_status)
	{
		case eTiroNormal:
			tela.MaskedBlit(m_dat_arquivo.Bitmap(m_tipo * 2), eCamadaEfeitos, m_largura * m_quadro, 0, m_x - x_real, m_y - y_real, m_largura, m_altura);
			//DesenharExplosao(tela, x_real, y_real, m_x + (m_largura/2), m_y + (m_altura/2), (m_quadro * 3) + (m_largura / 2), m_largura);
			/*
			if (m_tipo == eTiroCerra)
				m_explosoes.IniciarExplosao(m_x - x_real + (m_largura / 2), m_y - y_real + (m_altura / 2), (m_quadro * 3) + (m_largura / 2), m_largura);
			/**/
			break;

		case eTiroExplosao:
			DesenharExplosao(tela, x_real, y_real, m_x + (m_largura/2), m_y + (m_altura/2), (m_quadro * 3) + (m_largura / 2), m_largura);		
			break;
	}
}

//------------------------------------------------------------
inline void CTiro::Sonorizar()
{
	if(m_tocar_som && m_status == eTiroNormal)
	{
		stop_sample(m_dat_arquivo.Sample((m_tipo * 2) + 1));
		play_sample(m_dat_arquivo.Sample((m_tipo * 2) + 1), 100, 128, 1000, 0);
		m_tocar_som = 0;
	}
	else if(m_status == eTiroExplosao)
	{
		//play_sample(m_dat_arquivo.Sample(WAV_TIRO_EXPLOSAO), 100, 128, 1000, 0);
	}
}


//------------------------------------------------------------
inline void CTiro::SetarStatus(EStatusTiro status)
{
	m_status = status;
}


//------------------------------------------------------------
inline EStatusTiro CTiro::ObterStatus()
{
	return m_status;
}

//------------------------------------------------------------
inline void CTiro::Finalizar()
{
	//nada
}


#endif

