 /*------------------------------------------------------------*
 *  cobjeto.h - Definicao da Classe Base
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: terça-feira, 22 de Setembro de 2001
*
*  Alteracoes:
*  Diego Giacomelli em 01/01/2002
*   - Alterações na estrutura TRect;
*
*  Diego Giacomelli em 02/01/2002
*   - Implementação dos métodos Colisao(_x1, _y1, _x2, _y2),
*     SetarX, ObterX, IncX, DecX, SetarY, ObterY, IncY, DecY,
*     SetarLargura, ObterLargura, SetarAltura, ObterAltura;
*
*  Diego Giacomelli em 04/01/2002
*   - Declaração dos membros de dados (x, y,largura, altura,
*     vi, vx, vy) como protected;
*
*  Diego Giacomelli em 07/01/2002
*   - Alteração do nome do método Colisão para ChecarColisao
*     para adaptar-se aos padrões de nomenclatura;
*
*
*------------------------------------------------------------*/


#ifndef cobjeto_h_incluido
#define cobjeto_h_incluido


/* Estrutura de um retangulo */
typedef struct
{
	int x1, y1;
	int x2, y2;
} TRect;


//------------------------------------------------------------
/* Classe base para manipulação de objetos */
class CObjeto
{
public:
	int ChecarColisao(TRect _rect);
	int ChecarColisao(int _x1, int _y1, int _x2, int _y2);
	int ChecarColisao(int _x, int _y);
	TRect Rect(void);
	void SetarX(int _x);
	int ObterX(void);
	int ObterX2(void);
	void IncX(int _incremento);
	void DecX(int _decremento);
	void SetarY(int _y);
	int ObterY(void);
	int ObterY2(void);
	void IncY(int _incremento);
	void DecY(int _decremento);
	void SetarLargura(int _largura);
	int ObterLargura(void);
	void SetarAltura(int _altura);
	int ObterAltura(void);

protected:
	int x, y;
	int largura, altura;
	float vi, vx, vy;
};

#endif