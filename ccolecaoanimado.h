 /*------------------------------------------------------------*
 *  ccolecaoanimado.h - Classe CColecaoAnimado
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: terça, 09 de julho de 2002
*
*  Alterações:
*
*------------------------------------------------------------*/


#ifndef ccolecaoanimado_h_incluido
#define ccolecaoanimado_h_incluido


#include "cobjeto.h"
#include "ctiro.h"
#include "funcoes.h"
#include "erro.h"
#include "ccolecao.h"
#include "cveiculo.h"
#include "carma.h"

//------------------------------------------------------------
// Classe para colecao de objetos animados
template < class cls >
class CColecaoAnimado : public CColecao< cls >
{
public:
	bool Adicionar(int tipo, int x, int y);
	void Atualizar(TRect area, CObjetoAvancado * const alvo);
	void Desenhar(CTela & tela, int x_real, int y_real);
	void Sonorizar();
	void Finalizar();
	bool Colidir(TRect area, int energia);
	bool ChecarColisao(int x1, int y1, int x2, int y2);
	void RemoverPorColisao(int x1, int y1, int x2, int y2);
};



//------------------------------------------------------------
template < class cls >
bool CColecaoAnimado< cls >::Adicionar(int tipo, int x, int y)
{
	cls obj;

	obj.Iniciar(tipo, x, y);
	return AdicionarFim(obj);
}


//------------------------------------------------------------
template < class cls >
void CColecaoAnimado< cls >::Atualizar(TRect area, CObjetoAvancado * const alvo)
{
	int ind;

	ind = ObterIndice();
	if(MoverPrimeiro())
	{
		do
		{
			Obter().Atualizar(area, alvo);
		} while(MoverProximo());

		Mover(ind);
	}
}


//------------------------------------------------------------
template < class cls >
void CColecaoAnimado< cls >::Desenhar(CTela & tela, int x_real, int y_real)
{
	int ind;

	ind = ObterIndice();
	if(MoverPrimeiro())
	{
		do
		{
			Obter().Desenhar(tela, x_real, y_real);
		} while(MoverProximo());

		Mover(ind);
	}
}


//------------------------------------------------------------
template < class cls >
void CColecaoAnimado< cls >::Sonorizar()
{
	int ind;

	ind = ObterIndice();
	if(MoverPrimeiro())
	{
		do
		{
			Obter().Sonorizar();
		} while(MoverProximo());

		Mover(ind);
	}
}

//------------------------------------------------------------
template < class cls >
void CColecaoAnimado< cls >::Finalizar()
{
	if(MoverPrimeiro())
	{
		do
		{
			Obter().Finalizar();
		} while(MoverProximo());

		RemoverTodos();
	}
}


//------------------------------------------------------------
template < class cls >
bool CColecaoAnimado< cls >::Colidir(TRect area, int energia)
{
	bool colidiu = false;

	if(MoverPrimeiro())
	{
		do
		{
			if(Obter().Colidir(area, energia)) colidiu = true;
		} while(MoverProximo());
	}
	return colidiu;
}


//------------------------------------------------------------
template < class cls >
bool CColecaoAnimado< cls >::ChecarColisao(int x1, int y1, int x2, int y2)
{
	if(MoverPrimeiro())
	{
		do
		{
			if(Obter().ChecarColisao(x1, y1, x2, y2)) return true;
		} while(MoverProximo());
	}
	return false;
}

//------------------------------------------------------------
template < class cls >
void CColecaoAnimado< cls >::RemoverPorColisao(int x1, int y1, int x2, int y2)
{
	if(MoverPrimeiro())
	{
		do
		{
			if(Obter().ChecarColisao(x1, y1, x2, y2)) Remover();
		} while(MoverProximo());
	}
}
#endif