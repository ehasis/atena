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
*  Henrique Andreassy em 23/07/2002
*	- Incluido painel de informações
*
*  Diego Giacomelli em 13/09/2002
*   - Implementado o cálculo de FPS (Frames-Per-Second);
*
*  Henrique Andreassy em 23/01/2003
*	- Convertido dodos os DATAFILES do projeto para GADados
*
*------------------------------------------------------------*/

#ifndef cjogo_h_incluido
#define cjogo_h_incluido

#include "callegro.h"

#include "cfase.h"
#include "ctela.h"

enum EEstadoJogo
{
    eExibirAbertura,
    eExibirMenuPrincipal,
    eExibirMenuConfiguracao,
    eExibirCreditos,
    eIniciarPartida,
    eExecutarPartida,
    eFinalizarPartida,
    ePausa
};
    

class CJogo
{
public:
	void Iniciar();
	void Executar();
	void Finalizar();

protected:
	bool m_final_jogo;
	bool m_cfg_musica;
	bool m_cfg_efeitos;
	bool m_cfg_particulas;

	int  m_cfg_velocidade;
	int g_FPS;

	GADados		m_dados;
	GAConfig	m_cfg;
	CTela		m_tela;
	CFase		m_fase;
	
	EEstadoJogo m_estado;

	BITMAP *bmp_buffer;

	void ChecarArquivo(const char * arquivo);
	void CarregarConfiguracao();

	void IniciarPartida();
	void ExecutarPartida();
	void FinalizarPartida();

	void ExibirMenuPrincipal();
	void ExibirMenuConfiguracao();

	int CalcularFPS();
};

#endif

