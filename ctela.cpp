 /*------------------------------------------------------------*
 *  ctela.cpp - Implementação da CTela
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quarta-feira, 13 de fevereito de 2002
*
*
*------------------------------------------------------------*/

#include "ctela.h"
#include "funcoes.h"

//------------------------------------------------------------
void CTela::Iniciar()
{
	//Configurações
	utilizar_vsync 				= FALSE;
	utilizar_suavizar 			= FALSE;
	utilizar_escrever_sombra 	= FALSE;

	//Camadas
	bmp_fundo	= create_bitmap(TELA_L, TELA_A);
	bmp_objetos = create_bitmap(TELA_L, TELA_A);
	bmp_efeitos = create_bitmap(TELA_L, TELA_A);
	bmp_aux     = create_bitmap(SCREEN_W, SCREEN_H);
}

//------------------------------------------------------------
void CTela::Desligar()
{
	destroy_bitmap(bmp_fundo);
	destroy_bitmap(bmp_objetos);
	destroy_bitmap(bmp_efeitos);
	destroy_bitmap(bmp_aux);
}

//------------------------------------------------------------
void CTela::Atualizar()
{

	masked_blit(bmp_objetos, bmp_fundo, 0, 0, 0, 0, TELA_L, TELA_A);
	masked_blit(bmp_efeitos, bmp_fundo, 0, 0, 0, 0, TELA_L, TELA_A);

	if (utilizar_vsync) vsync();

	if (TELA_L == SCREEN_W)
	{
		if (utilizar_suavizar) SuavizarBitmap(bmp_fundo);
		blit(bmp_fundo, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	}
	else
	{
		stretch_blit(bmp_fundo, bmp_aux, 0, 0, TELA_L, TELA_A, 0, 0, SCREEN_W, SCREEN_H);
		if (utilizar_suavizar) SuavizarBitmap(bmp_aux);
		blit(bmp_aux, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	}

	clear_to_color(bmp_objetos, COR_ROSA);
	clear_to_color(bmp_efeitos, COR_ROSA);
}

//------------------------------------------------------------
BITMAP *CTela::RetornarCamada(ECamada camada)
{
	switch(camada)
	{
		case eCamadaFundo:
			return bmp_fundo;
		case eCamadaObjetos:
			return bmp_objetos;
		case eCamadaEfeitos:
			return bmp_efeitos;
        default:
			return bmp_efeitos;
	}
}

//------------------------------------------------------------
void CTela::SetarVsync(int valor)
{
	utilizar_vsync = valor;
}

//------------------------------------------------------------
void CTela::SetarSuavizar(int valor)
{
	utilizar_suavizar = valor;
}

//------------------------------------------------------------
void CTela::SetarEscreverSombra(int valor)
{
	utilizar_escrever_sombra = valor;
}

//////////////////////////////////////////////////////////////
//Espelho das funções da Allegro com algumas sobrecarcas
//////////////////////////////////////////////////////////////

//------------------------------------------------------------
void CTela::Blit(BITMAP *bmp, ECamada camada)
{
	blit(bmp, RetornarCamada(camada), 0, 0, 0, 0, bmp->w, bmp->h);
}

//------------------------------------------------------------
void CTela::Blit(BITMAP *bmp, ECamada camada, int fx, int fy, int dx, int dy, int l, int a)
{
	blit(bmp, RetornarCamada(camada), fx, fy, dx, dy, l, a);
}

//------------------------------------------------------------
void CTela::MaskedBlit(BITMAP *bmp, ECamada camada)
{
	masked_blit(bmp, RetornarCamada(camada), 0, 0, 0, 0, bmp->w, bmp->h);
}

//------------------------------------------------------------
void CTela::MaskedBlit(BITMAP *bmp, ECamada camada, int fx, int fy, int dx, int dy, int l, int a)
{
	masked_blit(bmp, RetornarCamada(camada), fx, fy, dx, dy, l, a);
}

//------------------------------------------------------------
void CTela::DrawSprite(ECamada camada, BITMAP *bmp, int x, int y)
{
	draw_sprite(RetornarCamada(camada), bmp, x, y);
}

//------------------------------------------------------------
void CTela::DrawTransSprite(ECamada camada, BITMAP *bmp, int x, int y)
{
	//draw_trans_sprite(RetornarCamada(camada), bmp, x, y);
	draw_sprite(RetornarCamada(camada), bmp, x, y);
}

//------------------------------------------------------------
void CTela::Rect(ECamada camada, int x1, int y1, int x2, int y2, int cor)
{
	rect(RetornarCamada(camada), x1, y1, x2, y2, cor);
}

//------------------------------------------------------------
void CTela::RectFill(ECamada camada, int x1, int y1, int x2, int y2, int cor)
{
	rectfill(RetornarCamada(camada), x1, y1, x2, y2, cor);
}

//------------------------------------------------------------
void CTela::Escrever(const char *str, int x, int y, int cor)
{
	if (utilizar_escrever_sombra)
	{
		textout(RetornarCamada(eCamadaEfeitos), font, str, x + 1, y + 1, COR_PRETO);
	}

	textout(RetornarCamada(eCamadaEfeitos), font, str, x, y, cor);
}

//------------------------------------------------------------
void CTela::Escrever(ECamada camada, const char *str, int x, int y, int cor)
{
	if (utilizar_escrever_sombra)
	{
		textout(RetornarCamada(camada), font, str, x + 1, y + 1, COR_PRETO);
	}

	textout(RetornarCamada(camada), font, str, x, y, cor);
}


//------------------------------------------------------------
void CTela::PutPixel(ECamada _camada, int _x, int _y, int _cor)
{
	putpixel(RetornarCamada(_camada), _x, _y, _cor);
}
