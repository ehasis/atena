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
#include "datalien.h"
#include "cnave.h"
#include "centrada.h"

//------------------------------------------------------------
// constructor
CNave::CNave()
{
	x = 300;
	y = 380;
	l = 50;
	a = 90;
	vi = 12;
	vx = 0;
	vy = 0;

	atirar	= 0;
	pontos	= 0;
	energia = 100;
	casco	= 100;
	status	= eNaveNormal;
	tempo	= 0;
}


//------------------------------------------------------------
void CNave::SetArquivoDat(DATAFILE *arquivo)
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
		status = eNaveNormal;

	case eNaveNormal:
		draw_trans_sprite(bmp, (BITMAP *)data[SOMBRA].dat, x+50, y+70);
		draw_sprite(bmp, (BITMAP *)data[NORMAL].dat, x, y);
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
		if(valor.y >  0) vy =  vi;
		if(valor.y <  0) vy = -vi;
		if(valor.y == 0) vy /= 2;
		
		if(valor.x >  0) vx =  vi;
		if(valor.x <  0) vx = -vi;
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
			vi = 12;
			status = eNaveRenacer;
			energia = 100;
		}
		else
		{
			tempo--;
		}
	}

	tempo++;
	if (tempo == 15)
	{
		tempo = 0;
		
		if (energia < 100)
			energia++;
	}
}

//------------------------------------------------------------
void CNave::DecEnergia(int valor)
{
	if (energia < valor)
	{
		if (casco < (valor - energia))
			casco = 0;
		else
			casco -= (valor - energia);

		energia = 0;
	}
	else
		energia -= valor;
}

//------------------------------------------------------------
void CNave::IncEnergia(int valor)
{
	if (energia > valor)
		energia = 100;
	else
		energia += valor;
}

//------------------------------------------------------------
void CAlien::SetArquivoDat(DATAFILE *arquivo)
{
	data = arquivo;
}

//------------------------------------------------------------
void CAlien::Desligar()
{
	unload_datafile(data);
}

//------------------------------------------------------------
void CAlien::Desenhar(BITMAP *bmp)
{

	switch(status)
	{
	//case eAlienEscudo:
		//draw_sprite(bmp, (BITMAP *)data[ALIEN_ESCUDO].dat, x, y);	
		//status = eAlienNormal;
	case eAlienNormal:
		draw_trans_sprite(bmp, (BITMAP *)data[ALIEN_SOMBRA].dat, x+50, y+70);
		draw_sprite(bmp, (BITMAP *)data[ALIEN_2].dat, x, y);
		break;
	
	case eAlienExplosao:
		masked_blit((BITMAP *)data[ALIEN_EXPLOSAO].dat, bmp, 250-(((tempo * 2) - ((tempo * 2)%10)) * 5), 0, x, y, 50, 50);
		break;
	}
}

//------------------------------------------------------------
void CAlien::Atualizar()
{
	if (status == eAlienNormal || status == eAlienEscudo)
	{
		if (x < -l) status = eAlienInativo;
		y += vi;
	}
	
	if (status == eAlienExplosao)
	{
		tempo--;
		if (tempo <= 0)
		{
			status = eAlienInativo;
		}
	}
}
