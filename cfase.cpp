 /*------------------------------------------------------------*
 *  cfase.cpp - Implementacao da Classe CFase
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: sábado, 27 de outubro de 2001
*
*  Diego em 13/02/2002
*   - Alterado o método Desenhar para aceitar CTela e
*     posicionamento relativo;
*
*------------------------------------------------------------*/


#include "cfase.h"
#include "erro.h"
#include "vglobal.h"
#include "time.h"


//------------------------------------------------------------
void CFase::Iniciar(char _arquivo_fase[], int _x1_destino, int _y1_destino, int _largura_destino, int _altura_destino)
{
	FILE *arquivo_map;
	TObjeto objeto;
	strcpy(arquivo_fase, _arquivo_fase);
	TLadrilho ladrilhos[MAPA_LARGURA_LADRILHOS][MAPA_ALTURA_LADRILHOS];

	x1_fonte = 0;
	y1_fonte = MAPA_ALTURA - _altura_destino;
	x1_destino = _x1_destino;
	y1_destino = _y1_destino;
	largura_destino = _largura_destino;
	altura_destino = _altura_destino;
	if(!fase_screen)
	{
		fase_screen = create_bitmap(MAPA_LARGURA, MAPA_ALTURA);
		if(!fase_screen)
		{
			Erro("0100", allegro_error);
		}
	}

	/* Executa a leitura do arquivo da fase
	para a variavel local ladrilhos */
	//Log("Lendo ladrilhos...");
	if((arquivo_map = fopen(arquivo_fase, "rb")) != NULL)
	{

		fseek(arquivo_map, 0 * sizeof(TLadrilho), SEEK_SET);
		fread(&ladrilhos, sizeof(TLadrilho), MAPA_TOTAL_LADRILHOS, arquivo_map);
	}
	else
      return;

	//Log("Lendo objetos...");
	while(!feof(arquivo_map))
	{
		if(fread(&objeto, sizeof(TObjeto), 1, arquivo_map) == 1)
		{
			if(objeto.tipo == eAlien)
			{
				//Log("Carregando alien...");
				aliens.Adicionar(objeto.subtipo, objeto.x, objeto.y);
			}
			else
			if(objeto.tipo == eConstrucao)
			{
				//Log("Carregando Construcao...");
				construcoes.Adicionar(objeto.subtipo, objeto.x, objeto.y);
			}

		}
		else
		{
			break;
		}
	}

	//Log("Fechando arquivo...");
	fclose(arquivo_map);

	CAlien::Carregar_dat_arquivo(load_datafile("aliens.dat"));
	CConstrucao::Carregar_dat_arquivo(load_datafile("construcoes.dat"));
	CTiro::Carregar_dat_arquivo(load_datafile("tiros.dat"));

	// Inicia o fundo com os dados lidos do arquivo
	//Log("Iniciando fundo...");
	fundo.Iniciar(ladrilhos, 0, 0, MAPA_LARGURA_LADRILHOS, MAPA_ALTURA_LADRILHOS, LADRILHO_LARGURA, LADRILHO_ALTURA, 0, 0, largura_destino, altura_destino);
	//Log("Iniciando nave...");
	nave.Iniciar();
	//Log("Fase iniciada!");
}


//------------------------------------------------------------
void CFase::Desenhar(CTela &_tela)
{
	//Log("Desenhado fundo ...");
	fundo.Desenhar(_tela, x1_destino + x1_fonte, y1_destino + y1_fonte);

	//Log("Desenhado construções ...");
	construcoes.DesenharTodos(_tela, x1_destino + x1_fonte, y1_destino + y1_fonte);

	//Log("Desenhado aliens ...");
	aliens.DesenharTodos(_tela, x1_destino + x1_fonte, y1_destino + y1_fonte);

	//Log("Desenhado nave ...");
	nave.Desenhar(_tela, x1_destino + x1_fonte, y1_destino + y1_fonte);
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
	construcoes.SalvarConstrucao(arquivo_fase);
}


//------------------------------------------------------------
void CFase::Desligar()
{
	char buf[80];

	sprintf(buf, "Fundo: %ld...", time(NULL));
	Log(buf);
	fundo.Desligar();

	sprintf(buf, "Aliens: %ld...", time(NULL));
	Log(buf);
	aliens.Desligar();
	CAlien::Descarregar_dat_arquivo();

	sprintf(buf, "Construcoes: %ld...", time(NULL));
	Log(buf);
	construcoes.Desligar();
	CConstrucao::Descarregar_dat_arquivo();

	sprintf(buf, "Nave: %ld...", time(NULL));
	Log(buf);
	nave.Desligar();
	destroy_bitmap(fase_screen);
	fase_screen = NULL;
	CTiro::Descarregar_dat_arquivo();
	sprintf(buf, "Fim: %ld...", time(NULL));
	Log(buf);
}

//------------------------------------------------------------
void CFase::SetarLadrilho(int _x, int _y, TLadrilho _ladrilho, BITMAP *_bmp_fonte)
{
	fundo.SetarLadrilho(_x, _y, _ladrilho, _bmp_fonte);
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
void CFase::AdicionarConstrucao(int _tipo, int _x, int _y)
{
	construcoes.Adicionar(_tipo, _x, _y);
}


//------------------------------------------------------------
void CFase::ExcluirAliens(int _x1, int _y1, int _x2, int _y2)
{
	aliens.Excluir(_x1, _y1, _x2, _y2);
}


//------------------------------------------------------------
void CFase::ExcluirConstrucoes(int _x1, int _y1, int _x2, int _y2)
{
	construcoes.Excluir(_x1, _y1, _x2, _y2);
}


//------------------------------------------------------------
int CFase::Atualizar(int _fundo_pixels)
{
	TRect area;

	area.x1 = x1_fonte;
	area.y1 = y1_fonte;
	area.x2 = x1_fonte + largura_destino;
	area.y2 = y1_fonte + altura_destino;

	if(nave.ObterStatus() == eNaveExplosao)
	{
		return FALSE;
	}

	Rolar(eCima, _fundo_pixels);

	nave.DecY(_fundo_pixels);
	nave.Atualizar(area, aliens.ObterMaisProximo(nave.ObterX(), nave.ObterY()));

	aliens.AtualizarTodos(area, nave.RetornarObjeto());

	construcoes.AtualizarTodos(area, nave.RetornarObjeto());

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
int CFase::ChecarColisaoConstrucoes(int _x1, int _y1, int _x2, int _y2)
{
	return construcoes.ChecarColisaoConstrucoes(_x1, _y1, _x2, _y2);
}


//------------------------------------------------------------
void CFase::Sonorizar(void)
{
	aliens.SonorizarTodos();
	construcoes.SonorizarTodos();
	nave.Sonorizar();
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
			&& aux_tiro->ChecarColisao(aux_alien->ObterRect()))
			{
				aux_tiro->SetarStatus(eTiroExplosao);
				aux_alien->SetarStatus(eAlienAtingido);
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
	CConstrucao *aux_construcao;

	// Aliens
	for(aux_alien = aliens.p_alien; aux_alien; aux_alien = aux_alien->p_alien)
	{
		if(aux_alien->ObterStatus() != eAlienInativo
		&& aux_alien->ObterStatus() != eAlienExplosao
		&& aux_alien->ChecarColisao(nave.ObterRect()))
		{
			aux_alien->SetarStatus(eAlienExplosao);
			nave.DecEnergia(aux_alien->ObterEnergia());
		}
		for(aux_tiro = aux_alien->ObterTiros()->p_tiro; aux_tiro; aux_tiro = aux_tiro->p_tiro)
		{
			if(aux_tiro->ChecarColisao(nave.ObterRect()))
			{
				aux_tiro->SetarStatus(eTiroExplosao);
				nave.DecEnergia(1);
			}
		}
	}

	// Construções
	for(aux_construcao = construcoes.p_construcao; aux_construcao; aux_construcao = aux_construcao->p_construcao)
	{
		/*
		if(aux_construcao->ObterStatus() != eAlienInativo
		&& aux_construcao->ObterStatus() != eAlienExplosao
		&& aux_construcao->ChecarColisao(nave.Rect()))
		{
			aux_construcao->SetarStatus(eAlienExplosao);
			nave.DecEnergia(aux_construcao->ObterEnergia() * 5);
		}
		*/
		for(aux_tiro = aux_construcao->ObterTiros()->p_tiro; aux_tiro; aux_tiro = aux_tiro->p_tiro)
		{
			if(aux_tiro->ChecarColisao(nave.ObterRect()))
			{
				aux_tiro->SetarStatus(eTiroExplosao);
				nave.DecEnergia(1);
			}
		}
	}
}


//------------------------------------------------------------
CNave CFase::ObterNave(void)
{
	return nave;
}



//------------------------------------------------------------
CAlien CFase::ObterAliens(void)
{
	return aliens;
}


//------------------------------------------------------------
CConstrucao CFase::ObterConstrucoes(void)
{
	return construcoes;
}
