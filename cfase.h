 /*------------------------------------------------------------*
 *  cfase.h - Classe CFase
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: sábado, 27 de outubro de 2001
*
*  Alterações:
*  Diego Giacomelli em 09/01/2002
*   - Implementação dos métodos ObterLargura_destino,
*     ObterAltura_destino;
*
*
*------------------------------------------------------------*/


#ifndef cfase_h_incluido
#define cfase_h_incluido


#include <stdio.h>
#include <allegro.h>
#include <string.h>
#include "cfundo.h"
#include "cladrilho.h"
#include "funcoes.h"
#include "calien.h"
#include "cnave.h"


//------------------------------------------------------------
/* Classe para as fases */
class CFase
{
public:
	void Iniciar(char arquivo_fase[], int _x1_destino, int _y1_destino, int _largura_destino, int _altura_destino);
	void Desenhar(BITMAP * _bmp_destino);
	int Rolar(EDirecao _direcao, int _pixels);
	void SetarCFundo(CFundo _fundo);
	CFundo ObterCFundo(void);
	int ObterX1_fonte(void);
	int ObterY1_fonte(void);
	BITMAP *ObterFase_screen(void);
	void SalvarFase(void);
	void Desligar(void);
	void SetarLadrilho(int _x, int _y, CLadrilho _ladrilho);
	CLadrilho CFase::ObterLadrilho(int _x, int _y);
	void SetarArquivo_fase(char _arquivo_fase[]);
	void SetarArquivoAlien(DATAFILE *_dat_aliens);
	void AdicionarAlien(int _tipo, int _x, int _y);
	void ExcluirAliens(int _x1, int _y1, int _x2, int _y2);
	int Atualizar(int _fundo_pixels);
	int ObterLargura_destino(void);
	int ObterAltura_destino(void);
	int ChecarColisaoAliens(int _x1, int _y1, int _x2, int _y2);
	void TocarSom(void);
	void ChecarColisaoTiroNosAliens(void);
	void ChecarColisaoNaNave(void);
	CNave ObterNave(void);

private:
	char arquivo_fase[50];  /* Nome do arquivo da fase */
	BITMAP *fase_screen;
	CFundo fundo;			/* Fundo atual da fase */
	CAlien aliens;
	CNave nave;
	int x1_fonte;
	int y1_fonte;
	int x1_destino;			/* Coordenada x onde a fase deve ser pintada no _bmp_destino */
	int y1_destino;			/* Coordenada y onde a fase deve ser pintada no _bmp_destino */
	int largura_destino;    /* Largura onde a fase deve ser pintada no _bmp_destino */
	int altura_destino;     /* Altura onde a fase deve ser pintada no _bmp_destino */
};

#endif