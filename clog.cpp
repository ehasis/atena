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

BITMAP *CLog::bmp_log = NULL;
int CLog::visivel = 0;

void CLog::Iniciar()
{
	bmp_log = create_bitmap(640, 100);
}

void CLog::Desligar()
{
	destroy_bitmap(bmp_log);
}

void CLog::LogXX(const char *_texto)
{
	blit(bmp_log, bmp_log, 0, 0, 0, -10, bmp_log->w, bmp_log->h);
	rectfill(bmp_log, 0, bmp_log->h - 10, bmp_log->w, bmp_log->h, 0);
	textout(bmp_log, font, _texto, 10, bmp_log->h - 10, makecol(255,255,255));
	if (visivel)
	{
		Desenhar(screen);
	}
}

void CLog::Desenhar(BITMAP *bmp)
{
	draw_sprite(bmp, bmp_log, 0, 0);
}

void CLog::SetarVisivel(int _visivel)
{
	visivel = _visivel;
}

int CLog::Visivel()
{
	return visivel;
}