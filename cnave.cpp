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

//------------------------------------------------------------
// constructor
CNave::CNave()
{
	x = 320;
	y = 6300;
	largura = 72;
	altura = 90;
	vi = 12;
	vx = 0;
	vy = 0;

	atirar	  = 0;
	pontos	  = 0;
	energia   = 100;
	casco	  = 100;
	status	  = eNaveNormal;
	tempo	  = 2;
	tipo_tiro = 0;
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
	tiros.DesenharTodos(bmp);
	switch(status)
	{
	case eNaveEscudo:
		draw_sprite(bmp, (BITMAP *)data[ESCUDO].dat, x, y);
		status = eNaveNormal;

	case eNaveNormal:
		masked_blit((BITMAP *)data[SOMBRA].dat, bmp, tempo * (largura / 1.5), 0, x + 50, y + 50, (largura / 1.5), (altura / 1.5));
		masked_blit((BITMAP *)data[NORMAL].dat, bmp, tempo * largura, 0, x, y, largura, altura);
		break;

	case eNaveExplosao:

	case eNaveRenacer:
		draw_sprite(bmp, (BITMAP *)data[EXPLOSAO].dat, x, y);
		break;
	}
}

//------------------------------------------------------------
// metodo para atualizacao do objeto
void CNave::Atualizar(int _x1, int _y1, int _x2, int _y2)
{
	TEntrada valor;
	
	valor.a = valor.b = valor.c = valor.x = valor.y = 0; 

	atirar = 0;

	/* Leitura das Teclas */
	if (key[KEY_UP])		valor.y--;
	if (key[KEY_DOWN])		valor.y++;
	if (key[KEY_LEFT])		valor.x--;
	if (key[KEY_RIGHT])		valor.x++;
	if (key[KEY_SPACE])		valor.a = 1;
	if (key[KEY_MINUS_PAD]) valor.b = 1; 
	if (key[KEY_PLUS_PAD])  valor.c = 1; 

	if (status == eNaveRenacer) status = eNaveNormal;

	/* se estiver normal */
	if (status == eNaveNormal)
	{

		/* com incercia */
		switch (valor.y)
		{
		case -1:
			vy = -vi;
			y += vy;
			break;
		case 0:
			vy /= 2;
			if (vy < 0) y -= abs(vy);
			else        y += vy;
			break;
		case 1:
			vy =  vi;
			y += vy;
			break;
		}
		
		switch (valor.x)
		{
		case -1:
			vx = -vi;
			x += vx;
			tempo = tempo > 0 ?tempo - 1 :0;
			break;
		case 0:
			vx /= 2;
			if (vx < 0) x -= abs(vx);
			else        x += vx;
			if(tempo != 2)
			{
				tempo = tempo > 2 ? tempo - 1 :tempo + 1;
			}
			break;
		case 1:
			vx =  vi;
			x += vx;
			tempo = tempo = tempo < 4 ?tempo + 1 : 4;
			break;
		}

		/* Testa os limites da tela */
		if (y < _y1) y = _y1;
		if (y + altura > _y2) y = _y2 - altura;

		if (x < _x1) x = _x1;
		if (x + largura > _x2) x = _x2 - largura;
	

		/* Troca a arma selecionada */
		if(valor.b && tipo_tiro > 0)
		{
			tipo_tiro--;
		}
		else 
		if(valor.c && tipo_tiro < 4)
		{
			tipo_tiro++;
		}

		/* Atira */
		if(valor.a)
		{
			tiros.Adicionar((ETiroTipo)tipo_tiro , x + (largura / 2), y);
		}
		tiros.AtualizarTodos(0, 0, 640, 0, _x1, _y1, _x2,  _y2);

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


	/*tempo++;
	if (tempo == 15)
	{
		tempo = 0;

		if (energia < 100)
			energia++;
	}*/
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
void CNave::TocarSom(void)
{
	tiros.TocarSomTodos();
}


//------------------------------------------------------------
CTiro *CNave::ObterTiros(void)
{
	return &tiros;
}


//------------------------------------------------------------
int CNave::ObterPontos(void)
{
	return pontos;
}


//------------------------------------------------------------
void CNave::IncPontos(int _incremento)
{
	pontos += _incremento;
}


//------------------------------------------------------------
int CNave::ObterCasco(void)
{
	return casco;
}


//------------------------------------------------------------
int CNave::ObterEnergia(void)
{
	return energia;
}


//------------------------------------------------------------
int CNave::ObterStatus(void)
{
	return status;
}

