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
*------------------------------------------------------------*/


#ifndef cfase_h_incluido
#define cfase_h_incluido

#include "cobjeto.h"
#include "cladrilho.h"
#include "cfundo.h"
#include "cnave.h"
#include "calien.h"
#include "carma.h"
#include "cconstrucao.h"

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
	void SalvarFase();
	void Finalizar();
	void SetarLadrilho(int x, int y, TLadrilho ladrilho, BITMAP * bmp_fonte);
	CLadrilho ObterLadrilho(int x, int y);
	void SetarArquivoFase(char arquivo_fase[]);
	void AdicionarAlien(int tipo, int x, int y);
	void AdicionarConstrucao(int tipo, int x, int y);
	void ExcluirAliens(int x1, int y1, int x2, int y2);
	void ExcluirConstrucoes(int x1, int y1, int x2, int y2);
	bool Atualizar(int fundo_pixels);
	void Sonorizar();
	CAlien ObterAliens();
	CConstrucao ObterConstrucoes();
	int ChecarColisaoAliens(int x1, int y1, int x2, int y2);
	int ChecarColisaoConstrucoes(int x1, int y1, int x2, int y2);
	CNave & ObterNave();


private:
	void ChecarColisaoTiroNosAliens();
	void ChecarColisaoNaNave();

	char m_arquivo_fase[50];  	// Nome do m_arquivo da m_fase
	CFundo m_fundo;			// Fundo atual da m_fase
	CAlien m_aliens;
	CConstrucao m_construcoes;
	CNave m_nave;
	int m_x1_fonte;
	int m_y1_fonte;
	int m_x1_destino;			// Coordenada x onde a m_fase deve ser pintada no bmp_destino
	int m_y1_destino;			// Coordenada y onde a m_fase deve ser pintada no bmp_destino
	int m_largura_destino;   		// Largura onde a m_fase deve ser pintada no bmp_destino
	int m_altura_destino;    		// Altura onde a m_fase deve ser pintada no bmp_destino
};

#endif