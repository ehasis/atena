 /*------------------------------------------------------------*
 *  nucleo.cpp - Nucleo Principal do Jogo
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quarta-feira, 5 de setembro de 2001
*
*
*
*------------------------------------------------------------*/

#include <math.h>
#include <allegro.h>
#include "nucleo.h"
#include "objgraf.h"
#include "vglobal.h"

#include "stdio.h"
#include "stdlib.h"
#include "atena.h"
#include "string.h"
#include "cnave.h"
#include "cfundo.h"
#include "funcoes.h"
#include "cfase.h"

// Variaveis
int velocidade_jogo = 0;

char		str[50];
DATAFILE	*data;
SAMPLE		*wav_fundo;

// Objetos
CFase		fase;


//------------------------------------------------------------
// Finalizacao do jogo (preliminar)
void MostrarPerdeu()
{
	char str[40];

	textout_centre(screen, font, "Voce morreu!", 320, 200, makecol(255,255,0));
	sprintf(str,"Sua Pontuacao: %d", fase.ObterNave().ObterPontos());
	textout_centre(screen, font, str, 320, 220, makecol(255,255,0));
	rest(700);
	clear_keybuf();
	readkey();
	final_jogo = TRUE;
}


//------------------------------------------------------------
void IniciarObjetos()
{
	char arquivo_selecionado[256], caminho[256];
	int nome_comprimento;

	srand(1);

	velocidade_jogo = get_config_int("jogo", "velocidade", 0);

	data = load_datafile("atena.dat");

	text_mode(-1);
	clear_keybuf();


	//Objetos
	// Código provisório para selecionar as fases
	show_mouse(screen);
	position_mouse(320, 240);
	get_executable_name(arquivo_selecionado, sizeof(arquivo_selecionado));
	nome_comprimento = strlen(arquivo_selecionado);
	strncpy(caminho, arquivo_selecionado, nome_comprimento - 8);
	strcpy(caminho, "fases//");
	strcpy(arquivo_selecionado, caminho);

	if((file_select_ex("Selecione o arquivo do mapa:", arquivo_selecionado, "map", sizeof(arquivo_selecionado), 400, 300)) != NULL)
	{
		//unscare_mouse();
		strcat(caminho, get_filename(arquivo_selecionado));
		show_mouse(NULL);
		textout_centre(screen, font, "aguarde, carregando mapa...", SCREEN_W/2, SCREEN_H/2, makecol(255,255,0));
		fase.Iniciar(caminho, 0, 0, 640, 480);
	}
	else
	{
		return;
	}

	if (get_config_int("som", "musica", 1) == 1)
	{
		play_midi((MIDI *)data[MID_FUNDO1].dat, 1);
		//wav_fundo = load_sample("fases//fundo.wav");
		//play_sample(wav_fundo, 50, 128, 1000, 1);
	}
}

//------------------------------------------------------------
//montagem da barra de status
void AtualizarStatus(CTela &_tela)
{
	//draw_trans_sprite(bmp, (BITMAP *)data[PAINEL].dat, 0, 460);
	_tela.DrawTransSprite(eCamadaEfeitos, (BITMAP *)data[PAINEL].dat, 0, 460);

	sprintf(str,"P: %d     ", fase.ObterNave().ObterPontos());
	_tela.Escrever(str, 5, 465, makecol(255,255,255));

	_tela.Escrever("F/E", 110, 465, makecol(255,255,255));

	barra_progresso_atena2(_tela, 140, 464, 100, fase.ObterNave().ObterCasco());
	barra_progresso_atena2(_tela, 140, 470, 100, fase.ObterNave().ObterEnergia());

}

//------------------------------------------------------------
void AtualizarObjetos()
{
	if(!fase.Atualizar(1))
	{
		MostrarPerdeu();
	}

	//Quebra galho ate implementar um regulador
	if (velocidade_jogo > 0) rest(velocidade_jogo);
}

//------------------------------------------------------------
// desenha os objetos no bitmap da tela
void DesenharObjetos(CTela &_tela)
{
	fase.Desenhar(_tela);
	fase.Sonorizar();
	AtualizarStatus(_tela);
}

//------------------------------------------------------------
// destroi os objetos
void DesligarObjetos()
{
	stop_midi();
	unload_datafile(data);
	//destroy_sample(wav_fundo);
	fase.Desligar();
}