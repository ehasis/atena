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

/* Estrutura de um retangulo */
struct TRect
{
	int e, t;
	int d, b;
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
	
	
	int getStatus() { return status; }
	void setStatus(int valor) { status = valor; }

	int Colisao(TRect &rect);
	TRect Rect();

protected:
	int x, y;
	int a, l;
	int v;
	int status;
	TRect ret;
};

class CNave: public CObjeto
{
public:
	CNave();
	void Desenhar(BITMAP *bmp);
	void Atualizar(TEntrada &valor);
	int Atirar() { return atirar; }

	int getVidas()   { return vidas;   }
	int getPontos()  { return pontos;  }
	int getTempo()   { return tempo;   }
	int getEnergia() { return energia; }

	void incPontos(int valor)  { pontos += valor; }
	void setPontos(int valor)  { pontos  = valor; }
	void setTempo(int valor)   { tempo   = valor; }
	
	void incEnergia(int valor) { energia += valor;}
	void decEnergia(int valor) { energia -= valor;}
	void setEnergia(int valor) { energia = valor; }

	void setDataFile(DATAFILE *arquivo);
	void Desligar();

private:
	DATAFILE *data;
	int energia;
	int tempo;
	int pontos;
	int vidas;
	int atirar;
};

#endif