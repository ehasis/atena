 /*------------------------------------------------------------*
 *  ctiro.h - Classe CTiro
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: terça-feira, 13 de janeiro de 2002
*
*  Diego Giacomelli em 13/02/2002
*   - Alterado os métodos Desenhar e DesenharTodos para aceitar
*     CTela e posicionamento relativo;
*
*  Diego Giacomelli em 24/02/2002
*   - Incluido membro de dados m_velocidade;
*
*  Diego Giacomelli em 05/03/2002
*   - Alterada herância para CObjetoAvancado;
*
*  Diego Giacomelli em 01/05/2002
*   - Inserido o método ObterMaisProximo;
*
*  Diego Giacomelli em 23/06/2002
*   - Renomeado ETiroTipo para ETiro
*
*  Diego Giacomelli em 20/06/2002
*	- Alterada toda a classe para ser utilizada com CColecaoAvancada;
*	- Implementado método ObterStatus;
*------------------------------------------------------------*/

#ifndef ctiro_h_incluido
#define ctiro_h_incluido

#include "callegro.h"

#include "cobjeto.h"
#include "tiros.h"

typedef enum
{
	eTiroCerra,
	eTiroBola,
	eTiroLaserVermelho,
	eTiroLaserVerde,
	eTiroFogoTeleguiado,
	eTiroFogo
} ETiro;


typedef enum
{
	eTiroNormal,
	eTiroExplosao,
	eTiroInativo
} EStatusTiro;

//------------------------------------------------------------
// Classe para as tiros
class CTiro : public CObjetoAvancado
{
public:
	CTiro();
	static void CarregarArquivoDados(const char *arquivo);
	static void DescarregarArquivoDados();
	void Iniciar(ETiro tipo, int x, int y, CObjetoAvancado * const alvo);
	void Atualizar(TRect area, CObjetoAvancado * const alvo);
	void Desenhar(CTela & tela, int x_real, int y_real);
	void Sonorizar();
	void SetarStatus(EStatusTiro status);
	EStatusTiro ObterStatus();
	void Finalizar();
	
	
private:
	ETiro m_tipo;
	static GADados m_dat_arquivo;
	CObjetoAvancado *m_alvo;
	int m_tocar_som;
	EStatusTiro m_status;
	int m_dir_x;
	int m_dir_y;
	int m_flag_x;
	int m_flag_y;
	int m_cont;
	int m_velocidade;
};

#endif

