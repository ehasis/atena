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
*  Henrique em 25/01/2002
*   - Implementado metodo DesenharExplosao()
*
*  Diego Giacomelli em 13/02/2002
*   - Alterado os métodos Desenhar e DesenharTodos para aceitar
*     CTela e posicionamento relativo;
*
*  Diego Giacomelli em 14/01/2002
*   - Implementado o método ObterMaisProximo;
*
*  Diego Giacomelli em 28/02/2002
*   - Retirado o membro de dados angulo, pois agora ele é herdado
*     do CObjeto;
*
*  Diego Giacomelli em 05/03/2002
*   - Alterada herânça para CObjetoAvancado
*
*  Diego Giacomelli em 26/06/2002
*	- Inserido o membro de dados m_pos_sombra;
*	- Criado o método ChecarColisaoSombra para que as sombras das 
*	  naves apareçam e desapareçam corretamente da tela;
*
*  Diego Giacomelli em 18/07/2002
*	- Alterada toda a classe para ser utilizada com CColecaoAvancada;
*	- Inserido o método Colidir;
*	- Retirados os métodos ObterNumeroAliens, DesenharTodos,
*	  AtualizarTodos, Adicionar, Excluir, ChecarColisaoAliens,
*	  SonorizarTodos, ObterEnergia, ObterMaisProximo;
*	- Retirados os membros de dados m_p_alien, int m_num_aliens;
*
*  Diego Giacomelli em 20/07/2002
*	- Inserido controle de m_tiros por CColecaoAvancada;
*	- Substituido m_tiros por m_armas; 
-----------------------------------------------------------*/


#ifndef calien_h_incluido
#define calien_h_incluido


#include "cobjeto.h"
#include "ccolecaoavancada.h"
#include "carma.h"

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
class CAlien : public CObjetoAvancado
{
public:
	CAlien();
	static void CarregarArquivoDados(DATAFILE * dat_arquivo);
	static void DescarregarArquivoDados();
	void Iniciar(int tipo, int x, int y);
	void Desenhar(CTela & tela, int x_real, int y_real);
	void Atualizar(TRect area, CObjetoAvancado * const alvo);
	void Finalizar();
	int ObterTipo();
	void Sonorizar();
	void SetarStatus(EStatusAlien status);
	EStatusAlien ObterStatus();
	void DecEnergia(int decremento);
	CColecaoAvancada< CArma > & ObterArmas();
	bool Colidir(TRect area, int energia);
	
protected:
	int m_tipo; //eAlien
	int m_atirar;
	int m_velocidade;
	EStatusAlien m_status;
	static DATAFILE *m_dat_arquivo;
	CColecaoAvancada< CArma > m_armas;
	int m_dir_x;
	int m_dir_y;
	int m_dir_r;		// Direção da rotação
	int m_flag_x;
	int m_flag_y;
	int m_pos_sombra;
};
#endif