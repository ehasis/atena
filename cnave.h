 /*------------------------------------------------------------*
 *  cnave.h - 
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


enum EStatusNave
{
	eNaveNormal,
	eNaveEscudo,
	eNaveExplosao,
	eNaveRenacer
};


/* Estrutura de um retangulo */
struct TRect
{
	int e, t;
	int d, b;
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
	int active;
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

struct TAlien
{
	int x, y;
	int a, l;
	int status;
	int type;
	int hit_points;
	int time;
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


/* Classe base dos demais objetos */
class CObjeto  
{
public:
	int getX() { return x; }
	int getY() { return y; }
	int getA() { return a; }
	int getL() { return l; }
	int getV() { return v; }
	void setX(int valor) { x = valor; }
	void setY(int valor) { y = valor; }
	void setA(int valor) { a = valor; }
	void setL(int valor) { l = valor; }
	
	void incV(int valor) { v += valor;}
	void setV(int valor) { v = valor; }
	
	int Colisao(TRect &rect);
	TRect Rect();

protected:
	int x, y;
	int a, l;
	int v;
	TRect ret;
};

class CNave: public CObjeto
{
public:
	CNave();
	void Desenhar(BITMAP *bmp);
	void Atualizar(TEntrada &valor);
	int Atirar() { return atirar; }

	int getPontos()  { return pontos;  }
	int getTempo()   { return tempo;   }
	int getEnergia() { return energia; }
	int getCasco()   { return casco;   }

	void setTempo(int valor)   { tempo   = valor; }
	void decCasco(int valor)   { casco  -= valor; }
	void setCasco(int valor)   { casco   = valor; }
	void incPontos(int valor)  { pontos += valor; }
	void setPontos(int valor)  { pontos  = valor; }
	void incEnergia(int valor) { energia += valor;}
	void decEnergia(int valor) { energia -= valor;}
	void setEnergia(int valor) { energia = valor; }

	void setDataFile(DATAFILE *arquivo);
	void Desligar();
	
	EStatusNave getStatus() { return status; }
	void setStatus(EStatusNave valor) { status = valor; }

private:
	DATAFILE *data;
	EStatusNave status;
	int energia;
	int tempo;
	int pontos;
	int casco;
	int atirar;
	int vx, vy;
};


/*
class CAlien: public CObjeto
{
public:
	//Energia
	int getEnergia() { return energia; }
	void incEnergia(int valor) { energia += valor;}
	void decEnergia(int valor) { energia -= valor;}
	void setEnergia(int valor) { energia = valor; }
	
	void setTempo(int valor)   { tempo   = valor; }
	void setDataFile(DATAFILE *arquivo);
	void Desligar();

private:
	int energia;
	int tempo;
	int atirar;
};

*/
#endif