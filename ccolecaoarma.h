 /*------------------------------------------------------------*
 *  ccolecaoarma.h - Classe CColecaoArma
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: sábado, 06 de julho de 2002
*
*  Alterações:
*
*------------------------------------------------------------*/


#ifndef ccolecaoarma_h_incluido
#define ccolecaoarma_h_incluido


#include "cobjeto.h"
#include "ctiro.h"
#include "funcoes.h"
#include "erro.h"
#include "ccolecao.h"
#include "carma.h"

//------------------------------------------------------------
// Classe para colecao de armas
class CColecaoArma : public CColecao< CArma >
{
public:
	bool Adicionar(int tipo, int x, int y);
	void Atualizar(TRect area, CObjetoAvancado * const alvo);
	void Desenhar(CTela & tela, int x_real, int y_real);
	void Sonorizar();
	void Finalizar();
};
#endif