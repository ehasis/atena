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
#include "cobjeto.h"

enum EStatusAlien
{
	eAlienNormal,
	eAlienEscudo,
	eAlienExplosao,
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

class CNave: public CObjeto
{
public:
	CNave();
	//Casco
	int  getCasco()            { return casco;     }
	void somCasco(int valor)   { casco  += valor;  }
	void setCasco(int valor)   { casco  =  valor;  }

	//Tempo
	int  getTempo()            { return tempo;     }
	void setTempo(int valor)   { tempo  = valor;   }
	
	//Pontos
	int  getPontos()           { return pontos;    }
	void somPontos(int valor)  { pontos += valor;  }
	void setPontos(int valor)  { pontos =  valor;  }
	
	//Energia
	int  getEnergia()          { return energia;   }
	void somEnergia(int valor) { energia += valor; }
	void setEnergia(int valor) { energia =  valor; }

	//Status
	EStatusNave getStatus() { return status; }
	void setStatus(EStatusNave valor) { status = valor; }

	//Diversos
	int Atirar() { return atirar; }
	void setDataFile(DATAFILE *arquivo);
	void Atualizar(TEntrada &valor);
	void Desenhar(BITMAP *bmp);
	void Desligar();
		
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

#endif