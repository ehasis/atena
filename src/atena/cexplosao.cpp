#include "cexplosao.h"

static unsigned int cor_mascara = 0xF7DEF7DE;
static unsigned int pixel_baixo_mascara = 0x08210821;
#define INTERPOLAR(A, B) ((((A & cor_mascara) >> 1) + ((B & cor_mascara) >> 1) + (A & B & pixel_baixo_mascara)))

bool		CExplosao::m_ativo;
int			CExplosao::num_bytes;
TPaleta		CExplosao::palette[TAM_PALETA];
TParticula	CExplosao::particulas[QTD_PARTICULAS];
BITMAP		*CExplosao::m_bmp;

void CExplosao::Iniciar(int largura, int altura, bool ativo)
{
	register int i;

	m_ativo = ativo;
	m_bmp = create_bitmap(largura + 2, altura + 2);
	clear_to_color(m_bmp, makecol(0,0,0));
	

	num_bytes = 2;

	palette[0].r = 255;
    palette[0].g = 0;
    palette[0].b = 255;
    
	for(i = 1; i < 64; i++) 
	{
		palette[i].r = i * 2;
        palette[i].g = 0;
        palette[i].b = 0;
    }

    for(i = 64; i < 128; i++) 
	{
		palette[i].r = 63 * 8;
        palette[i].g = (i - 64) * 4;
        palette[i].b = 0;
    }

    for(i = 128; i < 256; i++)
	{
		palette[i].r = 63 * 8;
        palette[i].g = 63 * 4;
        palette[i].b = ((i - 128) >> 1) * 8;
    }

}


void CExplosao::Desenhar(CTela & tela)
{
	if (!m_ativo) return;

	register int  x, y;
	register int data;

	for (y = 1; y <= ARENA_A; y++ )
	{
    	for (x = 1; x <= ARENA_L; x++)
        {		

			data  = m_bmp->line[y-1][x];
			data += m_bmp->line[y+1][x];
			data += m_bmp->line[y][x-1];
			data += m_bmp->line[y][x+1];

			//divide por quaro
			data /= 4;	
			data -= 7;

            /**/

	
			/*
			// FX1
			int data  = m_bmp->line[y][x];
				data -= 4;
			/**/

			/*
			// FX2
			int data  = m_bmp->line[y-1][x-1];
				data += m_bmp->line[y-1][x7+1];
				data += m_bmp->line[y+1][x-1];
				data += m_bmp->line[y+1][x+1];
				data >>= 2;
				data -= 1;
			/**/

			/*
			// FX3
			int data  = m_bmp->line[y][x];
				data += m_bmp->line[y+1][x];
				data >>= 1;
				data--;
			/**/			

			/*
			// FX4 
			int data  = m_bmp->line[y][x];
				data += m_bmp->line[y+1][x];
				data += m_bmp->line[y][x+1];
				data += m_bmp->line[y][x-1];
				data >>= 2;
				data -= 1;
			/**/
			
			/*
			// FX5 
			int data  = m_bmp->line[y][x];
				data += m_bmp->line[y+1][x];
				data += m_bmp->line[y][x+1];
				data += m_bmp->line[y+1][x-1];
				data >>= 2;
				data -= 1;
			/**/

			/*
			// FX6
			int data = m_bmp->line[y][x];
            data-=2;
			/**/

			/*
			// FX7
			int data = m_bmp->line[y][x];
			data += m_bmp->line[y+1][x];
			data >>= 1;
			data -= 2;
			/**/

			/*
			// FX8 *
        	int data = m_bmp->line[y][x];
            data += m_bmp->line[y+1][x];
            data += m_bmp->line[y][x+1];
            data += m_bmp->line[y][x-1];
            data += m_bmp->line[y+1][x+1];
            data += m_bmp->line[y+1][x-1];
            data /= 6;
            data -= 1;
  			/**/


			if (data < 20 || data > 230)
				m_bmp->line[y-1][x] = 0;
			else
			{
				m_bmp->line[y-1][x] = data;
				if (((x % 2 ) && !(y % 2)) || (!(x % 2) && (y % 2)))
					tela.PutPixel(eCamadaEfeitos, x, y, makecol16(palette[m_bmp->line[y][x]].r, palette[m_bmp->line[y][x]].g, palette[m_bmp->line[y][x]].b));
			}
/**/
        }
    }
}

void CExplosao::Desligar()
{
	destroy_bitmap(m_bmp);
}

void CExplosao::Ativo(bool ativo)
{
	m_ativo = ativo;
}

void CExplosao::IniciarExplosao(int x, int y, int raio, int num_particulas)
{
	if (!m_ativo) return;

	register int i;
	float dist, lx, ly, len;
	int p = QTD_PARTICULAS < num_particulas * 25 ? QTD_PARTICULAS : num_particulas * 25;
	for(i = 0; i < p ; i++)
	{
		particulas[i].x = x;
		particulas[i].y = y;
		particulas[i].dir_x = RANDOM(2) - 1;
		particulas[i].dir_y = RANDOM(2) - 1;
        dist = RANDOM(raio);
        lx = particulas[i].dir_x;
        ly = particulas[i].dir_y;
        len = sqrt(lx*lx + ly*ly);

        if(len == 0.0)
			len = 0.0;
        else
			len = 1.0 / len;

        particulas[i].dir_x *= len * dist;
        particulas[i].dir_y *= len * dist;
        particulas[i].cor = 65535 - len;
		
		particulas[i].x += particulas[i].dir_x;
		particulas[i].y += particulas[i].dir_y;

		if ((int)particulas[i].x > 0 && (int)particulas[i].x < 640 && (int)particulas[i].y > 0 && (int)particulas[i].y < 480)
		{
			//putpixel(m_bmp, (int)particulas[i].x/2, (int)particulas[i].y, particulas[i].cor);
			//circle(m_bmp, (int)particulas[i].x/2, (int)particulas[i].y, 5, particulas[i].cor);
			m_bmp->line[(int)particulas[i].y] [(int)particulas[i].x] = 0;
			m_bmp->line[(int)particulas[i].y] [(int)particulas[i].x + 1] = particulas[i].cor;
		}
	}	
}


void CExplosao::IniciarExplosaoRadial(int x, int y, int raio)
{
	if (!m_ativo) return;

	circlefill(m_bmp, x/2, y, raio >> 2, 65535);
	circle(m_bmp, x/2, y, raio / 1.5, 65535);
	circle(m_bmp, x/2, y, raio, 100);
}

void CExplosao::InserirSprite(BITMAP *bmp, int x, int y)
{
	if (!m_ativo) return;
	draw_sprite(m_bmp, bmp, x, y);
}
