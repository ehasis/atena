#include "gabarra.h"

GABarraProgresso::GABarraProgresso()
{
	m_vertical = false;
	m_x  = 0;
	m_y  = 0;
	m_l  = 0;
	m_a  = 0;
	m_cor = 0;
	m_min =   0.0f;
	m_max = 100.0f;
	m_pos =   0.0f;
}

GABarraProgresso& GABarraProgresso::SetarXYLA(int x, int y, int l, int a)
{
	m_x = x;
	m_y = y;
	m_l = l;
	m_a = a;
	return *this;
}

GABarraProgresso& GABarraProgresso::SetarCor(int valor)
{
	m_cor = valor;
	return *this;
}

GABarraProgresso& GABarraProgresso::SetarVertical(bool valor)
{
	m_vertical = valor;
	return *this;
}

GABarraProgresso& GABarraProgresso::SetarMinimo(float valor)
{
	m_min = valor;
	return *this;
}

GABarraProgresso& GABarraProgresso::SetarMaximo(float valor)
{
	m_max = valor;
	return *this;
}

float GABarraProgresso::ObterMinimo()
{
	return m_min;
}

float GABarraProgresso::ObterMaximo()
{
	return m_max;
}