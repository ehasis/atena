 /*------------------------------------------------------------*
 *  cobjeto.h - Definicao da Classe Base
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: terça-feira, 22 de setembro de 2001
*
*  
*
*------------------------------------------------------------*/

/* Estrutura de um retangulo */
struct TRect
{
	int e, t;
	int d, b;
};

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