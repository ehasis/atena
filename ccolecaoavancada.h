 /*------------------------------------------------------------*
 *  CColecaoAvancada.h - Classe CColecaoAvancada
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: terça, 09 de julho de 2002
*
*  Alterações:
*
*  Diego Giacomelli em 16/07/2002
*	- Retirado o método Adicionar, estava fora do contexto da
*	  classe;
*------------------------------------------------------------*/


#ifndef ccolecaoavancada_h_incluido
#define ccolecaoavancada_h_incluido


#include "cobjeto.h"
#include "ccolecao.h"

//------------------------------------------------------------
// Classe para colecao de objetos animados
template < class cls >
class CColecaoAvancada : public CColecao< cls >
{
public:
	void Atualizar(TRect area, CObjetoAvancado * const alvo);
	void Desenhar(CTela & tela, int x_real, int y_real);
	void Sonorizar();
	void Finalizar();
	bool Colidir(TRect area, int energia);
	bool ChecarColisao(int x1, int y1, int x2, int y2);
	bool ChecarColisao(TRect area);
	void RemoverPorColisao(int x1, int y1, int x2, int y2);
	cls & ObterMaisProximo(int x, int y);
};


//------------------------------------------------------------
template < class cls >
void CColecaoAvancada< cls >::Atualizar(TRect area, CObjetoAvancado * const alvo)
{
	if(MoverPrimeiro())
	{
		do
		{
			Obter().Atualizar(area, alvo);
		} while(MoverProximo());
	}
}



//------------------------------------------------------------
template < class cls >
void CColecaoAvancada< cls >::Desenhar(CTela & tela, int x_real, int y_real)
{
	if(MoverPrimeiro())
	{
		do
		{
			Obter().Desenhar(tela, x_real, y_real);
		} while(MoverProximo());
	}
}


//------------------------------------------------------------
template < class cls >
void CColecaoAvancada< cls >::Sonorizar()
{
	if(MoverPrimeiro())
	{
		do
		{
			Obter().Sonorizar();
		} while(MoverProximo());
	}
}

//------------------------------------------------------------
template < class cls >
void CColecaoAvancada< cls >::Finalizar()
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
bool CColecaoAvancada< cls >::Colidir(TRect area, int energia)
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
bool CColecaoAvancada< cls >::ChecarColisao(int x1, int y1, int x2, int y2)
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
bool CColecaoAvancada< cls >::ChecarColisao(TRect area)
{
	if(MoverPrimeiro())
	{
		do
		{
			if(Obter().ChecarColisao(area)) return true;
		} while(MoverProximo());
	}
	return false;
}


//------------------------------------------------------------
template < class cls >
void CColecaoAvancada< cls >::RemoverPorColisao(int x1, int y1, int x2, int y2)
{
	if(MoverPrimeiro())
	{
		do
		{
			if(Obter().ChecarColisao(x1, y1, x2, y2))
			{
				Remover();
				MoverAnterior();
			}
		} while(MoverProximo());
	}
}


//------------------------------------------------------------
template < class cls >
cls & CColecaoAvancada< cls >::ObterMaisProximo(int x, int y)
{
	int menor_distancia = 999;
	int distancia;
	int ind;

	if(MoverPrimeiro())
	{
		do
		{
			if(Obter().ObterVisivel())
			{
				distancia = sqrt(pow(x - Obter().ObterX(), 2) + pow(y - Obter().ObterY(), 2));
				if(distancia < menor_distancia)
				{
					menor_distancia = distancia;
					ind = ObterIndice();
				}
			}
		} while(MoverProximo());
	}
	return Obter(ind);
}


#endif