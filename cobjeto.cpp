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
// retorna se ha colisao com o objeto passado como parametro
int CObjeto::Colisao(TRect &rect)
{
	if ((x + l < rect.e)
	||  (y + a < rect.t)
	||  (x     > rect.d)
	||  (y     > rect.b))
	{		
		return 0;
	}
	else
	{
		return 1;
	}
}

//------------------------------------------------------------
// retorna os vertices do retangulo do objeto
TRect CObjeto::Rect()
{
	ret.e = x;
	ret.t = y;
	ret.d = x + l;
	ret.b = y + a;

	return ret;
}