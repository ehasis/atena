 /*------------------------------------------------------------*
 *  ceditor.h - Classe Principal do Editor
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: sexta-feira, 19 de outubro de 2001
*
*  Alterações:
*  Diego Giacomelli em 02/01/2002
*   - Opcões de flip vertical e horizontal e rotação para
*      os ladrilhos selecionados;
*
*  Diego Giacomelli em 03/01/2002
*   - Implementada a inserção dos aliens na m_fase;
*   - Implementação das funçoes VerificarLadrilho e
*     VerificarAlien;
*
*  Diego Giacomelli em 07/01/2002
*   - Alteração do nome do método Colisão para ChecarColisao
*     para adaptar-se aos padrões de nomenclatura;
*
*  Diego Giacomelli em 24/02/2002
*	- Permitido a inserção de objetos com colisão;
*	- Travamento das coordenadas do mouse quando pressiondo
*     as teclas ctrl (KEY_LCTRL trava _mouse_x e KEY_RCTRL trava _mouse_y);
* 	- Implementadas as procedures RotacionarLadrilho, VirarHLadrilho(),
*     VirarVLadrilho() e HabilitarApagarObjetos;
*
*  Diego Giacomelli em 25/02/2002
*   - Adicionado a opção para a dimensão do tamanho do pincel para
*     ladrilhos;
*   - Implementadas as procedures IncrementarPincel e DecrementarPincel;
*
*  Diego Giacomelli em 27/02/2002
*   - Adicionado teste em AbrirFundo para o validacao das dimensoes
*     do bitmap para o fundo (BMP_FUNDO_L, BMP_FUNDO_A);
*
*  Diego Giacomelli em 06/03/2002
*   - Reajustado para CTela;
*   - Quadrado de seleção para as dimensões do pincel dos ladrilhos;
*   - Agora é permitido inserir objetos com colisão;
*   - Trava as coordenadas do mouse quando pressionado as teclas ctrl;
*
*  Diego Giacomelli em 07/03/2002
*   - Apagar objetos condicional, somente são excluídos os objetos
*     do m_tipo atualmente selecionado no menu obj;
*
*  Diego Giacomelli em 09/03/2002
*	- Os arquivos zeus.h e zeus.cpp foram substituídos por
*     CEditor.h e CEditor.cpp e todo o editor de fases foi
*     convertido para POO;
*
*------------------------------------------------------------*/

#ifndef ceditor_h_incluido
#define ceditor_h_incluido

#include "..\atena\callegro.h"

#include "..\atena\cfase.h"
#include "..\atena\ctela.h"
#include "..\atena\cconfig.h"
#include "..\atena\clog.h"
#include "imagem.h"
#include "cbotao.h"


#define MENU_LARGURA				542
#define MENU_ALTURA					10

#define MENU_ARQUIVO_X1				MENU_OBJ_LARGURA + 1
#define MENU_ARQUIVO_X2				MENU_ARQUIVO_X1 + 64

#define MENU_OBJETOS_X1				MENU_ARQUIVO_X2 + 10
#define MENU_OBJETOS_X2				MENU_OBJETOS_X1 + 74

#define MENU_EXIBIR_X1				MENU_OBJETOS_X2 + 10
#define MENU_EXIBIR_X2				MENU_EXIBIR_X1 + 64

#define MENU_FERRAMENTAS_X1			MENU_EXIBIR_X2 + 10
#define MENU_FERRAMENTAS_X2			MENU_FERRAMENTAS_X1 + 108

#define MENU_OBJ_LARGURA_LADRILHO	3
#define MENU_OBJ_ALTURA_LADRILHO	15
#define MENU_OBJ_LARGURA			MENU_OBJ_LARGURA_LADRILHO * LADRILHO_LARGURA
#define MENU_OBJ_ALTURA				MENU_OBJ_ALTURA_LADRILHO * LADRILHO_ALTURA
#define MENU_OBJ_X1			        0
#define MENU_OBJ_Y1			        0
#define MENU_OBJ_X2					MENU_OBJ_X1 + MENU_OBJ_LARGURA
#define MENU_OBJ_Y2					MENU_OBJ_Y1 + MENU_OBJ_ALTURA


#define MAPA_EDITOR_LARGURA			543
#define MAPA_EDITOR_ALTURA			437
#define MAPA_EDITOR_X1				MENU_OBJ_X2 + 1
#define MAPA_EDITOR_X2				MAPA_EDITOR_X1 + MAPA_EDITOR_LARGURA
#define MAPA_EDITOR_Y1				MENU_ALTURA	+ 1
#define MAPA_EDITOR_Y2				MAPA_EDITOR_Y1 + MAPA_EDITOR_ALTURA


#define MENU_AUX_Y					MENU_ALTURA + MAPA_EDITOR_ALTURA + 1
#define MENU_AUX_X					MENU_OBJ_LARGURA + 1

#define BARRA_PROGRESSO_X			MENU_AUX_X + 340
#define BARRA_PROGRESSO_Y			MENU_AUX_Y + 20
#define BARRA_PROGRESSO_LARGURA		200
#define BARRA_PROGRESSO_ALTURA		10
#define BARRA_PROGRESSO_COR			makecol(0, 255, 0)

#define DIALOGO_LARGURA				400
#define DIALOGO_ALTURA				300

#define ARQUIVO_NOME_COMPRIMENTO	480

#define LADRILHO_NAO_SELECIONADO_COR	makecol(100, 100, 100)
#define LADRILHO_SEL_ESQUERDO_COR		makecol(255, 0, 0)
#define LADRILHO_SEL_DIREITO_COR		makecol(0, 0, 255)
#define SOBRE_LADRILHO_COR				makecol(0, 255, 0)

#define LADRILHO_SEL_ESQUERDO_X			MENU_AUX_X + 1
#define LADRILHO_SEL_ESQUERDO_Y			MENU_AUX_Y + 1
#define LADRILHO_SEL_DIREITO_X			MENU_AUX_X + LADRILHO_LARGURA + 1
#define LADRILHO_SEL_DIREITO_Y			MENU_AUX_Y + 1

#define BOTAO_H_FLIP_X				LADRILHO_SEL_DIREITO_X + LADRILHO_LARGURA + 1
#define BOTAO_H_FLIP_Y				MENU_AUX_Y + 1
#define BOTAO_V_FLIP_X				BOTAO_H_FLIP_X + LADRILHO_LARGURA + 1
#define BOTAO_V_FLIP_Y				MENU_AUX_Y + 1
#define BOTAO_ROTACAO_X				BOTAO_V_FLIP_X + LADRILHO_LARGURA + 1
#define BOTAO_ROTACAO_Y				MENU_AUX_Y + 1
#define BOTAO_INC_PINCEL_X			BOTAO_ROTACAO_X + LADRILHO_LARGURA + 1
#define BOTAO_INC_PINCEL_Y			MENU_AUX_Y + 1
#define BOTAO_DEC_PINCEL_X			BOTAO_INC_PINCEL_X + LADRILHO_LARGURA + 21
#define BOTAO_DEC_PINCEL_Y			MENU_AUX_Y + 1

#define BOTAO_APAGAR_X				BOTAO_DEC_PINCEL_X + LADRILHO_LARGURA + 1
#define BOTAO_APAGAR_Y				MENU_AUX_Y + 1

#define BMP_FUNDO_L				96
#define BMP_FUNDO_A				480

//------------------------------------------------------------
// Classe para o editor de fases
class CEditor
{
public:
	void Iniciar();
	void Executar();
	void Finalizar();

protected:
	CConfig		m_cfg;
	CTela		m_tela;
	CFase		m_fase;
	bool m_flag_fase, m_flag_obj, m_flag_desenhar;
	bool m_flag_alterado, m_flag_apagar;
	bool m_flag_sair;
	BITMAP *m_bmp_fundo;			// BITMAP para o fundo atualmente aberto
	GADados m_dat_aliens;			// DATAFILE para os aliens atualmente abertos
	GADados m_dat_construcoes;  	// DATAFILE para as construcoes atualmente abertas
	GADados m_dat_veiculos;  		// DATAFILE para os veiculos atualmente abertos
	GADados m_dat_imagem;			// DATAFILE para as imagens da interface do Zeus - NAO SAO OBJETOS DAS FASES
	CLadrilho m_menu_obj_ladrilhos[MENU_OBJ_LARGURA_LADRILHO][MENU_OBJ_ALTURA_LADRILHO];	// CLadrilho's para o menu dos objetos
	CLadrilho m_ladrilho, m_ladrilho_sel_esquerdo, m_ladrilho_sel_direito;
	CAlien m_alien_sel_esquerdo, m_alien_sel_direito;
	CConstrucao m_construcao_sel_esquerdo, m_construcao_sel_direito;
	CVeiculo m_veiculo_sel_esquerdo, m_veiculo_sel_direito;
	char m_arquivo_fundo[ARQUIVO_NOME_COMPRIMENTO];
	char m_arquivo_fase[ARQUIVO_NOME_COMPRIMENTO];
	char m_arquivo_aliens[ARQUIVO_NOME_COMPRIMENTO];
	char m_arquivo_construcoes[ARQUIVO_NOME_COMPRIMENTO];
	char m_caminho[ARQUIVO_NOME_COMPRIMENTO];
	int m_exibir_obj;
	int m_zeus_mouse_x, m_zeus_mouse_y;
	int m_tam_pincel_ladrilho;
	CBotao m_botao_rotacionar, m_botao_virar_h, m_botao_virar_v;
	CBotao m_botao_apagar, m_botao_inc_pincel, m_botao_dec_pincel;
	MENU m_menu_exibir[7];


	void MontarMenuObj(int modo);
	bool NovaFase();
	bool AbrirFase();
	bool SalvarFase();
	bool SalvarComoFase();
	bool FecharFase();
	bool AbrirFundo();
	bool AbrirAliens();
	bool AbrirConstrucoes();
	bool AbrirVeiculos();
	bool PreencherNulos();
	bool TrocarLadrilhos();
	bool Sair();
	void DesenharTela();
	void VerificarLadrilho();
	void VerificarAlien();
	void VerificarConstrucao();
	void VerificarVeiculo();
	void DesenharQuadrado();
	bool VerificarRolaTecla();
	bool VerificarRolaMouse();
	bool VerificarMenuArquivo();
	bool VerificarMenuObjetos();
	bool VerificarMenuExibir();
	bool VerificarMenuFerramentas();
	void VerificarMenuObj();
	void VerificarMenuAux();
	void VerificarApagar();
	bool RotacionarLadrilho();
	bool VirarHLadrilho();
	bool VirarVLadrilho();
	bool HabilitarApagarObjetos();
	bool IncrementarPincel();
	bool DecrementarPincel();
	void ChecarArquivo(const char *_arquivo);
	void CarregarConfiguracao();

};


#endif
