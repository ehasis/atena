 /*------------------------------------------------------------*
 *  nucleo.cpp - Nucleo Principal do Jogo
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quarta-feira, 5 de setembro de 2001
*
*  19/09/2001
*  - Implementada classe CNave
*
*------------------------------------------------------------*/

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

/* Variaveis */
int j;
int tempo_prox_tiro = 0;
int tempo_prox_alien = 0;
int tempo_prox_powerup = 700;
int velocidade_jogo = 0;
int max_aliens;
int num_aliens;
int num_balas;
int num_balasalien;

char		str[50];
BITMAP		*buffer;
DATAFILE	*data;

/* Objetos */
CNave		nave1;
CAlien		alien[30];
CFundo		fundo;

TPowerUp	powerup;
TBala		bala[30];
TBala		balaalien[30];


//------------------------------------------------------------
// Finalizacao do jogo (preliminar)
void MostrarPerdeu()
{
	char str[40];
	//clear(screen);
	textout_centre(screen, font, "Voce morreu!", 320, 200, makecol(255,255,0));
	sprintf(str,"Sua Pontuacao: %d",nave1.pontos);
	textout_centre(screen, font, str, 320, 220, makecol(255,255,0));
	rest(700);
	clear_keybuf();
	readkey();
	final_jogo = 1;
}

//------------------------------------------------------------
void ChecarImpacto()
{
	//Verifica impacto com alien ou bala do alien
	for (register int j = 0; j < 30; j++)
	{
		if(alien[j].status == eAlienNormal
		&& nave1.status == eNaveNormal
		&& nave1.Colisao(alien[j].Rect()))
		{
			alien[j].status = eAlienInativo;
			num_aliens--;
			nave1.DecEnergia(50);
			nave1.status = eNaveEscudo;
			nave1.pontos++;
		}

		if (balaalien[j].ativa
		&& nave1.status == eNaveNormal
		&& nave1.Colisao(balaalien[j].Rect()))
		{
			balaalien[j].ativa = 0;
			nave1.DecEnergia(25);
		}
	}

	//Verifica impacto com powerup
	if (powerup.status
	&& nave1.status == eNaveNormal
	&& nave1.Colisao(powerup.Rect()))
	{
		powerup.status = 0;
		nave1.IncEnergia(50);
	}
}

//------------------------------------------------------------
void Atirar(int x, int y)
{
	static int atirar = 0;

	if(num_balas == 29)
		num_balas = 0;

	bala[num_balas].x = x - 10;
	bala[num_balas].y = y + 10;
	bala[num_balas].a = 20;
	bala[num_balas].l = 20;
	bala[num_balas].ativa = 1;
	num_balas++;
	
	atirar++;
	if (atirar >= 3)
	{
		atirar = 0;
		stop_sample((SAMPLE *)data[WAV_TIRO1].dat);
		play_sample((SAMPLE *)data[WAV_TIRO1].dat, 160, 128, 1000, 0);
	}
}

//------------------------------------------------------------
void AtirarAlien(int x, int y)
{
	//static int atirar = 0;

	int nx = nave1.x;

	if(num_balasalien == 29)
		num_balasalien = 0;


	balaalien[num_balasalien].x = x + 20;
	balaalien[num_balasalien].y = y + 23;
	balaalien[num_balasalien].a = 20;
	balaalien[num_balasalien].l = 20;
	
	if (nx > x + 10)
		balaalien[num_balasalien].vx = 7;
	if (nx <= x + 10 && nx >= x - 10)
		balaalien[num_balasalien].vx = 0;
	if (nx < x - 10)
		balaalien[num_balasalien].vx = -7;

	balaalien[num_balasalien].vy = 10;
	balaalien[num_balasalien].ativa = 1;
	num_balasalien++;
	
	//atirar++;
	//if (atirar >= 2)
	//{
	//	atirar = 0;
	//	stop_sample((SAMPLE *)data[WAV_TIRO1].dat);
	//	play_sample((SAMPLE *)data[WAV_TIRO1].dat, 160, 128, 1000, 0);
	//}
}

//------------------------------------------------------------
void CriarAlien(int tipo)
{
	static int alien_atual = 0;
	num_aliens++;
	
	if(alien_atual == 29) alien_atual = 0;

	alien[alien_atual].status = eAlienNormal;
	alien[alien_atual].x = rand()%600;
	alien[alien_atual].y = rand()%420 - 480;
	alien[alien_atual].l = 50;
	alien[alien_atual].a = 50;
	alien[alien_atual].tipo = tipo;
	alien[alien_atual].energia = 5 * tipo;

	alien_atual++;
}

//------------------------------------------------------------
void CriarPowerUp()
{
	powerup.x = rand()%590;
	powerup.y = -50;
	powerup.a = 50;
	powerup.l = 50;
	powerup.status = 1;	
}

//------------------------------------------------------------
void IniciarObjetos()
{	
	//struct time t;
	//gettime(&t);
	//srand(t.ti_sec);
	srand(1);

	max_aliens		= 8;
	powerup.status	= 0;
	
	num_balas		= 0;
	num_balasalien  = 0;
	num_aliens		= 0;
	velocidade_jogo = get_config_int("jogo", "velocidade", 0);

	data = load_datafile("atena.dat");
	buffer = create_bitmap(640, 480);
	clear(buffer);
	
	text_mode(-1);
	clear_keybuf();
	
	play_midi((MIDI *)data[MID_FUNDO1].dat, 1);
	
	//Objetos
	fundo.Iniciar();
	nave1.SetArquivoDat(load_datafile("nave.dat"));
	for (int i = 0; i < 30; i++)
	{
		alien[i].SetArquivoDat(load_datafile("alien.dat"));
		alien[i].status = eAlienInativo;
	}
}

//------------------------------------------------------------
//montagem da barra de status
void AtualizarStatus(BITMAP *bmp)
{
	draw_trans_sprite(bmp, (BITMAP *)data[PAINEL].dat, 0, 0);

	sprintf(str,"Mortes : %d     ", nave1.pontos);

	escrever(bmp, str,        5,  5, makecol(255,255,255));
	escrever(bmp, "Casco  :", 5, 15, makecol(255,255,255));
	escrever(bmp, "Energia:", 5, 25, makecol(255,255,255));

	barra_progresso(bmp, 70, 25, 100, nave1.energia);
	barra_progresso(bmp, 70, 15, 100, nave1.casco);
}

//------------------------------------------------------------
void AtualizarObjetos()
{
	register int i;

	if(num_aliens < max_aliens)
		CriarAlien(1);
	
	//fundo	
	clear_to_color(buffer, makecol(255,0,255));
	fundo.Atualizar();

	//atualiza dados da nave
	nave1.Atualizar(entrada1);
	
	//verifica se pode atirar
	if (nave1.atirar && tempo_prox_tiro >= 2)
	{
		Atirar(nave1.x + (nave1.l / 2), nave1.y);
		tempo_prox_tiro = 0;
	}
	tempo_prox_tiro++;

	//verifica se o casco foi destruido
	if (nave1.casco <= 0) MostrarPerdeu();

	for (j = 0; j < 30; j++)
	{
		
		if (alien[j].status == eAlienNormal
		&&  alien[j].y >= 60
		&&  alien[j].y <  63)
		{
			AtirarAlien(alien[j].x, alien[j].y);
		}

		//Bala
		bala[j].y -= 25;
		balaalien[j].y += balaalien[j].vy;
		balaalien[j].x += balaalien[j].vx;
		
		if (bala[j].y < -10)
			bala[j].ativa = 0;

		if (bala[j].ativa)
			masked_blit((BITMAP *)data[TIRO].dat,buffer,0,0,bala[j].x,bala[j].y,20,20);

		if (balaalien[j].y > 480)
			balaalien[j].ativa = 0;

		if (balaalien[j].ativa)
			masked_blit((BITMAP *)data[TIROALIEN].dat,buffer,0,0,balaalien[j].x,balaalien[j].y,10,10);

		//Impacto e morte com o Alien
		if (bala[j].ativa)
		{
			for (i = 0; i < 30; i++)
			{
				if (bala[j].ativa
				&& alien[i].status == eAlienNormal
				&& alien[i].Colisao(bala[j].Rect()))
				{
					bala[j].ativa = 0;
					alien[i].energia--;
					if (alien[i].energia <= 0)
					{
						play_sample((SAMPLE *)data[WAV_EXPLOSAO1].dat, 255, 128, 1000, 0);
						alien[i].status = eAlienExplosao;
						alien[i].tempo = 25;
						nave1.pontos++;
					}
					break;
				}
			}
		}
	
		//Alien		
		if (alien[j].status != eAlienInativo)
		{
			alien[j].Atualizar();
			if (alien[j].status != eAlienInativo)
			{
				if (nave1.pontos >  50) alien[j].y += 2;
				if (nave1.pontos > 100) alien[j].y += 2;
				alien[j].y += 3;
			}
			else
				num_aliens--;
		}
	}

	ChecarImpacto();

	tempo_prox_powerup--;
	if (tempo_prox_powerup == 0)
	{
		tempo_prox_powerup = (rand()%500) + 600;
		CriarPowerUp();
	}
	
	if (powerup.status) powerup.y += 3;
	
	if (powerup.status == 1)
		masked_blit((BITMAP *)data[HEAL].dat,buffer,0,0,powerup.x,powerup.y,50,50);

	tempo_prox_alien++;
	if (nave1.pontos > 100) tempo_prox_alien +=2;
	
	if (tempo_prox_alien >= 100)
	{
		tempo_prox_alien = 0;
		max_aliens++;
	}

	//Quebra galho ate implementar um regulador
	if (velocidade_jogo > 0) rest(velocidade_jogo);
}

//------------------------------------------------------------
// desenha os objetos no bitmap da tela
void DesenharObjetos(BITMAP *bmp)
{
	register int i;

	fundo.Desenhar(bmp);
	masked_blit(buffer, bmp, 0, 0, 0, 0, 640, 480);
	for (i = 0; i < 30; i++)
	{
		alien[i].Desenhar(bmp);
	}
	nave1.Desenhar(bmp);
	AtualizarStatus(bmp);
}

//------------------------------------------------------------
// destroi os objetos
void DesligarObjetos()
{
	stop_midi();
	destroy_bitmap(buffer);
	fundo.Desligar();
	nave1.Desligar();
	for (register int i = 0; i < 30; i++)
	{
		alien[i].Desligar();
	}
}