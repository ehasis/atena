 /*------------------------------------------------------------*
 *  cfundo.h - Classe CFundo
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quinta-feira, 27 de setembro de 2001
*
*  
*
*------------------------------------------------------------*/

#ifndef cfundo_h_incluido
#define cfundo_h_incluido

#define LADRILHO_LARGURA		 32 //tamanho do ladrilho em pixel
#define LADRILHO_ALTURA			 32
#define MAPA_LARGURA_LADRILHOS   20 //tamanho do mapa em numero de ladrilhos
#define MAPA_ALTURA_LADRILHOS   200
#define MAPA_ALTURA				MAPA_ALTURA_LADRILHOS * LADRILHO_ALTURA //Tamanho do mapa em pixels
#define MAPA_LARGURA			MAPA_LARGURA_LADRILHOS * LADRILHO_LARGURA

//------------------------------------------------------------
// Classe para manipulacao do fundo
class CFundo
{
public:
	void Iniciar(char *mapa);
	void Desenhar(BITMAP *bmp);
	void Atualizar();
	void Desligar();
private:
	BITMAP *data;
	BITMAP *tela;
	float cont1, cont2;
	int ry1, ry2, ry3;
	int n_ladrilhos;
	int visivel_x1;
	int visivel_y1;
	int visivel_x2;
	int visivel_y2;
	int mapa_ladrilho[MAPA_LARGURA_LADRILHOS][MAPA_ALTURA_LADRILHOS];
};

#endif
