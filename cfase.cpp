 /*------------------------------------------------------------*
 *  cfase.cpp - Implementacao da Classe CFase
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: sábado, 27 de outubro de 2001
*
*
*
*------------------------------------------------------------*/


#include "cfase.h"
#include "erro.h"
#include "vglobal.h"


//------------------------------------------------------------
void CFase::Iniciar(char _arquivo_fase[], int _x1_destino, int _y1_destino, int _largura_destino, int _altura_destino)
{
	FILE * arquivo_map;
	TAlien alien;

	strcpy(arquivo_fase, _arquivo_fase);
	TLadrilho ladrilhos[MAPA_LARGURA_LADRILHOS][MAPA_ALTURA_LADRILHOS];

	x1_fonte = 0;
	y1_fonte = MAPA_ALTURA - _altura_destino;
	x1_destino = _x1_destino;
	y1_destino = _y1_destino;
	largura_destino = _largura_destino;
	altura_destino = _altura_destino;
	fase_screen = create_bitmap(MAPA_LARGURA, MAPA_ALTURA);

	/* Executa a leitura do arquivo da fase
	para a variavel local ladrilhos */
	if((arquivo_map = fopen(arquivo_fase, "rb")) != NULL)
	{

		fseek(arquivo_map, 0 * sizeof(TLadrilho), SEEK_SET);
		fread(&ladrilhos, sizeof(TLadrilho), MAPA_TOTAL_LADRILHOS, arquivo_map);
	}
	else
      return;

	while(!feof(arquivo_map))
	{
		if(fread(&alien, sizeof(TAlien), 1, arquivo_map) == 1)
		{
			//Log("Carregando alien...");
			aliens.Adicionar(alien.tipo, alien.x, alien.y);
		}
		else
		{
			break;
		}
	}

	fclose(arquivo_map);

	/* Inicia o fundo com os dados lidos do arquivo */
	fundo.Iniciar(ladrilhos, 0, 0, MAPA_LARGURA_LADRILHOS, MAPA_ALTURA_LADRILHOS, LADRILHO_LARGURA, LADRILHO_ALTURA, 0, 0, largura_destino, altura_destino);
	nave.SetArquivoDat(load_datafile("nave.dat"));
}


//------------------------------------------------------------
void CFase::Desenhar(BITMAP * _bmp_destino)
{
	fundo.Desenhar(fase_screen, x1_fonte, y1_fonte);
	aliens.DesenharTodos(fase_screen);
	nave.Desenhar(fase_screen);
	blit(fase_screen, _bmp_destino, x1_fonte, y1_fonte, x1_destino, y1_destino, largura_destino, altura_destino);
}


//------------------------------------------------------------
int CFase::Rolar(EDirecao _direcao, int _pixels)
{
	switch(_direcao)
	{
		case eCima:
		if((y1_fonte - _pixels) > 0)
			y1_fonte -= _pixels;
        else
        if(y1_fonte == 0)
			return FALSE;
        else
            y1_fonte = 0;
        break;

		case eDireita:
			if((x1_fonte + largura_destino + _pixels) < MAPA_LARGURA)
				x1_fonte += _pixels;
            else
            if(x1_fonte + largura_destino == MAPA_LARGURA)
				return FALSE;
            else
				x1_fonte = MAPA_LARGURA - largura_destino;
            break;

		case eBaixo:
			if((y1_fonte + altura_destino + _pixels) < MAPA_ALTURA)
				y1_fonte += _pixels;
			else
			if(y1_fonte + altura_destino == MAPA_ALTURA)
				return FALSE;
            else
				y1_fonte = MAPA_ALTURA - altura_destino;
            break;

		case eEsquerda:
			if((x1_fonte - _pixels) > 0)
				x1_fonte -= _pixels;
            else
			if(x1_fonte == 0)
				return FALSE;
            else
				x1_fonte = 0;
            break;
   }

	return TRUE;
}


//------------------------------------------------------------
void CFase::SetarCFundo(CFundo _fundo)
{
   fundo = _fundo;
}


//------------------------------------------------------------
CFundo CFase::ObterCFundo()
{
   return fundo;
}


//------------------------------------------------------------
BITMAP *CFase::ObterFase_screen()
{
	return (BITMAP *) fase_screen;
}

//------------------------------------------------------------
int CFase::ObterX1_fonte()
{
   return x1_fonte;
}


//------------------------------------------------------------
int CFase::ObterY1_fonte()
{
   return y1_fonte;
}


//------------------------------------------------------------
void CFase::SalvarFase()
{
	fundo.SalvarFundo(arquivo_fase);
	aliens.SalvarAlien(arquivo_fase);
}


//------------------------------------------------------------
void CFase::Desligar()
{
	fundo.Desligar();
	aliens.Desligar();
	nave.Desligar();
}

//------------------------------------------------------------
void CFase::SetarLadrilho(int _x, int _y, CLadrilho _ladrilho)
{
	fundo.SetarLadrilho(_x, _y, _ladrilho);
}


//------------------------------------------------------------
CLadrilho CFase::ObterLadrilho(int _x, int _y)
{
   return fundo.ObterLadrilho(_x, _y);
}


//------------------------------------------------------------
void CFase::SetarArquivo_fase(char _arquivo_fase[])
{
	strcpy(arquivo_fase, _arquivo_fase);
}


//------------------------------------------------------------
void CFase::AdicionarAlien(int _tipo, int _x, int _y)
{
	aliens.Adicionar(_tipo, _x, _y);
}

//------------------------------------------------------------
void CFase::ExcluirAliens(int _x1, int _y1, int _x2, int _y2)
{
	aliens.Excluir(_x1, _y1, _x2, _y2);
}

//------------------------------------------------------------
int CFase::Atualizar(int _fundo_pixels)
{
	if(nave.ObterStatus() == eNaveExplosao) 
	{ 
		return FALSE;
	}

	Rolar(eCima, _fundo_pixels);
	nave.DecY(_fundo_pixels);
	nave.Atualizar(x1_fonte, y1_fonte, x1_fonte + largura_destino, y1_fonte + altura_destino);
	aliens.AtualizarTodos(nave.ObterX(), nave.ObterY(), nave.ObterX2(), nave.ObterY2(), x1_fonte, y1_fonte, x1_fonte + largura_destino, y1_fonte + altura_destino);
	ChecarColisaoTiroNosAliens();
	ChecarColisaoNaNave();
	return TRUE;
}


//------------------------------------------------------------
int CFase::ObterLargura_destino(void)
{
	return largura_destino;
}


//------------------------------------------------------------
int CFase::ObterAltura_destino(void)
{
	return altura_destino;
}


//------------------------------------------------------------
int CFase::ChecarColisaoAliens(int _x1, int _y1, int _x2, int _y2)
{
	return aliens.ChecarColisaoAliens(_x1, _y1, _x2, _y2);
}


//------------------------------------------------------------
void CFase::TocarSom(void)
{
	aliens.TocarSomTodos();
	nave.TocarSom();
}


//------------------------------------------------------------
void CFase::ChecarColisaoTiroNosAliens(void)
{
	CTiro *aux_tiro;
	CAlien *aux_alien;

	for(aux_tiro = nave.ObterTiros()->p_tiro; aux_tiro; aux_tiro = aux_tiro->p_tiro)
	{
		for(aux_alien = aliens.p_alien; aux_alien; aux_alien = aux_alien->p_alien)
		{
			if(aux_alien->ObterStatus() != eAlienInativo
			&& aux_alien->ObterStatus() != eAlienExplosao
			&& aux_tiro->ChecarColisao(aux_alien->Rect()))
			{
				aux_tiro->SetarStatus(eTiroExplosao);
				aux_alien->DecEnergia(1);
				nave.IncPontos(1);
			}
		}
	}
}


//------------------------------------------------------------
void CFase::ChecarColisaoNaNave(void)
{
	CTiro *aux_tiro;
	CAlien *aux_alien;

	for(aux_alien = aliens.p_alien; aux_alien; aux_alien = aux_alien->p_alien)
	{
		if(aux_alien->ObterStatus() != eAlienInativo
		&& aux_alien->ObterStatus() != eAlienExplosao
		&& aux_alien->ChecarColisao(nave.Rect()))
		{
			aux_alien->SetarStatus(eAlienExplosao);
			nave.DecEnergia(aux_alien->ObterEnergia() * 5);
		}
		for(aux_tiro = aux_alien->ObterTiros()->p_tiro; aux_tiro; aux_tiro = aux_tiro->p_tiro)
		{
			if(aux_tiro->ChecarColisao(nave.Rect()))
			{
				aux_tiro->SetarStatus(eTiroExplosao);
				nave.DecEnergia(10);
			}
		}
	}
}


//------------------------------------------------------------
CNave CFase::ObterNave(void)
{
	return nave;
}
