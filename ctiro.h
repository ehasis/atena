 /*------------------------------------------------------------*
 *  ctiro.h - Classe CTiro
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: terça-feira, 13 de janeiro de 2002
*
*  Diego em 13/02/2002
*   - Alterado os métodos Desenhar e DesenharTodos para aceitar
*     CTela e posicionamento relativo;
*
*  Diego em 24/02/2002
*   - Incluido membro de dados m_velocidade;
*
*  Diego Giacomelli em 05/03/2002
*   - Alterada herância para CObjetoAvancado;
*
*  Diego Giacomelli em 01/05/2002
*   - Inserido o método ObterMaisProximo;
*
*  Diego Giacomelli em 23/06/2002
*   - Renomeado ETiroTipo para ETiro
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
} ETiro;


typedef enum
{
	eTiroNormal,
	eTiroExplosao
} EStatusTiro;

//------------------------------------------------------------
// Classe para as tiros
class CTiro : public CObjetoAvancado
{
public:
	CTiro();
	static void CarregarArquivoDados(DATAFILE * dat_arquivo);
	static void DescarregarArquivoDados();
	void Iniciar(ETiro tipo, int x, int y, CObjetoAvancado * const alvo);
	void Adicionar(ETiro tipo, int x, int y, CObjetoAvancado * const alvo);
	void AtualizarTodos(TRect area, CObjetoAvancado * const alvo);
	void Atualizar(CObjetoAvancado * const alvo);
	void Desenhar(CTela & tela, int x_real, int y_real);
	void DesenharTodos(CTela & tela, int x_real, int y_fase);
	int VerificarExisteTiros();
	int ChecarColisaoTiros(TRect obj);
	void Sonorizar();
	void SonorizarTodos();
	void SetarStatus(EStatusTiro status);
	void Finalizar();
	CObjetoAvancado *ObterMaisProximo(int x, int y);

	CTiro *m_p_tiro;
private:
	ETiro m_tipo;
	static DATAFILE *m_dat_arquivo;
	CObjetoAvancado *m_alvo;
	int m_tocar_som;
	EStatusTiro m_status;
	int m_dir_x;
	int m_dir_y;
	int m_flag_x;
	int m_flag_y;
	int m_cont;
	int m_velocidade;
};

#endif