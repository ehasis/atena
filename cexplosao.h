 /*------------------------------------------------------------*
 *  cexplosao.h - Classe CExplosao
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: terça-feira, 06 de agosto de 2002
*
*------------------------------------------------------------*/


#include <allegro.h>
#include "ctela.h"


#ifndef cexplosao_h_incluido
#define cexplosao_h_incluido
#define TAM_PALETA 256

#define QTD_PARTICULAS 8000
#define RANDOM(n)       (((float)rand() / (float)RAND_MAX)*(n))

typedef struct 
{
	float x;
	float y;			
	float dir_x;
	float dir_y;
	unsigned int cor;
} TParticula;

typedef struct
{
	int r;
	int g;
	int b;
}TPaleta;

class CExplosao
{
public:
	static void Iniciar(int largura, int altura);
	static void Desligar();
	static void Desenhar (CTela & tela);
	void IniciarExplosao(int x, int y, int raio, int num_particulas);
	void IniciarExplosaoRadial(int x, int y, int raio);
	void InserirSprite(BITMAP *bmp, int x, int y);

private:
	static BITMAP *m_bmp, *m_buffer, *m_exp;
	static TParticula particulas[QTD_PARTICULAS];
	static int num_bytes;
	static int tempo;
	static TPaleta palette[TAM_PALETA];

};
#endif