 /*------------------------------------------------------------*
 *  zeus.h - Editor de Fases
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: sexta-feira, 19 de outubro de 2001
*
*
*  Alterações:
*  Diego Giacomelli em 02/01/2002
*   - Opcões de flip vertical e horizontal e rotação para
*      os ladrilhos selecionados;
*
*  Diego Giacomelli em 03/01/2002
*   - Implementada a inserção dos aliens na fase;
*   - Implementação das funçoes VerificarLadrilho e
*     VerificarAlien;
*
*  Diego Giacomelli em 07/01/2002
*   - Alteração do nome do método Colisão para ChecarColisao
*     para adaptar-se aos padrões de nomenclatura;
*
*------------------------------------------------------------*/


#ifndef zeus_h_incluido
#define zeus_h_incluido


#include <stdio.h>
#include <allegro.h>
#include <string.h>
#include "..\erro.h"
#include "..\aliens.h"
#include "..\calien.h"
#include "..\cladrilho.h"
#include "..\cfundo.h"
#include "..\cfase.h"
#include "..\cobjeto.h"
#include "..\cconstrucao.h"
#include "..\ctela.h"
#include "..\clog.h"
#include "imagem.h"

#define MENU_LARGURA				542
#define MENU_ALTURA				10

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
#define LADRILHO_H_FLIP_X				LADRILHO_SEL_DIREITO_X + LADRILHO_LARGURA + 1
#define LADRILHO_H_FLIP_Y				MENU_AUX_Y + 1
#define LADRILHO_V_FLIP_X				LADRILHO_H_FLIP_X + LADRILHO_LARGURA + 1
#define LADRILHO_V_FLIP_Y				MENU_AUX_Y + 1
#define LADRILHO_ROTACAO_X				LADRILHO_V_FLIP_X + LADRILHO_LARGURA + 1
#define LADRILHO_ROTACAO_Y				MENU_AUX_Y + 1

#define LADRILHO_APAGAR_X				LADRILHO_SEL_DIREITO_X + LADRILHO_LARGURA + 1
#define LADRILHO_APAGAR_Y				MENU_AUX_Y + 1

void IniciarZeus(void);
void MontarMenuObj(int modo);
void ExecutarZeus(void);
void DesligarZeus(void);
int NovaFase(void);
int AbrirFase(void);
int SalvarFase(void);
int SalvarComoFase(void);
int FecharFase(void);
int AbrirFundo(void);
int AbrirAliens(void);
int PreencherNulos(void);
int TrocarLadrilhos(void);
int Sair(void);
void DesenharTela(void);
void VerificarLadrilho(void);
void VerificarAlien(void);
void VerificarConstrucao(void);
void DesenharQuadrado(void);
void VerificarRolaTecla(void);
void VerificarRolaMouse(void);
int VerificarMenuArquivo(void);
int VerificarMenuObjetos(void);
int VerificarMenuExibir(void);
int VerificarMenuFerramentas(void);
void VerificarMenuObj(void);
void VerificarMenuAux(void);
void VerificarApagar(void);
#endif