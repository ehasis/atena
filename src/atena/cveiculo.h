 /*------------------------------------------------------------*
 *  cveiculo.h - Classe CVeiculo
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: terça-feira, 09 de julho de 2002
*
*  Alterações:
*
*  Diego Giacomelli em 20/07/2002
*	- Substituido m_tiros por m_armas; 
*------------------------------------------------------------*/

#ifndef cveiculo_h_incluido
#define cveiculo_h_incluido

#include "callegro.h"

#include "cobjeto.h"
#include "ccolecaoavancada.h"
#include "carma.h"

typedef enum
{
	eVeiculoCarro,
	eVeiculoTanque
} EVeiculo;


enum EStatusVeiculo
{
	eVeiculoNormal,
	eVeiculoExplosao,
	eVeiculoInativo
};


//------------------------------------------------------------
// Classe para as veiculos
class CVeiculo : public CObjetoAvancado
{
public:
	CVeiculo();
	static void CarregarArquivoDados(const char *arquivo);
	static void DescarregarArquivoDados();
	void Iniciar(int tipo, int x, int y);
	void Desenhar(CTela & tela, int x_real, int y_real);
	void Atualizar(TRect area, CObjetoAvancado * const alvo);
	void Sonorizar();
	void Finalizar();
	int ObterTipo();
	CColecaoAvancada< CArma > & ObterArmas();
	void SetarStatus(EStatusVeiculo status);
	EStatusVeiculo ObterStatus();
	bool Colidir(TRect area, int energia);
	
protected:
	int m_tipo; // EVeiculo
	EStatusVeiculo m_status;
	static GADados m_dat_arquivo;
	int m_flag_x, m_flag_y;
	int m_dir_x;
	int m_dir_y;
	int m_dir_r;		
	int m_velocidade;
	CColecaoAvancada < CArma > m_armas;
};

#endif

