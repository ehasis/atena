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
	CFilme filme;
	//char copia_arquivo_fase[128], * nome_arquivo, * ext_arquivo, arquivo_filme[128];
	Log("");
	Log("[INICIO]:CFase::Iniciar();");

	CAlien::CarregarArquivoDados(load_datafile("aliens.dat"));
	CConstrucao::CarregarArquivoDados(load_datafile("construcoes.dat"));
	CVeiculo::CarregarArquivoDados("veiculos.dat");
	CTiro::CarregarArquivoDados(load_datafile("tiros.dat"));
	CArma::CarregarArquivoDados(load_datafile("armas.dat"));
	CBonus< CNave >::CarregarArquivoDados(load_datafile("bonus.dat"));


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
			if(objeto.tipo == eAlien)
			{
				m_aliens.Adicionar();
				m_aliens.Obter().Iniciar(objeto.subtipo, objeto.x, objeto.y);
			}
			else
			if(objeto.tipo == eConstrucao)
			{
				m_construcoes.Adicionar();
				m_construcoes.Obter().Iniciar(objeto.subtipo, objeto.x, objeto.y);
			}
			else
			if(objeto.tipo == eVeiculo)
			{
				m_veiculos.Adicionar();
				m_veiculos.Obter().Iniciar(objeto.subtipo, objeto.x, objeto.y);
			}
		}
		else
		{
			break;
		}
	}

	fclose(arquivo_map);

	// Inicia o fundo com os dados lidos do m_arquivo
	m_fundo.Iniciar(ladrilhos, 0, 0, MAPA_LARGURA_LADRILHOS, MAPA_ALTURA_LADRILHOS, LADRILHO_LARGURA, LADRILHO_ALTURA, m_x1_destino, m_y1_destino, m_largura_destino, m_altura_destino);
	
	Log("Adicionando nave");
	m_naves.AdicionarFim();
	Log("Nave adicionada");
	m_naves.Obter().Iniciar(eAtena_01, 284, 6300);
	Log("Nave iniciada");

	m_chefe.Iniciar();

	/* TESTE
	m_naves.AdicionarFim();
	m_naves.Obter().Iniciar(eAtena_01, 540, 6300);
	m_naves.Obter().SetarTeclas(KEY_8_PAD, KEY_2_PAD, KEY_4_PAD, KEY_6_PAD, KEY_1_PAD, KEY_2_PAD, KEY_3_PAD, KEY_0_PAD);
	/**/
	m_bonus.Iniciar(eBonusEnergiaTotal, 284, 5900, &m_naves);

	/*
	// TESTE
	Log("Filme");
	strcpy(copia_arquivo_fase, m_arquivo_fase);
	nome_arquivo = strrchr(copia_arquivo_fase, '/');
	ext_arquivo  = strrchr(nome_arquivo, '.');
	strcpy(ext_arquivo, ".txt");
	strcpy(arquivo_filme, "filmes");
	strcat(arquivo_filme, nome_arquivo);
	Log(arquivo_filme);
	if (exists(arquivo_filme))
		filme.Executar(arquivo_filme);
    /**/

	CExplosao::Iniciar(640, 480);
	Log("[FIM]:CFase::Iniciar();");
}


//------------------------------------------------------------
void CFase::Desenhar(CTela & tela)
{
	Log("m_fundo.Desenhar(tela, m_x1_fonte, m_y1_fonte);");
	m_fundo.Desenhar(tela, m_x1_fonte, m_y1_fonte);
	
	Log("m_veiculos.Desenhar(tela, m_x1_fonte - m_x1_destino, m_y1_fonte - m_y1_destino);");
	m_veiculos.Desenhar(tela, m_x1_fonte - m_x1_destino, m_y1_fonte - m_y1_destino);

	Log("m_construcoes.Desenhar(tela, m_x1_fonte - m_x1_destino, m_y1_fonte - m_y1_destino);");
	m_construcoes.Desenhar(tela, m_x1_fonte - m_x1_destino, m_y1_fonte - m_y1_destino);

	Log("m_chefe.Desenhar(tela, m_x1_fonte - m_x1_destino, m_y1_fonte - m_y1_destino);");
	m_chefe.Desenhar(tela, m_x1_fonte - m_x1_destino, m_y1_fonte - m_y1_destino);

	Log("m_aliens.Desenhar(tela, m_x1_fonte - m_x1_destino, m_y1_fonte - m_y1_destino);");
	m_aliens.Desenhar(tela, m_x1_fonte - m_x1_destino, m_y1_fonte - m_y1_destino);

	Log("m_naves.Desenhar(tela, m_x1_fonte - m_x1_destino, m_y1_fonte - m_y1_destino);");
	m_naves.Desenhar(tela, m_x1_fonte - m_x1_destino, m_y1_fonte - m_y1_destino);

	Log("m_bonus.Desenhar(tela, m_x1_fonte - m_x1_destino, m_y1_fonte - m_y1_destino);");

	m_bonus.Desenhar(tela, m_x1_fonte - m_x1_destino, m_y1_fonte - m_y1_destino);

	CExplosao::Desenhar(tela);
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
	SalvarObjetos(m_aliens, m_arquivo_fase);
	SalvarObjetos(m_construcoes, m_arquivo_fase);
	SalvarObjetos(m_veiculos, m_arquivo_fase);
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

	m_veiculos.Finalizar();
	CVeiculo::DescarregarArquivoDados();

	m_naves.Finalizar();

	m_chefe.Finalizar();

	CArma::DescarregarArquivoDados();
	CTiro::DescarregarArquivoDados();

	CBonus< CNave >::DescarregarArquivoDados();

	CExplosao::Desligar();
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
	m_aliens.AdicionarFim();
	m_aliens.Obter().Iniciar(tipo, x, y);
}


//------------------------------------------------------------
void CFase::AdicionarConstrucao(int tipo, int x, int y)
{
	m_construcoes.AdicionarFim();
	m_construcoes.Obter().Iniciar(tipo, x, y);
}


//------------------------------------------------------------
void CFase::ExcluirAliens(int x1, int y1, int x2, int y2)
{
	m_aliens.RemoverPorColisao(x1, y1, x2, y2);
}


//------------------------------------------------------------
void CFase::ExcluirConstrucoes(int x1, int y1, int x2, int y2)
{
	m_construcoes.RemoverPorColisao(x1, y1, x2, y2);
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

	if(m_naves.Obter(1).ObterStatus() == eNaveExplosao
	&& m_naves.Obter(2).ObterStatus() == eNaveExplosao)
	{
		return false;
	}


	area.x1 = m_x1_fonte;
	area.y1 = m_y1_fonte;
	area.x2 = m_x1_fonte + m_largura_destino;
	area.y2 = m_y1_fonte + m_altura_destino;


	Rolar(eCima, fundo_pixels);

	//if(m_chefe.ObterAtivo) m_chefe.DecY(fundo_pixels);
	m_naves.MoverPrimeiro();
	do
	{
		m_naves.Obter().DecY(fundo_pixels);
		obj_aliens = m_aliens.ObterMaisProximo(m_naves.Obter().ObterX(), m_naves.Obter().ObterY()).RetornarObjetoAvancado();
		m_naves.Obter().Atualizar(area, obj_aliens);
	} while(m_naves.MoverProximo());

	m_chefe.Atualizar(area, m_naves.Obter().RetornarObjetoAvancado());

	m_aliens.Atualizar(area, m_naves.Obter().RetornarObjetoAvancado());

	m_construcoes.Atualizar(area, m_naves.Obter().RetornarObjetoAvancado());

	m_veiculos.Atualizar(area, m_naves.Obter().RetornarObjetoAvancado());

	m_bonus.Atualizar(area);

	ChecarColisaoTirosDaNave();

	ChecarColisaoNaNave();


	return true;
}


//------------------------------------------------------------
int CFase::ChecarColisaoAliens(int x1, int y1, int x2, int y2)
{
	return m_aliens.ChecarColisao(x1, y1, x2, y2);
}


//------------------------------------------------------------
int CFase::ChecarColisaoConstrucoes(int x1, int y1, int x2, int y2)
{
	return m_construcoes.ChecarColisao(x1, y1, x2, y2);
}


//------------------------------------------------------------
void CFase::Sonorizar()
{
	m_aliens.Sonorizar();
	m_construcoes.Sonorizar();
	m_veiculos.Sonorizar();
	m_naves.Sonorizar();
}


//------------------------------------------------------------
void CFase::ChecarColisaoTirosDaNave()
{
	if(m_naves.MoverPrimeiro())
	{
		do
		{
			if(m_naves.Obter().ObterArmas().MoverPrimeiro())
			{
				do
				{
					if(m_naves.Obter().ObterArmas().Obter().ObterTiros().MoverPrimeiro())
					{
						do
						{
							if(m_naves.Obter().ObterArmas().Obter().ObterTiros().Obter().ObterStatus() == eTiroNormal)
							{
								// Nos Aliens
								if(m_aliens.Colidir(m_naves.Obter().ObterArmas().Obter().ObterTiros().Obter().ObterRect(), 1))
								{
									m_naves.Obter().ObterArmas().Obter().ObterTiros().Obter().SetarStatus(eTiroExplosao);
									m_naves.Obter().IncPontos(1);
								}

								// Nos veiculos
								if(m_veiculos.Colidir(m_naves.Obter().ObterArmas().Obter().ObterTiros().Obter().ObterRect(), 1))
								{
									m_naves.Obter().ObterArmas().Obter().ObterTiros().Obter().SetarStatus(eTiroExplosao);
									m_naves.Obter().IncPontos(1);
								}

								// No chefe
								if(m_chefe.Colidir(m_naves.Obter().ObterArmas().Obter().ObterTiros().Obter().ObterRect(), 1))
								{
									m_naves.Obter().ObterArmas().Obter().ObterTiros().Obter().SetarStatus(eTiroExplosao);
									m_naves.Obter().IncPontos(1);
								}
							}
						} while(m_naves.Obter().ObterArmas().Obter().ObterTiros().MoverProximo());
					}
				} while(m_naves.Obter().ObterArmas().MoverProximo());
			}
		} while(m_naves.MoverProximo());
	}
}



//------------------------------------------------------------
void CFase::ChecarColisaoNaNave()
{
	if(m_aliens.MoverPrimeiro())
	{
		do
		{
			if(m_aliens.Obter().ObterStatus() != eAlienInativo
			&& m_aliens.Obter().ObterStatus() != eAlienExplosao
			&& m_naves.Colidir(m_aliens.Obter().ObterRect(), 1))
				m_aliens.Obter().SetarStatus(eAlienExplosao);

			if(m_aliens.Obter().ObterArmas().Obter().ObterTiros().MoverPrimeiro())
			{
				do
				{
					if(m_aliens.Obter().ObterArmas().Obter().ObterTiros().Obter().ObterStatus() == eTiroNormal)
					{
						// Tiros aliens colidem na nave
						if(m_naves.Obter().Colidir(m_aliens.Obter().ObterArmas().Obter().ObterTiros().Obter().ObterRect(), 1))
							m_aliens.Obter().ObterArmas().Obter().ObterTiros().Obter().SetarStatus(eTiroExplosao);
					}

				} while(m_aliens.Obter().ObterArmas().Obter().ObterTiros().MoverProximo());
			}
		} while(m_aliens.MoverProximo());
	}

	// Construções
	if(m_construcoes.MoverPrimeiro())
	{
		do
		{	if(m_construcoes.Obter().ObterArmas().Obter().ObterTiros().MoverPrimeiro())
			{
				do
				{
					if(m_construcoes.Obter().ObterArmas().Obter().ObterTiros().Obter().ObterStatus() == eTiroNormal)
					{
						// Tiros construções colidem na nave
						if(m_naves.Obter().Colidir(m_construcoes.Obter().ObterArmas().Obter().ObterTiros().Obter().ObterRect(), 1))
							m_construcoes.Obter().ObterArmas().Obter().ObterTiros().Obter().SetarStatus(eTiroExplosao);
					}
				} while(m_construcoes.Obter().ObterArmas().Obter().ObterTiros().MoverProximo());
			}
		} while(m_construcoes.MoverProximo());
	}


	// Veículos
	if(m_veiculos.MoverPrimeiro())
	{
		do
		{
			// Veiculos colidem com a nave
			if(m_veiculos.Obter().ObterStatus() != eVeiculoExplosao
			&& m_veiculos.Obter().ObterStatus() != eVeiculoInativo
			&& m_naves.Obter().Colidir(m_veiculos.Obter().ObterRect(), 1))
				m_veiculos.Obter().SetarStatus(eVeiculoExplosao);

  
			if(m_veiculos.Obter().ObterArmas().Obter().ObterTiros().MoverPrimeiro())
			{
				do
				{
					if(m_veiculos.Obter().ObterArmas().Obter().ObterTiros().Obter().ObterStatus() == eTiroNormal)
					{
						// Tiros veiculos colidem na nave
						if(m_naves.Obter().Colidir(m_veiculos.Obter().ObterArmas().Obter().ObterTiros().Obter().ObterRect(), 1))
							m_veiculos.Obter().ObterArmas().Obter().ObterTiros().Obter().SetarStatus(eTiroExplosao);
					}
				} while(m_veiculos.Obter().ObterArmas().Obter().ObterTiros().MoverProximo());
			}
		} while(m_veiculos.MoverProximo());
	}
}


//------------------------------------------------------------
CColecaoAvancada< CAlien > & CFase::ObterAliens()
{
	return m_aliens;
}


//------------------------------------------------------------
CColecaoAvancada< CConstrucao > & CFase::ObterConstrucoes()
{
	return m_construcoes;
}


//------------------------------------------------------------
CNave & CFase::ObterNave()
{
	return m_naves.Obter();
}

//------------------------------------------------------------
CColecaoAvancada <CVeiculo> & CFase::ObterVeiculos()
{
	return m_veiculos;
}


//------------------------------------------------------------
template< class cls >
void CFase::SalvarObjetos(CColecaoAvancada< cls > cls_obj, char * fase)
{
	TObjeto obj;
	FILE *m_arquivo;

	if((m_arquivo = fopen(fase, "rb+")) != NULL)
	{
		if(cls_obj.MoverPrimeiro())
		{
			obj.tipo = cls_obj.Obter().ObterTipoObjeto();
			fseek(m_arquivo, 0, SEEK_END);
			do
			{
				obj.subtipo = cls_obj.Obter().ObterTipo();
				obj.x = cls_obj.Obter().ObterX();
				obj.y = cls_obj.Obter().ObterY();
				fwrite(&obj, sizeof(TObjeto), 1, m_arquivo);
			} while(cls_obj.MoverProximo());
		}
	}
    fclose(m_arquivo);
}

