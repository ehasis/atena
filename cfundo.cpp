 /*------------------------------------------------------------*
 *  cfundo.cpp - Implementacao da Classe de Fundo
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quarta-feira, 10 de outubro de 2001
*
*  
*
*------------------------------------------------------------*/

#include <stdio.h>
#include <allegro.h>
#include "cfundo.h"
//------------------------------------------------------------
void CFundo::Iniciar()
{
	FILE *f;
	int x, y;
	int n = 0;

	n_ladrilhos = 0;

	visivel_x1 = 0;
    visivel_x2 = SCREEN_W;
	visivel_y1 = cont1 = MAPA_ALTURA - SCREEN_H;
    visivel_y2 = cont2 = MAPA_ALTURA;

	ry1 = -1;
	ry2 = -2;
	ry3 = -3;

	// cria bitmap com o tamanho da tela mais o tamanho de um ladrilho para cada lado
    tela = create_bitmap(SCREEN_W + (LADRILHO_LARGURA * 2), SCREEN_H + (LADRILHO_ALTURA * 2) );
	
	// abertura do bitmap com os ladrilhos
	data = load_bmp("fases\\fase1.bmp", NULL);
	
	// abertura do arquivo de mapa
	f = fopen("fases\\fase1.map", "r");
	fscanf(f, "%4d", &n_ladrilhos);
	for (y = 0; y < MAPA_ALTURA_LADRILHOS; y++)
	{
		for (x = 0; x < MAPA_LARGURA_LADRILHOS; x++)
		{
			fscanf(f, "%3d", &n);
			mapa_ladrilho[x][y] = n - 1;
		}
	}
	fclose(f);
}

//------------------------------------------------------------
void CFundo::Desenhar(BITMAP *bmp)
{
    int x, y;
    int offset_visivel_x1;
    int offset_visivel_y1;
    int ladrilho_visivel_x1;
    int ladrilho_visivel_y1;
    int ladrilho_visivel_x2;
    int ladrilho_visivel_y2;

    ladrilho_visivel_x1 = visivel_x1 / LADRILHO_LARGURA;
    ladrilho_visivel_y1 = visivel_y1 / LADRILHO_ALTURA;
	offset_visivel_x1   = visivel_x1 % LADRILHO_LARGURA;
    offset_visivel_y1   = visivel_y1 % LADRILHO_ALTURA;

    ladrilho_visivel_x2 = visivel_x2 / LADRILHO_LARGURA;
    if (visivel_x2 % LADRILHO_LARGURA)
        ladrilho_visivel_x2++;

    ladrilho_visivel_y2 = visivel_y2 / LADRILHO_ALTURA;
    if (visivel_y2 % LADRILHO_ALTURA)
        ladrilho_visivel_y2++;

	for (y = ladrilho_visivel_y1; y < ladrilho_visivel_y2; y++)
	{
        for (x = ladrilho_visivel_x1; x < ladrilho_visivel_x2; x++)
		{
			/*-------------------------------------------
				Explicando este emaranhado de código:
				blit(fonte do conjunto de ladrilhos,
					 destino,
					 posição x da fonte (coluna),
					 posição y da fonte (linha),
					 destino em x,
					 destino em y,
					 altura do ladrilho,
					 largura do ladrilho
					);
			-------------------------------------------*/

			blit(data, tela,
				(mapa_ladrilho[x][y] % n_ladrilhos) * LADRILHO_LARGURA,
				(mapa_ladrilho[x][y] / n_ladrilhos) * LADRILHO_ALTURA,
				(x - ladrilho_visivel_x1) * LADRILHO_LARGURA,
                (y - ladrilho_visivel_y1) * LADRILHO_ALTURA,
                LADRILHO_LARGURA, LADRILHO_ALTURA);
		}
	}
	
	blit(tela, bmp, offset_visivel_x1, offset_visivel_y1, 0, 0, SCREEN_W, SCREEN_H);
	//masked_blit((BITMAP *)data[ESTRELAS2].dat, bmp, 0, 0, 0, ry2 - SCREEN_W, SCREEN_W, SCREEN_H);
	//masked_blit((BITMAP *)data[ESTRELAS2].dat, bmp, 0, 0, 0, ry2,       SCREEN_W, SCREEN_H);

}

//------------------------------------------------------------
void CFundo::Atualizar()
{
	ry1 += 1;
	//ry2 += 2;
	//ry3 += 3;
	
	if (ry1 >= 480) ry1 = 0;
	//if (ry2 >= 480) ry2 = 0;
	//if (ry3 >= 480) ry3 = 0;

	if (visivel_y1 > 0)
    {
		cont1 -= 1;//0.5;
		cont2 -= 1;//0.5;
		visivel_y1 = cont1;
        visivel_y2 = cont2;
    }
}

//------------------------------------------------------------
void CFundo::Desligar()
{
	destroy_bitmap(tela);
	destroy_bitmap(data);
}