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

#include <stdio.h>
#include <allegro.h>

#include "jogo.h"
#include "graficos.h"
#include "nucleo.h"
#include "vglobal.h"
#include "abertura.h"
#include "atena.h"
#include "cmenu.h"
#include "cconfig.h"

/*************************************************************/

int final_jogo;
int final_partida;
int final_fase;

static void MostrarMenuConfiguracao()
{
	char	str[80];
	int		valor;

	int sair = 0;
	CMenuH m;
	CConfig cfg("atena.ini");

	m.SetarFonte(font);
	m.SetarCorTexto(makecol(0,0,255));
	m.SetarCorSelecao(makecol(255,255,0));
	m.SetarAlinhamento(eAlinharEsquerda);
	m.SetarX(50);
	m.SetarY(80);
	m.SetarNumeroItens(8);	

	while (!sair)
	{
		sprintf(str, "Abertura     %d", cfg.ObterInt("jogo", "abertura"));
		m.SetarTexto(0, str);

		cfg.SetarSecao("video");
		sprintf(str, "Modo         %d", cfg.ObterInt("modo"));
		m.SetarTexto(1, str);
		sprintf(str, "Resolucao    %d", cfg.ObterInt("resolucao"));
		m.SetarTexto(2, str);
		sprintf(str, "Sincronizar  %d", cfg.ObterInt("vsync"));
		m.SetarTexto(3, str);
		sprintf(str, "Suavizar     %d", cfg.ObterInt("suavizar"));
		m.SetarTexto(4, str);

		cfg.SetarSecao("som");
		sprintf(str, "Musica       %d", cfg.ObterInt("musica"));
		m.SetarTexto(5, str);
		sprintf(str, "Efeitos      %d", cfg.ObterInt("efeitos"));
		m.SetarTexto(6, str);

		sprintf(str, "Sair");
		m.SetarTexto(7, str);

		
		switch (m.Executar())
		{
		case 0:
			valor = !cfg.ObterInt("jogo", "abertura");
			cfg.SetarInt("abertura", valor);
			break;
		
		case 1:
			valor = (cfg.ObterInt("video", "modo") + 1) % 11;
			cfg.SetarInt("modo", valor);
			break;
		
		case 2:
			valor = (cfg.ObterInt("video", "resolucao") + 1) % 3;
			cfg.SetarInt("resolucao", valor);
			break;
		
		case 3:
			valor = !cfg.ObterInt("video", "vsync");
			cfg.SetarInt("vsync", valor);
			break;
		
		case 4:
			valor = !cfg.ObterInt("video", "suavizar");
			cfg.SetarInt("suavizar", valor);
			break;

		case 5:
			valor = !cfg.ObterInt("som", "musica");
			cfg.SetarInt("musica", valor);
			break;

		case 6:
			valor = !cfg.ObterInt("som", "efeitos");
			cfg.SetarInt("efeitos", valor);
			break;

		case 7:
			sair = TRUE;
			break;
		}
	}
}



//Henrique em 31/10/2001
static void MostrarMenuPrincipal()
{
	int sair = 0;
	DATAFILE *data = load_datafile("atena.dat");
	CMenuH m;
	

	blit((BITMAP *)data[ABERTURA].dat, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

	//Propriedades do Menu
	m.SetarFonte((FONT *)data[BANKGOTIC].dat);
	m.SetarCorTexto(makecol(0,0,255));
	m.SetarCorSelecao(makecol(255,255,0));
	m.SetarAlinhamento(eAlinharCentro);
	m.SetarX(SCREEN_W/2);
	m.SetarY(100);

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
			MostrarMenuConfiguracao();
			break;
		case 2:
			final_jogo = 1;
			sair       = 1;
			break;
		}
	}

	unload_datafile(data);
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