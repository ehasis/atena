 /*------------------------------------------------------------*
 *  cnave.cpp - Implementacao da Classe Nave
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: terça-feira, 18 de setembro de 2001
*
*  
*
*------------------------------------------------------------*/

#include <allegro.h>

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
	void setX(int valor) { x = valor; }
	void setY(int valor) { y = valor; }
	void setA(int valor) { a = valor; }
	void setL(int valor) { l = valor; }
	int Status() { return status; }
	int Colisao(TRect &rect);
	TRect Rect();
private:
	int x, y;
	int a, l;
	int status;
	TRect ret;
};

//------------------------------------------------------------
int CObjeto::Colisao(TRect &rect)
{
	if ((x + l < rect.e)
	||  (y + a < rect.t)
	||  (x     > rect.d)
	||  (y     > rect.b))
	{		
		return 0;
	}
	else
	{
		return 1;
	}
}

//------------------------------------------------------------
TRect CObjeto::Rect()
{
	ret.e = x;
	ret.t = y;
	ret.d = x + l;
	ret.b = y + a;

	return ret;
}

/*************************************************************/
class CNave: public CObjeto
{
public:
	CNave(char *arquivo);
	virtual ~CNave();
	void Desenhar(BITMAP *bmp);

private:
	DATAFILE *data;
	int energia;
	int tempo;
	int mortes;
	int escapadas;
	int vidas;	
};

//------------------------------------------------------------
CNave::CNave(char *arquivo)
{
	data = load_datafile(arquivo);
}

//------------------------------------------------------------
CNave::~CNave()
{
	unload_datafile(data);
}

//------------------------------------------------------------
void CNave::Desenhar(BITMAP *bmp)
{
	switch(Status())
	{
	case 1:
		draw_sprite(bmp, (BITMAP *)data[1].dat, getX(), getY());
		break;
	case 2:
		draw_sprite(bmp, (BITMAP *)data[2].dat, getX(), getY());
		break;
	}
}
