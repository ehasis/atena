 /*------------------------------------------------------------*
 *  graficos.cpp - Motor Grafico
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quarta-feira, 5 de setembro de 2001
*
*  Henrique em 22/01/2002
*   - Modificado AtualizarGraficos() para utilizar stretch
*     se a resolucao nao for 640x480
*
*  Henrique em 01/02/2002
*   - Incluido utilizar_suavizar para controloar a utilizacao
*     da rotina SuavizarBitmap() 
*
*  Henrique em 08/02/2002
*   - Adicionado Console (Log) para exibir na tela
*
*------------------------------------------------------------*/

#include <allegro.h>
#include "graficos.h"
#include "objgraf.h"
#include "funcoes.h"
#include "clog.h"
#include "erro.h"
#include "nucleo.h"

#define LARGURA_TELA    640
#define ALTURA_TELA     480

static CTela tela_principal;

// Inicializacao das rotinas graficas
void IniciarGraficos()
{
	set_trans_blender(0, 0, 0, 96);
	clear(screen);
    
	tela_principal.Iniciar();

	// Arquivo de configuracao
	tela_principal.SetarVsync(get_config_int("video", "vsyc", 1));
	tela_principal.SetarSuavizar(get_config_int("video", "suavizar", 0));
}

// Destruicao dos objetos Graficos
void DesligarGraficos()
{
	//Destruicao do motor
	tela_principal.Desligar();
}

// Atualizacao dos Graficos
void AtualizarGraficos()
{
	DesenharObjetos(tela_principal);
	tela_principal.Atualizar();

/*
	if (key[KEY_L]) CLog::SetarVisivel(TRUE);
	if (key[KEY_K]) CLog::SetarVisivel(FALSE);

	if (CLog::Visivel())
	{
		CLog::Desenhar(bmp_buffer);
	}
/**/

}
