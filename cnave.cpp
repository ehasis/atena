 /*------------------------------------------------------------*
 *  cnave.cpp - Implementacao da Classe Nave
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: terça-feira, 18 de setembro de 2001
*
*
*------------------------------------------------------------*/

#include <allegro.h>
#include "datnave.h"
#include "datalien.h"
#include "cnave.h"
#include "erro.h"


//------------------------------------------------------------
CNave::CNave()
{
}


//------------------------------------------------------------
void CNave::Iniciar(int tipo, int x, int y)
{
	Log("[INICIO]:CNave::Iniciar()");

	m_armas.Adicionar();
	m_armas.Obter().Iniciar(eArmaCanhao, x, y);

	m_armas.Adicionar();
	m_armas.Obter().Iniciar(eArmaCanhao, x, y);

	m_armas.Adicionar();
	m_armas.Obter().Iniciar(eArmaCanhao, x, y);

	m_largura = 72;
	m_altura = 100;
	SetarX(x);
	SetarY(y);
	m_tipo = tipo;
	m_vi = 5;
	m_vx = 0;
	m_vy = 0;
	m_dx = 0;
	m_dy = 0;
	m_ativo = TRUE;
	m_visivel = TRUE;
	m_turbina = 0;
	m_atirar = 0;
	m_pontos = 0;
	m_energia = 100;
	m_casco	= 100;
	m_status = eNaveNormal;
	m_quadro = 2;
	m_tipo_tiro = 3;
	m_dat_arquivo = load_datafile("nave.dat");
	SetarTeclas();
	Log("[FIM]:CNave::Iniciar()");

}


//------------------------------------------------------------
void CNave::Finalizar()
{
	unload_datafile(m_dat_arquivo);
	m_dat_arquivo = NULL;

	m_armas.Finalizar();
}

//------------------------------------------------------------
// metodo para desenhar o objeto
void CNave::Desenhar(CTela & tela, int x_real, int y_real)
{
	switch(m_status)
	{
		case eNaveEscudo:
			tela.DrawSprite(eCamadaObjetos, (BITMAP *)m_dat_arquivo[ESCUDO].dat, m_x - x_real, m_y - x_real);
			m_status = eNaveNormal;

		case eNaveNormal:
             tela.MaskedBlit((BITMAP *)m_dat_arquivo[NAVE_13_S].dat, eCamadaObjetos, m_quadro * (m_largura / 1.5), 0, m_x + 50 - x_real, m_y + 50 - y_real, (m_largura / 1.5), (m_altura / 1.5));
			 tela.MaskedBlit((BITMAP *)m_dat_arquivo[NAVE_13].dat, eCamadaObjetos, m_quadro * m_largura , 0, m_x - x_real, m_y - y_real, m_largura, m_altura);
			 if(m_turbina)
			 {
				DesenharExplosao(tela, x_real, y_real, m_x + (m_largura/2) - 13, m_y + m_altura - 20, 5, 10);
				DesenharExplosao(tela, x_real, y_real, m_x + (m_largura/2) + 10, m_y + m_altura - 20, 5, 10);
			 }
			 else
			 {
				 DesenharExplosao(tela, x_real, y_real, m_x + (m_largura/2) - 13, m_y + m_altura - 20, 3, 10);
				 DesenharExplosao(tela, x_real, y_real, m_x + (m_largura/2) + 10, m_y + m_altura - 20, 3, 10);
			 }
			break;

		case eNaveExplosao:
			DesenharExplosao(tela, x_real, y_real, m_x + (m_largura/2), m_y + (m_altura/2), (m_quadro * 3) + (m_largura / 2), m_largura);
			break;

		case eNaveAtingida:
			break;

		case eNaveRenacer:
			tela.DrawSprite(eCamadaObjetos, (BITMAP *)m_dat_arquivo[EXPLOSAO].dat, m_x - x_real, m_y - x_real);
			break;
	}
	
	m_armas.Desenhar(tela, x_real, y_real);
}

//------------------------------------------------------------
// metodo para atualizacao do objeto
void CNave::Atualizar(TRect area, CObjetoAvancado * const alvo)
{
	TEntrada valor;

	valor.a = valor.b = valor.c = valor.x = valor.y = 0;
	valor.arma_esquerda = valor.arma_centro = valor.arma_direita = false;

	m_atirar = 0;

	// Leitura das Teclas
	if (key[m_tecla_cima])		valor.y--;
	if (key[m_tecla_baixo])		valor.y++;
	if (key[m_tecla_esquerda])		valor.x--;
	if (key[m_tecla_direita])		valor.x++;
	//if (key[]) valor.b = 1;
	//if (key[])  valor.c = 1;
	if (key[m_tecla_arma_esquerda])			valor.arma_esquerda = true;
	if (key[m_tecla_arma_centro])			valor.arma_centro = true;
	if (key[m_tecla_arma_direita])			valor.arma_direita = true;
	if (key[m_tecla_todas_armas])		valor.arma_esquerda = valor.arma_centro = valor.arma_direita = true;

	if (m_status == eNaveRenacer) m_status = eNaveNormal;
	
	/* Teste de HFSM
	if(alvo)
	{
		// Posições
		if(y > alvo->ObterY2())
		{
			if(x < alvo->ObterX()) m_dx = 1;
			else if(x > alvo->ObterX2()) m_dx = -1;
			m_tipo_tiro = 3;
		}
		else
		{
			if(ChecarColisaoX(alvo->ObterX() - alvo->ObterLargura(), alvo->ObterX2() + alvo->ObterLargura()))
			{
				m_dx = (ObterPMX() - alvo->ObterPMX()) >= 0 ? 1 : -1;
				m_tipo_tiro = 4;
				valor.a = 1;
			}
		}

		// Tiros
		if(ChecarColisaoX(alvo->ObterX(), alvo->ObterX2()))
		{
			valor.a = 1;
		}

		if(y > alvo->ObterY2() + alvo->ObterAltura())
		{
			if(ObterY2() == area.y2 && y > area.y1 + (area.y2 - area.y1) / 2) m_dy = -1;
		}
		else m_dy = 1;

	}
	else
	{
		m_dy = 1;
		m_dx = 0;
	}

	/**/

	// se estiver normal
	if (m_status == eNaveNormal)
	{

		m_turbina = 0;
		// com inercia
		switch (valor.x)
		{
		case -1:
		//	m_turbina++;
			m_vx = -m_vi;
			IncX(m_vx);
			m_quadro = m_quadro > 0 ?m_quadro - 1 :0;
			break;
		case 0:
			m_vx /= 2;
			if (m_vx < 0) DecX(abs(m_vx));
			else        IncX(m_vx);
			if(m_quadro != 2)
			{
				m_quadro = m_quadro > 2 ? m_quadro - 1 :m_quadro + 1;
			}
			break;
		case 1:
		//	m_turbina++;
			m_vx =  m_vi;
			IncX(m_vx);
			m_quadro = m_quadro = m_quadro < 4 ?m_quadro + 1 : 4;
			break;
		}

		switch (valor.y)
		{
		case -1:
			m_turbina++; 
			m_vy = -m_vi;
			IncY(m_vy);
			break;
		case 0:
			m_vy /= 2;
			if (m_vy < 0) DecY(abs(m_vy));
			else        IncY(m_vy);
			break;
		case 1:
		//	m_turbina++;
			m_vy =  m_vi;
			IncY(m_vy);
			break;
		}


		// Testa os limites da m_tela
		if (m_y < area.y1)
		{
			SetarY(area.y1);
			m_dy = 0;
		}
		else
		if (m_y + m_altura > area.y2)
		{
			SetarY(area.y2 - m_altura);
			m_dy = 0;
		}

		if (m_x < area.x1)
		{
			SetarX(area.x1);
			m_dx = 0;
		}
		else
		if (m_x + m_largura > area.x2)
		{
			SetarX(area.x2 - m_largura);
			m_dx = 0;
		}


		// Troca a arma selecionada
		if(valor.b && m_tipo_tiro > 2)
		{
			m_tipo_tiro--;
		}
		else
		if(valor.c && m_tipo_tiro < 4)
		{
			m_tipo_tiro++;
		}

		if(valor.a)
		{
			//m_tiros.Adicionar((ETiro)m_tipo_tiro , m_x + (m_largura / 2), m_y, alvo);
		}
		if (m_casco <= 0)
		{
			m_status = eNaveExplosao;
			m_quadro = 70;
			m_energia = 0;
		}
	}

	// se estiver explodindo
	if (m_status == eNaveExplosao)
	{
		// se o quadro explodindo esgotou
		if (m_quadro <= 0)
		{
			m_vi = 12;
			m_status = eNaveRenacer;
			m_energia = 100;
		}
		else
		{
			m_quadro--;
		}
	}

	m_armas.MoverPrimeiro();
	if(valor.arma_esquerda) m_armas.Obter().Atirar(alvo);

	m_armas.MoverProximo();
	if(valor.arma_centro) m_armas.Obter().Atirar(alvo);

	m_armas.MoverProximo();
	if(valor.arma_direita) m_armas.Obter().Atirar(alvo);


	m_armas.Atualizar(area, alvo);

}

//------------------------------------------------------------
void CNave::DecEnergia(int valor)
{
	if (m_energia < valor)
	{
		if (m_casco < (valor - m_energia))
			m_casco = 0;
		else
			m_casco -= (valor - m_energia);

		m_energia = 0;
	}
	else
		m_energia -= valor;
}

//------------------------------------------------------------
void CNave::IncEnergia(int valor)
{
	if (m_energia > valor)
		m_energia = 100;
	else
		m_energia += valor;
}


//------------------------------------------------------------
void CNave::Sonorizar()
{
	m_armas.Sonorizar();
}


//------------------------------------------------------------
int CNave::ObterPontos()
{
	return m_pontos;
}


//------------------------------------------------------------
void CNave::IncPontos(int incremento)
{
	m_pontos += incremento;
}


//------------------------------------------------------------
int CNave::ObterCasco()
{
	return m_casco;
}


//------------------------------------------------------------
int CNave::ObterStatus()
{
	return m_status;
}

//------------------------------------------------------------
CColecaoAvancada< CArma > & CNave::ObterArmas()
{
	return m_armas;
}


//------------------------------------------------------------
void CNave::SetarX(int x)
{
	m_x = x;
	m_armas.MoverPrimeiro();
	m_armas.Obter().SetarX(x - 50);

	m_armas.MoverProximo();
	m_armas.Obter().SetarX(ObterPMX() - m_armas.Obter().ObterLargura() / 2);

	m_armas.MoverProximo();
	m_armas.Obter().SetarX(x + m_largura + 25);
}


//------------------------------------------------------------
void CNave::IncX(int incremento)
{
	m_x += incremento;
	m_armas.MoverPrimeiro();
	m_armas.Obter().IncX(incremento);

	m_armas.MoverProximo();
	m_armas.Obter().IncX(incremento);

	m_armas.MoverProximo();
	m_armas.Obter().IncX(incremento);

}


//------------------------------------------------------------
void CNave::DecX(int decremento)
{
	m_x -= decremento;
	m_armas.MoverPrimeiro();
	m_armas.Obter().DecX(decremento);

	m_armas.MoverProximo();
	m_armas.Obter().DecX(decremento);

	m_armas.MoverProximo();
	m_armas.Obter().DecX(decremento);
}


//------------------------------------------------------------
void CNave::SetarY(int y)
{
	m_y = y;
	m_armas.MoverPrimeiro();
	m_armas.Obter().SetarY(y + 50);

	m_armas.MoverProximo();
	m_armas.Obter().SetarY(y - 60);

	m_armas.MoverProximo();
	m_armas.Obter().SetarY(y + 50);
}


//------------------------------------------------------------
void CNave::IncY(int incremento)
{
	m_y += incremento;
	m_armas.MoverPrimeiro();
	m_armas.Obter().IncY(incremento);

	m_armas.MoverProximo();
	m_armas.Obter().IncY(incremento);

	m_armas.MoverProximo();
	m_armas.Obter().IncY(incremento);
}


//------------------------------------------------------------
void CNave::DecY(int decremento)
{
	m_y -= decremento;
	m_armas.MoverPrimeiro();
	m_armas.Obter().DecY(decremento);

	m_armas.MoverProximo();
	m_armas.Obter().DecY(decremento);

	m_armas.MoverProximo();
	m_armas.Obter().DecY(decremento);
}


//------------------------------------------------------------
bool CNave::Colidir(TRect area, int energia)
{
	bool colidiu = false;

	if(ChecarColisao(area)
	&& m_status != eNaveExplosao)
	{
		DecEnergia(energia);
		colidiu = true;
	}

	if(m_armas.Colidir(area, energia)) colidiu = true;

	return colidiu;
}


//------------------------------------------------------------
void CNave::SetarBonus(int bonus)
{
	m_bonus = bonus;
	switch(m_bonus)
	{
		case eBonusEnergiaTotal:
			m_energia = 100;
			break;
	}
}


//------------------------------------------------------------
void CNave::SetarTeclas(int tecla_cima, int tecla_baixo, int tecla_esquerda, int tecla_direita, int tecla_arma_esquerda, int tecla_arma_centro, int tecla_arma_direita, int tecla_todas_armas)
{
	m_tecla_cima = tecla_cima;
	m_tecla_baixo = tecla_baixo;
	m_tecla_esquerda = tecla_esquerda;
	m_tecla_direita = tecla_direita;
	m_tecla_arma_esquerda = tecla_arma_esquerda;
	m_tecla_arma_centro = tecla_arma_centro;
	m_tecla_arma_direita = tecla_arma_direita;
	m_tecla_todas_armas = tecla_todas_armas;
}