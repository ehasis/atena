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
*  Diego Giacomelli em 14/01/2002
*   - Implementado o método ObterMaisProximo;
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
} EAlien;


enum EStatusAlien
{
	eAlienNormal,
	eAlienEscudo,
	eAlienAtingido,
	eAlienExplosao,
	eAlienInativo
};


//------------------------------------------------------------
// Classe para as naves aliens
class CAlien : public CObjeto
{
public:
	CAlien(void);
	static void Carregar_dat_arquivo(DATAFILE * _dat_arquivo){dat_arquivo = _dat_arquivo;}
	static void Descarregar_dat_arquivo(void){unload_datafile(dat_arquivo);}
	static int ObterNumeroAliens(void) { return num_aliens; };
	void Iniciar(int _tipo, int _x, int _y);
	void Desenhar(CTela &_tela, int _x_real, int _y_real);
	void DesenharTodos(CTela &_tela, int _x_real, int _y_fase);
	void Atualizar(TRect _area, CObjeto * const _alvo);
	void AtualizarTodos(TRect _area, CObjeto * const _alvo);
	void Desligar(void);
	void Adicionar(int _tipo, int _x, int _y);
	int ObterTipo(void);
	void SalvarAlien(char *_fase);
	void Excluir(int _tipo, int _x, int _y);
	void Excluir(int _x1, int _y1, int _x2, int _y2);
	int ChecarColisaoAliens(int _x1, int _y1, int _x2, int _y2);
	int ChecarColisaoAliens(void);
	void Sonorizar(void);
	void SonorizarTodos(void);
	void SetarStatus(EStatusAlien _status);
	EStatusAlien ObterStatus(void);
	int ObterEnergia(void);
	void DecEnergia(int _decremento);
	CTiro *ObterTiros(void);
	CObjeto *ObterMaisProximo(int _x, int _y);

	CAlien *p_alien;	// Ponteiro para o proximo nodo da lista
private:
	int tipo; //eAlien
	int energia;
	int quadro;
	int atirar;
	int velocidade;
	EStatusAlien status;
	static DATAFILE *dat_arquivo;
	static int num_aliens;
	CTiro tiros;
	int dir_x;
	int dir_y;
};
#endif