 /*------------------------------------------------------------*
 *  cconstrucao.cpp - Implementacao da Classe CConstrucao
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: domingo, 27 de janeiro de 2002
*
*  Diego em 13/02/2002
*   - Alterado os métodos Desenhar e DesenharTodos para aceitar
*     CTela e posicionamento relativo;
*
*------------------------------------------------------------*/


#include "erro.h"
#include "cconstrucao.h"
#include "construcoes.h"


//------------------------------------------------------------
// Membros static
DATAFILE *CConstrucao::dat_arquivo = NULL;
int CConstrucao::num_construcoes = 0;


//------------------------------------------------------------
// Construtor
CConstrucao::CConstrucao(void)
{
	p_construcao = NULL;
}


//------------------------------------------------------------
void CConstrucao::Iniciar(int _tipo, int _x, int _y)
{
	x			= _x;
	y			= _y;
	tipo		= _tipo;
	quadro	    = 0;
	atirar		= TRUE;
	ativo  = TRUE;
	status	    = eConstrucaoNormal;
	atirar	    = 1;

	switch(tipo)
	{
		case eConstrucao_01:
			largura    = 110;
			altura     = 99;
			energia	   = 1;
			break;

		case eConstrucao_02:
			largura    = 161;
			altura     = 161;
			energia	   = 2;
			break;

		case eConstrucao_03:
			largura    = 102;
			altura     = 103;
			energia	   = 2;
			break;

		case eConstrucao_04:
			largura    = 62;
			altura     = 67;
			energia	   = 2;
			break;

		case eConstrucao_05:
			largura    = 132;
			altura     = 132;
			energia	   = 2;
			break;

		case eConstrucao_06:
			largura    = 111;
			altura     = 97;
			energia	   = 2;
			break;
	}
}


//------------------------------------------------------------
void CConstrucao::Adicionar(int _tipo, int _x, int _y)
{
	CConstrucao *aux;

    for(aux = this; aux->p_construcao; aux = aux->p_construcao);

	aux->p_construcao = new CConstrucao;
	if(!aux->p_construcao)
	{
		Erro("Código do erro:", "0600");
	}
	aux->p_construcao->Iniciar(_tipo, _x, _y);
	num_construcoes++;
}


//------------------------------------------------------------
void CConstrucao::Atualizar(TRect _area, CObjeto * const _alvo)
{
	if(tipo == eConstrucao_04)
	{
		if(atirar >= 500)
		{
			tiros.Adicionar(eTiroFogo, x + (largura / 2), y + altura, _alvo);
			atirar = 0;
		}
		atirar += rand() % 11;
		quadro = quadro == 2 ? 0 : quadro + 1;
	}

	tiros.AtualizarTodos(_area, _alvo);
	if(status == eConstrucaoExplosao)
	{
		quadro++;
		if (quadro == 9)
		{
			status = eConstrucaoInativo;
		}
	}
}


//------------------------------------------------------------
void CConstrucao::AtualizarTodos(TRect _area, CObjeto * const _alvo)
{
	CConstrucao *aux;

	for(aux = p_construcao; aux; aux = aux->p_construcao)
	{
		if(aux->ChecarColisao(_area))
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
void CConstrucao::Desenhar(CTela &_tela, int _x_real, int _y_real)
{
	switch(status)
	{
		case eConstrucaoNormal:
			_tela.MaskedBlit((BITMAP *)dat_arquivo[tipo].dat, eCamadaObjetos, quadro * largura, 0, x - _x_real, y - _y_real, largura, altura);
			break;

		case eConstrucaoExplosao:
			_tela.Blit((BITMAP *)dat_arquivo[CONSTRUCAO_EXPLOSAO].dat, eCamadaObjetos, quadro * 50, 0, x - _x_real, y - _y_real, 50, 50);
			break;
	}
	tiros.DesenharTodos(_tela, _x_real, _y_real);
}


//------------------------------------------------------------
void CConstrucao::DesenharTodos(CTela &_tela, int _x_real, int _y_real)
{
	CConstrucao *aux;

	for(aux = p_construcao; aux; aux = aux->p_construcao)
	{
		if(aux->ativo)
		{
			aux->Desenhar(_tela, _x_real, _y_real);
		}
	}
}


//------------------------------------------------------------
void CConstrucao::Desligar(void)
{
	CConstrucao *aux, *del;

	for(aux = p_construcao; aux;)
	{
		del = aux;
		aux = aux->p_construcao;
		delete del;
		num_construcoes--;
	}
}


//------------------------------------------------------------
int CConstrucao::ObterTipo(void)
{
	return tipo;
}


//------------------------------------------------------------
void CConstrucao::SalvarConstrucao(char *_fase)
{
	CConstrucao *aux_construcao;
	TObjeto construcao;
	FILE *arquivo;
	int flag = 2;

	if((arquivo = fopen(_fase, "rb+")) != NULL)
	{
		if(p_construcao)
		{
			construcao.tipo = eConstrucao;
			fseek(arquivo, 0, SEEK_END);
			for(aux_construcao = p_construcao; aux_construcao; aux_construcao = aux_construcao->p_construcao)
			{
				construcao.subtipo = aux_construcao->ObterTipo();
				construcao.x = aux_construcao->ObterX();
				construcao.y = aux_construcao->ObterY();
				fwrite(&construcao, sizeof(TObjeto), 1, arquivo);
			}
		}
	}
    fclose(arquivo);
}


//------------------------------------------------------------
void CConstrucao::Excluir(int _tipo, int _x, int _y)
{
	CConstrucao *aux, *del;

	for(aux = this; aux->p_construcao;)
	{
		if(aux->p_construcao->ObterTipo() == _tipo
		&& aux->p_construcao->ObterX()    == _x
		&& aux->p_construcao->ObterY()    == _y)
		{
			del = aux->p_construcao;
			aux->p_construcao = aux->p_construcao->p_construcao;
			delete del;
			num_construcoes--;
		}
		else
		{
			aux = aux->p_construcao;
		}
	}
}

void CConstrucao::Excluir(int _x1, int _y1, int _x2, int _y2)
{
	CConstrucao *aux, *del;

	for(aux = this; aux->p_construcao;)
	{
		if(aux->p_construcao->ChecarColisao(_x1, _y1, _x2, _y2))
		{
			del = aux->p_construcao;
			aux->p_construcao = aux->p_construcao->p_construcao;
			delete del;
			num_construcoes--;
		}
		else
		{
			aux = aux->p_construcao;
		}
	}
}



//------------------------------------------------------------
int CConstrucao::ChecarColisaoConstrucoes(int _x1, int _y1, int _x2, int _y2)
{
	CConstrucao *aux;

	for(aux = p_construcao; aux; aux = aux->p_construcao)
	{
		if(aux->ChecarColisao(_x1, _y1, _x2, _y2))
		{
			return TRUE;
		}
	}
	return FALSE;
}


//------------------------------------------------------------
void CConstrucao::Sonorizar(void)
{
	if(status == eConstrucaoExplosao
	&& quadro == 0)
	{
		play_sample((SAMPLE *)dat_arquivo[WAV_CONSTRUCAO_EXPLOSAO].dat, 128, 128, 1000, 0);
	}
	tiros.SonorizarTodos();
}


//------------------------------------------------------------
void CConstrucao::SonorizarTodos(void)
{
	CConstrucao *aux;

	for(aux = p_construcao; aux; aux = aux->p_construcao)
	{
		if(aux->ativo)
		{
			aux->Sonorizar();
		}
	}
}


//------------------------------------------------------------
void CConstrucao::SetarStatus(EStatusConstrucao _status)
{
	status = _status;
}


//------------------------------------------------------------
EStatusConstrucao CConstrucao::ObterStatus(void)
{
	return status;
}


//------------------------------------------------------------
int CConstrucao::ObterEnergia(void)
{
	return energia;
}


//------------------------------------------------------------
void CConstrucao::DecEnergia(int _decremento)
{
	energia -= _decremento;

	if(energia == 0)
	{
		status = eConstrucaoExplosao;
		quadro = 0;
	}
}


//------------------------------------------------------------
CTiro *CConstrucao::ObterTiros(void)
{
	return &tiros;
}