 /*------------------------------------------------------------*
 *  cfase.cpp - Implementacao da Classe CFase
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: sábado, 27 de outubro de 2001
*
*
*------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <allegro.h>

#include "time.h"
#include "erro.h"
#include "funcoes.h"

#include "cfase.h"


//------------------------------------------------------------
void CFase::Iniciar(char arquivo_fase[], int x1_destino, int y1_destino, int largura_destino, int altura_destino)
{
	Log("");
	Log("[INICIO]:CFase::Iniciar();");

	FILE *arquivo_map;
	TObjeto objeto;
	strcpy(m_arquivo_fase, arquivo_fase);
	TLadrilho ladrilhos[MAPA_LARGURA_LADRILHOS][MAPA_ALTURA_LADRILHOS];

	m_largura_destino = largura_destino;
	m_altura_destino = altura_destino;
	m_x1_fonte = 0;
	m_y1_fonte = MAPA_ALTURA - m_altura_destino;
	m_x1_destino = x1_destino;
	m_y1_destino = y1_destino;

	/* Executa a leitura do m_arquivo da m_fase
	para a variavel local ladrilhos */
	if((arquivo_map = fopen(m_arquivo_fase, "rb")) != NULL)
	{

		fseek(arquivo_map, 0 * sizeof(TLadrilho), SEEK_SET);
		fread(&ladrilhos, sizeof(TLadrilho), MAPA_TOTAL_LADRILHOS, arquivo_map);
	}
	else
      return;

	while(!feof(arquivo_map))
	{
		if(fread(&objeto, sizeof(TObjeto), 1, arquivo_map) == 1)
		{
			if(objeto.m_tipo == eAlien)
			{
				m_aliens.Adicionar(objeto.subtipo, objeto.x, objeto.y);
			}
			else
			if(objeto.m_tipo == eConstrucao)
			{
				m_construcoes.Adicionar(objeto.subtipo, objeto.x, objeto.y);
			}

		}
		else
		{
			break;
		}
	}

	fclose(arquivo_map);


	CAlien::CarregarArquivoDados(load_datafile("aliens.dat"));
	CConstrucao::CarregarArquivoDados(load_datafile("construcoes.dat"));
	CTiro::CarregarArquivoDados(load_datafile("tiros.dat"));
	CArma::CarregarArquivoDados(load_datafile("armas.dat"));

	// Inicia o fundo com os dados lidos do m_arquivo
	m_fundo.Iniciar(ladrilhos, 0, 0, MAPA_LARGURA_LADRILHOS, MAPA_ALTURA_LADRILHOS, LADRILHO_LARGURA, LADRILHO_ALTURA, m_x1_destino, m_y1_destino, m_largura_destino, m_altura_destino);
	m_nave.Iniciar();

	Log("[FIM]:CFase::Iniciar();");
}


//------------------------------------------------------------
void CFase::Desenhar(CTela & tela)
{
	Log("");
	Log("[INICIO]:CFase::Desenhar();");

	m_fundo.Desenhar(tela, m_x1_fonte, m_y1_fonte);

	m_construcoes.DesenharTodos(tela, m_x1_fonte - m_x1_destino, m_y1_fonte - m_y1_destino);

	m_aliens.DesenharTodos(tela, m_x1_fonte - m_x1_destino, m_y1_fonte - m_y1_destino);

	m_nave.Desenhar(tela, m_x1_fonte - m_x1_destino, m_y1_fonte - m_y1_destino);
	Log("[FIM]:CFase::Desenhar();");
}


//------------------------------------------------------------
int CFase::Rolar(EDirecao direcao, int pixels)
{
	switch(direcao)
	{
		case eCima:
		if((m_y1_fonte - pixels) > 0)
			m_y1_fonte -= pixels;
        else
        if(m_y1_fonte == 0)
			return FALSE;
        else
            m_y1_fonte = 0;
        break;

		case eDireita:
			if((m_x1_fonte + m_largura_destino + pixels) < MAPA_LARGURA)
				m_x1_fonte += pixels;
            else
            if(m_x1_fonte + m_largura_destino == MAPA_LARGURA)
				return FALSE;
            else
				m_x1_fonte = MAPA_LARGURA - m_largura_destino;
            break;

		case eBaixo:
			if((m_y1_fonte + m_altura_destino + pixels) < MAPA_ALTURA)
				m_y1_fonte += pixels;
			else
			if(m_y1_fonte + m_altura_destino == MAPA_ALTURA)
				return FALSE;
            else
				m_y1_fonte = MAPA_ALTURA - m_altura_destino;
            break;

		case eEsquerda:
			if((m_x1_fonte - pixels) > 0)
				m_x1_fonte -= pixels;
            else
			if(m_x1_fonte == 0)
				return FALSE;
            else
				m_x1_fonte = 0;
            break;
   }

	return TRUE;
}


//------------------------------------------------------------
int CFase::ObterX1Fonte()
{
   return m_x1_fonte;
}


//------------------------------------------------------------
int CFase::ObterY1Fonte()
{
   return m_y1_fonte;
}


//------------------------------------------------------------
void CFase::SalvarFase()
{
	m_fundo.SalvarFundo(m_arquivo_fase);
	m_aliens.SalvarAlien(m_arquivo_fase);
	m_construcoes.SalvarConstrucao(m_arquivo_fase);
}


//------------------------------------------------------------
void CFase::Finalizar()
{
	Log("");
	Log("[INICIO]:CFase::Finalizar();");

	m_fundo.Finalizar();

	m_aliens.Finalizar();
	CAlien::DescarregarArquivoDados();

	m_construcoes.Finalizar();
	CConstrucao::DescarregarArquivoDados();

	m_nave.Finalizar();

	CArma::DescarregarArquivoDados();
	CTiro::DescarregarArquivoDados();

	Log("[FIM]:CFase::Finalizar();");
}

//------------------------------------------------------------
void CFase::SetarLadrilho(int x, int y, TLadrilho ladrilho, BITMAP * bmp_fonte)
{
	m_fundo.SetarLadrilho(x, y, ladrilho, bmp_fonte);
}


//------------------------------------------------------------
CLadrilho CFase::ObterLadrilho(int x, int y)
{
   return m_fundo.ObterLadrilho(x, y);
}


//------------------------------------------------------------
void CFase::SetarArquivoFase(char arquivo_fase[])
{
	strcpy(m_arquivo_fase, arquivo_fase);
}


//------------------------------------------------------------
void CFase::AdicionarAlien(int tipo, int x, int y)
{
	m_aliens.Adicionar(tipo, x, y);
}


//------------------------------------------------------------
void CFase::AdicionarConstrucao(int tipo, int x, int y)
{
	m_construcoes.Adicionar(tipo, x, y);
}


//------------------------------------------------------------
void CFase::ExcluirAliens(int x1, int y1, int x2, int y2)
{
	m_aliens.Excluir(x1, y1, x2, y2);
}


//------------------------------------------------------------
void CFase::ExcluirConstrucoes(int x1, int y1, int x2, int y2)
{
	m_construcoes.Excluir(x1, y1, x2, y2);
}


//------------------------------------------------------------
bool CFase::Atualizar(int fundo_pixels)
{
	TRect area;
	CObjetoAvancado *obj_aliens; //, *obj_tiros_aliens;

	if (key[KEY_ESC])
	{
		return false;
	}

	if(m_nave.ObterStatus() == eNaveExplosao)
	{
		return false;
	}

	area.x1 = m_x1_fonte;
	area.y1 = m_y1_fonte;
	area.x2 = m_x1_fonte + m_largura_destino;
	area.y2 = m_y1_fonte + m_altura_destino;


	Rolar(eCima, fundo_pixels);

	obj_aliens = m_aliens.ObterMaisProximo(m_nave.ObterX(), m_nave.ObterY());
	//obj_tiros_aliens = aliens.ObterTiros()->ObterMaisProximo(nave.ObterX(), nave.ObterY());

	m_nave.DecY(fundo_pixels);
	m_nave.Atualizar(area, obj_aliens);



	m_aliens.AtualizarTodos(area, m_nave.RetornarObjetoAvancado());

	m_construcoes.AtualizarTodos(area, m_nave.RetornarObjetoAvancado());

	ChecarColisaoTiroNosAliens();

	ChecarColisaoNaNave();

	return true;
}


//------------------------------------------------------------
int CFase::ChecarColisaoAliens(int x1, int y1, int x2, int y2)
{
	return m_aliens.ChecarColisaoAliens(x1, y1, x2, y2);
}


//------------------------------------------------------------
int CFase::ChecarColisaoConstrucoes(int x1, int y1, int x2, int y2)
{
	return m_construcoes.ChecarColisaoConstrucoes(x1, y1, x2, y2);
}


//------------------------------------------------------------
void CFase::Sonorizar()
{
	m_aliens.SonorizarTodos();
	m_construcoes.SonorizarTodos();
	m_nave.Sonorizar();
}


//------------------------------------------------------------
void CFase::ChecarColisaoTiroNosAliens()
{
	CTiro *aux_tiro;
	CAlien *aux_alien;
	int ind;

	ind = m_nave.ObterArmas().ObterIndice();
	m_nave.ObterArmas().MoverPrimeiro();
	
	do
	{
		for(aux_tiro = m_nave.ObterArmas().Obter().ObterTiros().m_p_tiro; aux_tiro; aux_tiro = aux_tiro->m_p_tiro)
		{	
			for(aux_alien = m_aliens.m_p_alien; aux_alien; aux_alien = aux_alien->m_p_alien)
			{
				if(aux_alien->ObterStatus() != eAlienInativo
				&& aux_alien->ObterStatus() != eAlienExplosao
				&& aux_tiro->ChecarColisao(aux_alien->ObterRect()))
				{
					aux_tiro->SetarStatus(eTiroExplosao);
					aux_alien->SetarStatus(eAlienAtingido);
					aux_alien->DecEnergia(1);
					m_nave.IncPontos(1);
				}
			}
		}
	
	} while(m_nave.ObterArmas().MoverProximo());

	m_nave.ObterArmas().Mover(ind);
}


//------------------------------------------------------------
void CFase::ChecarColisaoNaNave()
{
	CTiro *aux_tiro;
	CAlien *aux_alien;
	CConstrucao *aux_construcao;

	// Aliens
	for(aux_alien = m_aliens.m_p_alien; aux_alien; aux_alien = aux_alien->m_p_alien)
	{
		if(aux_alien->ObterStatus() != eAlienInativo
		&& aux_alien->ObterStatus() != eAlienExplosao)
		{
			// Aliens colidem na nave
			if(aux_alien->ChecarColisao(m_nave.ObterRect()))
			{
				aux_alien->SetarStatus(eAlienExplosao);
				m_nave.DecEnergia(aux_alien->ObterEnergia());
			}
			else 
			{
				// Aliens colidem nas armas
				m_nave.ObterArmas().MoverPrimeiro();
				do 
				{
					if(m_nave.ObterArmas().Obter().ObterStatus() != eArmaInativa
					&& m_nave.ObterArmas().Obter().ObterStatus() != eArmaExplosao
					&& aux_alien->ChecarColisao(m_nave.ObterArmas().Obter().ObterRect()))
					{
						aux_alien->SetarStatus(eAlienExplosao);
						m_nave.ObterArmas().Obter().DecEnergia(aux_alien->ObterEnergia());
					}
				} while(m_nave.ObterArmas().MoverProximo());
			}
		}

		// Aliens colidem nas armas
		if(aux_alien->ObterStatus() != eAlienInativo
		&& aux_alien->ObterStatus() != eAlienExplosao
		&& aux_alien->ChecarColisao(m_nave.ObterRect()))
		{
			aux_alien->SetarStatus(eAlienExplosao);
			m_nave.DecEnergia(aux_alien->ObterEnergia());
		}

		for(aux_tiro = aux_alien->ObterTiros()->m_p_tiro; aux_tiro; aux_tiro = aux_tiro->m_p_tiro)
		{
			// Tiros aliens colidem na nave
			if(aux_tiro->ChecarColisao(m_nave.ObterRect()))
			{
				aux_tiro->SetarStatus(eTiroExplosao);
				m_nave.DecEnergia(1);
			}

			// Tiros aliens colidem nas armas
			m_nave.ObterArmas().MoverPrimeiro();
			do 
			{
				if(m_nave.ObterArmas().Obter().ObterStatus() != eArmaInativa
				&& m_nave.ObterArmas().Obter().ObterStatus() != eArmaExplosao
				&& aux_tiro->ChecarColisao(m_nave.ObterArmas().Obter().ObterRect()))
				{
					aux_tiro->SetarStatus(eTiroExplosao);
					m_nave.ObterArmas().Obter().DecEnergia(1);
				}
			} while(m_nave.ObterArmas().MoverProximo());
		}
	}

	// Construções
	for(aux_construcao = m_construcoes.m_p_construcao; aux_construcao; aux_construcao = aux_construcao->m_p_construcao)
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
		
		for(aux_tiro = aux_construcao->ObterTiros()->m_p_tiro; aux_tiro; aux_tiro = aux_tiro->m_p_tiro)
		{
			// Tiros construções colidem na nave
			if(aux_tiro->ChecarColisao(m_nave.ObterRect()))
			{
				aux_tiro->SetarStatus(eTiroExplosao);
				m_nave.DecEnergia(1);
			}

			// Tiros  construções colidem nas armas
			m_nave.ObterArmas().MoverPrimeiro();
			do 
			{
				if(m_nave.ObterArmas().Obter().ObterStatus() != eArmaInativa
				&& m_nave.ObterArmas().Obter().ObterStatus() != eArmaExplosao
				&& aux_tiro->ChecarColisao(m_nave.ObterArmas().Obter().ObterRect()))
				{
					aux_tiro->SetarStatus(eTiroExplosao);
					m_nave.ObterArmas().Obter().DecEnergia(1);
				}
			} while(m_nave.ObterArmas().MoverProximo());
		}
	}
}


//------------------------------------------------------------
CAlien CFase::ObterAliens()
{
	return m_aliens;
}


//------------------------------------------------------------
CConstrucao CFase::ObterConstrucoes()
{
	return m_construcoes;
}


//------------------------------------------------------------
CNave & CFase::ObterNave()
{
	return m_nave;
}