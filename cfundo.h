 /*------------------------------------------------------------*
 *  cfundo.h - Classe CFundo
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quinta-feira, 27 de setembro de 2001
*
*  Alterações:
*  Diego Giacomelli em 19/10/2001
*   - Reformulação dos métodos existentes na classe para
*     trabalhar com arquivo binário;
*   - Inserção das enum EDirecao e TBmp;
*   - Implementação dos métodos Rolar, ObterLadrilho,
*     SetarLadrilho, SetarTLadrilho, ObterFundo_screen,
*     ObterX_fonte, ObterY_fonte, ObterX_destino,
*     ObterY_destino e SalvarFundo;
*
*  Diego Giacomelli em 07/01/2002
*   - Alteração do nome do método Colisão para ChecarColisao
*     para adaptar-se aos padrões de nomenclatura;
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


/* Estrutura para os nodos de bmp relacionados aos ladrilhos */
typedef struct
{
	char arquivo_bmp[100];
	BITMAP *bmp_bmp;
} TBmp;


//------------------------------------------------------------
/* Classe para manipulacao do fundo */
class CFundo
{
public:
	int Iniciar(TLadrilho _mapa_ladrilhos[MAPA_LARGURA_LADRILHOS][MAPA_ALTURA_LADRILHOS], int _x_fonte, int _y_fonte, int _mapa_largura_ladrilhos, int _mapa_altura_ladrilhos, int _ladrilho_largura, int _ladrilho_altura, int _x_destino, int _y_destino, int _largura_destino, int _altura_destino);
	void Desenhar(BITMAP * _bmp_destino, int _x_fonte, int _y_fonte);
	int Rolar(EDirecao _direcao, int _pixels);
	void Atualizar(void);
	CLadrilho ObterLadrilho(int _x, int _y);
	void SetarLadrilho(int _x, int _y, CLadrilho _ladrilho);
	void SetarTLadrilho(int _x, int _y, TLadrilho _ladrilho);
	BITMAP *ObterFundo_screen(void);
	int ObterX_fonte(void);
	int ObterY_fonte(void);
	int ObterX_destino(void);
	int ObterY_destino(void);
	void SalvarFundo(char *_fase);
	void Desligar(void);

private:
	TBmp bmp_arquivos[ARQUIVOS_BMP_QUANT];
	BITMAP *fundo_screen;
	int x_fonte;
	int y_fonte;
	int mapa_largura_ladrilhos;
	int mapa_altura_ladrilhos;
	int ladrilho_largura;
	int ladrilho_altura;
	int x_destino;
	int y_destino;
	int largura_destino;
	int altura_destino;
	CLadrilho mapa_ladrilho[MAPA_LARGURA_LADRILHOS][MAPA_ALTURA_LADRILHOS];
};

#endif