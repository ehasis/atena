 /*------------------------------------------------------------*
 *  cobjeto.h - Definicao da Classe Base
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: terça-feira, 22 de Setembro de 2001
*
*  
*
*------------------------------------------------------------*/

#ifndef cobjeto_h_incluido
#define cobjeto_h_incluido

/* Estrutura de um retangulo */
struct TRect
{
	int e, t;
	int d, b;
};

class CObjeto  
{
public:
	int GetX() { return x; }
	int GetY() { return y; }
	int GetA() { return a; }
	int GetL() { return l; }
	int GetV() { return v; }
	
	void SetX(int valor) { x  = valor; }
	void SetY(int valor) { y  = valor; }
	void SetA(int valor) { a  = valor; }
	void SetL(int valor) { l  = valor; }
	void SetV(int valor) { v  = valor; }
	
	void IncX(int valor) { x += valor; }
	void IncY(int valor) { y += valor; }
	void IncA(int valor) { a += valor; }
	void IncL(int valor) { l += valor; }
	void IncV(int valor) { v += valor; }
	
	int Colisao(TRect &rect);
	TRect Rect();

protected:
	int x, y;
	int a, l;
	int v;
	TRect ret;
};

#endif