 /*------------------------------------------------------------*
 *  calien.h - Classe CAlien
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: terça-feira, 13 de dezembro de 2001
*
*  Alterações:
*  Diego Giacomelli em 07/01/2002
*   - Alteração do nome do método Colisão para ChecarColisao
*     para adaptar-se aos padrões de nomenclatura;
*
*
*------------------------------------------------------------*/


#ifndef calien_h_incluido
#define calien_h_incluido


#include "cobjeto.h"
#include "ctiro.h"

typedef enum
{
	eAlien_01,
	eAlien_02,
	eAlien_03,
	eAlien_04,
	eAlien_05,
	eAlien_06,
	eAlien_07
} eAlien;


enum EStatusAlien
{
	eAlienNormal,
	eAlienEscudo,
	eAlienExplosao,
	eAlienInativo
};


typedef struct
{
	int tipo;
	int x;
	int y;
} TAlien;



//------------------------------------------------------------
/* Classe para as naves aliens */
class CAlien : public CObjeto
{
public:
	CAlien(void);
	void Iniciar(int _tipo, int _x, int _y, DATAFILE *_dat_arquivo);
	void Desenhar(BITMAP *_bmp_destino);
	void DesenharTodos(BITMAP *_bmp_destino);
	void Atualizar(int _x1_alvo, int _y1_alvo, int _x2_alvo, int _y2_alvo, int _x1, int _y1, int _x2, int _y2);
	void AtualizarTodos(int _x1_alvo, int _y1_alvo, int _x2_alvo, int _y2_alvo, int _x1, int _y1, int _x2, int _y2);
	void Desligar(void);
	void Adicionar(int _tipo, int _x, int _y);
	int ObterTipo(void);
	void SalvarAlien(char *_fase);
	void Excluir(int _tipo, int _x, int _y);
	void Excluir(int _x1, int _y1, int _x2, int _y2);
	int ChecarColisaoAliens(int _x1, int _y1, int _x2, int _y2);
	int ChecarColisaoAliens(void);
	void TocarSom(void);
	void TocarSomTodos(void);
	void SetarStatus(EStatusAlien _status);
	EStatusAlien ObterStatus(void);
	int ObterEnergia(void);
	void DecEnergia(int _decremento);
	CTiro *ObterTiros(void);

	CAlien *p_alien;	   		/* Ponteiro para o proximo nodo da lista */
private:
	int tipo; //eAlien
	int energia;
	int tempo;
	int atirar;
	int velocidade;
	EStatusAlien status;
	DATAFILE *dat_arquivo;
	int atualizado;
	CTiro tiros;
};
#endif