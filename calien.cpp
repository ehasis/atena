 /*------------------------------------------------------------*
 *  calien.cpp - Implementação da Classe de alien
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: terça-feira, 13 de dezembro de 2001
*
*
*
*------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro.h>
#include "aliens.h"
#include "calien.h"
#include "erro.h"


//------------------------------------------------------------
/* Construtor */
CAlien::CAlien(void)
{
	p_alien = NULL;
}


//------------------------------------------------------------
void CAlien::Iniciar(int _tipo, int _x, int _y, DATAFILE *_dat_arquivo)
{
	x			= _x;
	y			= _y;
	tipo		= _tipo;
	dat_arquivo = _dat_arquivo;
	tempo	    = 0;
	atirar		= TRUE;
	atualizado  = TRUE;

	switch(tipo)
	{
		case eAlien_01:
			largura    = 47;
			altura     = 31;
			energia	   = 1;
			atirar	   = 1;
			velocidade = 5;
			status	   = eAlienNormal;
			break;

		case eAlien_02:
			largura    = 50;
			altura     = 50;
			energia	   = 2;
			atirar	   = 1;
			velocidade = 6;
			status	   = eAlienNormal;
			break;

		case eAlien_03:
			largura    = 52;
			altura     = 48;
			energia	   = 2;
			atirar	   = 1;
			velocidade = 7;
			status	   = eAlienNormal;
			break;

		case eAlien_04:
			largura    = 65;
			altura     = 106;
			energia	   = 1;
			atirar	   = 1;
			velocidade = 8;
			status	   = eAlienNormal;
			break;

		case eAlien_05:
			largura    = 41;
			altura     = 38;
			energia	   = 1;
			atirar	   = 1;
			velocidade = 9;
			status	   = eAlienNormal;
			break;

		case eAlien_06:
			largura    = 40;
			altura     = 40;
			energia	   = 3;
			atirar	   = 1;
			velocidade = 8;
			status	   = eAlienNormal;
			break;

		case eAlien_07:
			largura    = 98;
			altura     = 73;
			energia	   = 3;
			atirar	   = 1;
			velocidade = 7;
			status	   = eAlienNormal;
			break;
	}
}


//------------------------------------------------------------
void CAlien::Adicionar(int _tipo, int _x, int _y)
{
	if(p_alien)
	{
		p_alien->Adicionar(_tipo, _x, _y);
	}
	else
	{
		p_alien = new CAlien;
		p_alien->Iniciar(_tipo, _x, _y, load_datafile("aliens.dat"));
	}
}


//------------------------------------------------------------
void CAlien::Atualizar(int _x1_alvo, int _y1_alvo, int _x2_alvo, int _y2_alvo, int _x1, int _y1, int _x2, int _y2)
{
	time_t tm;

	if (status == eAlienNormal || status == eAlienEscudo)
	{
		//if (x < -l) status = eAlienInativo;
		y += velocidade;
	}

	/*
	if(ChecarColisaoAliens())
	{
		status = eAlienExplosao;
	}
	*/
	switch(tipo)
	{
		case eAlien_03:
			tempo = tempo < 2 ?tempo + 1 :0;
			break;
	}

	if(atirar)
	{
		if(tipo != eAlien_04)
		{
			srand((unsigned) time(&tm));
			tiros.Adicionar((ETiroTipo) (rand() % 5), x + (largura / 2), y + altura);
			atirar = FALSE;
		}
		else
		{
			tiros.Adicionar(eTiroLaserVermelho, x, y + (altura / 2));
			tiros.Adicionar(eTiroLaserVermelho, x + largura, y + (altura / 2));
			atirar = FALSE;
		}
	}

	tiros.AtualizarTodos(_x1_alvo, _y1_alvo, _x2_alvo, _y2_alvo, _x1, _y1, _x2,  _y2);

	if(status == eAlienExplosao)
	{
		tempo++;
		if (tempo == 9)
		{
			status = eAlienInativo;
		}
	}
}


//------------------------------------------------------------
void CAlien::AtualizarTodos(int _x1_alvo, int _y1_alvo, int _x2_alvo, int _y2_alvo, int _x1, int _y1, int _x2, int _y2)
{
	if(p_alien)
	{
 		if(p_alien->ChecarColisao(_x1, _y1, _x2, _y2)
		|| p_alien->tiros.VerificarExisteTiros())
		{
			p_alien->Atualizar(_x1_alvo, _y1_alvo, _x2_alvo, _y2_alvo, _x1, _y1, _x2, _y2);
			p_alien->atualizado = TRUE;
		}
		else
		{
			p_alien->atualizado = FALSE;
		}

		if(p_alien->p_alien)
		{
			p_alien->AtualizarTodos(_x1_alvo, _y1_alvo, _x2_alvo, _y2_alvo, _x1, _y1, _x2, _y2);
		}
	}
}


//------------------------------------------------------------
void CAlien::Desenhar(BITMAP *_bmp_destino)
{
	switch(status)
	{
		case eAlienNormal:
			//draw_trans_sprite(_bmp_destino, (BITMAP *)dat_arquivo[(tipo * 2) + 1].dat, x + 25, y + 35);
			//draw_sprite(_bmp_destino, (BITMAP *)dat_arquivo[(tipo * 2)].dat, x, y);
			masked_blit((BITMAP *)dat_arquivo[(tipo * 2) + 1].dat, _bmp_destino, tempo * (largura / 1.5), 0, x + 50, y + 50, (largura / 1.5), (altura / 1.5));
			masked_blit((BITMAP *)dat_arquivo[(tipo * 2)].dat, _bmp_destino, tempo * largura, 0, x, y, largura, altura);
			break;

		case eAlienExplosao:
			masked_blit((BITMAP *)dat_arquivo[ALIEN_EXPLOSAO].dat, _bmp_destino, tempo * 50, 0, x, y, 50, 50);
			break;
	}
	tiros.DesenharTodos(_bmp_destino);
}


//------------------------------------------------------------
void CAlien::DesenharTodos(BITMAP *_bmp_destino)
{
	if(p_alien)
	{
		if(p_alien->atualizado)
		{
			p_alien->Desenhar(_bmp_destino);
		}
		if(p_alien->p_alien)
		{
			p_alien->DesenharTodos(_bmp_destino);
		}
	}
}


//------------------------------------------------------------
void CAlien::Desligar(void)
{
	CAlien *aux_alien, *del_alien;

	for(aux_alien = p_alien; aux_alien;)
	{
		del_alien = aux_alien;
		aux_alien = aux_alien->p_alien;
		delete del_alien;
	}
	p_alien = NULL;
	unload_datafile(dat_arquivo);
}


//------------------------------------------------------------
int CAlien::ObterTipo(void)
{
	return tipo;
}


//------------------------------------------------------------
void CAlien::SalvarAlien(char *_fase)
{
	CAlien *aux_alien;
	TAlien alien;
	FILE *arquivo;

	if((arquivo = fopen(_fase, "rb+")) != NULL)
	{
		if(p_alien)
		{
			fseek(arquivo, 0, SEEK_END);
	 		for(aux_alien = p_alien; aux_alien; aux_alien = aux_alien->p_alien)
			{
				alien.tipo = aux_alien->ObterTipo();
				alien.x = aux_alien->ObterX();
				alien.y = aux_alien->ObterY();
				fwrite(&alien, sizeof(TAlien), 1, arquivo);
			}
		}
	}
    fclose(arquivo);
}


//------------------------------------------------------------
void CAlien::Excluir(int _tipo, int _x, int _y)
{
	CAlien *aux;

	if(p_alien)
	{
		if(p_alien->p_alien)
		{
			p_alien->Excluir(_tipo, _x, _y);
		}
		if(p_alien)
		{
			if(p_alien->ObterTipo() == _tipo
			&& p_alien->ObterX()    == _x
			&& p_alien->ObterY()    == _y)
			{

				aux = p_alien->p_alien;
				delete p_alien;
				if(aux)
				{
					p_alien = aux;
				}
				else
				{
					p_alien = NULL;
				}
			}
		}
	}
}

void CAlien::Excluir(int _x1, int _y1, int _x2, int _y2)
{
	CAlien *aux;

	if(p_alien)
	{
		if(p_alien->p_alien)
		{
			p_alien->Excluir(_x1, _y1, _x2, _y2);
		}
		if(p_alien)
		{
			if(p_alien->ChecarColisao(_x1, _y1, _x2, _y2))
			{
				aux = p_alien->p_alien;
				delete p_alien;
				if(aux)
				{
					p_alien = aux;
				}
				else
				{
					p_alien = NULL;
				}
			}
		}
	}
}



//------------------------------------------------------------
int CAlien::ChecarColisaoAliens(int _x1, int _y1, int _x2, int _y2)
{
	if(p_alien)
	{
		if(p_alien->ChecarColisao(_x1, _y1, _x2, _y2))
		{
			//p_alien->atualizado = FALSE;
			return TRUE;
		}
		if(p_alien->ChecarColisaoAliens(_x1, _y1, _x2, _y2))
		{
			return TRUE;
		}
	}
	return FALSE;
}

int CAlien::ChecarColisaoAliens(void)
{
	if(p_alien)
	{
		if(p_alien->ChecarColisao(x, y, x + largura, y + altura))
		{
			p_alien->atualizado = FALSE;
			return TRUE;
		}
		if(p_alien->ChecarColisaoAliens())
		{
			return TRUE;
		}
	}
	return FALSE;
}


//------------------------------------------------------------
void CAlien::TocarSom(void)
{
	if(status == eAlienExplosao
	&& tempo == 0)
	{
		play_sample((SAMPLE *)dat_arquivo[WAV_ALIEN_EXPLOSAO].dat, 128, 128, 1000, 0);
	}
	tiros.TocarSomTodos();
}


//------------------------------------------------------------
void CAlien::TocarSomTodos(void)
{
	if(p_alien)
	{
		if(p_alien->atualizado)
		{
			p_alien->TocarSom();
		}
		if(p_alien->p_alien)
		{
			p_alien->TocarSomTodos();
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
		tempo = 0;
	}
}


//------------------------------------------------------------
CTiro *CAlien::ObterTiros(void)
{
	return &tiros;
}

//------------------------------------------------------------
/*int CAlien::ObterXAlienProximo(int _x, int _menor_distancia)
{
	if(p_alien)
	{
		if(abs((x - p_alien->x)) < _menor_distancia)
		{
			p_alien->Desenhar(_bmp_destino);
		}
		if(p_alien->p_alien)
		{
			p_alien->DesenharTodos(_bmp_destino);
		}
	}
}*/