 /*------------------------------------------------------------*
 *  jogo.cpp - Rotinas basicas do jogo
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: terça-feira, 04 de setembro de 2001
*
*  Contem a execucao das funcoes de inicializacao
*  relacionadas ao jogo.
*
*  Henrique em 31/10/2001
*   - Adicionado rotina para mostrar menu e novos laços
*
*  Henrique em 23/01/2002
*   - Retirado arquivo "entrada.h", pois se tornou obsoleto
*------------------------------------------------------------*/

#include <allegro.h>

#include "jogo.h"
#include "graficos.h"
#include "nucleo.h"
#include "vglobal.h"
#include "abertura.h"
#include "atena.h"
#include "cmenu.h"

/*************************************************************/

int final_jogo;
int final_partida;
int final_fase;

//Henrique em 31/10/2001
static void MostrarMenuPrincipal()
{
	int sair = 0;
	DATAFILE *data = load_datafile("atena.dat");

	blit((BITMAP *)data[ABERTURA].dat, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

	CMenuH m((FONT *)data[BANKGOTIC].dat, makecol(0,0,255), makecol(255,255,0));
	m.Adicionar("Iniciar");
	m.Adicionar("Configurar");
	m.Adicionar("Sair");
	
	while (!sair)
	{
		switch (m.Executar())
		{
		case 0:
			final_jogo	  = 0;
			final_partida = 0;
			final_fase	  = 0;
			sair		  = 1;
			break;
		case 1:
			break;
		case 2:
			final_jogo = 1;
			sair       = 1;
			break;
		}
	}

	//unload_datafile(data);
}

// Inicializacao do Jogo
void IniciarJogo()
{
	final_jogo = 0;
	if (get_config_int("jogo", "abertura", 1))
		MostrarAbertura();
}

// Desligamento do Jogo
void DesligarJogo()
{
}

static void IniciarFase()
{
	final_partida = 0;
	final_fase = 0;

	IniciarGraficos();
	IniciarObjetos();
}

static void ExecutarFase()
{
	
	while(!final_fase && !final_jogo)
	{
		if (key[KEY_ESC])
			final_fase = TRUE;

		AtualizarObjetos();
		AtualizarGraficos();
	}
}

static void DesligarFase()
{
	DesligarObjetos();
	DesligarGraficos();
}

// Laco Principal
void ExecutarJogo()
{
	while(!final_jogo)
	{
		MostrarMenuPrincipal();
		if (!final_fase && !final_jogo)
		{
			IniciarFase();
			ExecutarFase();
			DesligarFase();
		}
	}
}