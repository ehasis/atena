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
	int x, y;
	int a, l;
	int v;
	int Colisao(TRect &rect);
	TRect ret;
	TRect Rect();
};

#endif