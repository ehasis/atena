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
#include "funcoes.h"

/* Variaveis */
int j;
int scroll_y = 0;
int scroll_y2 = 0;
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
TPowerUp	powerup;
TBala		bala[30], balaalien[30];
TAlien		myalien[30];


void MostrarPerdeu()
{
	char str[40];
	clear(screen);
	textout_centre(screen, font, "Voce morreu!", 320, 200, makecol(255,255,0));
	sprintf(str,"Sua Pontuacao: %d",nave1.getPontos());
	textout_centre(screen, font, str, 320, 220, makecol(255,255,0));
	rest(700);
	clear_keybuf();
	readkey();
	final_jogo = 1;
}

int ChecarColisao(TRect &recta, TRect &rectb)
{
	if (recta.d < rectb.e) return 0;
	if (recta.b < rectb.t) return 0;
	if (recta.e > rectb.d) return 0;
	if (recta.t > rectb.b) return 0;

	return 1;
}

void ChecarImpacto()
{
	register int j;
	int hit=0, hit_bala = 0, hit_powerup=0;

	//Verifica impacto com alien
	for(j=0;j<30;j++)
	{
		if(myalien[j].status == 1
		&& nave1.getStatus() == eNaveNormal
		&& nave1.Colisao(myalien[j].Rect()))
		{
			myalien[j].status=0;
			hit=1;
		}
		
		if (balaalien[j].active
		&& nave1.getStatus() == eNaveNormal
		&& nave1.Colisao(balaalien[j].Rect()))
		{
			balaalien[j].active = 0;
			hit_bala = 1;
		}
	}

	//Verifica impacto com powerup
	if(powerup.status
	&& nave1.getStatus() == eNaveNormal
	&& nave1.Colisao(powerup.Rect()))
	{
		hit_powerup = 1;
	}
	

	if(hit)
	{
		if (nave1.getEnergia() <= 0)
			nave1.somCasco(-50);
		else
			if (nave1.getEnergia() < 50)
			{
				nave1.somCasco(nave1.getEnergia() - 50);
				nave1.setEnergia(0);
			}
			else
				nave1.somEnergia(-50);

		
		nave1.somPontos(1);
		nave1.setStatus(eNaveEscudo);
		num_aliens--;
	}
	if (hit_bala)
	{
		if (nave1.getEnergia() <= 0)
			nave1.somCasco(-25);
		else
			if (nave1.getEnergia() < 25)
			{
				nave1.somCasco(nave1.getEnergia() - 25);
				nave1.setEnergia(0);
			}
			else
				nave1.somEnergia(-25);
		nave1.setStatus(eNaveEscudo);
	}

	if(hit_powerup)
	{
		if(powerup.status==1)
		{
			//nave1.incV(4);
			if (nave1.getEnergia() > 50)
				nave1.setEnergia(100);
			else
				nave1.somEnergia(50);
		}
		powerup.status=0;
	}
}

void ChecarMorteAlien()
{
	register int i,j;
	
	for(i = 0; i < 30; i++)
	{
		for(j = 0; j < 30; j++)
		{
			if (bala[i].active
			&& myalien[j].status == 1
			&& ChecarColisao(bala[i].Rect(), myalien[j].Rect()))
			{
				bala[i].active = 0;
				myalien[j].hit_points--;
				if (myalien[j].hit_points <= 0)
				{
					play_sample((SAMPLE *)data[WAV_EXPLOSAO1].dat, 255, 128, 1000, 0);
					myalien[j].status = 2;
					myalien[j].time = 25;
					nave1.somPontos(1);
				}
			}
		}
	}
}

void Atirar(int x, int y)
{
	static int atirar = 0;

	if(num_balas == 29)
		num_balas = 0;

	bala[num_balas].x = x - 10;
	bala[num_balas].y = y + 10;
	bala[num_balas].a = 20;
	bala[num_balas].l = 20;
	bala[num_balas].active = 1;
	num_balas++;
	
	atirar++;
	if (atirar >= 3)
	{
		atirar = 0;
		play_sample((SAMPLE *)data[WAV_TIRO1].dat, 160, 128, 1000, 0);
	}
}

void AtirarAlien(int x, int y)
{
	//static int atirar = 0;

	int nx = nave1.getX();


	if(num_balasalien == 29)
		num_balasalien = 0;


	balaalien[num_balas].x = x + 20;
	balaalien[num_balas].y = y + 23;
	balaalien[num_balas].a = 20;
	balaalien[num_balas].l = 20;
	
	if (nx > x + 10)
		balaalien[num_balas].vx = 7;
	if (nx <= x + 10 && nx >= x - 10)
		balaalien[num_balas].vx = 0;
	if (nx < x - 10)
		balaalien[num_balas].vx = -7;

	balaalien[num_balas].vy = 10;
	balaalien[num_balas].active = 1;
	num_balasalien++;
	
	//atirar++;
	//if (atirar >= 2)
	//{
	//	atirar = 0;
	//	play_sample((SAMPLE *)data[WAV_TIRO1].dat, 160, 128, 1000, 0);
	//}
}

void CriarAlien(int type)
{
	static int alien_atual;
	num_aliens++;
	
	if(alien_atual == 29)
		alien_atual = 0;
	
	myalien[alien_atual].x = rand()%600;
	myalien[alien_atual].y = rand()%420 - 480;
	myalien[alien_atual].l = 50;
	myalien[alien_atual].a = 50;
	myalien[alien_atual].type = type;
	
	if(type == 0)
		myalien[alien_atual].hit_points = 5;

	myalien[alien_atual].status = 1;
	alien_atual++;
}

void CriarPowerUp()
{
	powerup.x = rand()%590;
	powerup.y = -50;
	powerup.a = 50;
	powerup.l = 50;
	powerup.status = 1;	
}

/***********************************************************/
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
	set_pallete((RGB *)data[PALETA_JOGO].dat);

	text_mode(-1);
	clear_keybuf();
	
	play_midi((MIDI *)data[MID_FUNDO1].dat, 1);
	nave1.setDataFile(load_datafile("nave.dat"));
}

//------------------------------------------------------------
//montagem da barra de status
void AtualizarStatus()
{
	masked_blit((BITMAP *)data[PAINEL].dat,buffer,0,0,0,0,200,50);
	
	sprintf(str,"Mortes : %d   ", nave1.getPontos());
	
	escrever(buffer, str, 5, 5, makecol(255,255,255));
	escrever(buffer, "Casco  :", 5, 15, makecol(255,255,255));
	escrever(buffer, "Energia:", 5, 25, makecol(255,255,255));
	
	barra_progresso(buffer, 70, 25, 100, nave1.getEnergia());
	barra_progresso(buffer, 70, 15, 100, nave1.getCasco());
}


//------------------------------------------------------------
void AtualizarObjetos()
{
	if(num_aliens < max_aliens)
		CriarAlien(0);
	
	/* fundo */
	blit((BITMAP *)data[SOL].dat,buffer, 0, 0, 0, 0,640, 480);
	masked_blit((BITMAP *)data[ESTRELAS1].dat,buffer, 0, 0, 0, scroll_y2 - 480,640, 480);
	masked_blit((BITMAP *)data[ESTRELAS1].dat,buffer, 0, 0, 0, scroll_y2,      640, 480);
	masked_blit((BITMAP *)data[ESTRELAS2].dat,buffer, 0, 0, 0, scroll_y  - 480,640, 480);
	masked_blit((BITMAP *)data[ESTRELAS2].dat,buffer, 0, 0, 0, scroll_y,       640, 480);

	scroll_y2 += 1;
	scroll_y  += 2;

	if(scroll_y  == 480) scroll_y  = 0;
	if(scroll_y2 == 480) scroll_y2 = 0;


	/* atualiza dados da nave */
	nave1.Atualizar(entrada1);
	
	ChecarMorteAlien();
	ChecarImpacto();

	/* verifica se pode atirar */
	if (nave1.Atirar() && tempo_prox_tiro >= 2)
	{
		Atirar(nave1.getX() + (nave1.getL() / 2), nave1.getY());
		tempo_prox_tiro = 0;
	}
	tempo_prox_tiro++;

	/* verifica se o casco foi destruido */
	if (nave1.getCasco() <= 0) MostrarPerdeu();


	for(j = 0; j < 30; j++)
	{
		bala[j].y -= 25;
		balaalien[j].y += balaalien[j].vy;
		balaalien[j].x += balaalien[j].vx;

		
		if (myalien[j].status == 1
		&& myalien[j].y >= 60
		&& myalien[j].y <= 65)
			AtirarAlien(myalien[j].x, myalien[j].y);
		
		if(bala[j].y < -10)
			bala[j].active = 0;

		if(bala[j].active)
			masked_blit((BITMAP *)data[TIRO].dat,buffer,0,0,bala[j].x,bala[j].y,20,20);

		if(balaalien[j].y > 480)
			balaalien[j].active = 0;

		if(balaalien[j].active)
			masked_blit((BITMAP *)data[TIROALIEN].dat,buffer,0,0,balaalien[j].x,balaalien[j].y,10,10);

		if(myalien[j].status == 1)
			masked_blit((BITMAP *)data[ALIEN].dat,buffer,0,0,myalien[j].x,myalien[j].y,50,50);
		
		if(myalien[j].status == 2)
		{
			masked_blit((BITMAP *)data[EXPLOSAO1].dat, buffer, 
				250-(((myalien[j].time*2) - ((myalien[j].time*2)%10))*5),
				0, myalien[j].x, myalien[j].y, 50, 50);
		}
		
		if(myalien[j].time > 0) myalien[j].time--;
		
		if(myalien[j].time <= 0 && myalien[j].status == 2)
		{
			myalien[j].status = 0;
			num_aliens--;
		}
		
		if(myalien[j].status)
		{
			if (nave1.getPontos() > 50) myalien[j].y += 2;
			if (nave1.getPontos() > 100) myalien[j].y += 2;
			myalien[j].y += 3;
		}
		if(myalien[j].x < -50 && myalien[j].status == 1)
		{
			num_aliens--;
			myalien[j].status = 0;
		}
	}
		
	tempo_prox_powerup--;
	
	if(tempo_prox_powerup == 0)
	{
		tempo_prox_powerup=(rand()%500) + 600;
		CriarPowerUp();
	}
	
	if(powerup.status) powerup.y += 3;
	
	if(powerup.status == 1)
		masked_blit((BITMAP *)data[HEAL].dat,buffer,0,0,powerup.x,powerup.y,50,50);

	if (nave1.getPontos() > 100) tempo_prox_alien +=2;
	tempo_prox_alien++;
	
	if(tempo_prox_alien >= 100)
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
	//fundo.Desenhar(buffer);
	nave1.Desenhar(buffer);
	//nave2.Desenhar(buffer);
	//for (int i=0; i < 30; i++)
	//{
	//	bala[i].Desenhar(buffer);
	//	balaalien[i].Desenhar(buffer);
	//	aliens[i].Desenhar(buffer);
	//}
	//status.Desenhar(buffer);
	AtualizarStatus();
	blit(buffer, bmp, 0, 0, 0, 0, 640, 480);
}

//------------------------------------------------------------
// destroi os objetos
void DesligarObjetos()
{
	stop_midi();
	destroy_bitmap(buffer);
	nave1.Desligar();
	//nave2.Desligar();
	//for (int i=0; i < 30; i++)
	//{
	//	bala[i].Desligar();
	//	balaalien[i].Desligar();
	//	aliens[i].Desligar();
	//}
}