 /*------------------------------------------------------------*
 *  cconstrucao.h - Classe CConstrucao
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: sábado, 27 de janeiro de 2002
*
*
*
*------------------------------------------------------------*/


#ifndef cconstrucao_h_incluido
#define cconstrucao_h_incluido


#include <stdio.h>
#include <allegro.h>
#include <string.h>
#include "funcoes.h"
#include "ctiro.h"


typedef enum
{
	eConstrucao_01,
	eConstrucao_02,
	eConstrucao_03,
	eConstrucao_04,
	eConstrucao_05,
	eConstrucao_06,
	eConstrucao_07
} EConstrucao;


enum EStatusConstrucao
{
	eConstrucaoNormal,
	eConstrucaoExplosao,
	eConstrucaoInativo
};


//------------------------------------------------------------
// Classe para as construções
class CConstrucao : public CObjeto
{
public:
	CConstrucao(void);
	static void Carregar_dat_arquivo(DATAFILE * _dat_arquivo){dat_arquivo = _dat_arquivo;}
	static void Descarregar_dat_arquivo(void){unload_datafile(dat_arquivo);}
	static int ObterNumeroConstrucoes(void) { return num_construcoes; };
	void Iniciar(int _tipo, int _x, int _y);
	void Desenhar(CTela &_tela, int _x_real, int _y_real);;
	void DesenharTodos(CTela &_tela, int _x_real, int _y_fase);
	void Atualizar(TRect _area, CObjeto * const _alvo);
	void AtualizarTodos(TRect _area, CObjeto * const _alvo);
	void Desligar(void);
	void Adicionar(int _tipo, int _x, int _y);
	int ObterTipo(void);
	void SalvarConstrucao(char *_fase);
	void Excluir(int _tipo, int _x, int _y);
	void Excluir(int _x1, int _y1, int _x2, int _y2);
	int ChecarColisaoConstrucoes(int _x1, int _y1, int _x2, int _y2);
	void Sonorizar(void);
	void SonorizarTodos(void);
	void SetarStatus(EStatusConstrucao _status);
	EStatusConstrucao ObterStatus(void);
	int ObterEnergia(void);
	void DecEnergia(int _decremento);
	CTiro *ObterTiros(void);

	CConstrucao *p_construcao;	   		// Ponteiro para o proximo nodo da lista
private:
	int tipo; //eConstrucao
	int energia;
	int quadro;
	int atirar;
	EStatusConstrucao status;
	static DATAFILE *dat_arquivo;
	static int num_construcoes;
	CTiro tiros;
};

#endif