 /*------------------------------------------------------------*
 *  ctiro.cpp - Implementação da Classe de tiro
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: terça-feira, 13 de janeiro de 2002
*
*
*
*------------------------------------------------------------*/


#include <stdio.h>
#include <allegro.h>
#include "erro.h"
#include "ctiro.h"


//------------------------------------------------------------
/* Construtor */
CTiro::CTiro(void)
{
	p_tiro = NULL;
}


//------------------------------------------------------------
void CTiro::Iniciar(ETiroTipo _tipo, int _x, int _y)
{
	tipo = _tipo;
	y = _y;
	tempo = 0;
	x_alvo = 0;
	y_alvo = 0;
	tocar_som = TRUE;
	dat_arquivo = load_datafile("tiros.dat");

	switch(tipo)
	{
		case eTiroCerra:
			largura = 18;
			altura  = 16;
			break;

		case eTiroFogo:
			largura = 10;
			altura  = 8;
			break;

		case eTiroLaserVermelho:
			largura = 10;
			altura  = 50;
			break;

		case eTiroLaserVerde:
			largura = 10;
			altura  = 50;
			break;

		case eTiroBola:
			largura = 5;
			altura  = 5;
			break;

		case eTiroMissil:
			largura = 22;
			altura  = 35;
			break;
	}
	x = _x - (largura / 2);
}



//------------------------------------------------------------
void CTiro::Adicionar(ETiroTipo _tipo, int _x, int _y)
{
	if(p_tiro)
	{
		p_tiro->Adicionar(_tipo, _x, _y);
	}
	else
	{
		p_tiro = new CTiro;
		p_tiro->Iniciar(_tipo, _x, _y);
	}
}


//------------------------------------------------------------
void CTiro::Atualizar(int _x1_alvo, int _y1_alvo, int _x2_alvo, int _y2_alvo)
{
	switch(tipo)
	{
		case eTiroCerra:
			if(y_alvo == 0)
			{
				y_alvo = _y1_alvo >= y ? 1 : -1;
			}
			y += (y_alvo * (altura / 2));
			tempo = tempo == 3 ? 0 : tempo + 1;
			break;

		case eTiroFogo:
			if(y_alvo == 0)
			{
				y_alvo = _y1_alvo >= y ? 1 : -1;
			}
			if(x > _x1_alvo
			&& x < _x2_alvo)
			{
				x_alvo = 0;
			}
			else
			{
				x_alvo = _x1_alvo > x ? 1 : -1;
			}
			x += x_alvo * altura;
			y += y_alvo * altura;
			tempo = tempo == 2 ? 0 : tempo + 1;
			break;

		case eTiroLaserVermelho:
		case eTiroLaserVerde:
		if(y_alvo == 0)
			{
				y_alvo = _y1_alvo >= y ? 1 : -1;
			}
			y += y_alvo * (altura / 2);
			tempo = 0;
			break;

		case eTiroBola:
			if(y_alvo == 0)
			{
				y_alvo = _y1_alvo >= y ? 1 : -1;
			}
			y += y_alvo * (altura * 4);
			tempo = 0;
			break;

		case eTiroMissil:
			if(y_alvo == 0)
			{
				y_alvo = _y1_alvo >= y ? 1 : -1;
			}
			y += y_alvo * (altura / 2);
			tempo = tempo == 4 ? 0 : tempo + 1;
			break;

	}
}


//------------------------------------------------------------
void CTiro::AtualizarTodos(int _x1_alvo, int _y1_alvo, int _x2_alvo, int _y2_alvo, int _x1, int _y1, int _x2, int _y2)
{
	CTiro *aux;

	if(p_tiro)
	{
 		if(p_tiro->ChecarColisao(_x1, _y1, _x2, _y2) 
		&& p_tiro->status != eTiroExplosao)
		{
			p_tiro->Atualizar(_x1_alvo, _y1_alvo, _x2_alvo, _y2_alvo);
			p_tiro->atualizado = TRUE;
		}
		else
		{
			aux = p_tiro->p_tiro;
			delete p_tiro;
			if(aux)
			{
				p_tiro = aux;
			}
			else
			{
				p_tiro = NULL;
				return;
			}
		}
		if(p_tiro->p_tiro)
		{
			p_tiro->AtualizarTodos(_x1_alvo, _y1_alvo, _x2_alvo, _y2_alvo, _x1, _y1, _x2, _y2);
		}
	}
	
}


//------------------------------------------------------------
void CTiro::Desenhar(BITMAP *_bmp_destino)
{
	masked_blit((BITMAP *)dat_arquivo[tipo * 2].dat, _bmp_destino, largura * tempo, 0, x, y, largura, altura);
}


//------------------------------------------------------------
void CTiro::DesenharTodos(BITMAP *_bmp_destino)
{
	if(p_tiro)
	{
		if(p_tiro->atualizado)
		{
			p_tiro->Desenhar(_bmp_destino);
		}
		if(p_tiro->p_tiro)
		{
			p_tiro->DesenharTodos(_bmp_destino);
		}
	}
}


//------------------------------------------------------------
void CTiro::Excluir(void)
{
    CTiro *aux;

	if(p_tiro)
	{
		Log("1Testando tiro ...");
		if(p_tiro->p_tiro)
		{
			p_tiro->Excluir();
		}
		if(p_tiro)
		{
			if(!p_tiro->atualizado)
			{
				aux = p_tiro->p_tiro;
				delete p_tiro;
				if(aux)
				{
					p_tiro = aux;
				}
				else
				{
					p_tiro = NULL;
				}
			}
		}
	}
	else
		Log("Tiro inexistente.");
	Log("");
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
	if(p_tiro)
	{
		if(p_tiro->ChecarColisao(_obj))
		{
			p_tiro->atualizado = FALSE;
			return TRUE;
		}
		if(p_tiro->ChecarColisaoTiros(_obj))
		{
			return TRUE;
		}
	}
	return FALSE;
}


//------------------------------------------------------------
void CTiro::TocarSom(void)
{
	stop_sample((SAMPLE *)dat_arquivo[(tipo * 2) + 1].dat);
	play_sample((SAMPLE *)dat_arquivo[(tipo * 2) + 1].dat, 128, 128, 1000, 0);
	tocar_som = FALSE;
}


//------------------------------------------------------------
void CTiro::TocarSomTodos(void)
{
	if(p_tiro)
	{
		if(p_tiro->atualizado && p_tiro->tocar_som)
		{
			p_tiro->TocarSom();
		}
		if(p_tiro->p_tiro)
		{
			p_tiro->TocarSomTodos();
		}
	}
}


//------------------------------------------------------------
void CTiro::SetarStatus(EStatusTiro _status)
{
	status = _status;
}