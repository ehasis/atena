 /*------------------------------------------------------------*
 *  ctela.h - Definição da CTela
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quarta-feira, 13 de fevereito de 2002
*
*  Alterações:
*  Diego Giacomelli em 25/02/2002
*   - Adicionado método RotateSprite;
*
*  Henrique Andreassy em 27/02/2002
*   - Corrigido método Desligar
*   - Incluido método Limpar
*   - Incluido método SetarModoGrafico
*   - Incluido método AtualizarNaTela
*   - Incluido método SetarTransBlender
*   - Incluido no enum que representa a camada screen e todas
*   - Modificado método Atualizar para executar em um bitmap
*   - Modificado método Iniciar para chamar SetarModoGrafico
*   - Modificado nome das constantes de cores para feminino
*   - Modificado alguns tipos de variaveis de int para bool
*   - Retirada a variavel bitmap m_bmp_aux
*
*  Henrique Andreassy em 23/07/2002
*	- Adicionado mais uma sobrecarga para o método Escrever
*	  para aceitar escrever com uma determinada fonte
*
*  Henrique Andreassy em 27/07/2002
*	- Adicionado método para salvar captura de tela
*
*  Henrique Andreassy em 23/01/2003
*	- Modificado as camadas de efeitos e objetos para terem
*     apenas o tamanho da arena
*
*------------------------------------------------------------*/

#ifndef ctela_h_incluido
#define ctela_h_incluido

#include "callegro.h"
#include "cexplosao.h"

#define TELA_L    640	//Largura da Tela
#define TELA_A	  480	//Altura da Tela

#define ARENA_L	  544	//Largura da Arena
#define ARENA_A   480	//Altura da Arena

#define STATUS_L   96
#define STATUS_A  480


//Cores basicas no modo 16bit
#define COR_VERMELHA    31	//makecol16(255,   0,   0)
#define COR_VERDE     2016	//makecol16(0,   255,   0)
#define COR_AZUL     63488	//makecol16(0,     0, 255)
#define COR_AMARELA   2047	//makecol16(255, 255,   0)
#define COR_ROSA     63519	//makecol16(255,   0, 255)
#define COR_BRANCA   65535	//makecol16(255, 255, 255)
#define COR_PRETA        0	//makecol16(0,     0,   0)


//Enum das camadas disponiveis na classe
enum ECamada
{
	eCamadaScreen,
	eCamadaFundo,
	eCamadaObjetos,
	eCamadaEfeitos,
	eCamadaTodas
};

class CTela
{
public:
	//Metodos Basicos
	void Iniciar(int modo, int largura, int altura, int bit_cores);
	void Atualizar(BITMAP * bmp_destino);
	void AtualizarNaTela();
	void Desligar();
	void Limpar(ECamada camada = eCamadaTodas, int cor = COR_ROSA);

	//Metodos de Configuração
	void SetarVsync(bool valor);
	void SetarSuavizar(bool valor);
	void SetarEscreverSombra(bool valor);
	void SetarModoGrafico(int modo, int largura, int altura, int bit_cores);
	void SetarTransBlender(int r, int g, int b, int alpha);
	void SetarExibirParticulas(bool valor);

	//Metodos espelhos das funções da Allegro e sobrecargas
	void Blit(BITMAP *bmp, ECamada camada);
	void Blit(BITMAP *bmp, ECamada camada, int fx, int fy, int dx, int dy, int l, int a);
	void MaskedBlit(BITMAP *bmp, ECamada camada);
	void MaskedBlit(BITMAP *bmp, ECamada camada, int fx, int fy, int dx, int dy, int l, int a);
	void DrawSprite(ECamada camada, BITMAP *bmp, int x, int y);
	void DrawTransSprite(ECamada camada, BITMAP *bmp, int x, int y);
	void Rect(ECamada camada, int x1, int y1, int x2, int y2, int cor);
	void RectFill(ECamada camada, int x1, int y1, int x2, int y2, int cor);
	void PutPixel(ECamada camada, int x, int y, int cor);
	void RotateSprite(ECamada camada, BITMAP * bmp, int x, int y, fixed angulo);

	//Metodos Extras
	void Escrever(const char * str, int x, int y, int cor, ALFONT_FONT *fonte);

	//Metodo auxiliar que retorna o bitmap associado a camada
	BITMAP *ObterCamada(ECamada camada);
protected:
	void Salvar(BITMAP *bmp);

protected:
	bool m_utilizar_vsync;
	bool m_utilizar_suavizar;
	bool m_utilizar_escrever_sombra;

	BITMAP *m_bmp_fundo;
	BITMAP *m_bmp_objetos;
	BITMAP *m_bmp_efeitos;

	
};


//------------------------------------------------------------
// Métodos INLINE
//------------------------------------------------------------


//------------------------------------------------------------
inline void CTela::AtualizarNaTela()
{
	//if (m_utilizar_vsync) vsync();
	acquire_screen();
	Atualizar(screen);
	release_screen();
}


//------------------------------------------------------------
inline void CTela::Limpar(ECamada camada, int cor)
{
	if (camada == eCamadaTodas)
	{
		clear_to_color(m_bmp_fundo, cor);
		clear_to_color(m_bmp_objetos, cor);
		clear_to_color(m_bmp_efeitos, cor);
	}
	else
	{
		clear_to_color(ObterCamada(camada), cor);
	}
}

//------------------------------------------------------------
inline BITMAP *CTela::ObterCamada(ECamada camada)
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

//////////////////////////////////////////////////////////////
//Espelho das funções da Allegro com algumas sobrecarcas
//////////////////////////////////////////////////////////////

//------------------------------------------------------------
inline void CTela::Blit(BITMAP *bmp, ECamada camada)
{
	Blit(bmp, camada, 0, 0, 0, 0, bmp->w, bmp->h);
}

//------------------------------------------------------------
inline void CTela::Blit(BITMAP *bmp, ECamada camada, int fx, int fy, int dx, int dy, int l, int a)
{
	blit(bmp, ObterCamada(camada), fx, fy, dx, dy, l, a);
}

//------------------------------------------------------------
inline void CTela::MaskedBlit(BITMAP *bmp, ECamada camada)
{
	MaskedBlit(bmp, camada, 0, 0, 0, 0, bmp->w, bmp->h);
}

//------------------------------------------------------------
inline void CTela::MaskedBlit(BITMAP *bmp, ECamada camada, int fx, int fy, int dx, int dy, int l, int a)
{
	masked_blit(bmp, ObterCamada(camada), fx, fy, dx, dy, l, a);
}

//------------------------------------------------------------
inline void CTela::DrawSprite(ECamada camada, BITMAP *bmp, int x, int y)
{
	draw_sprite(ObterCamada(camada), bmp, x, y);
}

//------------------------------------------------------------
inline void CTela::DrawTransSprite(ECamada camada, BITMAP *bmp, int x, int y)
{
	draw_trans_sprite(ObterCamada(camada), bmp, x, y);
}

//------------------------------------------------------------
inline void CTela::Rect(ECamada camada, int x1, int y1, int x2, int y2, int cor)
{
	rect(ObterCamada(camada), x1, y1, x2, y2, cor);
}

//------------------------------------------------------------
inline void CTela::RectFill(ECamada camada, int x1, int y1, int x2, int y2, int cor)
{
	rectfill(ObterCamada(camada), x1, y1, x2, y2, cor);
}

//------------------------------------------------------------
inline void CTela::Escrever(const char * str, int x, int y, int cor, ALFONT_FONT *fonte)
{
	if (fonte != NULL)
		alfont_textout(ObterCamada(eCamadaFundo), fonte, str, x, y, cor);
	else
		textout(ObterCamada(eCamadaFundo), font, str, x, y, cor);
}

//------------------------------------------------------------
inline void CTela::PutPixel(ECamada camada, int x, int y, int cor)
{
	putpixel(ObterCamada(camada), x, y, cor);
}

//------------------------------------------------------------
inline void CTela::SetarTransBlender(int r, int g, int b, int alpha)
{
	set_trans_blender(r, g, b, alpha);
}

inline void CTela::RotateSprite(ECamada camada, BITMAP * bmp, int x, int y, fixed angulo)
{
	rotate_sprite(ObterCamada(camada), bmp, x, y, angulo);
}


#endif

