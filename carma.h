 /*------------------------------------------------------------*
 *  carma.h - Classe CArma
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: quarta-feira, 27 de fevereiro de 2002
*
*  Alterações:
*
*  Diego Giacomelli em 11/07/2002
*	- Implementado o método Colidir(); 
*
*  Diego Giacomelli em 20/07/2002
*	- Inserido membro de dado m_tipo_tiro;
*
*  Henrique Andreassy em 07/08/2002
*	- Adicionado método SetarTipoTiro()
*------------------------------------------------------------*/


#ifndef carma_h_incluido
#define carma_h_incluido


#include "cobjeto.h"
#include "ctiro.h"
#include "ccolecaoavancada.h"

typedef enum
{
	eArmaCanhao,
	eArmaEscudo, 
	eArmaInvisivel,
	eArmaBracoEsquerdo,
	eArmaBracoDireito
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
	void Desenhar(CTela & tela, int x_real, int y_real);
	void Atualizar(TRect area, CObjetoAvancado * const alvo);
	void Sonorizar();
	void Finalizar();
	void Atirar(CObjetoAvancado * const alvo);
	int ObterTipo();
	CColecaoAvancada< CTiro > & ObterTiros();
	void SetarStatus(EStatusArma status);
	EStatusArma ObterStatus();
	bool Colidir(TRect area, int energia);
	void SetarTipoTiro(ETiro tipo_tiro);
	void DecY(int decremento);

protected:
	int m_tipo; // EArma
	ETiro m_tipo_tiro;
	EStatusArma m_status;
	static DATAFILE *m_dat_arquivo;
	CColecaoAvancada< CTiro > m_tiros;
	int m_flag_x, m_flag_y;
	int m_turbina;
};


#endif