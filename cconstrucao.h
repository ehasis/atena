 /*------------------------------------------------------------*
 *  cconstrucao.h - Classe CConstrucao
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: sábado, 27 de janeiro de 2002
*
*  Diego em 13/02/2002
*   - Alterado os métodos Desenhar e DesenharTodos para aceitar
*     CTela e posicionamento relativo;
*
*  Diego Giacomelli em 05/03/2002
*   - Alterada herânça para CObjetoAvancado
*------------------------------------------------------------*/


#ifndef cconstrucao_h_incluido
#define cconstrucao_h_incluido


#include <stdio.h>
#include <allegro.h>
#include <string.h>
#include "funcoes.h"
#include "ctiro.h"


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
	static void CarregarArquivoDados(DATAFILE * dat_arquivo);
	static void DescarregarArquivoDados();
	static int ObterNumeroConstrucoes() { return m_num_construcoes; };
	void Iniciar(int tipo, int x, int y);
	void Desenhar(CTela & tela, int x_real, int y_real);;
	void DesenharTodos(CTela & tela, int x_real, int y_fase);
	void Atualizar(TRect area, CObjetoAvancado * const alvo);
	void AtualizarTodos(TRect area, CObjetoAvancado * const alvo);
	void Finalizar();
	void Adicionar(int tipo, int x, int y);
	int ObterTipo();
	void SalvarConstrucao(char * fase);
	void Excluir(int tipo, int x, int y);
	void Excluir(int x1, int y1, int x2, int y2);
	int ChecarColisaoConstrucoes(int x1, int y1, int x2, int y2);
	void Sonorizar();
	void SonorizarTodos();
	void SetarStatus(EStatusConstrucao status);
	EStatusConstrucao ObterStatus();
	int ObterEnergia();
	void DecEnergia(int decremento);
	CTiro *ObterTiros();

	CConstrucao *m_p_construcao;	   		// Ponteiro para o proximo nodo da lista
private:
	int m_tipo; //eConstrucao
	int m_atirar;
	EStatusConstrucao m_status;
	static DATAFILE *m_dat_arquivo;
	static int m_num_construcoes;
	CTiro m_tiros;
};

#endif