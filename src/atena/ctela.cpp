 /*------------------------------------------------------------*
 *  ctela.cpp - Implementação da CTela
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quarta-feira, 13 de fevereito de 2002
*
*
*------------------------------------------------------------*/

#include "ctela.h"
#include "erro.h"

//------------------------------------------------------------
void CTela::Iniciar(int modo, int largura, int altura, int bit_cores)
{
	//Configurações
	m_utilizar_vsync 			 = false;
	m_utilizar_suavizar 		 = false;
	m_utilizar_escrever_sombra = false;

	m_bmp_fundo	= NULL;
	m_bmp_objetos = NULL;
	m_bmp_efeitos	= NULL;

	SetarModoGrafico(modo, largura, altura, bit_cores);
}

//------------------------------------------------------------
void CTela::SetarModoGrafico(int modo, int largura, int altura, int bit_cores)
{

	//Destroi todos os objetos
	Desligar();

	set_color_depth(bit_cores);

	if (set_gfx_mode(modo, largura, altura, 0, 0) < 0)
	{
		Erro("Nao foi possivel definir o modo grafico", allegro_error);
	}

	clear_to_color(screen, 0);

	//Recria os bitmaps
	m_bmp_fundo	= create_bitmap(TELA_L, TELA_A);
	m_bmp_objetos = create_bitmap(ARENA_L, ARENA_A);
	m_bmp_efeitos = create_bitmap(ARENA_L, ARENA_A);
	
	CExplosao::Iniciar(ARENA_L, ARENA_A, true);
}

//------------------------------------------------------------
void CTela::Desligar()
{
	CExplosao::Desligar();

	if (m_bmp_fundo) destroy_bitmap(m_bmp_fundo);
	if (m_bmp_objetos) destroy_bitmap(m_bmp_objetos);
	if (m_bmp_efeitos) destroy_bitmap(m_bmp_efeitos);

	m_bmp_fundo	= NULL;
	m_bmp_objetos = NULL;
	m_bmp_efeitos	= NULL;
}


void CTela::Atualizar(BITMAP * bmp_destino)
{
	CExplosao::Desenhar(m_bmp_efeitos);

	masked_blit(m_bmp_objetos, m_bmp_fundo, 0, 0, STATUS_L, 0, ARENA_L, ARENA_A);
	masked_blit(m_bmp_efeitos, m_bmp_fundo, 0, 0, STATUS_L, 0, ARENA_L, ARENA_A);
	draw_sprite(bmp_destino, m_bmp_fundo, 0, 0);

	if (key[KEY_F12])
		Salvar(m_bmp_fundo);
}

//------------------------------------------------------------
void CTela::SetarVsync(bool valor)
{
	m_utilizar_vsync = valor;
}

//------------------------------------------------------------
void CTela::SetarSuavizar(bool valor)
{
	m_utilizar_suavizar = valor;
}

//------------------------------------------------------------
void CTela::SetarEscreverSombra(bool valor)
{
	m_utilizar_escrever_sombra = valor;
}

void CTela::SetarExibirParticulas(bool valor)
{
	CExplosao::Ativo(valor);
}

void CTela::Salvar(BITMAP *bmp)
{
	bool sair = false;
	int i = 0;
	char arquivo[512];

	do {
		sprintf(arquivo, "captura_%d.bmp", i);
		if (!exists(arquivo))
		{
			textout_centre(screen, font, "SALVANDO CAPTURA DE TELA...", SCREEN_W / 2, SCREEN_H / 2, makecol16(255,255,0));
			sair = true;
			save_bmp(arquivo, bmp, NULL);
		}
		i++;
	} while (!sair);
	rest(1000);
}



/*
static unsigned int cor_mascara = 0xF7DEF7DE;
static unsigned int pixel_baixo_mascara = 0x08210821;

//macro para interpolar cores
#define INTERPOLAR(A, B) ((((A & cor_mascara) >> 1) + ((B & cor_mascara) >> 1) + (A & B & pixel_baixo_mascara)))


void SuavizarBitmap(BITMAP *bmp)
{
	int y, x;
	char *linha;
	unsigned short *slinha;

	//por enquanto a rotina só funciona no modo 16-bit
	if (bitmap_color_depth(bmp) != 16)
	{
		return;
	}

	//aloca o espaço para caber uma linha
	linha = (char *)malloc(sizeof(short) * (bmp->w + 2));
	if (!linha)
	{
		return;
	}

	//tranca o bitmap para poder trabalhar com ele
	acquire_bitmap(bmp);

	//laço para todas as linhas
	for (y = 0; y < bmp->h; y++)
	{
        unsigned int cor1, cor2, cor3, d;
        int endereco_linha;

		bmp_select(bmp);
		endereco_linha = bmp_read_line(bmp, y);

		//preenche a linha temporaria com os pixeis da linha corrente
		for (x = 0; x < (int)(bmp->w * sizeof(short)); x += sizeof(long))
		{
			*((unsigned long *) &linha[x]) = bmp_read32(endereco_linha + x);
        }

        slinha = (unsigned short *)linha;

		bmp_select(bmp);

		d = bmp_write_line(bmp, y);

		//laço para os pixeis da linha
		for (x = 0; x < bmp->w - 2; x += 2)
		{
			unsigned int produto;
			cor1 = slinha[x];
			cor2 = slinha[x + 1];
			cor3 = slinha[x + 2];
			
			//interpola os pixeis
			produto = (INTERPOLAR(cor2, cor3) << 16 | INTERPOLAR(cor2, cor1));

			//escreve o pixel interpolado
			bmp_write32(d, produto);
			d += sizeof(int);
		}
	}
	
	//libera o bitmap e desaloca a memoria
	bmp_unwrite_line(bmp);
	release_bitmap(bmp);
	free(linha);

	return;
}

/**/