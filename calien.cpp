 /*------------------------------------------------------------*
 *  calien.cpp - Implementação da Classe de alien
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: terça-feira, 13 de dezembro de 2001
*
*  Henrique em 25/01/2002
*   - Implementado metodo DesenharExplosao()
*
*  Diego em 13/02/2002
*   - Alterado os métodos Desenhar e DesenharTodos para aceitar
*     CTela e posicionamento relativo;
*
*------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro.h>
#include <math.h>
#include "aliens.h"
#include "calien.h"
#include "erro.h"

//------------------------------------------------------------
// Membros static
DATAFILE *CAlien::dat_arquivo = NULL;
int CAlien::num_aliens = 0;


//------------------------------------------------------------
// Construtor
CAlien::CAlien(void)
{
	p_alien = NULL;
}


//------------------------------------------------------------
void CAlien::Iniciar(int _tipo, int _x, int _y)
{
	tipo		= _tipo;
	x			= _x;
	y			= _y;
	dir_x       = 0;
	dir_y	    = 1;
	quadro	    = 0;
	ativo       = FALSE;
	visivel		= FALSE;
	atirar      = 150;
	status	    = eAlienNormal;

	switch(tipo)
	{
		case eAlien_01:
			largura    = 47;
			altura     = 31;
			energia	   = 1;
			velocidade = 5;
			dir_x      = 1;
			break;

		case eAlien_02:
			largura    = 50;
			altura     = 50;
			energia	   = 2;
			velocidade = 6;
			break;

		case eAlien_03:
			largura    = 52;
			altura     = 48;
			energia	   = 3;
			velocidade = 7;
			break;

		case eAlien_04:
			largura    = 65;
			altura     = 106;
			energia	   = 4;
			velocidade = 8;
			break;

		case eAlien_05:
			largura    = 41;
			altura     = 38;
			energia	   = 1;
			velocidade = 9;
			break;

		case eAlien_06:
			largura    = 40;
			altura     = 40;
			energia	   = 2;
			velocidade = 8;
			break;

		case eAlien_07:
			largura    = 98;
			altura     = 73;
			energia	   = 3;
			velocidade = 7;
			break;
	}
}


//------------------------------------------------------------
void CAlien::Adicionar(int _tipo, int _x, int _y)
{
	CAlien *aux;

    for(aux = this; aux->p_alien; aux = aux->p_alien);

	aux->p_alien = new CAlien;
	if(!aux->p_alien)
	{
		Erro("Código do erro:", "0000");
	}
	aux->p_alien->Iniciar(_tipo, _x, _y);
	num_aliens++;
}


//------------------------------------------------------------
void CAlien::Atualizar(TRect _area, CObjeto * const _alvo)
{
	time_t tm;

	if (status != eAlienExplosao && status != eAlienInativo)
	{
		switch(tipo)
		{
			case eAlien_01:
				if(x <= (largura * 2))
				{
					dir_x = 1;
				}
				else if(x > SCREEN_W - (largura * 2))
				{
					dir_x = -1;
				}
				break;
			case eAlien_03:
				quadro = quadro < 2 ?quadro + 1 :0;
				break;
			case eAlien_06:
				if(!_alvo->ChecarColisaoX(x, x + largura))
				{
					dir_x = _alvo->ObterX() >= x ? 1 : -1;
				}
				else
				{
					dir_x = 0;
				}
		}
		x += dir_x * velocidade;
		y += dir_y * velocidade;
		
		if(atirar >= 125) 
		{
			srand((unsigned) time(&tm));
			tiros.Adicionar((ETiroTipo) (rand() % 2), x + (largura / 2), y + altura, _alvo);
			atirar = 0;
		}
		atirar += rand() % 11;
	}
	else if(status == eAlienAtingido)
	{
		quadro++;
		if(quadro == 2)
		{
			status = eAlienNormal;
			quadro = 0;
		}
	}
	else if(status == eAlienExplosao)
	{
		quadro++;
		if (quadro == 5)
		{
			status = eAlienInativo;
		}
	}
	tiros.AtualizarTodos(_area, _alvo);
}


//------------------------------------------------------------
void CAlien::AtualizarTodos(TRect _area, CObjeto * const _alvo)
{
	CAlien *aux;

	for(aux = p_alien; aux; aux = aux->p_alien)
	{
		if((aux->ChecarColisao(_area)
		&& aux->status != eAlienExplosao
		&& aux->status != eAlienInativo))
		{
			aux->Atualizar(_area, _alvo);
			aux->ativo = TRUE;
			aux->visivel = TRUE;
		}
		else if(aux->tiros.VerificarExisteTiros())
		{
			aux->Atualizar(_area, _alvo);
			aux->visivel = FALSE;
		}
		else
		{
			aux->ativo = FALSE;
			aux->visivel = FALSE;
		}
	}
}


//------------------------------------------------------------
void CAlien::Desenhar(CTela &_tela, int _x_real, int _y_real)
{
	switch(status)
	{
		case eAlienNormal:

			_tela.MaskedBlit((BITMAP *)dat_arquivo[(tipo * 2) + 1].dat, eCamadaObjetos, quadro * (largura / 1.5), 0, x - _x_real + 50, y  - _y_real + 50, (largura / 1.5), (altura / 1.5));
			_tela.MaskedBlit((BITMAP *)dat_arquivo[(tipo * 2)].dat, eCamadaObjetos, quadro * largura, 0, x - _x_real, y  - _y_real, largura, altura);
			break;

		case eAlienAtingido:
			_tela.MaskedBlit((BITMAP *)dat_arquivo[(tipo * 2) + 1].dat, eCamadaObjetos, quadro * (largura / 1.5), 0, x - _x_real + 50, y  - _y_real + 50, (largura / 1.5), (altura / 1.5));
			_tela.MaskedBlit((BITMAP *)dat_arquivo[(tipo * 2)].dat, eCamadaObjetos, quadro * largura, 0, x - _x_real, y - _y_real, largura, altura);
			break;

		case eAlienExplosao:
			DesenharExplosao(_tela, _x_real, _y_real, x + (largura/2), y + (altura/2), (quadro * 3) + (largura / 2), 250);
			break;
	}
	tiros.DesenharTodos(_tela, _x_real, _y_real);
}


//------------------------------------------------------------
void CAlien::DesenharTodos(CTela &_tela, int _x_real, int _y_real)
{
	CAlien *aux;

	for(aux = p_alien; aux; aux = aux->p_alien)
	{
		if(aux->ativo)
		{
			aux->Desenhar(_tela, _x_real, _y_real);
		}
	}
}


//------------------------------------------------------------
void CAlien::Desligar(void)
{
	CAlien *aux, *del;

	for(aux = p_alien; aux;)
	{
		del = aux;
		aux = aux->p_alien;
		delete del;
		num_aliens--;
	}
}


//------------------------------------------------------------
int CAlien::ObterTipo(void)
{
	return tipo;
}


//------------------------------------------------------------
void CAlien::SalvarAlien(char *_fase)
{
	CAlien *aux;
	TObjeto alien;
	FILE *arquivo;

	if((arquivo = fopen(_fase, "rb+")) != NULL)
	{
		alien.tipo = eAlien;
		fseek(arquivo, 0, SEEK_END);
		for(aux = p_alien; aux; aux = aux->p_alien)
		{
			alien.subtipo = aux->ObterTipo();
			alien.x = aux->ObterX();
			alien.y = aux->ObterY();
			fwrite(&alien, sizeof(TObjeto), 1, arquivo);
		}
	}
    fclose(arquivo);
}


//------------------------------------------------------------
void CAlien::Excluir(int _tipo, int _x, int _y)
{
	CAlien *aux, *del;

	for(aux = this; aux->p_alien;)
	{
		if(aux->p_alien->ObterTipo() == _tipo
		&& aux->p_alien->ObterX()    == _x
		&& aux->p_alien->ObterY()    == _y)
		{
			del = aux->p_alien;
			aux->p_alien = aux->p_alien->p_alien;
			delete del;
			num_aliens--;
		}
		else
		{
			aux = aux->p_alien;
		}
	}
}

void CAlien::Excluir(int _x1, int _y1, int _x2, int _y2)
{
	CAlien *aux, *del;

	for(aux = this; aux->p_alien;)
	{
		if(aux->p_alien->ChecarColisao(_x1, _y1, _x2, _y2))
		{
			del = aux->p_alien;
			aux->p_alien = aux->p_alien->p_alien;
			delete del;
			num_aliens--;
		}
		else
		{
			aux = aux->p_alien;
		}
	}
}


//------------------------------------------------------------
int CAlien::ChecarColisaoAliens(int _x1, int _y1, int _x2, int _y2)
{
	CAlien *aux;

	for(aux = p_alien; aux; aux = aux->p_alien)
	{
		if(aux->ChecarColisao(_x1, _y1, _x2, _y2))
		{
			return TRUE;
		}
	}
	return FALSE;
}

int CAlien::ChecarColisaoAliens(void)
{
	CAlien *aux;

	for(aux = p_alien; aux; aux = aux->p_alien)
	{
		if(aux->ChecarColisao(x, y, x + largura, y + altura))
		{
			return TRUE;
		}
	}
	return FALSE;
}


//------------------------------------------------------------
void CAlien::Sonorizar(void)
{
	if(status == eAlienExplosao
	&& quadro == 0)
	{
		play_sample((SAMPLE *)dat_arquivo[WAV_ALIEN_EXPLOSAO].dat, 128, 128, 1000, 0);
	}
	tiros.SonorizarTodos();
}


//------------------------------------------------------------
void CAlien::SonorizarTodos(void)
{
	CAlien *aux;

	for(aux = p_alien; aux; aux = aux->p_alien)
	{
		if(aux->ativo)
		{
			aux->Sonorizar();
		}
	}
}


//------------------------------------------------------------
void CAlien::SetarStatus(EStatusAlien _status)
{
	status = _status;
}


//------------------------------------------------------------
EStatusAlien CAlien::ObterStatus(void)
{
	return status;
}


//------------------------------------------------------------
int CAlien::ObterEnergia(void)
{
	return energia;
}


//------------------------------------------------------------
void CAlien::DecEnergia(int _decremento)
{
	energia -= _decremento;

	if(energia == 0)
	{
		status = eAlienExplosao;
		quadro = 0;
	}
}


//------------------------------------------------------------
CTiro *CAlien::ObterTiros(void)
{
	return &tiros;
}

//------------------------------------------------------------
CObjeto *CAlien::ObterMaisProximo(int _x, int _y)
{
	CAlien *aux;
	int menor_distancia = 999;
	int distancia;
	CObjeto *obj;

	obj = NULL;
	if(p_alien)
	{
		for(aux = p_alien; aux; aux = aux->p_alien)
		{
			if(aux->visivel)
			{
				distancia = sqrt(pow(_x - aux->x, 2) + pow(_y - aux->y, 2));
				if(distancia < menor_distancia)
				{
					menor_distancia = distancia;
					obj = aux->RetornarObjeto();
				}
			}
		}
	}
	return obj;
}