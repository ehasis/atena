 /*------------------------------------------------------------*
 *  cfundo.h - Classe CFundo
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quinta-feira, 27 de setembro de 2001
*
*  Alterações:
*  Diego Giacomelli em 19/10/2001
*   - Reformulação dos métodos existentes na classe para
*     trabalhar com m_arquivo binário;
*   - Inserção das enum EDirecao e TBmp;
*   - Implementação dos métodos Rolar, ObterLadrilho,
*     SetarLadrilho, SetarTLadrilho, ObterFundo_screen,
*     ObterXFonte, ObterYFonte, ObterXDestino,
*     ObterYDestino e SalvarFundo;
*
*  Diego Giacomelli em 07/01/2002
*   - Alteração do nome do método Colisão para ChecarColisao
*     para adaptar-se aos padrões de nomenclatura;
*
*  Diego Giacomelli em 27/01/2002
*   - Alterada a alocação dos bitmaps dos ladrilhos de vetor para
*	  lista encadeada;
*
*  Diego Giacomelli em 13/02/2002
*   - Alterado o método Desenhar para aceitar CTela e
*     posicionamento relativo;
*
*  Diego Giacomelli em 08/03/2002
*   - Retirado o membro de dado fundo_screen (obsoleto);
*   - Retirados os métodos ObterFundo_screen, ObterXFonte,
*     ObterYFonte, ObterXDestino, ObterYDestino, SetarTLadrilho
*     (obsoletos);
*------------------------------------------------------------*/


#ifndef cfundo_h_incluido
#define cfundo_h_incluido


#include <stdio.h>
#include <string.h>
#include <allegro.h>
#include "cfundo.h"
#include "funcoes.h"
#include "erro.h"
#include "cladrilho.h"
#include "cobjeto.h"

#define MAPA_LARGURA_LADRILHOS   20 											// Largura do mapa em numero de ladrilhos
#define MAPA_ALTURA_LADRILHOS   200												// Altura do mapa em numero de ladrilhos
#define MAPA_TOTAL_LADRILHOS    MAPA_LARGURA_LADRILHOS * MAPA_ALTURA_LADRILHOS  // Quantidade total de ladrilhos do mapa
#define MAPA_LARGURA			MAPA_LARGURA_LADRILHOS * LADRILHO_LARGURA		// Largura do mapa em pixels
#define MAPA_ALTURA				MAPA_ALTURA_LADRILHOS * LADRILHO_ALTURA 		// Altura do mapa em pixels
#define ARQUIVOS_BMP_QUANT		10												// Quantidade maxima de bitmaps associados a um mesmo fundo


typedef enum
{
	eCima,
	eDireita,
	eBaixo,
	eEsquerda
} EDirecao;


// Estrutura para os nodos de bmp relacionados aos ladrilhos
typedef struct TBmp
{
	char arquivo_bmp[32];
	BITMAP *bmp_bmp;
	struct TBmp *p_TBmp;

} TBmp;


//------------------------------------------------------------
// Classe para manipulacao do fundo
class CFundo
{
public:
	int Iniciar(TLadrilho mapa_ladrilhos[MAPA_LARGURA_LADRILHOS][MAPA_ALTURA_LADRILHOS], int x_fonte, int y_fonte, int mapa_largura_ladrilhos, int mapa_altura_ladrilhos, int ladrilho_largura, int ladrilho_altura, int x_destino, int y_destino, int m_largura_destino, int m_altura_destino);
	void Desenhar(CTela & tela, int x_real, int y_real);;
	int Rolar(EDirecao direcao, int pixels);
	void Atualizar();
	CLadrilho ObterLadrilho(int x, int y);
	void SetarLadrilho(int x, int y, TLadrilho ladrilho, BITMAP * bmp_fonte);
	void SalvarFundo(char * fase);
	void Finalizar();
private:
	TBmp *m_bmp_arquivos;
	int m_x_fonte;
	int m_y_fonte;
	int m_mapa_largura_ladrilhos;
	int m_mapa_altura_ladrilhos;
	int m_ladrilho_largura;
	int m_ladrilho_altura;
	int m_x_destino;
	int m_y_destino;
	int m_largura_destino;
	int m_altura_destino;
	CLadrilho m_mapa_ladrilho[MAPA_LARGURA_LADRILHOS][MAPA_ALTURA_LADRILHOS];
};

#endif