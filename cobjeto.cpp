 /*------------------------------------------------------------*
 *  cobjeto.cpp - Implementacao da Classe Base
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: terça-feira, 22 de setembro de 2001
*
*
*
*------------------------------------------------------------*/


#include <allegro.h>
#include "cobjeto.h"


//------------------------------------------------------------
/* retorna se ha colisao com o objeto passado como parametro */
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
/* retorna os vertices do retangulo do objeto */
TRect CObjeto::Rect(void)
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