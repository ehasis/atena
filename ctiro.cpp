 /*------------------------------------------------------------*
 *  ctiro.cpp - Implementação da Classe de tiro
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: terça-feira, 13 de janeiro de 2002
*
*  Diego em 13/02/2002
*   - Alterado os métodos Desenhar e DesenharTodos para aceitar
*     CTela e posicionamento relativo;
*
*------------------------------------------------------------*/


#include <stdio.h>
#include <allegro.h>
#include "erro.h"
#include "ctiro.h"


//------------------------------------------------------------
// Membros static
DATAFILE *CTiro::dat_arquivo = NULL;


//------------------------------------------------------------
// Construtor
CTiro::CTiro(void)
{
	p_tiro = NULL;
}


//------------------------------------------------------------
void CTiro::Iniciar(ETiroTipo _tipo, int _x, int _y, CObjeto * const _alvo)
{
	tipo = _tipo;
	x = _x;
	y = _y;
	alvo = _alvo;
	dir_x = 0;
	dir_y = 0;
	flag_x = 0;
	flag_y = 0;
	cont = 0;
	quadro = 0;
	tocar_som = TRUE;
	status = eTiroNormal;

	switch(tipo)
	{	
		// Tiro alien
		case eTiroCerra:
			largura = 18;
			altura  = 16;
			dir_x	= 0;
			dir_y	= 1;
			break;

		case eTiroBola:
			largura = 5;
			altura  = 5;
			cont    = 5;
			dir_x   = 1;
			dir_y	= 1;
			break;

		// Tiro nave
		case eTiroLaserVermelho:
			largura = 10;
			altura  = 50;
			break;

		case eTiroLaserVerde:
			largura = 72;
			altura  = 100;
			break;

		case eTiroFogoTeleguiado:
			largura = 10;
			altura  = 8;
			break;

		// Tiro construcao
		case eTiroFogo:
			largura = 10;
			altura  = 8;
			dir_x	= 0;
			dir_y	= 0;
			break;

	}
	x = _x - (largura / 2);
}



//------------------------------------------------------------
void CTiro::Adicionar(ETiroTipo _tipo, int _x, int _y, CObjeto * const _alvo)
{
	CTiro *aux;

    for(aux = this; aux->p_tiro; aux = aux->p_tiro);

	aux->p_tiro = new CTiro;
	/*
	if(!aux->p_tiro)
	{
		Erro("Código do erro:", "0500");
	}
	*/
	aux->p_tiro->Iniciar(_tipo, _x, _y, _alvo);
}


//------------------------------------------------------------
void CTiro::Atualizar(CObjeto * const _alvo)
{
	switch(tipo)
	{
    		case eTiroCerra: 
			if(!dir_x)
			{
				if(alvo->ObterX() != x)
				{
					dir_x = alvo->ObterX() >= x ? 1 : -1;
				}
			}
	
			x += dir_x * altura;
			y += dir_y * altura;
			quadro = quadro == 3 ? 0 : quadro + 1;
			break;
		
		case eTiroBola:
			if(cont == 5)
			{
				dir_x = dir_x * -1;
				cont = 0;
			}

			cont++;
			x += dir_x * altura;		 
       		y += dir_y * (altura * 2);
			break;

		case eTiroLaserVermelho:
		case eTiroLaserVerde:
			y += -1 * 100;
			break;

		case eTiroFogoTeleguiado:
			if(!alvo || !alvo->Obter_visivel())
			{
				alvo = _alvo;
				dir_y = -1;
			}
			
			if(alvo)
			{
				// Coordenada x
				if(alvo->ChecarColisaoX(x,  x + largura))
				{
					dir_x = 0;
				}
				else if(x > alvo->ObterX())
				{
					dir_x = -1;
				}
				else
				{
					dir_x = 1;
				}

				// Coordenada y
				if(alvo->ChecarColisaoY(y,  y + altura))
				{
					dir_y = 0;
				}
				else if(y > alvo->ObterY())
				{
					dir_y = -1;
				}
				else 
				{
					dir_y = 1;
				}
			}
			
			x += dir_x * 30;
			y += dir_y * 30;

			quadro = quadro == 2 ? 0 : quadro + 1;
			break;
	
		case eTiroFogo: 
			if(!dir_x)
			{
				if(alvo->ObterX() != x)
				{
					dir_x = alvo->ObterX() >= x ? 1 : -1;
				}
				if(alvo->ObterY() != y)
				{
					dir_y = alvo->ObterY() >= y ? 1 : -1;
				}

			}
			
			x += dir_x * 15;
			y += dir_y * 20;
			quadro = quadro == 2 ? 0 : quadro + 1;
			break;
	}
}


//------------------------------------------------------------
void CTiro::AtualizarTodos(TRect _area, CObjeto * const _alvo)
{
	CTiro *aux, *del;

	for(aux = this; aux->p_tiro;)
	{
		if(aux->p_tiro->ChecarColisao(_area)
		&& aux->p_tiro->status != eTiroExplosao	)
		{
			//Log("Atualizando tiro ...");
			aux->p_tiro->Atualizar(_alvo);
			aux->p_tiro->ativo = TRUE;
			//Log("Tiro ativo ...");
			aux = aux->p_tiro;
		}
		else
		{
			//Log("Excluindo tiro ...");
			del = aux->p_tiro;
			aux->p_tiro = aux->p_tiro->p_tiro;
			delete del;
			//Log("Tiro Excluido ...");
		}
	}
}

//------------------------------------------------------------
void CTiro::Desenhar(CTela &_tela, int _x_real, int _y_real)
{

	switch(status)
	{
		case eTiroNormal:
			_tela.MaskedBlit((BITMAP *)dat_arquivo[tipo * 2].dat, eCamadaEfeitos, largura * quadro, 0, x - _x_real, y - _y_real, largura, altura);
			break;

		case eTiroExplosao:
			DesenharExplosao(_tela, _x_real, _y_real, x + (largura/2), y + (altura/2), (quadro * 3) + (largura / 2), 250);
		break;
	}
}


//------------------------------------------------------------
void CTiro::DesenharTodos(CTela &_tela, int _x_real, int _y_real)
{
	CTiro *aux;

	for(aux = p_tiro; aux; aux = aux->p_tiro)
	{
		if(aux->ativo)
		{
			aux->Desenhar(_tela, _x_real, _y_real);
		}
	}
}


//------------------------------------------------------------
int CTiro::VerificarExisteTiros(void)
{
	if(p_tiro) return TRUE;
	return FALSE;
}


//------------------------------------------------------------
int CTiro::ChecarColisaoTiros(TRect _obj)
{
	CTiro *aux;

	for(aux = p_tiro; aux; aux = aux->p_tiro)
	{
		if(aux->ChecarColisao(_obj))
		{
			return TRUE;
		}
	}
	return FALSE;
}


//------------------------------------------------------------
void CTiro::Sonorizar(void)
{
	if(tocar_som && status == eTiroNormal)
	{
		stop_sample((SAMPLE *)dat_arquivo[(tipo * 2) + 1].dat);
		play_sample((SAMPLE *)dat_arquivo[(tipo * 2) + 1].dat, 128, 128, 1000, 0);
		tocar_som = FALSE;
	}
	else if(status == eTiroExplosao)
	{
		play_sample((SAMPLE *)dat_arquivo[WAV_TIRO_EXPLOSAO].dat, 128, 128, 1000, 0);
	}
}


//------------------------------------------------------------
void CTiro::SonorizarTodos(void)
{
	CTiro *aux;

	for(aux = p_tiro; aux; aux = aux->p_tiro)
	{
		if(aux->ativo)
		{
			aux->Sonorizar();
		}
	}
}


//------------------------------------------------------------
void CTiro::SetarStatus(EStatusTiro _status)
{
	status = _status;
}

//------------------------------------------------------------
void CTiro::Desligar(void)
{
	CTiro *aux, *del;

	for(aux = p_tiro; aux;)
	{
		del = aux;
		aux = aux->p_tiro;
		delete del;
	}
}

