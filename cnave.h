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
	//Casco
	int  GetCasco()            { return casco;     }
	void IncCasco(int valor)   { casco  += valor;  }
	void SetCasco(int valor)   { casco  =  valor;  }

	//Tempo
	int  GetTempo()            { return tempo;     }
	void SetTempo(int valor)   { tempo  = valor;   }
	
	//Pontos
	int  GetPontos()           { return pontos;    }
	void IncPontos(int valor)  { pontos += valor;  }
	void SetPontos(int valor)  { pontos =  valor;  }
	
	//Energia
	int  GetEnergia()          { return energia;   }
	void IncEnergia(int valor) { energia += valor; }
	void SetEnergia(int valor) { energia =  valor; }

	//Status
	EStatusNave GetStatus() { return status; }
	void SetStatus(EStatusNave valor) { status = valor; }

	//Diversos
	int Atirar() { return atirar; }
	void SetArquivoDat(DATAFILE *arquivo);
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

//------------------------------------------------------------
class CAlien: public CObjeto
{
public:
	//Energia
	int  GetEnergia()          { return energia;   }
	void IncEnergia(int valor) { energia += valor; }
	void SetEnergia(int valor) { energia =  valor; }
	
	//Tempo
	int  GetTempo()            { return tempo;     }
	void IncTempo(int valor)   { tempo  += valor;  }
	void SetTempo(int valor)   { tempo   =  valor; }
	
	//Status
	EStatusAlien GetStatus() { return status; }
	void SetStatus(EStatusAlien valor) { status = valor; }

	//Tipo
	int  GetTipo() { return tipo; }
	void SetTipo(int valor) { tipo = valor; }

	//Diversos
	void SetArquivoDat(DATAFILE *arquivo);
	void Desenhar(BITMAP *bmp);
	void Atualizar();
	void Desligar();

private:
	EStatusAlien status;
	DATAFILE *data;
	int energia;
	int tempo;
	int atirar;
	int tipo;
};

#endif