 /*------------------------------------------------------------*
 *  carma.h - Classe CArma
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: quarta-feira, 27 de fevereiro de 2002
*
*  Alterações:
*
*------------------------------------------------------------*/


#ifndef carma_h_incluido
#define carma_h_incluido


#include "cobjeto.h"
#include "ctiro.h"
#include "funcoes.h"
#include "erro.h"
#include "ccolecao.h"

typedef enum
{
	eArmaCanhao,
	eArmaEscudo
} EArma;


enum EStatusArma
{
	eArmaNormal,
	eArmaExplosao,
	eArmaInativa
};


//------------------------------------------------------------
// Classe para as armas
class CArma : public CObjetoAvancado
{
public:
	CArma();
	static void CarregarArquivoDados(DATAFILE * dat_arquivo);
	static void DescarregarArquivoDados();
	void Iniciar(int tipo, int x, int y);
	void Desenhar(CTela & m_tela, int x_real, int y_real);
	void Atualizar(TRect area, CObjetoAvancado * const alvo);
	void Sonorizar();
	void Finalizar();
	void Atirar(CObjetoAvancado * const alvo);
	int ObterTipo();
	CTiro & ObterTiros();
	void SetarStatus(EStatusArma status);
	EStatusArma ObterStatus();
	
protected:
	int m_tipo; // EArma
	EStatusArma m_status;
	static DATAFILE *m_dat_arquivo;
	CTiro m_tiros;
	int m_flag_x, m_flag_y;
};
#endif