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
	clear(screen);
	textout_centre(screen, font, "Voce morreu!", 320, 200, makecol(255,255,0));
	sprintf(str,"Sua Pontuacao: %d",nave1.GetPontos());
	textout_centre(screen, font, str, 320, 220, makecol(255,255,0));
	rest(700);
	clear_keybuf();
	readkey();
	final_jogo = 1;
}

//------------------------------------------------------------
void ChecarImpacto()
{
	register int j;
	int hit=0, hit_bala = 0, hit_powerup=0;

	//Verifica impacto com alien
	for (j = 0; j < 30; j++)
	{
		if(alien[j].GetStatus() == eAlienNormal
		&& nave1.GetStatus() == eNaveNormal
		&& nave1.Colisao(alien[j].Rect()))
		{
			alien[j].SetStatus(eAlienInativo);
			hit = 1;
		}

		if (balaalien[j].ativa
		&& nave1.GetStatus() == eNaveNormal
		&& nave1.Colisao(balaalien[j].Rect()))
		{
			balaalien[j].ativa = 0;
			hit_bala = 1;
		}
	}

	//Verifica impacto com powerup
	if (powerup.status
	&& nave1.GetStatus() == eNaveNormal
	&& nave1.Colisao(powerup.Rect()))
	{
		powerup.status = 0;
		hit_powerup = 1;
	}
	

	if(hit)
	{
		if (nave1.GetEnergia() < 50)
		{
			nave1.IncCasco(nave1.GetEnergia() - 50);
			nave1.SetEnergia(0);
		}
		else
			nave1.IncEnergia(-50);
		
		nave1.IncPontos(1);
		nave1.SetStatus(eNaveEscudo);
		num_aliens--;
	}
	
	if (hit_bala)
	{
		if (nave1.GetEnergia() < 25)
		{
			nave1.IncCasco(nave1.GetEnergia() - 25);
			nave1.SetEnergia(0);
		}
		else
			nave1.IncEnergia(-25);

		nave1.SetStatus(eNaveEscudo);
	}

	if(hit_powerup)
	{
		if (nave1.GetEnergia() > 50)
			nave1.SetEnergia(100);
		else
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

	int nx = nave1.GetX();

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

	alien[alien_atual].SetStatus(eAlienNormal);
	alien[alien_atual].SetX(rand()%600);
	alien[alien_atual].SetY(rand()%420 - 480);
	alien[alien_atual].SetL(50);
	alien[alien_atual].SetA(50);
	alien[alien_atual].SetTipo(tipo);
	alien[alien_atual].SetEnergia(5 * tipo);

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
	fundo.SetArquivoDat(load_datafile("atena.dat"));
	nave1.SetArquivoDat(load_datafile("nave.dat"));
	for (int i = 0; i < 30; i++)
	{
		alien[i].SetArquivoDat(load_datafile("alien.dat"));
		alien[i].SetStatus(eAlienInativo);
	}
}

//------------------------------------------------------------
//montagem da barra de status
void AtualizarStatus(BITMAP *bmp)
{
	masked_blit((BITMAP *)data[PAINEL].dat, bmp, 0, 0, 0, 0, 200, 50);

	sprintf(str,"Mortes : %d     ", nave1.GetPontos());

	escrever(bmp, str,        5,  5, makecol(255,255,255));
	escrever(bmp, "Casco  :", 5, 15, makecol(255,255,255));
	escrever(bmp, "Energia:", 5, 25, makecol(255,255,255));

	barra_progresso(bmp, 70, 25, 100, nave1.GetEnergia());
	barra_progresso(bmp, 70, 15, 100, nave1.GetCasco());
}

//------------------------------------------------------------
void AtualizarObjetos()
{
	if(num_aliens < max_aliens)
		CriarAlien(1);
	
	//fundo	
	clear_to_color(buffer, makecol(255,0,255));
	fundo.Atualizar();

	//atualiza dados da nave
	nave1.Atualizar(entrada1);
	
	//verifica se pode atirar
	if (nave1.Atirar() && tempo_prox_tiro >= 2)
	{
		Atirar(nave1.GetX() + (nave1.GetL() / 2), nave1.GetY());
		tempo_prox_tiro = 0;
	}
	tempo_prox_tiro++;

	//verifica se o casco foi destruido
	if (nave1.GetCasco() <= 0) MostrarPerdeu();

	for (j = 0; j < 30; j++)
	{
		
		if (alien[j].GetStatus() == eAlienNormal
		&&  alien[j].GetY() >= 60
		&&  alien[j].GetY() <  63)
		{
			AtirarAlien(alien[j].GetX(), alien[j].GetY());
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
			for (register int i = 0; i < 30; i++)
			{
				if (bala[j].ativa
				&& alien[i].GetStatus() == eAlienNormal
				&& alien[i].Colisao(bala[j].Rect()))
				{
					bala[j].ativa = 0;
					alien[i].IncEnergia(-1);
					//alien[i].SetStatus(eAlienEscudo);
					if (alien[i].GetEnergia() <= 0)
					{
						play_sample((SAMPLE *)data[WAV_EXPLOSAO1].dat, 255, 128, 1000, 0);
						alien[i].SetStatus(eAlienExplosao);
						alien[i].SetTempo(25);
						nave1.IncPontos(1);
					}
					break;
				}
			}
		}
	
		//Alien		
		if (alien[j].GetStatus() != eAlienInativo)
		{
			alien[j].Atualizar();
			if (alien[j].GetStatus() != eAlienInativo)
			{
				if (nave1.GetPontos() >  50) alien[j].IncY(2);
				if (nave1.GetPontos() > 100) alien[j].IncY(2);
				alien[j].IncY(3);
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
	if (nave1.GetPontos() > 100) tempo_prox_alien +=2;
	
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
	fundo.Desenhar(bmp);
	masked_blit(buffer, bmp, 0, 0, 0, 0, 640, 480);
	for (register int i = 0; i < 30; i++)
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