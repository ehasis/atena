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


#include "callegro.h"

#include "cobjeto.h"
#include "ctiro.h"
#include "ccolecaoavancada.h"

typedef enum
{
	eArmaCanhao,
	eArmaEscudo, 
	eArmaInvisivel,
	eArmaNave
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
	static void CarregarArquivoDados(const char *arquivo);
	static void DescarregarArquivoDados();
	void Iniciar(int tipo, int x, int y);
	void Desenhar(CTela &tela, int x_real, int y_real);
	void Atualizar(TRect &area, CObjetoAvancado * const alvo);
	void Sonorizar();
	void Finalizar();
	void Atirar(CObjetoAvancado * const alvo);
	int ObterTipo();
	CColecaoAvancada< CTiro > & ObterTiros();
	void SetarStatus(EStatusArma status);
	EStatusArma ObterStatus();
	bool Colidir(TRect &area, int energia);
	void SetarTipoTiro(ETiro tipo_tiro);
	void DecY(int decremento);

protected:
	int			m_tipo; // EArma
	int			m_flag_x;
	int			m_flag_y;
	int			m_turbina;
	ETiro		m_tipo_tiro;
	EStatusArma m_status;
	CColecaoAvancada< CTiro > m_tiros;
	static GADados m_dat_arquivo;
};

//------------------------------------------------------------
inline void CArma::Atirar(CObjetoAvancado * const alvo)
{
	if(m_status != eArmaExplosao
	&& m_status != eArmaInativa)
	{
		m_tiros.AdicionarFim();
		m_tiros.Obter().Iniciar(m_tipo_tiro,  m_x + (m_largura / 2), m_y, alvo);
	}
}

//------------------------------------------------------------
inline CColecaoAvancada< CTiro > & CArma::ObterTiros()
{
	return m_tiros;
}


//------------------------------------------------------------
inline bool CArma::Colidir(TRect &area, int energia)
{
	if(m_status != eArmaInativa
	&& m_status != eArmaExplosao
	&& ChecarColisao(area))
	{
		DecEnergia(energia);
		return true;
	}
	return false;
}

//------------------------------------------------------------
inline void CArma::DecY(int decremento)
{
	m_y -= decremento;
	m_turbina = 1;
}

//------------------------------------------------------------
inline void CArma::Sonorizar()
{
	m_tiros.Sonorizar();
}


#endif

