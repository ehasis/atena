 /*----------------------------------------------------------*
 *  ccolecaoavancada.h - Classe CColecaoAvancada
*------------------------------------------------------------*
*  Nome: cls Giacomelli
*  Data: sábado, 06 de julho de 2002
*
*
*------------------------------------------------------------*/


#ifndef ccolecaoavancada_h_incluido
#define ccolecaoavancada_h_incluido


#include "erro.h"
#include "ccolecao.h"


template< class cls >
class CColecaoAvancada : public CColecao< cls > 
{
public:
	virtual bool Adicionar(int tipo, int x, int y);
	virtual void Atualizar(TRect area, CObjetoAvancado * const alvo);
	virtual void Desenhar(CTela & tela, int x_real, int y_real);
	virtual void Finalizar();
	virtual void Sonorizar();
};	

#endif