 /*------------------------------------------------------------*
 *  gabarra.h - Componente que cria uma barra de progresso
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quinta-feira, 03 de julho de 2003
*
*  Alterações:
*
*------------------------------------------------------------*/
#ifndef GABARRA_H_INCLUIDO
#define GABARRA_H_INCLUIDO

#include <allegro.h>

class GABarraProgresso
{
public:
	GABarraProgresso();

	GABarraProgresso& SetarXYLA(int x, int y, int l, int a);
	GABarraProgresso& SetarCor(int valor);
	GABarraProgresso& SetarVertical(bool valor);
	GABarraProgresso& SetarMinimo(float valor);
	GABarraProgresso& SetarMaximo(float valor);

	void IncPosicao(float valor);
	void DecPosicao(float valor);
	void SetarPosicao(float valor);

	float ObterMinimo();
	float ObterMaximo();
	float ObterPosicao();

	void Desenhar(BITMAP *bmp);

private:
	bool m_vertical;
	int m_x, m_y;
	int m_l, m_a;
	int m_cor;
	float m_min;
	float m_max;
	float m_pos;
	float m_percentual;
};

inline void GABarraProgresso::IncPosicao(float valor)
{
	SetarPosicao(m_pos + valor);
}

inline void GABarraProgresso::DecPosicao(float valor)
{
	SetarPosicao(m_pos - valor);
}

inline void GABarraProgresso::SetarPosicao(float valor)
{
	if (valor < m_min)
		m_pos = m_min;
	else if (valor > m_max)
		m_pos = m_max;
	else
	{
		m_pos = valor;
		if (m_min == m_max)
			m_percentual = 0.0f;
		else
			m_percentual = ((m_pos - m_min) * 100.0f) / (m_max - m_min);
	}
}

inline float GABarraProgresso::ObterPosicao()
{
	return m_pos;
}

inline void GABarraProgresso::Desenhar(BITMAP *bmp)
{
	if (m_vertical)
		rectfill(bmp, m_x, m_y + m_a, m_x + m_l, m_y + m_a - ((m_percentual * m_a) / 100), m_cor);
	else
		rectfill(bmp, m_x, m_y, m_x + ((m_percentual * m_l) / 100), m_y + m_a, m_cor);
}

#endif