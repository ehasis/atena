 /*------------------------------------------------------------*
 *  gabitmap.h - Classe GABitmap
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: sexta-feira, 18 de julho de 2003
*
*  Alterações:
*
*------------------------------------------------------------*/
#ifndef GABITMAP_H_INCLUIDO
#define GABITMAP_H_INCLUIDO

#include <allegro.h>

class GABitmap
{
public:
	GABitmap();
	GABitmap(const char *arquivo);
	GABitmap(int largura, int algura);
	virtual ~GABitmap();

	virtual void Iniciar(const char *arquivo);
	virtual void Iniciar(int largura, int altura);
	void Finalizar();

protected:
	BITMAP *m_bitmap;
};

GABitmap::GABitmap(): m_bitmap(NULL)
{
}

GABitmap::GABitmap(const char *arquivo): m_bitmap(NULL)
{
	Iniciar(arquivo);
}

GABitmap::GABitmap(int largura, int altura): m_bitmap(NULL)
{
	Iniciar(largura, altura);
}

void GABitmap::Iniciar(const char *arquivo)
{
	m_bitmap = load_bitmap(arquivo, NULL);
}

void GABitmap::Iniciar(int largura, int altura)
{
	m_bitmap = create_bitmap(largura, altura);
}

void GABitmap::Finalizar()
{
}

#endif