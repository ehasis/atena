 /*------------------------------------------------------------*
 *  cladrilho.cpp - Implementacao da Classe CLadrilho
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: sexta-feira, 19 de outubro de 2001
*
*
*------------------------------------------------------------*/


#include "cladrilho.h"
#include <string.h>
#include "erro.h"


//------------------------------------------------------------
CLadrilho::CLadrilho()
{
	m_bmp_ladrilho = NULL;
	m_bmp_aux = NULL;
}


//------------------------------------------------------------
void CLadrilho::Iniciar(TLadrilho ladrilho, int largura, int altura, BITMAP * bmp_fonte)
{
	//Log("Inicio");
	int aux_angulo;

	m_x      = ladrilho.x;
	m_y      = ladrilho.y;
	m_bmp_x  = ladrilho.bmp_x;
	m_bmp_y  = ladrilho.bmp_y;
	m_h_flip = ladrilho.h_flip;
	m_v_flip = ladrilho.v_flip;
	m_angulo = ladrilho.angulo;
	strcpy(m_arquivo_bmp, ladrilho.arquivo_bmp);

	m_largura   = largura;
	m_altura    = altura;
	//Log("m_bmp_fonte");
	m_bmp_fonte = bmp_fonte;

	//Log("m_bmp_ladrilho");
	if(!m_bmp_ladrilho)
	{
		m_bmp_ladrilho = create_bitmap(m_largura, m_altura);
		if(!m_bmp_ladrilho)
		{
			Erro("Código do Erro:", "0300");
		}
	}

	clear(m_bmp_ladrilho);
	blit(m_bmp_fonte, m_bmp_ladrilho, m_bmp_x, m_bmp_y, 0, 0, m_largura, m_altura);

	//Log("m_bmp_aux");
	if(!m_bmp_aux)
	{
		m_bmp_aux = create_bitmap(m_largura, m_altura);
		if(!m_bmp_aux)
		{
			Erro("Código do Erro:", "0301");
		}
	}
	clear(m_bmp_aux);

	if(m_v_flip)
	{
		VirarVertical();
		m_v_flip = TRUE;
	}
	if(m_h_flip)
	{
		VirarHorizontal();
		m_h_flip = TRUE;
	}
	aux_angulo = m_angulo;
	m_angulo = 0;
	Rotacionar(aux_angulo);
	//SuavizarBitmap(m_bmp_ladrilho);
}

//------------------------------------------------------------
void CLadrilho::Desenhar(CTela & tela, int x_real, int y_real)
{
	tela.DrawSprite(eCamadaFundo, m_bmp_ladrilho, m_x - x_real, m_y - y_real);
}

//------------------------------------------------------------
void CLadrilho::SetarXBmp(int bmp_x)
{
   m_bmp_x = bmp_x;
}

//------------------------------------------------------------
int CLadrilho::ObterXBmp()
{
   return m_bmp_x;
}

//------------------------------------------------------------
void CLadrilho::SetarYBmp(int bmp_y)
{
   m_bmp_y = bmp_y;
}

//------------------------------------------------------------
int CLadrilho::ObterYBmp()
{
   return m_bmp_y;
}


//------------------------------------------------------------
TLadrilho CLadrilho::ObterTLadrilho()
{
   TLadrilho lad;

   lad.bmp_x  = m_bmp_x;
   lad.bmp_y  = m_bmp_y;
   lad.x	  = m_x;
   lad.y	  = m_y;
   lad.h_flip = m_h_flip;
   lad.v_flip = m_v_flip;
   lad.angulo = m_angulo;
   strcpy(lad.arquivo_bmp, m_arquivo_bmp);

   return lad;
}

//------------------------------------------------------------
void CLadrilho::SetarArquivoBmp(char * arquivo_bmp)
{
   strcpy(m_arquivo_bmp, arquivo_bmp);
}

//------------------------------------------------------------
char *CLadrilho::ObterArquivoBmp()
{
   return m_arquivo_bmp;
}


//------------------------------------------------------------
void CLadrilho::VirarHorizontal()
{
	m_h_flip = !m_h_flip;
	draw_sprite_h_flip(m_bmp_aux, m_bmp_ladrilho, 0, 0);
	draw_sprite(m_bmp_ladrilho, m_bmp_aux, 0, 0);
	clear(m_bmp_aux);
}

//------------------------------------------------------------
void CLadrilho::VirarVertical()
{
	m_v_flip = !m_v_flip;
	draw_sprite_v_flip(m_bmp_aux, m_bmp_ladrilho, 0, 0);
	draw_sprite(m_bmp_ladrilho, m_bmp_aux, 0, 0);
	clear(m_bmp_aux);
}

//------------------------------------------------------------
void CLadrilho::Rotacionar(int rotacoes)
{
	m_angulo = (m_angulo + rotacoes) <= 4 ? m_angulo + rotacoes : 1;
	rotate_sprite(m_bmp_aux, m_bmp_ladrilho, 0, 0, itofix(rotacoes * 64));
	draw_sprite(m_bmp_ladrilho, m_bmp_aux, 0, 0);
	clear(m_bmp_aux);
}

//------------------------------------------------------------
int CLadrilho::ObterHFlip()
{
	return m_h_flip;
}

//------------------------------------------------------------
int CLadrilho::ObterVFlip()
{
	return m_v_flip;
}


//------------------------------------------------------------
void CLadrilho::Finalizar()
{
	destroy_bitmap(m_bmp_ladrilho);
	m_bmp_ladrilho = NULL;
	destroy_bitmap(m_bmp_aux);
	m_bmp_aux = NULL;
}


//------------------------------------------------------------
BITMAP *CLadrilho::ObterBmpFonte()
{
	return m_bmp_fonte;
}
