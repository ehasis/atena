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

int max_aliens;
int num_aliens;
int num_balas;

struct TRect
{
	int e, t;
	int d, b;
};

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

struct TNave
{
	int x, y;
	int a, l;
	int status;
	int time;
	int kills, escaped, lives;
	int health;
	TRect Rect()
	{
		TRect ret;
		ret.e = x;
		ret.t = y;
		ret.d = x + l;
		ret.b = y + a;

		return ret;
	}
}nave;


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
	sprintf(str,"Sua Pontuacao: %d",nave.kills-nave.escaped/2+max_aliens*2);
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
		&& nave.status==1
		&& ChecarColisao(nave.Rect(), myalien[j].Rect()))
		{
			myalien[j].status=0;
			hit=1;
		}
		
		if(powerup.status && nave.status==1 && nave.x+100>=powerup.x && nave.y+40<powerup.y+50 && nave.y+40>=powerup.y  && nave.x+100<powerup.x+50)
			hit_powerup=1;
		
		if(powerup.status && nave.status==1 && nave.x+50>=powerup.x && nave.y+20<powerup.y+50 && nave.y+20>=powerup.y  && nave.x+50<powerup.x+50)
			hit_powerup=1;
				
		if(powerup.status && nave.status==1 && nave.x>=powerup.x && nave.y+40<powerup.y+50 && nave.y+40>=powerup.y  && nave.x<powerup.x+50)
			hit_powerup=1;

		
		if(powerup.status && nave.status==1 && nave.x+45>=powerup.x && nave.y+75<powerup.y+50 && nave.y+75>=powerup.y  && nave.x<powerup.x+40)
			hit_powerup=1;

	}

	if(hit)
	{
		num_aliens--;
		nave.health-=50;
		nave.kills++;
		rectfill(screen,0,0,639,479,250);
	}

	if(hit_powerup)
	{
		if(powerup.status==1) nave.health+=50;
		powerup.status=0;
	}	

	if(nave.health<=0 && nave.status==1)
	{
		nave.status=2;
		nave.lives--;
		nave.time=70;
		nave.health=0;
	}
}

void ChecarMorteAlien()
{
	register int i,j;
	
	for(i = 0; i < 30; i++)
	{
		for(j = 0; j < 30; j++)
		{
			if(bala[i].active
			&& myalien[j].status
			&& bala[i].x >= myalien[j].x
			&& bala[i].y <  myalien[j].y+50
			&& bala[i].y >= myalien[j].y
			&& bala[i].x <  myalien[j].x+50)
			{
				bala[i].active=0;
				if(myalien[j].status==1) myalien[j].time=40;
				myalien[j].status=2;
				nave.kills++;
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
	powerup.x = (rand()%600) - 640;
	powerup.y = -20;
	powerup.status = 1;	
}

void IniciarNave()
{
	nave.x = 300;
	nave.y = 380;
	nave.l = 64;
	nave.a = 100;
	nave.kills = 0;
	nave.escaped = 0;
	nave.health = 100;
	nave.status = 1;
	nave.lives = 3;
}


/***********************************************************/
void IniciarObjetos()
{
	IniciarNave();
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

}
void DesligarObjetos()
{
	destroy_bitmap(buffer);
	destroy_bitmap(big_boom);
}

void AtualizarObjetos()
{
	if(num_aliens < max_aliens)
		CriarAlien(0);
	
	blit((BITMAP *)data[NUVENS].dat,buffer, 0, 0, 0, scroll_y - 480,640, 480);
	blit((BITMAP *)data[NUVENS].dat,buffer, 0, 0, 0, scroll_y,      640, 480);
	
	if(nave.status == 1)
		draw_sprite(buffer, (BITMAP *)data[JATO].dat, nave.x, nave.y);
	
	if(nave.status == 2)
		draw_sprite(buffer, big_boom, nave.x, nave.y);

	if(nave.status == 1)
	{
		if(key[KEY_UP])    nave.y -= 3;
		if(key[KEY_RIGHT]) nave.x += 3;
		if(key[KEY_DOWN])  nave.y += 3;
		if(key[KEY_LEFT])  nave.x -= 3;
		if(key[KEY_SPACE] && bla2 >= 25)
		{
			Atirar(nave.x,nave.y);
			bla2 = 0;
		}
	}

	bla++;
	bla2++;

	scroll_y++;

	for(j = 0; j < 30; j++)
	{
		bala[j].y -= 5;
		
		if(bala[j].y < 0)
			bala[j].active = 0;
		
		if(bala[j].active)
			line(buffer, bala[j].x, bala[j].y, bala[j].x,bala[j].y + 4,254);
		
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
		if(myalien[j].status) myalien[j].y += 2;
		if(myalien[j].x < -50 && myalien[j].status == 1)
		{
			num_aliens--;
			myalien[j].status = 0;
			nave.escaped++;
		}
	}
	
	if(nave.status == 2)
		nave.time--;
	
	if(nave.status == 2 && nave.time <= 0)
	{
		num_aliens = 0;
		nave.status = 1;
		nave.health = 100;
		
		for(j = 0; j < 30; j++) 
			myalien[j].status=0;
	}
	
	if(nave.lives == 0)
		lose();
	
	ChecarMorteAlien();
	ChecarImpacto();

	tempo_prox_powerup--;
	
	if(tempo_prox_powerup == 0)
	{
		tempo_prox_powerup=(rand()%500) + 600;
		CriarPowerUp();
	}
	
	if(powerup.status)
		powerup.x -= 2;
	
	if(powerup.status == 1)
		masked_blit((BITMAP *)data[HEAL].dat,buffer,0,0,powerup.x,powerup.y,50,50);

	tempo_prox_alien++;
	
	if(tempo_prox_alien == 500)
	{
		tempo_prox_alien = 0;
		max_aliens++;
	}

	sprintf(str,"Mortes: %d   Escapadas: %d",nave.kills,nave.escaped);
	textout(buffer,font,str,5,15,254);
	sprintf(str,"Vidas: %d",nave.lives);
	textout(buffer,font,str,5,460,254);
	sprintf(str,"Energia: %d",nave.health);
	textout(buffer,font,str,5,470,254);

	if(scroll_y == 480)
		scroll_y = 0;

}

void DesenharObjetos(BITMAP *bmp)
{
	blit(buffer, bmp, 0, 0, 0, 0, 640, 480);
}