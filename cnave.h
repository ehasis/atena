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
*  Diego em 24/01/2002
*  	- Criado o método Iniciar;
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
	void Iniciar(void);
	void DecEnergia(int valor);
	void IncEnergia(int valor);
	void Atualizar(TRect _area, CObjeto * const _alvo);
	void Desenhar(CTela &_tela, int _x_real, int _y_real);;
	void Desligar(void);
	void Sonorizar(void);
	CTiro *ObterTiros(void);
	int ObterPontos(void);
	void IncPontos(int _incremento);
	int ObterCasco(void);
	int ObterEnergia(void);
	int ObterStatus(void);

private:
	DATAFILE *dat_arquivo;
	CTiro tiros;
	int energia;
	int quadro;
	int pontos;
	int casco;
	int atirar;
	int tipo_tiro;
	EStatusNave status;
	int turbina;
	float vi, vx, vy;

};

#endif