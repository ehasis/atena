 /*------------------------------------------------------------*
 *  cnave.h - Definicao das classes de Naves
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quarta-feira, 19 de setembro de 2001
*
*  
*
*------------------------------------------------------------*/

#ifndef cnave_h_incluido
#define cnave_h_incluido

#include "centrada.h"
#include "cobjeto.h"

enum EStatusAlien
{
	eAlienNormal,
	eAlienEscudo,
	eAlienExplosao,
	eAlienInativo
};

enum EStatusNave
{
	eNaveNormal,
	eNaveEscudo,
	eNaveExplosao,
	eNaveRenacer
};

struct TPowerUp
{
	int x, y;
	int a, l;
	int status;
	TRect Rect()
	{
		TRect ret;
		ret.e = x;
		ret.t = y;
		ret.d = x + l;
		ret.b = y + a;

		return ret;
	}
};

struct TBala
{
	int x, y;
	int a, l;
	float vx, vy;
	int ativa;
	TRect Rect()
	{
		TRect ret;
		ret.e = x;
		ret.t = y;
		ret.d = x + l;
		ret.b = y + a;

		return ret;
	}
};

class CNave: public CObjeto
{
public:
	CNave();
	
	//Propriedades
	int energia;
	int tempo;
	int pontos;
	int casco;
	int atirar;
	EStatusNave status;

	//Metodos
	void DecEnergia(int valor);
	void IncEnergia(int valor);
	void SetArquivoDat(DATAFILE *arquivo);
	void Atualizar(TEntrada &valor);
	void Desenhar(BITMAP *bmp);
	void Desligar();
		
private:
	DATAFILE *data;
};

//------------------------------------------------------------
class CAlien: public CObjeto
{
public:
	//Propriedades
	int energia;
	int tempo;
	int atirar;
	int tipo;
	EStatusAlien status;

	//Metodos
	void SetArquivoDat(DATAFILE *arquivo);
	void Desenhar(BITMAP *bmp);
	void Atualizar();
	void Desligar();

private:
	DATAFILE *data;
};

#endif