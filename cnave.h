 /*------------------------------------------------------------*
 *  cnave.h - Definicao das classes de Naves
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quarta-feira, 19 de setembro de 2001
*
*  Alterações:
*  Diego Giacomelli em 19/09/2001
*  	- Adicionada sombra à nave Alien no método Desenhar;
*
*------------------------------------------------------------*/

#ifndef cnave_h_incluido
#define cnave_h_incluido

#include "cobjeto.h"
#include "ctiro.h"

enum EStatusNave
{
	eNaveNormal,
	eNaveEscudo,
	eNaveExplosao,
	eNaveRenacer
};

struct TEntrada
{
	int x, y;
	int a, b, c;
};

class CNave: public CObjeto
{
public:
	CNave();
	void DecEnergia(int valor);
	void IncEnergia(int valor);
	void SetArquivoDat(DATAFILE *arquivo);
	void Atualizar(int _x1, int _y1, int _x2, int _y2);
	void Desenhar(BITMAP *bmp);
	void Desligar(void);
	void TocarSom(void);
	CTiro *ObterTiros(void);
	int ObterPontos(void);
	void IncPontos(int _incremento);
	int ObterCasco(void);
	int ObterEnergia(void);
	int ObterStatus(void);

private:
	DATAFILE *data;
	CTiro tiros;
	int energia;
	int tempo;
	int pontos;
	int casco;
	int atirar;
	int tipo_tiro;
	EStatusNave status;

};

#endif