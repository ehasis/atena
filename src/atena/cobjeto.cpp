 /*------------------------------------------------------------*
 *  cobjeto.cpp - Implementacao da Classe Base
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: terça-feira, 22 de setembro de 2001
*
*
*------------------------------------------------------------*/


#include "cobjeto.h"

//------------------------------------------------------------
// CObjetoBasico
//------------------------------------------------------------
void CObjetoBasico::Iniciar(int x, int y, int largura, int altura)
{
	m_x = x;
	m_y = y;
	m_largura = largura;
	m_altura = altura;
}

//------------------------------------------------------------
// retorna se ha colisao com o objeto passado como parametro
int CObjetoBasico::ChecarColisao(TRect &rect)
{
	if ((m_x + m_largura < rect.x1)
	||  (m_y + m_altura  < rect.y1)
	||  (m_x           > rect.x2)
	||  (m_y           > rect.y2))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

int CObjetoBasico::ChecarColisao(int x1, int y1, int x2, int y2)
{
	if ((m_x + m_largura < x1)
	||  (m_y + m_altura  < y1)
	||  (m_x           > x2)
	||  (m_y           > y2))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

int CObjetoBasico::ChecarColisao(int x, int y)
{
	if ((m_x + m_largura < x)
	||  (m_y + m_altura  < y)
	||  (m_x           > x)
	||  (m_y           > y))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

//------------------------------------------------------------
int CObjetoBasico::ChecarColisaoX(int x1, int x2)
{
	if ((m_x + m_largura < x1)
	||  (m_x           > x2))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}


//------------------------------------------------------------
int CObjetoBasico::ChecarColisaoY(int y1, int y2)
{
	if ((m_y + m_altura < y1)
	||  (m_y          > y2))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

//------------------------------------------------------------
// retorna os vertices do retangulo do objeto
TRect& CObjetoBasico::ObterRect()
{
	m_rect.x1 = m_x;
	m_rect.y1 = m_y;
	m_rect.x2 = m_x + m_largura;
	m_rect.y2 = m_y + m_altura;

	return m_rect;
}


//------------------------------------------------------------
void CObjetoBasico::SetarX(int x)
{
	m_x = x;
}


//------------------------------------------------------------
int CObjetoBasico::ObterX()
{
	return m_x;
}


//------------------------------------------------------------
int CObjetoBasico::ObterPMX()
{
	return (m_x + m_largura / 2);
}


//------------------------------------------------------------
int CObjetoBasico::ObterX2()
{
	return (m_x + m_largura);
}

//------------------------------------------------------------
void CObjetoBasico::IncX(int incremento)
{
	m_x += incremento;
}


//------------------------------------------------------------
void CObjetoBasico::DecX(int decremento)
{
	m_x -= decremento;
}


//------------------------------------------------------------
void CObjetoBasico::SetarY(int y)
{
	m_y = y;
}


//------------------------------------------------------------
int CObjetoBasico::ObterY()
{
	return m_y;
}


//------------------------------------------------------------
int CObjetoBasico::ObterPMY()
{
	return (m_y + m_altura / 2);
}


//------------------------------------------------------------
int CObjetoBasico::ObterY2()
{
	return (m_y + m_altura);
}


//------------------------------------------------------------
void CObjetoBasico::IncY(int incremento)
{
	m_y += incremento;
}


//------------------------------------------------------------
void CObjetoBasico::DecY(int decremento)
{
	m_y -= decremento;
}


void CObjetoBasico::SetarXY(int x, int y)
{
	m_x = x;
	m_y = y;
}


//------------------------------------------------------------
void CObjetoBasico::SetarLargura(int largura)
{
	m_largura = largura;
}


//------------------------------------------------------------
int CObjetoBasico::ObterLargura()
{
	return m_largura;
}


//------------------------------------------------------------
void CObjetoBasico::SetarAltura(int altura)
{
	m_altura = altura;
}


//------------------------------------------------------------
int CObjetoBasico::ObterAltura()
{
	return m_altura;
}


//------------------------------------------------------------
void CObjetoBasico::SetarTipoObjeto(EObjeto tipo_objeto)
{
	m_tipo_objeto = tipo_objeto;
}


//------------------------------------------------------------
EObjeto CObjetoBasico::ObterTipoObjeto()
{
	return m_tipo_objeto;
}


//------------------------------------------------------------
CObjetoBasico *CObjetoBasico::RetornarObjetoBasico()
{
	return (CObjeto *)this;
}


//------------------------------------------------------------
// CObjeto
//------------------------------------------------------------
int CObjeto::ObterAngulo()
{
	return m_angulo;
}

void CObjeto::SetarAngulo(int angulo)
{
	m_angulo = angulo;
}


//------------------------------------------------------------
// CObjetoAvancado
//------------------------------------------------------------
void CObjetoAvancado::DesenharExplosao(CTela &m_tela, int x_real, int y_real, int x, int y, int raio, int num_particulas)
{
	m_explosao.IniciarExplosao(x - x_real, y - y_real, raio, num_particulas);
}


//------------------------------------------------------------
void CObjetoAvancado::DesenharExplosaoRadial(int x_real, int y_real, int x, int y, int raio)
{
	m_explosao.IniciarExplosaoRadial (x - x_real, y - y_real, raio);
}

//------------------------------------------------------------
void CObjetoAvancado::SetarAtivo(int ativo)
{
	m_ativo = ativo;
}


//------------------------------------------------------------
int CObjetoAvancado::ObterAtivo()
{
	return m_ativo;
}


//------------------------------------------------------------
int CObjetoAvancado::ObterVisivel()
{
	return m_visivel;
}


//------------------------------------------------------------
void CObjetoAvancado::SetarVisivel(int visivel)
{
	m_visivel = visivel;
}


//------------------------------------------------------------
CObjetoAvancado *CObjetoAvancado::RetornarObjetoAvancado()
{
	return (CObjetoAvancado *)this;
}


//------------------------------------------------------------
int CObjetoAvancado::ObterEnergia() 
{
	return m_energia;
}


//------------------------------------------------------------
void CObjetoAvancado::IncEnergia(int incremento)
{
	m_energia += incremento;
}


//------------------------------------------------------------
void CObjetoAvancado::DecEnergia(int decremento)
{
	m_energia -= decremento;
}

