 /*------------------------------------------------------------*
 *  cnave.cpp - Implementacao da Classe Nave
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: terça-feira, 18 de setembro de 2001
*
*  
*
*------------------------------------------------------------*/

#include <allegro.h>
#include "datnave.h"
#include "cnave.h"
#include "centrada.h"

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

/*************************************************************/
//------------------------------------------------------------
// constructor
CNave::CNave()
{
	x = 300;
	y = 380;
	l = 64;
	a = 100;
	v = 12;
	vx = 0;
	vy = 0;

	
	pontos	= 0;
	energia = 100;
	status	= 1;
	vidas	= 3;
	atirar	= 0;
}


//------------------------------------------------------------
void CNave::setDataFile(DATAFILE *arquivo)
{
	data = arquivo;
}
//------------------------------------------------------------
void CNave::Desligar()
{
	unload_datafile(data);
}

//------------------------------------------------------------
// metodo para desenhar o objeto
void CNave::Desenhar(BITMAP *bmp)
{
	switch(status)
	{
	case 1: //normal
		draw_sprite(bmp, (BITMAP *)data[NORMAL].dat, x, y);
		break;
	case 2: //esplosao
	case 3: //renacer
		draw_sprite(bmp, (BITMAP *)data[EXPLOSAO].dat, x, y);
		break;
	}
}

//------------------------------------------------------------
// metodo para atualizacao do objeto
void CNave::Atualizar(TEntrada &valor)
{
	atirar = 0;
	if (status == 3) status = 1;
	/* se estiver normal */
	if (status == 1)
	{
		
		/* se tiver energia */
		if (energia > 0)
		{
			/* com incercia */

			if(valor.y >  0) vy =  v;
			if(valor.y <  0) vy = -v;
			if(valor.y == 0) vy /= 2;
			
			if(valor.x >  0) vx =  v;
			if(valor.x <  0) vx = -v;
			if(valor.x == 0) vx /= 2;

			y += vy;
			x += vx;
			

			/* sem inercia 
			
			if(valor.y >  0) y += v;
			if(valor.y <  0) y -= v;
			
			if(valor.x >  0) x += v;
			if(valor.x <  0) x -= v;
			*/
			
			atirar = valor.a;
		}
		else
		{
			status = 2;
			vidas--;
			tempo = 70;
			energia = 0;
		}
	}

	/* se estiver explodindo */
	if (status == 2)
	{
		/* se o tempo explodindo esgotou */
		if (tempo <= 0)
		{
			status = 3;
			energia = 100;
		}
		else
		{
			tempo--;
		}
	}
}