 /*------------------------------------------------------------*
 *  clog.cpp - Log em modo Console
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: sexta-feira, 8 de fevereiro de 2002
*
*
*------------------------------------------------------------*/

#include <allegro.h>
#include "clog.h"

BITMAP *CLog::m_bmp_log = NULL;
int CLog::m_visivel = 0;

void CLog::Iniciar()
{
	m_bmp_log = create_bitmap(640, 100);
}

void CLog::Desligar()
{
	destroy_bitmap(m_bmp_log);
}

void CLog::LogXX(const char * texto)
{
	blit(m_bmp_log, m_bmp_log, 0, 0, 0, -10, m_bmp_log->w, m_bmp_log->h);
	rectfill(m_bmp_log, 0, m_bmp_log->h - 10, m_bmp_log->w, m_bmp_log->h, 0);
	textout(m_bmp_log, font, texto, 10, m_bmp_log->h - 10, makecol(255,255,255));
	if (m_visivel)
	{
		Desenhar(screen);
	}
}

void CLog::Desenhar(BITMAP *bmp)
{
	draw_sprite(bmp, m_bmp_log, 0, 0);
}

void CLog::SetarVisivel(int visivel)
{
	m_visivel = visivel;
}

int CLog::Visivel()
{
	return m_visivel;
}