 /*------------------------------------------------------------*
 *  ccenario.h - Classe CCenario
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: sexta-feira, 11 de julho de 2003
*
*  Alterações:
*
*
*------------------------------------------------------------*/

#ifndef ccenario_h_incluido
#define ccenario_h_incluido

#include "callegro.h"

#include "cobjeto.h"

class CCenario: public CObjetoEstatico
{
public:
	CCenario();
	~CCenario();

	virtual void Iniciar(TObjeto &obj);
	virtual void Finalizar();
	virtual void Atualizar(TRect &area, CObjetoAvancado * const alvo);
	virtual void Desenhar(CTela &tela, int x_real, int y_real);

protected:
	BITMAP *m_bitmap;

};

//------------------------------------------------------------
inline void CCenario::Atualizar(TRect &area, CObjetoAvancado * const alvo)
{
	//nada
}


//------------------------------------------------------------
inline void CCenario::Desenhar(CTela &tela, int x_real, int y_real)
{
	tela.MaskedBlit(m_bitmap, eCamadaObjetos, 0, 0, m_x - x_real, m_y - y_real, m_largura, m_altura);
}

#endif
