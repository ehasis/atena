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
*------------------------------------------------------------*/

#ifndef cnave_h_incluido
#define cnave_h_incluido

#include "cobjeto.h"
#include "ctiro.h"
#include "ccolecaoarma.h"

enum EStatusNave
{
	eNaveNormal,
	eNaveEscudo,
	eNaveExplosao,
	eNaveRenacer
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
	void Iniciar();
	void DecEnergia(int valor);
	void IncEnergia(int valor);
	void Atualizar(TRect area, CObjetoAvancado * const alvo);
	void Desenhar(CTela & tela, int x_real, int y_real);;
	void Finalizar();
	void Sonorizar();
	CTiro *ObterTiros();
	int ObterPontos();
	void IncPontos(int incremento);
	int ObterCasco();
	int ObterStatus();
	CColecaoArma & ObterArmas();
	void SetarX(int x);			
	void IncX(int incremento);
	void DecX(int decremento);
	void SetarY(int y);
	void IncY(int incremento);
	void DecY(int decremento);

private:
	DATAFILE *m_dat_arquivo;
	CColecaoArma m_armas;
	CTiro m_tiros;
	int m_pontos;
	int m_casco;
	int m_atirar;
	int m_tipo_tiro;
	EStatusNave m_status;
	int m_turbina;
	float m_vi, m_vx, m_vy;
	int m_dx, m_dy;

};

#endif