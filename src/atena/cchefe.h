 /*------------------------------------------------------------*
 *  calien.h - Classe CAlien
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: doming, 4 de agosto de 2002
*
*  Alterações:
*
*
*
*-----------------------------------------------------------*/

#ifndef CCHEFE_H_INCLUIDO
#define CCHEFE_H_INCLUIDO

#include "callegro.h"

#include "cobjeto.h"
#include "ctela.h"
#include "ccolecaoavancada.h"
#include "carma.h"

enum EStatusChefe
{
	eChefeNormal,
	eChefeEscudo,
	eChefeAtingido,
	eChefeExplosao,
	eChefeInativo
};


class CChefe: public CObjetoAvancado
{
public:
	void Iniciar();
	void Atualizar(TRect area, CObjetoAvancado * const alvo);
	void Desenhar(CTela & tela, int x_real, int y_real);
	void Sonorizar();
	void Finalizar();
	
	void DecEnergia(int decremento);
	void SetarStatus(EStatusChefe status);
	EStatusChefe ObterStatus();
	bool CChefe::Colidir(TRect area, int energia);

private:
	EStatusChefe m_status;
	GADados m_dados;
	CColecaoAvancada< CArma > m_armas;

};

#endif

