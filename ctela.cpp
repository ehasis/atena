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
#include "erro.h"

//------------------------------------------------------------
void CTela::Iniciar(int modo, int largura, int altura, int bit_cores)
{
	//Configurações
	m_utilizar_vsync 			 = false;
	m_utilizar_suavizar 		 = false;
	m_utilizar_escrever_sombra = false;

	m_bmp_fundo	= NULL;
	m_bmp_objetos = NULL;
	m_bmp_efeitos	= NULL;

	SetarModoGrafico(modo, largura, altura, bit_cores);
}

//------------------------------------------------------------
void CTela::SetarModoGrafico(int modo, int largura, int altura, int bit_cores)
{

	//Destroi todos os objetos
	Desligar();

	set_color_depth(bit_cores);

	if (set_gfx_mode(modo, largura, altura, 0, 0) < 0)
	{
		Erro("Nao foi possivel definir o modo grafico", allegro_error);
	}

	//
	clear_to_color(screen, 0);

	//Recria os bitmaps
	m_bmp_fundo	= create_bitmap(TELA_L, TELA_A);
	m_bmp_objetos = create_bitmap(TELA_L, TELA_A);
	m_bmp_efeitos = create_bitmap(TELA_L, TELA_A);
}

//------------------------------------------------------------
void CTela::Desligar()
{
	if (m_bmp_fundo) destroy_bitmap(m_bmp_fundo);
	if (m_bmp_objetos) destroy_bitmap(m_bmp_objetos);
	if (m_bmp_efeitos) destroy_bitmap(m_bmp_efeitos);

	m_bmp_fundo	= NULL;
	m_bmp_objetos = NULL;
	m_bmp_efeitos	= NULL;
}

//------------------------------------------------------------
void CTela::AtualizarNaTela()
{
	if (m_utilizar_vsync) vsync();
	acquire_bitmap(screen);
	Atualizar(screen);
	release_bitmap(screen);
}

void CTela::Atualizar(BITMAP * bmp_destino)
{
	masked_blit(m_bmp_objetos, m_bmp_fundo, 0, 0, 0, 0, TELA_L, TELA_A);
	masked_blit(m_bmp_efeitos, m_bmp_fundo, 0, 0, 0, 0, TELA_L, TELA_A);

	if (m_utilizar_suavizar) SuavizarBitmap(m_bmp_fundo);

	if (TELA_L == SCREEN_W)
	{
		blit(m_bmp_fundo, bmp_destino, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	}
	else
	{
		stretch_blit(m_bmp_fundo, bmp_destino, 0, 0, TELA_L, TELA_A, 0, 0, SCREEN_W, SCREEN_H);
	}
	if (key[KEY_F12])
		Salvar(m_bmp_fundo);
}

//------------------------------------------------------------
void CTela::Limpar(ECamada camada, int cor)
{
	if (camada == eCamadaTodas)
	{
		clear_to_color(m_bmp_fundo, cor);
		clear_to_color(m_bmp_objetos, cor);
		clear_to_color(m_bmp_efeitos, cor);
	}
	else
	{
		clear_to_color(RetornarCamada(camada), cor);
	}
}

//------------------------------------------------------------
BITMAP *CTela::RetornarCamada(ECamada camada)
{
	switch (camada)
	{
		case eCamadaFundo:
			return m_bmp_fundo;
		case eCamadaObjetos:
			return m_bmp_objetos;
		case eCamadaEfeitos:
			return m_bmp_efeitos;
		default:
			return screen;
	}
}

//------------------------------------------------------------
void CTela::SetarVsync(bool valor)
{
	m_utilizar_vsync = valor;
}

//------------------------------------------------------------
void CTela::SetarSuavizar(bool valor)
{
	m_utilizar_suavizar = valor;
}

//------------------------------------------------------------
void CTela::SetarEscreverSombra(bool valor)
{
	m_utilizar_escrever_sombra = valor;
}

void CTela::Salvar(BITMAP *bmp)
{
	bool sair = false;
	int i = 0;
	char arquivo[512];

	do {
		sprintf(arquivo, "captura_%d.bmp", i);
		if (!exists(arquivo))
		{
			textout_centre(screen, font, "SALVANDO CAPTURA DE TELA...", SCREEN_W / 2, SCREEN_H / 2, makecol(255,255,0));
			sair = true;
			save_bmp(arquivo, bmp, NULL);
		}
		i++;
	} while (!sair);
	rest(1000);
}

//////////////////////////////////////////////////////////////
//Espelho das funções da Allegro com algumas sobrecarcas
//////////////////////////////////////////////////////////////

//------------------------------------------------------------
void CTela::Blit(BITMAP *bmp, ECamada camada)
{
	Blit(bmp, camada, 0, 0, 0, 0, bmp->w, bmp->h);
}

//------------------------------------------------------------
void CTela::Blit(BITMAP *bmp, ECamada camada, int fx, int fy, int dx, int dy, int l, int a)
{
	blit(bmp, RetornarCamada(camada), fx, fy, dx, dy, l, a);
}

//------------------------------------------------------------
void CTela::MaskedBlit(BITMAP *bmp, ECamada camada)
{
	MaskedBlit(bmp, camada, 0, 0, 0, 0, bmp->w, bmp->h);
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
	draw_trans_sprite(RetornarCamada(camada), bmp, x, y);
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
void CTela::Escrever(const char * str, int x, int y, int cor)
{
	Escrever(eCamadaEfeitos, str, x, y, cor);
}

void CTela::Escrever(const char * str, int x, int y, int cor, FONT *fonte)
{
	if (m_utilizar_escrever_sombra)
	{
		textout(RetornarCamada(eCamadaEfeitos), fonte, str, x + 1, y + 1, COR_PRETA);
	}

	textout(RetornarCamada(eCamadaEfeitos), fonte, str, x, y, cor);
}
//------------------------------------------------------------
void CTela::Escrever(ECamada camada, const char * str, int x, int y, int cor)
{
	if (m_utilizar_escrever_sombra)
	{
		textout(RetornarCamada(camada), font, str, x + 1, y + 1, COR_PRETA);
	}

	textout(RetornarCamada(camada), font, str, x, y, cor);
}


//------------------------------------------------------------
void CTela::PutPixel(ECamada camada, int x, int y, int cor)
{
	putpixel(RetornarCamada(camada), x, y, cor);
}

//------------------------------------------------------------
void CTela::SetarTransBlender(int r, int g, int b, int alpha)
{
	set_trans_blender(r, g, b, alpha);
}

void CTela::RotateSprite(ECamada camada, BITMAP * bmp, int x, int y, fixed angulo)
{
	rotate_sprite(RetornarCamada(camada), bmp, x, y, angulo);
}