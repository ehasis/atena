#include "cchefe.h"


//------------------------------------------------------------
void CChefe::Iniciar()
{
	
	SetarX(100);
	SetarY(10);

    /*
	// TESTE
	SetarX(100);
	SetarY(5500);
	/**/

	m_dados.Abrir(ARQUIVO_CHEFES_DAT);
	
	m_armas.Adicionar();
	m_armas.Obter().Iniciar(eArmaCanhao, m_x, m_y);
	m_armas.Obter().SetarTipoTiro(eTiroFogoTeleguiado);
	m_armas.Obter().SetarX(ObterX()- 50);

	m_armas.Adicionar();
	m_armas.Obter().Iniciar(eArmaCanhao, m_x, m_y);
	m_armas.Obter().SetarTipoTiro(eTiroCerra);
	m_armas.Obter().SetarX(ObterX() + 350);


	m_largura = 300;
	m_altura = 240;
	m_energia = 50;
	m_ativo = 1;
	m_visivel = 1;
	m_status = eChefeNormal;

}


//------------------------------------------------------------
void CChefe::Finalizar()
{
	m_dados.Fechar();
	m_armas.Finalizar();
}

void CChefe::Atualizar(TRect area, CObjetoAvancado * const alvo)
{
	if (m_status == eChefeInativo) return;
	if (!ChecarColisao(area))
	{
		m_ativo = FALSE;
		m_visivel = FALSE;
		return;
	}
	m_ativo = TRUE;
	m_visivel = TRUE;
	
	if(m_status != eChefeInativo)
	{
		if(m_quadro == 50) m_status = eChefeInativo;
		else if(m_status == eChefeExplosao) m_quadro++;
	}

	m_armas.MoverPrimeiro();
	m_armas.Obter().Atirar(alvo);
	m_armas.MoverProximo();
	m_armas.Obter().Atirar(alvo);

	m_armas.Atualizar(area, alvo);
}


//------------------------------------------------------------
void CChefe::Desenhar(CTela & tela, int x_real, int y_real)
{
	if (!m_ativo) return;
	char buf[128];
	
	switch (m_status)
	{
		case eChefeNormal:
			sprintf(buf, "Energia: %d", m_energia);
			tela.MaskedBlit(m_dados.Bitmap(0), eCamadaObjetos, 0, 0, m_x - x_real, m_y - y_real, m_largura, m_altura);
			tela.Escrever(eCamadaEfeitos, buf, 150, 30, makecol(0,255,0));
			break;

		case eChefeExplosao:
			DesenharExplosao(tela, x_real, y_real, m_x + (m_largura/2), m_y + (m_altura/2), (m_quadro * 3) + (m_largura / 2), m_largura);
			DesenharExplosaoRadial(x_real, y_real, m_x + (m_largura/2), m_y + (m_altura/2), 100 + (m_quadro * 3));
			/*
			DesenharExplosao(tela, x_real, y_real, m_x + (m_largura/2), m_y + (m_altura/2), (m_quadro * 3) + (m_largura / 2), m_largura);
			DesenharExplosao(tela, x_real, y_real, m_x + m_largura, m_y + m_altura, (m_quadro * 3) + (m_largura / 2), m_largura);
			DesenharExplosao(tela, x_real, y_real, m_x + (m_largura/2), m_y + (m_altura/2), (m_quadro * 3) + (m_largura / 2), m_largura);
			*/

			break;
	}
	m_armas.Desenhar(tela, x_real, y_real);
}


//------------------------------------------------------------
void CChefe::DecEnergia(int decremento)
{
	m_energia -= decremento;

	if(m_energia <= 0)
	{
		m_status = eChefeExplosao;
		m_quadro = 0;
		//m_status = eChefeInativo;
		m_ativo = FALSE;
		m_visivel = FALSE;
	}
}

void CChefe::SetarStatus(EStatusChefe status)
{
	m_status = status;
}

EStatusChefe CChefe::ObterStatus()
{
	return m_status;
}


//------------------------------------------------------------
bool CChefe::Colidir(TRect area, int energia)
{
	if(ChecarColisao(area)
	&& m_status != eChefeInativo
	&& m_status != eChefeExplosao)
	{
		DecEnergia(energia);
		return true;
	}
	return false;
}