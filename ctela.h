 /*------------------------------------------------------------*
 *  ctela.h - Definição da CTela
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quarta-feira, 13 de fevereito de 2002
*
*
*------------------------------------------------------------*/

#ifndef _ctela_h_incluido
#define _ctela_h_incluido

#include <allegro.h>

#define TELA_L 640			//Largura da Tela
#define TELA_A 480			//Altura da Tela

//Cores basicas no modo 16bit
#define COR_VERMELHO    31	//makecol16(255,   0,   0)
#define COR_VERDE     2016	//makecol16(0,   255,   0)
#define COR_AZUL     63488	//makecol16(0,     0, 255)
#define COR_AMARELO   2047	//makecol16(255, 255,   0)
#define COR_ROSA     63519	//makecol16(255,   0, 255)
#define COR_BRANCO   65535	//makecol16(255, 255, 255)
#define COR_PRETO        0	//makecol16(0,     0,   0)


//Enum das camadas disponiveis na classe
enum ECamada
{
	eCamadaFundo,
	eCamadaObjetos,
	eCamadaEfeitos
};

class CTela
{
public:
	//Metodos Basicos
	void Iniciar();
	void Desligar();
	void Atualizar();

	//Metodos de Configuração
	void SetarVsync(int valor);
	void SetarSuavizar(int valor);
	void SetarEscreverSombra(int valor);
	
	//Metodos espelhos das funções da Allegro e sobrecargas
	void Blit(BITMAP *bmp, ECamada camada);
	void Blit(BITMAP *bmp, ECamada camada, int fx, int fy, int dx, int dy, int l, int a);
	void MaskedBlit(BITMAP *bmp, ECamada camada);
	void MaskedBlit(BITMAP *bmp, ECamada camada, int fx, int fy, int dx, int dy, int l, int a);
	void DrawSprite(ECamada camada, BITMAP *bmp, int x, int y);
	void DrawTransSprite(ECamada camada, BITMAP *bmp, int x, int y);
	void Rect(ECamada camada, int x1, int y1, int x2, int y2, int cor);
	void RectFill(ECamada camada, int x1, int y1, int x2, int y2, int cor);
	void PutPixel(ECamada _camada, int _x, int _y, int _cor);

	//Metodos Extras
    void Escrever(const char *str, int x, int y, int cor);
    void Escrever(ECamada camada, const char *str, int x, int y, int cor);
    
	//Metodo auxiliar que retorna o bitmap associado a camada
	BITMAP *RetornarCamada(ECamada camada);
	
protected:
    int utilizar_vsync;
	int utilizar_suavizar;
	int utilizar_escrever_sombra; 
	
	BITMAP *bmp_fundo;
	BITMAP *bmp_objetos;
	BITMAP *bmp_efeitos;
	BITMAP *bmp_aux;
};

#endif