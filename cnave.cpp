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

//------------------------------------------------------------
// constructor
CNave::CNave()
{
	x = 300;
	y = 380;
	l = 50;
	a = 90;
	v = 12;
	vx = 0;
	vy = 0;

	atirar	= 0;
	pontos	= 0;
	energia = 100;
	casco	= 100;
	status	= eNaveNormal;
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
	case eNaveEscudo:
		draw_sprite(bmp, (BITMAP *)data[ESCUDO].dat, x, y);
	
	case eNaveNormal:
		draw_sprite(bmp, (BITMAP *)data[NORMAL].dat, x, y);
		status = eNaveNormal;
		break;
	
	case eNaveExplosao:
	
	case eNaveRenacer:
		draw_sprite(bmp, (BITMAP *)data[EXPLOSAO].dat, x, y);
		break;
	}
}

//------------------------------------------------------------
// metodo para atualizacao do objeto
void CNave::Atualizar(TEntrada &valor)
{
	atirar = 0;
	if (status == eNaveRenacer) status = eNaveNormal;
	
	/* se estiver normal */
	if (status == eNaveNormal)
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

		if (y < 0) y = 0;
		if (y + a > 479) y = 478 - a;

		if (x < 0) x = 0;
		if (x + l > 639) x = 639 - l;

		atirar = valor.a;
		
		if (casco <= 0)
		{
			status = eNaveExplosao;
			tempo = 70;
			energia = 0;
		}
	}

	/* se estiver explodindo */
	if (status == eNaveExplosao)
	{
		/* se o tempo explodindo esgotou */
		if (tempo <= 0)
		{
			v = 12;
			status = eNaveRenacer;
			energia = 100;
		}
		else
		{
			tempo--;
		}
	}
}