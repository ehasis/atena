 /*------------------------------------------------------------*
 *  cjogo.h - Classe Principal do Jogo
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: sabado, 23 de fevereito de 2001
*
*  Henrique Andreassy em 03/03/2002
*   - Incluído Metodo ExibirMenuPrincipal
*   - Incluído Metodo ExibirMenuConfiguração
*
*  Diego Giacomelli em 01/05/2002
*   - Incluída a opçãod de menu Demo;
*
*------------------------------------------------------------*/

#ifndef cjogo_h_incluido
#define cjogo_h_incluido

#include "cfase.h"
#include "ctela.h"
#include "cconfig.h"

class CJogo
{
public:
	void Iniciar();
	void Executar();
	void Desligar();

protected:
	bool m_final_jogo;
	bool m_final_partida;

	bool m_cfg_musica;
	bool m_cfg_efeitos;

	int  m_cfg_velocidade;

	DATAFILE	* m_data;
	CConfig		m_cfg;
	CTela		m_tela;
	CFase		m_fase;

	void ChecarArquivo(const char * arquivo);
	void CarregarConfiguracao();

	void IniciarPartida();
	void ExecutarPartida();
	void DesligarPartida();

	void ExibirMenuPrincipal();
	void ExibirMenuConfiguracao();
};

#endif