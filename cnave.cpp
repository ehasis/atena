 /*------------------------------------------------------------*
 *  cnave.cpp - Implementacao da Classe Nave
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: terça-feira, 18 de setembro de 2001
*
*  Diego em 24/01/2002
*   - Retirado o método SetArquivoDat (obsoleto);
*
*
*------------------------------------------------------------*/

#include <allegro.h>
#include "datnave.h"
#include "datalien.h"
#include "cnave.h"
#include "erro.h"


//------------------------------------------------------------
void CNave::Iniciar(void)
{
	x = 320;
	y = 6300;
	largura = 72;
	altura = 100;
	vi = 20;
	vx = 0;
	vy = 0;
	ativo = TRUE;
	visivel = TRUE;

	turbina		= 0;
	atirar	    = 0;
	pontos	    = 0;
	energia     = 100;
	casco	    = 100;
	status	    = eNaveNormal;
	quadro	    = 2;
	tipo_tiro   = 2;
	dat_arquivo = load_datafile("nave.dat");
}


//------------------------------------------------------------
void CNave::Desligar()
{
	unload_datafile(dat_arquivo);
	dat_arquivo = NULL;
}

//------------------------------------------------------------
// metodo para desenhar o objeto
void CNave::Desenhar(CTela &_tela, int _x_real, int _y_real)
{
	switch(status)
	{
		case eNaveEscudo:
			_tela.DrawSprite(eCamadaObjetos, (BITMAP *)dat_arquivo[ESCUDO].dat, x - _x_real, y - _x_real);
			status = eNaveNormal;

		case eNaveNormal:
			_tela.MaskedBlit((BITMAP *)dat_arquivo[SOMBRA].dat, eCamadaObjetos, (quadro + (5 * turbina)) * (largura / 1.5), 0, x + 50 - _x_real, y + 50 - _y_real, (largura / 1.5), (altura / 1.5));
			_tela.MaskedBlit((BITMAP *)dat_arquivo[NORMAL].dat, eCamadaObjetos, (quadro + (5 * turbina)) * largura , 0, x - _x_real, y - _y_real, largura, altura);
			break;

		case eNaveExplosao:

		case eNaveRenacer:
			_tela.DrawSprite(eCamadaObjetos, (BITMAP *)dat_arquivo[EXPLOSAO].dat, x - _x_real, y - _x_real);
			break;
	}
	tiros.DesenharTodos(_tela, _x_real, _y_real);
}

//------------------------------------------------------------
// metodo para atualizacao do objeto
void CNave::Atualizar(TRect _area, CObjeto * const _alvo)
{
	TEntrada valor;

	valor.a = valor.b = valor.c = valor.x = valor.y = 0;

	atirar = 0;

	// Leitura das Teclas
	if (key[KEY_UP])		valor.y--;
	if (key[KEY_DOWN])		valor.y++;
	if (key[KEY_LEFT])		valor.x--;
	if (key[KEY_RIGHT])		valor.x++;
	if (key[KEY_SPACE])		valor.a = 1;
	if (key[KEY_MINUS_PAD]) valor.b = 1;
	if (key[KEY_PLUS_PAD])  valor.c = 1;

	if (status == eNaveRenacer) status = eNaveNormal;

	// se estiver normal
	if (status == eNaveNormal)
	{

		// com incercia
		switch (valor.x)
		{
		case -1:
			vx = -vi;
			x += vx;
			quadro = quadro > 0 ?quadro - 1 :0;
			break;
		case 0:
			vx /= 2;
			if (vx < 0) x -= abs(vx);
			else        x += vx;
			if(quadro != 2)
			{
				quadro = quadro > 2 ? quadro - 1 :quadro + 1;
			}
			break;
		case 1:
			vx =  vi;
			x += vx;
			quadro = quadro = quadro < 4 ?quadro + 1 : 4;
			break;
		}

		switch (valor.y)
		{
		case -1:
			turbina = 1;
			vy = -vi;
			y += vy;
			break;
		case 0:
			turbina = 0;
			vy /= 2;
			if (vy < 0) y -= abs(vy);
			else        y += vy;
			break;
		case 1:
			turbina = 0;
			vy =  vi;
			y += vy;
			break;
		}


		// Testa os limites da tela
		if (y < _area.y1) y = _area.y1;
		if (y + altura > _area.y2) y = _area.y2 - altura;

		if (x < _area.x1) x = _area.x1;
		if (x + largura > _area.x2) x = _area.x2 - largura;


		// Troca a arma selecionada
		if(valor.b && tipo_tiro > 2)
		{
			tipo_tiro--;
		}
		else
		if(valor.c && tipo_tiro < 4)
		{
			tipo_tiro++;
		}

		// Atira
		if(valor.a)
		{
			//Log("Adicionando tiro nave...");
			tiros.Adicionar((ETiroTipo)tipo_tiro , x + (largura / 2), y, _alvo);
			//Log("Tiro nave adicionado...");
		}
		//Log("Atualizando tiros nave...");
		tiros.AtualizarTodos(_area, _alvo);
		//Log("Ttiros nave atualizados...");
		if (casco <= 0)
		{
			status = eNaveExplosao;
			quadro = 70;
			energia = 0;
		}
	}

	// se estiver explodindo
	if (status == eNaveExplosao)
	{
		// se o quadro explodindo esgotou
		if (quadro <= 0)
		{
			vi = 12;
			status = eNaveRenacer;
			energia = 100;
		}
		else
		{
			quadro--;
		}
	}


	/*
	quadro++;
	if (quadro == 15)
	{
		quadro = 0;

		if (energia < 100)
			energia++;
	}
	*/
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
void CNave::Sonorizar(void)
{
	tiros.SonorizarTodos();
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

