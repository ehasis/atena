 /*------------------------------------------------------------*
 *  cconstrucao.cpp - Implementacao da Classe CConstrucao
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: domingo, 27 de janeiro de 2002
*
*
*
*------------------------------------------------------------*/


#include "erro.h"
#include "cconstrucao.h"
#include "construcoes.h"


//------------------------------------------------------------
// Membros static
DATAFILE *CConstrucao::m_dat_arquivo = NULL;
int CConstrucao::m_num_construcoes = 0;


//------------------------------------------------------------
void CConstrucao::CarregarArquivoDados(DATAFILE * dat_arquivo)
{
	Log("CConstrucao::CarregarArquivoDados();");
	if(m_dat_arquivo) DescarregarArquivoDados();
	m_dat_arquivo = dat_arquivo;
}


//------------------------------------------------------------
void CConstrucao::DescarregarArquivoDados()
{
	Log("CConstrucao::DescarregarArquivoDados();");
	unload_datafile(m_dat_arquivo);
	m_dat_arquivo = NULL;
}



//------------------------------------------------------------
// Construtor
CConstrucao::CConstrucao()
{
	m_p_construcao = NULL;
}


//------------------------------------------------------------
void CConstrucao::Iniciar(int tipo, int x, int y)
{
	Log("CConstrucao::Iniciar();");
	m_x			= x;
	m_y			= y;
	m_tipo		= tipo;
	m_quadro	    = 0;
	m_atirar		= 1;
	m_ativo		= 1;
	m_status	    = eConstrucaoNormal;
	m_atirar	    = 1;
	m_objeto		= eConstrucao;

	switch(m_tipo)
	{
		case eConstrucao_01:
			m_largura    = 110;
			m_altura     = 99;
			m_energia	   = 1;
			break;

		case eConstrucao_02:
			m_largura    = 161;
			m_altura     = 161;
			m_energia	   = 2;
			break;

		case eConstrucao_03:
			m_largura    = 102;
			m_altura     = 103;
			m_energia	   = 2;
			break;

		case eConstrucao_04:
			m_largura    = 62;
			m_altura     = 67;
			m_energia	   = 2;
			break;

		case eConstrucao_05:
			m_largura    = 132;
			m_altura     = 132;
			m_energia	   = 2;
			break;

		case eConstrucao_06:
			m_largura    = 111;
			m_altura     = 97;
			m_energia	   = 2;
			break;
	}
}


//------------------------------------------------------------
void CConstrucao::Adicionar(int tipo, int x, int y)
{
	Log("CConstrucao::Adicionar();");
	CConstrucao *aux;

    for(aux = this; aux->m_p_construcao; aux = aux->m_p_construcao);

	aux->m_p_construcao = new CConstrucao;
	if(!aux->m_p_construcao)
	{
		Erro("Código do erro:", "0600");
	}
	aux->m_p_construcao->Iniciar(tipo, x, y);
	m_num_construcoes++;
}


//------------------------------------------------------------
void CConstrucao::Atualizar(TRect area, CObjetoAvancado * const alvo)
{
	if(m_tipo == eConstrucao_04)
	{
		if(m_atirar >= 500)
		{
			m_tiros.Adicionar(eTiroFogo, m_x + (m_largura / 2), m_y + m_altura, alvo);
			m_atirar = 0;
		}
		m_atirar += rand() % 11;
		m_quadro = m_quadro == 2 ? 0 : m_quadro + 1;
	}

	m_tiros.AtualizarTodos(area, alvo);
	if(m_status == eConstrucaoExplosao)
	{
		m_quadro++;
		if (m_quadro == 9)
		{
			m_status = eConstrucaoInativo;
		}
	}
}


//------------------------------------------------------------
void CConstrucao::AtualizarTodos(TRect area, CObjetoAvancado * const alvo)
{
	Log("");
	Log("[INICIO]:CConstrucao::AtualizarTodos();");

	CConstrucao *aux;

	for(aux = m_p_construcao; aux; aux = aux->m_p_construcao)
	{
		if(aux->ChecarColisao(area))
		{
			aux->Atualizar(area, alvo);
			aux->m_ativo = TRUE;
			aux->m_visivel = TRUE;
		}
		else if(aux->m_tiros.VerificarExisteTiros())
		{
			aux->Atualizar(area, alvo);
			aux->m_visivel = FALSE;
		}
		else
		{
			aux->m_ativo = FALSE;
			aux->m_visivel = FALSE;
		}
	}
	Log("[FIM]:CConstrucao::AtualizarTodos();");
	Log("");
}


//------------------------------------------------------------
void CConstrucao::Desenhar(CTela & tela, int x_real, int y_real)
{
	switch(m_status)
	{
		case eConstrucaoNormal:
			tela.MaskedBlit((BITMAP *)m_dat_arquivo[m_tipo].dat, eCamadaObjetos, m_quadro * m_largura, 0, m_x - x_real, m_y - y_real, m_largura, m_altura);
			break;

		case eConstrucaoExplosao:
			tela.Blit((BITMAP *)m_dat_arquivo[_CONSTRUCAO_EXPLOSAO].dat, eCamadaObjetos, m_quadro * 50, 0, m_x - x_real, m_y - y_real, 50, 50);
			break;
	}
	m_tiros.DesenharTodos(tela, x_real, y_real);
}


//------------------------------------------------------------
void CConstrucao::DesenharTodos(CTela & tela, int x_real, int y_real)
{
	Log("[INICIO]:CConstrucao::DesenharTodos();");
	CConstrucao *aux;

	for(aux = m_p_construcao; aux; aux = aux->m_p_construcao)
	{
		if(aux->m_ativo)
		{
			aux->Desenhar(tela, x_real, y_real);
		}
	}
	Log("[FIM]:CConstrucao::DesenharTodos();");
}


//------------------------------------------------------------
void CConstrucao::Finalizar()
{
	Log("");
	Log("[INICIO]:CConstrucao::Finalizar();");

	CConstrucao *aux, *del;

	for(aux = m_p_construcao; aux;)
	{
		del = aux;
		aux = aux->m_p_construcao;
		del->m_tiros.Finalizar();
		delete del;
		m_num_construcoes--;
	}

	m_p_construcao = NULL;
	Log("[FIM]:CConstrucao::Finalizar();");
	Log("");
}


//------------------------------------------------------------
int CConstrucao::ObterTipo()
{
	return m_tipo;
}


//------------------------------------------------------------
void CConstrucao::SalvarConstrucao(char * fase)
{
	CConstrucao *aux_construcao;
	TObjeto construcao;
	FILE *m_arquivo;
	int flag = 2;

	if((m_arquivo = fopen(fase, "rb+")) != NULL)
	{
		if(m_p_construcao)
		{
			construcao.m_tipo = eConstrucao;
			fseek(m_arquivo, 0, SEEK_END);
			for(aux_construcao = m_p_construcao; aux_construcao; aux_construcao = aux_construcao->m_p_construcao)
			{
				construcao.subtipo = aux_construcao->ObterTipo();
				construcao.x = aux_construcao->ObterX();
				construcao.y = aux_construcao->ObterY();
				fwrite(&construcao, sizeof(TObjeto), 1, m_arquivo);
			}
		}
	}
    fclose(m_arquivo);
}


//------------------------------------------------------------
void CConstrucao::Excluir(int tipo, int x, int y)
{
	CConstrucao *aux, *del;

	for(aux = this; aux->m_p_construcao;)
	{
		if(aux->m_p_construcao->ObterTipo() == tipo
		&& aux->m_p_construcao->ObterX()    == x
		&& aux->m_p_construcao->ObterY()    == y)
		{
			del = aux->m_p_construcao;
			aux->m_p_construcao = aux->m_p_construcao->m_p_construcao;
			delete del;
			m_num_construcoes--;
		}
		else
		{
			aux = aux->m_p_construcao;
		}
	}
}

void CConstrucao::Excluir(int x1, int y1, int x2, int y2)
{
	CConstrucao *aux, *del;

	for(aux = this; aux->m_p_construcao;)
	{
		if(aux->m_p_construcao->ChecarColisao(x1, y1, x2, y2))
		{
			del = aux->m_p_construcao;
			aux->m_p_construcao = aux->m_p_construcao->m_p_construcao;
			delete del;
			m_num_construcoes--;
		}
		else
		{
			aux = aux->m_p_construcao;
		}
	}
}



//------------------------------------------------------------
int CConstrucao::ChecarColisaoConstrucoes(int x1, int y1, int x2, int y2)
{
	CConstrucao *aux;

	for(aux = m_p_construcao; aux; aux = aux->m_p_construcao)
	{
		if(aux->ChecarColisao(x1, y1, x2, y2))
		{
			return TRUE;
		}
	}
	return FALSE;
}


//------------------------------------------------------------
void CConstrucao::Sonorizar()
{
	if(m_status == eConstrucaoExplosao
	&& m_quadro == 0)
	{
		play_sample((SAMPLE *)m_dat_arquivo[_WAV_CONSTRUCAO_EXPLOSAO].dat, 128, 128, 1000, 0);
	}
	m_tiros.SonorizarTodos();
}


//------------------------------------------------------------
void CConstrucao::SonorizarTodos()
{
	CConstrucao *aux;

	for(aux = m_p_construcao; aux; aux = aux->m_p_construcao)
	{
		if(aux->m_ativo)
		{
			aux->Sonorizar();
		}
	}
}


//------------------------------------------------------------
void CConstrucao::SetarStatus(EStatusConstrucao status)
{
	m_status = status;
}


//------------------------------------------------------------
EStatusConstrucao CConstrucao::ObterStatus()
{
	return m_status;
}


//------------------------------------------------------------
int CConstrucao::ObterEnergia()
{
	return m_energia;
}


//------------------------------------------------------------
void CConstrucao::DecEnergia(int decremento)
{
	m_energia -= decremento;

	if(m_energia == 0)
	{
		m_status = eConstrucaoExplosao;
		m_quadro = 0;
	}
}


//------------------------------------------------------------
CTiro *CConstrucao::ObterTiros()
{
	return &m_tiros;
}