 /*------------------------------------------------------------*
 *  ccolecao.h - Classe CColecao
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: sexta-feira, 28 de junho de 2002
*
*  Alterações:
*
*  Diego Giacomelli em 16/07/2002
*	- Retirados o qualificado const do parâmetro valor 
*	  dos métodos;
*	- Inseridos os métodos Adicionar, AdicionarFim,  sem parâmetros;
*
*  Diego Giacomelli em 19/07/2002
*	- Corrigida falha em Adicionar(cls valor) quando se insiria
*	  um valor no meio da lista;
*------------------------------------------------------------*/


#ifndef ccolecao_h_incluido
#define ccolecao_h_incluido

#include "callegro.h"


template< class cls >
class CNodo
{
public:
	CNodo();
	CNodo< cls > * m_p_itm_ant;
	cls valor;
	CNodo< cls > * m_p_prx_itm;
};

template< class cls >
CNodo< cls >::CNodo()
{
	m_p_itm_ant = NULL;
	m_p_prx_itm = NULL;
}

template< class cls >
class CColecao
{
public:
	CColecao();
	~CColecao();
	bool Adicionar();
	bool Adicionar(cls valor);
	bool Adicionar(cls valor, int indice);
	bool AdicionarInicio(cls valor);
	bool AdicionarFim();
	bool AdicionarFim(cls valor);
	bool Remover();
	bool Remover(int indice);
	bool RemoverInicio();
	bool RemoverFim();
	bool RemoverTodos();
	cls & Obter();
	cls & Obter(int indice);
	int ObterIndice();
	int ObterQuantidade();
	bool Mover(int indice);
	bool MoverPrimeiro();
	bool MoverUltimo();
	bool MoverAnterior();
	bool MoverProximo();

private:
	CNodo< cls > * m_p_pri_itm;
	CNodo< cls > * m_p_ult_itm;
	CNodo< cls > * m_p_itm_atual;
	int m_ind_itm_atual;
	int m_qtd_itm;

};	


template< class cls > 
//------------------------------------------------------------
CColecao< cls >::CColecao()
{
	m_p_pri_itm = NULL;
	m_p_ult_itm = NULL;
	m_p_itm_atual = NULL;
	m_qtd_itm = 0;
	m_ind_itm_atual = 0;
}


template< class cls > 
//------------------------------------------------------------
CColecao< cls >::~CColecao()
{
	while(m_p_pri_itm) RemoverFim();
}


//------------------------------------------------------------
template< class cls > 
bool CColecao< cls >::Adicionar()
{
	cls valor;

	return Adicionar(valor);
}


//------------------------------------------------------------
template< class cls > 
bool CColecao< cls >::Adicionar(cls valor)
{
	CNodo< cls > *novo;

    novo = new CNodo< cls >;

	if (!novo) return false;

	novo->valor = valor;
	
	if(m_p_itm_atual)
	{
		if(m_p_itm_atual->m_p_itm_ant)
		{
			m_p_itm_atual->m_p_itm_ant->m_p_prx_itm = novo;
			novo->m_p_itm_ant = m_p_itm_atual->m_p_itm_ant;
		}
		else
		{
			m_p_pri_itm = novo;
		}

		
		m_p_itm_atual->m_p_itm_ant = novo;
		novo->m_p_prx_itm = m_p_itm_atual;
		m_p_itm_atual = novo;
	}
	else
	{
		m_p_pri_itm = novo;
		m_p_ult_itm = novo;
		m_p_itm_atual = novo;
	}
	
	m_qtd_itm++;
	return true;
}


//------------------------------------------------------------
template< class cls > 
bool CColecao< cls >::Adicionar(cls valor, int indice)
{
	int ind;
	char buf[80];
	
	if(indice < 1 || indice > m_qtd_itm + 1) return false;
	if(m_qtd_itm == 0) return AdicionarInicio(valor) ;
	if(indice == m_qtd_itm + 1)
		return AdicionarFim(valor);

	Mover(indice);
	m_ind_itm_atual = indice;
	return Adicionar(valor);
}


//------------------------------------------------------------
template< class cls > 
bool CColecao< cls >::AdicionarInicio(cls valor)
{
	m_p_itm_atual = m_p_pri_itm;
	m_ind_itm_atual = 1;
	return Adicionar(valor);
}


//------------------------------------------------------------
template< class cls > 
bool CColecao< cls >::AdicionarFim()
{
	cls valor;

	return AdicionarFim(valor);
}


//------------------------------------------------------------
template< class cls > 
bool CColecao< cls >::AdicionarFim(cls valor)
{
	CNodo< cls > *novo;

	if(!m_p_pri_itm) 
		return Adicionar(valor);
	
	novo = new CNodo< cls >;

	if (!novo) return false;

	novo->valor = valor;

	m_p_ult_itm->m_p_prx_itm = novo;
	novo->m_p_itm_ant = m_p_ult_itm;
	m_p_ult_itm = novo;
	m_p_itm_atual = novo;
	m_qtd_itm++;
	m_ind_itm_atual = m_qtd_itm;
	return true;
}


//------------------------------------------------------------	
template< class cls > 
bool CColecao< cls >::Remover()
{
	CNodo< cls > *aux;

	if(!m_p_itm_atual) return false;

	aux = m_p_itm_atual;
	if(m_p_itm_atual->m_p_itm_ant)
		m_p_itm_atual->m_p_itm_ant->m_p_prx_itm = m_p_itm_atual->m_p_prx_itm;
	else
	{
		m_p_pri_itm = m_p_itm_atual->m_p_prx_itm;
		if(m_p_pri_itm) m_ind_itm_atual = 1;
		else m_ind_itm_atual = 0;
	}

	if(m_p_itm_atual->m_p_prx_itm)
	{
		m_p_itm_atual->m_p_prx_itm->m_p_itm_ant = m_p_itm_atual->m_p_itm_ant;
		m_p_itm_atual = m_p_itm_atual->m_p_prx_itm;
	}
	else
	{
		m_p_itm_atual = m_p_itm_atual->m_p_itm_ant;
		m_p_ult_itm = m_p_itm_atual;
		m_ind_itm_atual--;
	}
	
	
	delete aux;
	m_qtd_itm--;
	
	return true;
}


//------------------------------------------------------------	
template< class cls > 
bool CColecao< cls >::Remover(int indice)
{
	if(Mover(indice)) return Remover();
	return false;
}


//------------------------------------------------------------	
template< class cls > 
bool CColecao< cls >::RemoverInicio()
{
	m_p_itm_atual = m_p_pri_itm;
	return Remover();
}


//------------------------------------------------------------	
template< class cls > 
bool CColecao< cls >::RemoverFim()
{
	m_p_itm_atual = m_p_ult_itm;
	return Remover();
}


//------------------------------------------------------------	
template< class cls > 
bool CColecao< cls >::RemoverTodos()
{
	while(m_p_pri_itm)
		if(!RemoverFim()) return false;

	return true;
}

//------------------------------------------------------------	
template< class cls > 
cls & CColecao< cls >::Obter()
{
	return m_p_itm_atual->valor;
}


//------------------------------------------------------------	
template< class cls > 
cls & CColecao< cls >::Obter(int indice)
{
	Mover(indice);
	return Obter();
}


//------------------------------------------------------------	
template< class cls > 
int CColecao< cls >::ObterIndice()
{
	return m_ind_itm_atual;
}


//------------------------------------------------------------	
template< class cls > 
int CColecao< cls >::ObterQuantidade()
{
	return m_qtd_itm;
}


//------------------------------------------------------------	
template< class cls > 
bool CColecao< cls >::Mover(int indice)
{
	int ind;

	if(indice < 1 || indice > m_qtd_itm) return false;
		
	m_p_itm_atual = m_p_pri_itm;
	for(ind = 1; ind != indice; ind++)
		m_p_itm_atual = m_p_itm_atual->m_p_prx_itm;

	m_ind_itm_atual = indice;
	return true;
}


//------------------------------------------------------------	
template< class cls > 
bool CColecao< cls >::MoverPrimeiro()
{
	if(m_p_pri_itm)	
	{
		m_p_itm_atual = m_p_pri_itm;
		m_ind_itm_atual = 1;
		return true;
	}
	return false;
}


//------------------------------------------------------------	
template< class cls > 
bool CColecao< cls >::MoverUltimo()
{
	if(m_p_ult_itm)	
	{
		m_p_itm_atual = m_p_ult_itm;
		m_ind_itm_atual = m_qtd_itm;
		return true;
	}
	return false;
}


//------------------------------------------------------------	
template< class cls > 
bool CColecao< cls >::MoverAnterior()
{
	if(m_p_itm_atual && m_p_itm_atual->m_p_itm_ant)
	{
		m_p_itm_atual = m_p_itm_atual->m_p_itm_ant;
		m_ind_itm_atual--;
		return true;
	}
	return false;
}


//------------------------------------------------------------	
template< class cls > 
bool CColecao< cls >::MoverProximo()
{
	if(m_p_itm_atual && m_p_itm_atual->m_p_prx_itm)
	{
		m_p_itm_atual = m_p_itm_atual->m_p_prx_itm;
		m_ind_itm_atual++;
		return true;
	}
	return false;
}

#endif

