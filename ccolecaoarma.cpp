 /*------------------------------------------------------------*
 *  ccolecaoarma.cpp - Implementação da Classe CColecaoArma
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: sábado, 06 de julho de 2002
*
*  Alterações:
*
*------------------------------------------------------------*/


#include "ccolecaoarma.h"


//------------------------------------------------------------
bool CColecaoArma::Adicionar(int tipo, int x, int y)
{
	CArma arma;

	arma.Iniciar(tipo, x, y);
	return AdicionarFim(arma);
}


//------------------------------------------------------------
void CColecaoArma::Atualizar(TRect area, CObjetoAvancado * const alvo)
{
	int ind;

	ind = ObterIndice();
	MoverPrimeiro();

	do
	{
		Obter().Atualizar(area, alvo);
	} while(MoverProximo());

	Mover(ind);
}


//------------------------------------------------------------
void CColecaoArma::Desenhar(CTela & tela, int x_real, int y_real)
{
	int ind;

	ind = ObterIndice();
	MoverPrimeiro();

	do
	{
		Obter().Desenhar(tela, x_real, y_real);
	} while(MoverProximo());

	Mover(ind);
}


//------------------------------------------------------------
void CColecaoArma::Sonorizar()
{
	int ind;

	ind = ObterIndice();
	MoverPrimeiro();

	do
	{
		Obter().Sonorizar();
	} while(MoverProximo());

	Mover(ind);
}

//------------------------------------------------------------
void CColecaoArma::Finalizar()
{
	MoverPrimeiro();

	do
	{
		Obter().Finalizar();
		Obter().ObterTiros().Finalizar();
	} while(MoverProximo());

	RemoverTodos();
}