 /*------------------------------------------------------------*
 *  clog.h - Log em modo Console
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: sexta-feira, 8 de fevereiro de 2002
*
*
*------------------------------------------------------------*/

#include <allegro.h>

class CLog
{
public:
	static void Iniciar();
	static void LogXX(const char *_texto);
	static void Desenhar(BITMAP *bmp);
	static void Desligar();
	static void SetarVisivel(int _visivel);
	static int Visivel();


protected:
	static BITMAP *bmp_log;
	static int visivel;

};
