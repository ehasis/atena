 /*------------------------------------------------------------*
 *  cladrilho.cpp - Implementacao da Classe CLadrilho
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: sexta-feira, 19 de outubro de 2001
*
*  Henrique em 18/01/2002
*   - Corrigido erro na rotação do bitmap com "itofix(rotacao)"
*   - Modificado metodo Rotacionar
*
*  Henrique em 23/01/2002
*   - Chamada de SetarTLadrilho() a partir de Iniciar()
*   - Criação de bmp_aux_1 e 2 em Iniciar()
*   - Implementado metodo CLadrilho::Desligar()
*
*  Diego em 24/01/2002
*   - Retirado o método SetarBmp_fonte (obsoleto);
*	- Criado bmp_ladrilho;
*   - Alterado os métodos Iniciar, Desenhar
*
*  Diego em 13/02/2002
*   - Alterado o método Desenhar para aceitar CTela e
*     posicionamento relativo;
*------------------------------------------------------------*/


#include "cladrilho.h"
#include <string.h>
#include "erro.h"


//------------------------------------------------------------
CLadrilho::CLadrilho()
{
	bmp_ladrilho = NULL;
	bmp_aux = NULL;
}


//------------------------------------------------------------
void CLadrilho::Iniciar(TLadrilho _ladrilho, int _largura, int _altura, BITMAP *_bmp_fonte)
{
	//Log("Inicio");
	int aux_rotacao;

	//Log("SetarTLadrilho");
	SetarTLadrilho(_ladrilho);

	largura   = _largura;
	altura    = _altura;
	//Log("bmp_fonte");
	bmp_fonte = _bmp_fonte;

	//Log("bmp_ladrilho");
	if(!bmp_ladrilho)
	{
		bmp_ladrilho = create_bitmap(largura, altura);
		if(!bmp_ladrilho)
		{
			Erro("Código do Erro:", "0300");
		}
	}

	clear(bmp_ladrilho);
	blit(bmp_fonte, bmp_ladrilho, bmp_x, bmp_y, 0, 0, largura, altura);

	//Log("bmp_aux");
	if(!bmp_aux)
	{
		bmp_aux = create_bitmap(largura, altura);
		if(!bmp_aux)
		{
			Erro("Código do Erro:", "0301");
		}
	}
	clear(bmp_aux);

	if(v_flip)
	{
		VirarVertical();
		v_flip = TRUE;
	}
	if(h_flip)
	{
		VirarHorizontal();
		h_flip = TRUE;
	}
	aux_rotacao = rotacao;
	rotacao = 0;
	Rotacionar(aux_rotacao);
}

//------------------------------------------------------------
void CLadrilho::Desenhar(CTela &_tela, int _x_real, int _y_real)
{
	_tela.DrawSprite(eCamadaFundo, bmp_ladrilho, x - _x_real, y - _y_real);
}

//------------------------------------------------------------
void CLadrilho::SetarBmp_x(int _bmp_x)
{
   bmp_x = _bmp_x;
}

//------------------------------------------------------------
int CLadrilho::ObterBmp_x(void)
{
   return bmp_x;
}

//------------------------------------------------------------
void CLadrilho::SetarBmp_y(int _bmp_y)
{
   bmp_y = _bmp_y;
}

//------------------------------------------------------------
int CLadrilho::ObterBmp_y(void)
{
   return bmp_y;
}

//------------------------------------------------------------
void CLadrilho::SetarTLadrilho(TLadrilho _ladrilho)
{
   x         = _ladrilho.x;
   y	     = _ladrilho.y;
   bmp_x     = _ladrilho.bmp_x;
   bmp_y     = _ladrilho.bmp_y;
   h_flip    = _ladrilho.h_flip;
   v_flip    = _ladrilho.v_flip;
   rotacao   = _ladrilho.rotacao;
   strcpy(arquivo_bmp, _ladrilho.arquivo_bmp);
}

//------------------------------------------------------------
TLadrilho CLadrilho::ObterTLadrilho(void)
{
   TLadrilho lad;

   lad.bmp_x   = bmp_x;
   lad.bmp_y   = bmp_y;
   lad.x  = x;
   lad.y  = y;
   lad.h_flip  = h_flip;
   lad.v_flip  = v_flip;
   lad.rotacao = rotacao;
   strcpy(lad.arquivo_bmp, arquivo_bmp);

   return lad;
}

//------------------------------------------------------------
void CLadrilho::SetarArquivo_bmp(char *_arquivo_bmp)
{
   strcpy(arquivo_bmp, _arquivo_bmp);
}

//------------------------------------------------------------
char *CLadrilho::ObterArquivo_bmp()
{
   return arquivo_bmp;
}


//------------------------------------------------------------
void CLadrilho::VirarHorizontal(void)
{
	h_flip = !h_flip;
	draw_sprite_h_flip(bmp_aux, bmp_ladrilho, 0, 0);
	draw_sprite(bmp_ladrilho, bmp_aux, 0, 0);
	clear(bmp_aux);
}

//------------------------------------------------------------
void CLadrilho::VirarVertical(void)
{
	v_flip = !v_flip;
	draw_sprite_v_flip(bmp_aux, bmp_ladrilho, 0, 0);
	draw_sprite(bmp_ladrilho, bmp_aux, 0, 0);
	clear(bmp_aux);
}

//------------------------------------------------------------
void CLadrilho::Rotacionar(int _rotacoes)
{
	rotacao = (rotacao + _rotacoes) <= 4 ? rotacao + _rotacoes : 1;
	rotate_sprite(bmp_aux, bmp_ladrilho, 0, 0, itofix(_rotacoes * 64));
	draw_sprite(bmp_ladrilho, bmp_aux, 0, 0);
	clear(bmp_aux);
}

//------------------------------------------------------------
int CLadrilho::ObterH_flip(void)
{
	return h_flip;
}

//------------------------------------------------------------
int CLadrilho::ObterV_flip(void)
{
	return v_flip;
}

//------------------------------------------------------------
int CLadrilho::ObterRotacao(void)
{
	return rotacao;
}

//------------------------------------------------------------
void CLadrilho::Desligar()
{
	destroy_bitmap(bmp_ladrilho);
	bmp_ladrilho = NULL;
	destroy_bitmap(bmp_aux);
	bmp_aux = NULL;
}


//------------------------------------------------------------
BITMAP *CLadrilho::ObterBmp_fonte(void)
{
	return bmp_fonte;
}
