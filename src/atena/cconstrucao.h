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
*------------------------------------------------------------*/

#ifndef cconstrucao_h_incluido
#define cconstrucao_h_incluido

#include "callegro.h"

#include "cobjeto.h"
#include "carma.h"
#include "ccolecaoavancada.h"

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


enum EStatusConstrucao
{
	eConstrucaoNormal,
	eConstrucaoExplosao,
	eConstrucaoInativo
};


//------------------------------------------------------------
// Classe para as construções
class CConstrucao : public CObjetoAvancado
{
public:
	CConstrucao();
	static void CarregarArquivoDados(const char *arquivo);
	static void DescarregarArquivoDados();
	void Iniciar(int tipo, int x, int y);
	void Desenhar(CTela & tela, int x_real, int y_real);;
	void Atualizar(TRect area, CObjetoAvancado * const alvo);
	void Finalizar();
	int ObterTipo();
	void Sonorizar();
	void SetarStatus(EStatusConstrucao status);
	EStatusConstrucao ObterStatus();
	int ObterEnergia();
	void DecEnergia(int decremento);
	CColecaoAvancada< CArma > & ObterArmas();

private:
	int m_tipo; //eConstrucao
	int m_atirar;
	EStatusConstrucao m_status;
	static GADados m_dat_arquivo;
	CColecaoAvancada< CArma > m_armas;
};

#endif

