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

#include <allegro.h>
#include "galib.h"

class CChefe: public CObjetoAvancado
{
public:
	void Iniciar();
	void Atualizar(TRect area, CObjetoAvancado * const alvo);
	void Desenhar(CTela & tela, int x_real, int y_real);
	void Sonorizar();
	void Finalizar();

private:
	GADados m_dados;
	CColecaoArma m_armas;

};

#endif