 /*------------------------------------------------------------*
 *  objetos.cpp - Manipulacao dos Objetos
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quarta-feira, 5 de setembro de 2001
*
*  
*
*------------------------------------------------------------*/

#include "objetos.h"
#include "objgraf.h"
#include "vglobal.h"

#include "stdio.h"
#include "stdlib.h"
#include "atena.h"
#include "string.h"
#include "cnave.h"

int max_aliens;
int num_aliens;
int num_balas;


CNave nave1;

struct TPowerUp
{
	int x, y;
	int a, l;
	int status;
	TRect Rect()
	{
		TRect ret;
		ret.e = x;
		ret.t = y;
		ret.d = x + l;
		ret.b = y + a;

		return ret;
	}
}powerup;

struct TBala
{
	int x, y;
	int a, l;
	int active;
}bala[30];

struct TAlien
{
	int x, y;
	int a, l;
	int status;
	int type;
	int hit_points;
	int time;
	TRect Rect()
	{
		TRect ret;
		ret.e = x;
		ret.t = y;
		ret.d = x + l;
		ret.b = y + a;

		return ret;
	}
}myalien[30];


int j;
int scroll_y = 0;
int scroll_y2 = 0;
int bla	= 0;
int bla2 = 0;
int tempo_prox_alien = 0;
int tempo_prox_powerup = 700;
char str[50];
BITMAP *buffer,*big_boom;
DATAFILE *data;

void lose()
{
	char str[40];
	clear(screen);
	textout_centre(screen,font,"Voce morreu!",320,200,250);
	sprintf(str,"Sua Pontuacao: %d",nave1.getPontos());
	textout_centre(screen,font,str,320,220,250);
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
	int hit=0,hit_powerup=0;

	for(j=0;j<30;j++)
	{
		if(myalien[j].status
		&& nave1.getStatus() == 1
		&& nave1.Colisao(myalien[j].Rect()))
		{
			myalien[j].status=0;
			hit=1;
		}
		
	}

	
	if(powerup.status
	&& nave1.getStatus() == 1
	&& nave1.Colisao(powerup.Rect()))
	{
		hit_powerup = 1;
	}
	
	if(hit)
	{
		nave1.decEnergia(50);
		nave1.incPontos(1);

		num_aliens--;
		rectfill(screen,0,0,639,479,250);
	}

	if(hit_powerup)
	{
		if(powerup.status==1)
		{
			nave1.incV(4);
			nave1.incEnergia(50);

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
			&& myalien[j].status
			&& bala[i].x >= myalien[j].x
			&& bala[i].y <  myalien[j].y+50
			&& bala[i].y >= myalien[j].y
			&& bala[i].x <  myalien[j].x+50)
			{
				bala[i].active = 0;
				myalien[j].status = 2;
				if(myalien[j].status == 1)
					myalien[j].time = 40;

				nave1.incPontos(1);
			}
		}
	}
}

void Atirar(int x, int y)
{
	if(num_balas == 29)
		num_balas = 0;
	bala[num_balas].x = x + 32;
	bala[num_balas].y = y + 23;
	bala[num_balas].active = 1;
	num_balas++;
}

void CriarAlien(int type)
{
	static int current_alien;
	num_aliens++;
	
	if(current_alien == 29)
		current_alien = 0;
	
	myalien[current_alien].x = rand()%600;
	myalien[current_alien].y = rand()%420 - 480;
	myalien[current_alien].l = 50;
	myalien[current_alien].a = 50;
	myalien[current_alien].type = type;
	
	if(type == 0)
		myalien[current_alien].hit_points = 10;

	myalien[current_alien].status = 1;
	current_alien++;
}

void CriarPowerUp()
{
	powerup.x = rand()%100;
	powerup.y = -20;
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

	max_aliens		= 5;
	powerup.status	= 0;
	
	num_balas		= 0;
	num_aliens		= 0;

	data = load_datafile("atena.dat");
	big_boom = create_bitmap(100,75);
	stretch_blit((BITMAP *)data[BOOM].dat, big_boom, 0, 0, 50, 50, 0, 0, 100, 75);
	buffer = create_bitmap(640, 480);
	set_pallete((RGB *)data[PALETA_JOGO].dat);

	text_mode(-1);
	clear_keybuf();
	
	nave1.setDataFile(load_datafile("nave.dat"));
}

//------------------------------------------------------------
void DesligarObjetos()
{
	nave1.Desligar();
	destroy_bitmap(buffer);
	destroy_bitmap(big_boom);
}

//------------------------------------------------------------
void AtualizarObjetos()
{
	if(num_aliens < max_aliens)
		CriarAlien(0);
	
	/* fundo */
	blit((BITMAP *)data[SOL].dat,buffer, 0, 0, 0, 0,640, 480);
	masked_blit((BITMAP *)data[ESTRELAS2].dat,buffer, 0, 0, 0, scroll_y2 - 480,640, 480);
	masked_blit((BITMAP *)data[ESTRELAS2].dat,buffer, 0, 0, 0, scroll_y2,      640, 480);
	masked_blit((BITMAP *)data[NUVENS].dat,buffer, 0, 0, 0, scroll_y - 480,640, 480);
	masked_blit((BITMAP *)data[NUVENS].dat,buffer, 0, 0, 0, scroll_y,      640, 480);
	
	ChecarMorteAlien();
	ChecarImpacto();

	/* atualiza dados da nave */
	nave1.Atualizar(entrada1);

	/* se havia morrido, reinicia os aliens */
	if (nave1.getStatus() == 3 && nave1.getTempo() <= 0)
	{
		for(j = 0; j < 30; j++) 
			myalien[j].status=0;
	}

	/* verifica se pode atirar */
	if (nave1.Atirar() && bla2 >= 2)
	{
		Atirar(nave1.getX(), nave1.getY());
		bla2 = 0;
	}
	
	/* verifica se acabou as vidas */
	if (nave1.getVidas() == 0)
	{
		lose();
	}


	bla++;
	bla2++;

	scroll_y2 += 1;
	scroll_y  += 2;

	for(j = 0; j < 30; j++)
	{
		bala[j].y -= 20;

		if(bala[j].y < 0)
			bala[j].active = 0;

		if(bala[j].active)
			line(buffer, bala[j].x, bala[j].y, bala[j].x,bala[j].y + 4,250);
		
		if(myalien[j].status == 1)
			masked_blit((BITMAP *)data[ALIEN].dat,buffer,0,0,myalien[j].x,myalien[j].y,50,50);
		
		if(myalien[j].status == 2)
			masked_blit((BITMAP *)data[BOOM].dat,buffer,0,0,myalien[j].x,myalien[j].y,50,50);
		
		if(myalien[j].time > -10)
			myalien[j].time--;
		
		if(myalien[j].time == 0 && myalien[j].status == 2)
		{
			myalien[j].status=0;
			num_aliens--;
		}
		if(myalien[j].status) myalien[j].y += 3;
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
	
	if(powerup.status)
		powerup.y += 3;
	
	if(powerup.status == 1)
		masked_blit((BITMAP *)data[HEAL].dat,buffer,0,0,powerup.x,powerup.y,50,50);

	tempo_prox_alien++;
	
	if(tempo_prox_alien >= 100)
	{
		tempo_prox_alien = 0;
		max_aliens++;
	}

	sprintf(str,"Mortes: %d   ", nave1.getPontos());
	textout(buffer,font,str,5,15,250);
	sprintf(str,"Vidas: %d",nave1.getVidas());
	textout(buffer,font,str,5,460,250);
	sprintf(str,"Energia: %d",nave1.getEnergia());
	textout(buffer,font,str,5,470,250);

	if(scroll_y == 480)
		scroll_y = 0;
	
	if(scroll_y2 == 480)
		scroll_y2 = 0;

}

void DesenharObjetos(BITMAP *bmp)
{
	nave1.Desenhar(buffer);
	blit(buffer, bmp, 0, 0, 0, 0, 640, 480);
}