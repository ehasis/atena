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
	eTiroBola,
	eTiroLaserVermelho,
	eTiroLaserVerde,
	eTiroFogoTeleguiado,
	eTiroFogo
} ETiroTipo;


typedef enum
{
	eTiroNormal,
	eTiroExplosao
} EStatusTiro;

//------------------------------------------------------------
// Classe para as tiros
class CTiro : public CObjeto
{
public:
	CTiro(void);
	static void Carregar_dat_arquivo(DATAFILE * _dat_arquivo){dat_arquivo = _dat_arquivo;}
	static void Descarregar_dat_arquivo(void){unload_datafile(dat_arquivo);}
	void Iniciar(ETiroTipo _tipo, int _x, int _y,   CObjeto * const _alvo);
	void Adicionar(ETiroTipo _tipo, int _x, int _y,  CObjeto * const _alvo);
	void AtualizarTodos(TRect _area, CObjeto * const _alvo);
	void Atualizar(CObjeto * const _alvo);
	void Desenhar(CTela &_tela, int _x_real, int _y_real);;
	void DesenharTodos(CTela &_tela, int _x_real, int _y_fase);
	int VerificarExisteTiros(void);
	int ChecarColisaoTiros(TRect _obj);
	void Sonorizar(void);
	void SonorizarTodos(void);
	void SetarStatus(EStatusTiro _status);
	void Desligar(void);

	CTiro *p_tiro;
private:
	ETiroTipo tipo;
	static DATAFILE *dat_arquivo;
	int quadro;
	CObjeto *alvo;
	int tocar_som;
	EStatusTiro status;
	int dir_x;
	int dir_y;
	int flag_x;
	int flag_y;
	int cont;
};

#endif