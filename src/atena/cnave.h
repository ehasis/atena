 /*------------------------------------------------------------*
 *  cnave.h - Definicao das classes de Naves
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quarta-feira, 19 de setembro de 2001
*
*  Alterações:
*  Diego Giacomelli em 19/09/2001
*  	- Adicionada sombra à nave Alien no método Desenhar;
*
*  Diego Giacomelli em 24/01/2002
*  	- Criado o método Iniciar;
*   - Retirado o método SetArquivoDat (obsoleto);
*
*  Diego Giacomelli em 05/03/2002
*   - Alterada herânça para CObjetoAvancado
*
*  Diego Giacomelli em 01/05/2002
*   - Inseridos membros de dados m_dx e m_dy;
*
*  Diego Giacomelli em 26/06/2002
*	- Implementação do método ObterArmas;
*
*  Diego Giacomelli em 06/07/2002
*	- Alterado TEntrada para suportar duas armas na nave;
*	- Utilizando polimorfismo nos métodos IncX, DecX, IncY, DecY
*     para garantir que quando a nave se movimentar suas armas se
*	  movimentarão juntas;
*
*  Diego Giacomelli em 11/07/2002
*	- Implementado o método Colidir();
*
*  Diego Giacomelli em 15/07/2002
*	- Inserido enum ENave;
*	- Inseridos membros de dados m_tipo, m_bonus;
*	- Implementados os métodos SetarBonus, CNave;
*
*  Diego Giacomelli em 18/07/2002
*	- Inseridos os membros de dados m_tecla_cima, m_tecla_baixo,
*	  m_tecla_esquerda, m_tecla_direita, m_tecla_arma_esquerda,
*	  m_tecla_arma_centro, m_tecla_arma_direita, m_tecla_todas_armas;
*	- Criado método SetarTeclas;
*
*  Diego Giacomelli em 27/08/2002
*	- Reduzidas as dimensões da nave para adaptá-las as dimensões
*	  tela jogável;
*------------------------------------------------------------*/

#ifndef cnave_h_incluido
#define cnave_h_incluido

#include "callegro.h"

#include "cobjeto.h"
#include "carma.h"
#include "cbonus.h"
#include "ccolecaoavancada.h"

typedef enum
{
	eAtena_01,
	eAtena_02,
	eTartaro_01,
	eTartaro_02,
	eMercurio_01,
	eMercurio_02,
	eCrono_01,
	eCrono_02,
	ePontos_01,
	ePontos_02
} ENave;


enum EStatusNave
{
	eNaveNormal,
	eNaveEscudo,
	eNaveExplosao,
	eNaveRenacer,
	eNaveAtingida
};

struct TEntrada
{
	int x, y;
	int a, b, c;
	bool arma_esquerda, arma_centro, arma_direita;
};

class CNave: public CObjetoAvancado
{
public:
	CNave();
	void Iniciar(int tipo, int x, int y);
	void DecEnergia(int valor);
	void IncEnergia(int valor);
	void Atualizar(TRect area, CObjetoAvancado * const alvo);
	void Desenhar(CTela & tela, int x_real, int y_real);;
	void Finalizar();
	void Sonorizar();
	int ObterPontos();
	void IncPontos(int incremento);
	int ObterCasco();
	int ObterStatus();
	CColecaoAvancada< CArma > & ObterArmas();
	void SetarX(int x);
	void IncX(int incremento);
	void DecX(int decremento);
	void SetarY(int y);
	void IncY(int incremento);
	void DecY(int decremento);
	bool Colidir(TRect area, int energia);
	void SetarBonus(int bonus);
	void SetarTeclas(int tecla_cima = KEY_UP, int tecla_baixo = KEY_DOWN, int tecla_esquerda = KEY_LEFT, int tecla_direita = KEY_RIGHT, int tecla_arma_esquerda = KEY_Z, int tecla_arma_centro = KEY_X, int tecla_arma_direita = KEY_C, int tecla_todas_armas = KEY_SPACE);

private:
	GADados m_dat_arquivo;
	CColecaoAvancada < CArma > m_armas;
	int m_pontos;
	int m_casco;
	int m_atirar;
	int m_tipo_tiro;
	EStatusNave m_status;
	int m_turbina;
	float m_vi, m_vx, m_vy;
	int m_dx, m_dy;
	int m_tipo; // ENave
	int m_bonus;
	int m_tecla_cima;
	int m_tecla_baixo;
	int m_tecla_esquerda;
	int m_tecla_direita;
	int m_tecla_arma_esquerda;
	int m_tecla_arma_centro;
	int m_tecla_arma_direita;
	int m_tecla_todas_armas;
	bool atirando;
};

#endif

