 /*------------------------------------------------------------*
 *  abertura.cpp - Abertura do jogo
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: Terça-feira, 22 de janeiro de 2002
*
*
*
*------------------------------------------------------------*/

#include <string.h>
#include <stdio.h>
#include <allegro.h>
#include "abertura.h"
#include "atena.h"
#include "funcoes.h"

class CEscrita
{
public:
	void IncY() { y += 11; }
	void SetarX(int valor) { x = valor; }
	void SetarY(int valor) { y = valor; }
	void SetarCor(int valor) { cor = valor; }
	void SetarModo(BITMAP *pbmp, FONT *pfonte, int px, int py, int pcor);
	void Escrever(const char *texto);
	void EscreverLn(const char *texto);
protected:
	int x, y;
	int cor;
	int alinhamento;
	FONT *fonte;
	BITMAP *bmp;
};

void CEscrita::SetarModo(BITMAP *pbmp, FONT *pfonte, int px, int py, int pcor)
{
	bmp = pbmp;
	fonte = pfonte;
	x = px;
	y = py;
	cor = pcor;
}

void CEscrita::Escrever(const char *texto)
{
	size_t c;
	clear_keybuf();
	for (c = 0; c <= strlen(texto); c++)
	{
		textprintf(screen, fonte, c*7+1+x, y+1, makecol(0,0,0), "%c", texto[c]);
		textprintf(screen, fonte, c*7+x, y, cor, "%c", texto[c]);

		if (!keypressed())
			rest(25);
	}
}

void CEscrita::EscreverLn(const char *texto)
{
	Escrever(texto);
	IncY();
}

//------------------------------------------------------------
void MostrarAbertura()
{
	DATAFILE *dados = load_datafile("atena.dat");
	BITMAP *buffer;
	CEscrita cap1;

	text_mode(-1);

	buffer = create_bitmap(SCREEN_W, SCREEN_H);

	play_sample((SAMPLE *)dados[WAV_LOGO_GA].dat, 128, 128, 1000, 0);
	draw_sprite(screen, (BITMAP *)dados[LOGO_GA].dat, 106, 187);
	rest(4000);

	blit((BITMAP *)dados[ABERTURA].dat, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

	rest(1000);
	cap1.SetarModo(buffer, (FONT *)dados[LUCIDA].dat, 20, 100, makecol(255, 255, 0));
	cap1.EscreverLn("No ano de 2073, uma grande disputa de poder comeca a pertubar a balanca");
	cap1.EscreverLn("de poderes da galaxia Afrone. No planeta chamado Cibele, e realizado uma das");
	cap1.EscreverLn("mais importantes reunioes ja realizadas. Erebo, lider do imperio Anteros");
	cap1.EscreverLn("deseja explorar o mineral Vita Tiberium, encontrado em todos os planetas da");
	cap1.EscreverLn("Galaxia, porem o conselho do planeta, nao se mostrava muito a favor.");
	cap1.IncY();
	cap1.EscreverLn("Vita Tiberium pode ser usado como fonte de energia para fazer armas de poder");
	cap1.EscreverLn("inigualavel, porem esta energia e a força vital de todos os planetas. Sem");
	cap1.EscreverLn("este mineral, os planetas simplesmente morreriam.");
	cap1.IncY();
	cap1.EscreverLn("Apos dias de discussao, a ideia de Erebo foi recusada, em vista, a");
	cap1.EscreverLn("destruicao eminente, e lhe foi avisado que qualquer tentativa contraria");
	cap1.EscreverLn("seria punida. Erebo se calou, e no mais profundo segredo, continuou com suas");
	cap1.EscreverLn("ideias para a exploracao do Vita Tiberium, organizando a maior frota");
	cap1.EscreverLn("estrelar jamais vista.");
	readkey();

	unload_datafile(dados);
	destroy_bitmap(buffer);
}

