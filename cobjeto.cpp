 /*------------------------------------------------------------*
 *  cobjeto.cpp - Implementacao da Classe Base
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: terça-feira, 22 de setembro de 2001
*
*  Diego em 13/02/2002
*   - Alterado o método DesenharExplosao para aceitar CTela e
*     posicionamento relativo;
*
*------------------------------------------------------------*/


#include <allegro.h>
#include "cobjeto.h"


//------------------------------------------------------------
// retorna se ha colisao com o objeto passado como parametro
int CObjeto::ChecarColisao(TRect _rect)
{
	if ((x + largura < _rect.x1)
	||  (y + altura  < _rect.y1)
	||  (x           > _rect.x2)
	||  (y           > _rect.y2))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

int CObjeto::ChecarColisao(int _x1, int _y1, int _x2, int _y2)
{
	if ((x + largura < _x1)
	||  (y + altura  < _y1)
	||  (x           > _x2)
	||  (y           > _y2))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

int CObjeto::ChecarColisao(int _x, int _y)
{
	if ((x + largura < _x)
	||  (y + altura  < _y)
	||  (x           > _x)
	||  (y           > _y))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

//------------------------------------------------------------
int CObjeto::ChecarColisaoX(int _x1, int _x2)
{
	if ((x + largura < _x1)
	||  (x           > _x2))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}


//------------------------------------------------------------
int CObjeto::ChecarColisaoY(int _y1, int _y2)
{
	if ((y + altura < _y1)
	||  (y          > _y2))
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
TRect CObjeto::ObterRect(void)
{
	TRect ret;

	ret.x1 = x;
	ret.y1 = y;
	ret.x2 = x + largura;
	ret.y2 = y + altura;

	return ret;
}


//------------------------------------------------------------
void CObjeto::SetarX(int _x)
{
	x = _x;
}


//------------------------------------------------------------
int CObjeto::ObterX(void)
{
	return x;
}


//------------------------------------------------------------
int CObjeto::ObterPMX(void)
{
	return (x + largura / 2);
}


//------------------------------------------------------------
int CObjeto::ObterX2(void)
{
	return (x + largura);
}

//------------------------------------------------------------
void CObjeto::IncX(int _incremento)
{
	x += _incremento;
}


//------------------------------------------------------------
void CObjeto::DecX(int _decremento)
{
	x -= _decremento;
}


//------------------------------------------------------------
void CObjeto::SetarY(int _y)
{
	y = _y;
}


//------------------------------------------------------------
int CObjeto::ObterY(void)
{
	return y;
}


//------------------------------------------------------------
int CObjeto::ObterPMY(void)
{
	return (y + altura / 2);
}


//------------------------------------------------------------
int CObjeto::ObterY2(void)
{
	return (y + altura);
}


//------------------------------------------------------------
void CObjeto::IncY(int _incremento)
{
	y += _incremento;
}


//------------------------------------------------------------
void CObjeto::DecY(int _decremento)
{
	y -= _decremento;
}


//------------------------------------------------------------
void CObjeto::SetarLargura(int _largura)
{
	largura = _largura;
}


//------------------------------------------------------------
int CObjeto::ObterLargura(void)
{
	return largura;
}


//------------------------------------------------------------
void CObjeto::SetarAltura(int _altura)
{
	altura = _altura;
}


//------------------------------------------------------------
int CObjeto::ObterAltura(void)
{
	return altura;
}


//------------------------------------------------------------
void CObjeto::DesenharExplosao(CTela &_tela, int _x_real, int _y_fase, int _x, int _y, int _raio, int _num_particulas)
{
	int ex, ey, ei;

	for (ei = 0; ei < _num_particulas; ei++)
	{
		ex = (rand() % (_raio * 2)) - _raio;
		ey = (rand() % (_raio * 2)) - _raio;

		if ((ex * ex) + (ey * ey) <= _raio * _raio)
		{
			_tela.PutPixel(eCamadaEfeitos, ex + _x - _x_real, ey + _y - _y_fase, makecol(255,rand()%255,0));
		}
	}
}


//------------------------------------------------------------
CObjeto *CObjeto::RetornarObjeto(void)
{
	return (CObjeto *)this;
}


//------------------------------------------------------------
int CObjeto::Obter_ativo(void)
{
	return ativo;
}


//------------------------------------------------------------
int CObjeto::Obter_visivel(void)
{
	return visivel;
}
