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
void CVeiculo::Iniciar(TObjeto &obj)
{
	CInimigo::Iniciar(obj);

	m_flag_x	= (rand() % 2) * -2 + 1;
	m_flag_y	= (rand() % 2) * -2 + 1;
	m_dir_x     = 0;
	m_dir_y	    = 1;
}

//------------------------------------------------------------
void CVeiculo::Finalizar()
{
	CInimigo::Finalizar();
}


//------------------------------------------------------------
void CVeiculo::Desenhar(CTela &tela, int x_real, int y_real)
{
	switch(m_status)
	{
		case eInimigoNormal:
			tela.RotateSprite(eCamadaObjetos, m_bitmap, m_x - x_real, m_y - y_real, itofix(m_angulo));

			break;
			
		case eInimigoExplosao:
			DesenharExplosaoRadial(x_real, y_real, m_x + (m_largura / 2), m_y + (m_altura / 2), (m_quadro * 3) + (m_largura / 2));
	  		break;
	}
	m_armas.Desenhar(tela, x_real, y_real);
}



//------------------------------------------------------------
void CVeiculo::Atualizar(TRect &area, CObjetoAvancado * const alvo)
{
	
	if(ChecarColisao(area)
	|| m_armas.Obter().ObterTiros().ObterQuantidade())
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

	
		if(m_status != eInimigoInativo)
		{	
			if(m_quadro == 10) m_status = eInimigoInativo;
			else if(m_status == eInimigoExplosao) m_quadro++;
			else if(m_energia <= 0) m_status = eInimigoExplosao;
		}
		m_armas.Obter().SetarXY(m_x, m_y);
		m_armas.Atualizar(area, alvo);
	}
}