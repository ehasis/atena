 /*------------------------------------------------------------*
 *  cfase.h - Classe CFase
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: sábado, 27 de outubro de 2001
*
*  Alterações:
*  Diego Giacomelli em 09/01/2002
*   - Implementação dos métodos ObterLarguraDestino,
*     ObterAlturaDestino;
*
*  Diego Giacomelli em 13/02/2002
*   - Alterado o método Desenhar para aceitar CTela e
*     posicionamento relativo;
*
*  Diego Giacomelli em 04/03/2002
*   - Retirado o método SetarArquivoAlien (obsoleto);
*
*  Diego Giacomelli em 07/03/2002
*   - Retirado os métodos SetarCFundo, ObterCFundo,
*     ObterLarguraDestino, ObterAlturaDestino e  ObterNave (obsoletos);
*   - Métodos ChecarColisaoTiroNosAliens e ChecarColisaoNaNave
*     retirados do escopo public e inseridos no private;
*
*  Diego Giacomelli em 01/05/2002
*	- Inserido o método ObterNave();
*
*  Diego Giacomelli em 10/07/2002
*	- Inserido o membro de dados m_veiculos;
*	- Inserido o método SalvarVeiculos();
*   - Renomeado o método ChecarColisaoNosAliens para ChecarColisaoTirosDaNave;
*
*  Diego Giacomelli em 15/07/2002
*	- Inserido controle de CNave por CColecaoAvancada para permitir mais de uma nave (jogador)
*	  por fase;
*
*  Diego Giacomelli em 18/07/2002
*	- Inserido controle de m_alien por CColecaoAvancada;
*
*  Diego Giacomelli em 20/07/2002
*	- Inserido controle de m_construcoes por CColecaoAvancada;
*	- Substituídos os métodos SalvarAliens, SalvarVeiculos, SalvarConstrucoes pelo template
*	  de função SalvarObjetos;
*
*  Henrique Andreassy em 04/08/2002
*	- Inserido o objeto CChefe
*
*  Henrique Andreasy em 23/01/2003
*	- Modificado o método Desenhar para passar o x_real
*     de acordo com a nova especificação das camadas
*
*------------------------------------------------------------*/


#ifndef cfase_h_incluido
#define cfase_h_incluido

#include "callegro.h"

#include "cobjeto.h"
#include "cladrilho.h"
#include "cfundo.h"
#include "cnave.h"
#include "calien.h"
#include "cconstrucao.h"
#include "cveiculo.h"
#include "cbonus.h"
#include "cfilme.h"
#include "cchefe.h"

//------------------------------------------------------------
// Classe para as fases
class CFase
{
public:
	void Iniciar(char arquivo_fase[], int x1_destino, int y1_destino, int largura_destino, int altura_destino);
	void Desenhar(CTela & tela);
	int Rolar(EDirecao direcao, int pixels);
	int ObterX1Fonte();
	int ObterY1Fonte();
	void Finalizar();
	void SetarLadrilho(int x, int y, TLadrilho ladrilho, BITMAP * bmp_fonte);
	CLadrilho ObterLadrilho(int x, int y);
	void SetarArquivoFase(char arquivo_fase[]);
	bool Atualizar(int fundo_pixels);
	void Sonorizar();
	CColecaoAvancada< CAlien > & ObterAliens();
	CColecaoAvancada< CConstrucao > & ObterConstrucoes();
	int ChecarColisaoAliens(int x1, int y1, int x2, int y2);
	int ChecarColisaoConstrucoes(int x1, int y1, int x2, int y2);
	CNave & ObterNave();
	CColecaoAvancada <CVeiculo> & ObterVeiculos();
	void SalvarAliens(char * fase);
	void SalvarVeiculos(char * fase);
	template< class cls >
	void SalvarObjetos(CColecaoAvancada< cls > cls_obj, char * fase);

private:
	void ChecarColisaoTirosDaNave();
	void ChecarColisaoNoChefe();
	void ChecarColisaoNaNave();

	char m_arquivo_fase[50];  	// Nome do m_arquivo da m_fase
	CFundo m_fundo;			// Fundo atual da m_fase
	CColecaoAvancada< CAlien > m_aliens;
	CColecaoAvancada< CConstrucao > m_construcoes;
	CColecaoAvancada< CVeiculo > m_veiculos;
	CColecaoAvancada< CNave > m_naves;
	CBonus< CNave > m_bonus;
	CChefe		m_chefe;
	int m_x1_fonte;
	int m_y1_fonte;
	int m_x1_destino;			// Coordenada x onde a m_fase deve ser pintada no bmp_destino
	int m_y1_destino;			// Coordenada y onde a m_fase deve ser pintada no bmp_destino
	int m_largura_destino;   		// Largura onde a m_fase deve ser pintada no bmp_destino
	int m_altura_destino;    		// Altura onde a m_fase deve ser pintada no bmp_destino
};

#endif

