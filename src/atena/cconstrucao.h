 /*------------------------------------------------------------*
 *  cconstrucao.h - Classe CConstrucao
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: sábado, 27 de janeiro de 2002
*
*  Diego Giacomelli em 13/02/2002
*   - Alterado os métodos Desenhar e DesenharTodos para aceitar
*     CTela e posicionamento relativo;
*
*  Diego Giacomelli em 05/03/2002
*   - Alterada herânça para CObjetoAvancado;
*
*  Diego Giacomelli em 20/07/2002
*	- Alterada toda a classe para ser utilizada com CColecaoAvancada;
*	- Substituido m_tiros por m_armas; 
*
*  Henrique Andreassy em 17/06/2003
*	- Modificado a classe para derivar de CInimigo
*
*------------------------------------------------------------*/

#ifndef cconstrucao_h_incluido
#define cconstrucao_h_incluido

#include "cinimigo.h"

typedef enum
{
	eConstrucao_01,
	eConstrucao_02,
	eConstrucao_03,
	eConstrucao_04,
	eConstrucao_05,
	eConstrucao_06,
	eConstrucao_07
} EConstrucao;

//------------------------------------------------------------
// Classe para as construções
class CConstrucao : public CInimigo
{
public:
	virtual void Iniciar(TObjeto &obj);
	virtual void Finalizar();

	virtual void Desenhar(CTela &tela, int x_real, int y_real);;
	void Atualizar(TRect &area, CObjetoAvancado * const alvo);

private:
	int m_atirar;
};

#endif

