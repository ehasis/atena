/*------------------------------------------------------------*
 *  ctiro.h - Classe CTiro
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: terça-feira, 13 de janeiro de 2002
*
*
*
*------------------------------------------------------------*/


#ifndef ctiro_h_incluido
#define ctiro_h_incluido


#include "cobjeto.h"
#include "tiros.h"


typedef enum
{
	eTiroCerra,
	eTiroFogo,
	eTiroLaserVermelho,
	eTiroLaserVerde,
	eTiroBola,
	eTiroMissil
} ETiroTipo;


typedef enum
{
	eTiroNormal,
	eTiroExplosao
} EStatusTiro;

//------------------------------------------------------------
/* Classe para as tiros */
class CTiro : public CObjeto
{
public:
	CTiro(void);
	void Iniciar(ETiroTipo _tipo, int _x, int _y);
	void Adicionar(ETiroTipo _tipo, int _x, int _y);
	void AtualizarTodos(int _x1_alvo, int _y1_alvo, int _x2_alvo, int _y2_alvo, int _x1, int _y1, int _x2, int _y2);
	void Atualizar(int _x1_alvo, int _y1_alvo, int _x2_alvo, int _y2_alvo);
	void Desenhar(BITMAP *_bmp_destino);
	void DesenharTodos(BITMAP *_bmp_destino);
	void Excluir(void);
	int VerificarExisteTiros(void);
	int ChecarColisaoTiros(TRect _obj);
	void TocarSom(void);
	void TocarSomTodos(void);
	void SetarStatus(EStatusTiro _status);

	CTiro *p_tiro;
private:
	ETiroTipo tipo;
	int bmp_x;
	int atualizado;
	DATAFILE *dat_arquivo;
	int tempo;
	int x_alvo;
	int y_alvo;
	int tocar_som;
	EStatusTiro status;
};

#endif