 /*------------------------------------------------------------*
 *  cobjeto.cpp - Implementacao da Classe Base
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: terça-feira, 22 de setembro de 2001
*
*
*------------------------------------------------------------*/


#include "cobjeto.h"

//------------------------------------------------------------
// CObjetoBasico
//------------------------------------------------------------

CObjetoBasico::CObjetoBasico()
: m_x(0), m_y(0), m_largura(0), m_altura(0)
{
}

void CObjetoBasico::Iniciar(int x, int y, int largura, int altura)
{
	m_x = x;
	m_y = y;
	m_altura = altura;
	m_largura = largura;
}
