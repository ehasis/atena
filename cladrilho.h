 /*------------------------------------------------------------*
 *  cladrilho.h - Classe CLadrilho
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: sexta-feira, 19 de outubro de 2001
*
*  Alterações:
*  Diego Giacomelli em 02/01/2002
*   - Classe CLadrilho declarada com herança de CObjeto;
*   - Alterações nos membros de dados da estrutura TLadrilho
*     e na classe CLadrilho;
*   - Implementação dos métodos VirarHorizontal, VirarVertical,
*	  Rotacionar, ObterH_flip, ObterV_flip e ObterRotacao;
*
*  Henrique em 23/01/2002
*   - bmp_aux_1 e 2 agora pertecem a toda a classe
*
*------------------------------------------------------------*/

#ifndef cladrilho_h_incluido
#define cladrilho_h_incluido


#include <stdio.h>
#include <allegro.h>
#include "funcoes.h"
#include "cobjeto.h"

#define LADRILHO_LARGURA		 32	// Largura do ladrilho em pixel
#define LADRILHO_ALTURA			 32 // Altura do ladrilho em pixel


// Estrutura dos ladrilhos para armazenamento no arquivo binário
typedef struct {
	int bmp_x;  		// Coordenadas do ladrilho no bitmap
	int bmp_y;
	int x;			// Coordenadas do ladrilho no mapa
	int y;
	int h_flip;		// Flip horizontal
	int v_flip;		// Flip vertical
	int rotacao;		// rotacao do ladrilho 0-90-180-360
	char arquivo_bmp[32];	// Path do bmp associado ao ladrilho
} TLadrilho;


//------------------------------------------------------------
// Classe para manipulacao do ladrilho
class CLadrilho : public CObjeto
{
public:
	CLadrilho();
	void Iniciar(TLadrilho _ladrilho, int _largura, int _altura, BITMAP *_bmp_fonte);
	void Desligar();
	void Desenhar(CTela &_tela, int _x_real, int _y_real);;

	void SetarBmp_x(int _bmp_x);
	int ObterBmp_x(void);

	void SetarBmp_y(int _bmp_y);
	int ObterBmp_y(void);

	void SetarTLadrilho(TLadrilho _ladrilho);
	TLadrilho ObterTLadrilho(void);

	void SetarArquivo_bmp(char *_arquivo_bmp);
	char *ObterArquivo_bmp(void);

	void VirarHorizontal(void);
	void VirarVertical(void);
	void Rotacionar(int _rotacoes);
	int ObterH_flip(void);
	int ObterV_flip(void);
	int ObterRotacao(void);

	BITMAP *ObterBmp_fonte(void);

private:
	int bmp_x;				// Coordenadas do ladrilho no bitmap
	int bmp_y;    		    // Coordenadas do ladrilho no mapa
	int h_flip;				// Flip horizontal
	int v_flip;				// Flip vertical
	int rotacao;			// rotacao do ladrilho 0-90-180-360
	char arquivo_bmp[100];	// Path do bmp associado ao arquivo
	BITMAP *bmp_fonte;
	BITMAP *bmp_ladrilho, *bmp_aux;
};

#endif