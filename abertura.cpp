#include <allegro.h>
#include "abertura.h"
#include "atena.h"

void MostrarAbertura()
{
	DATAFILE *dados = load_datafile("atena.dat");
	PALETTE pal;
	generate_332_palette(pal);
	set_palette (black_palette);
	blit((BITMAP *)dados[ABERTURA].dat, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	fade_in(pal, 3);
	readkey();
	fade_out(5);
	unload_datafile(dados);
}