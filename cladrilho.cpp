 /*------------------------------------------------------------*
 *  cladrilho.cpp - Implementacao da Classe CLadrilho
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: sexta-feira, 19 de outubro de 2001
*
*  Henrique em 18/01/2001
*   - Corrigido erro na rotação do bitmap com "itofix(rotacao)"
*   - Modificado metodo Rotacionar
*
*  Henrique em 23/01/2001
*   - Chamada de SetarTLadrilho() a partir de Iniciar()
*   - Criação de bmp_aux_1 e 2 em Iniciar()
*   - Implementado metodo CLadrilho::Desligar()
*
*------------------------------------------------------------*/


#include "cladrilho.h"
#include <string.h>
#include "erro.h"

//------------------------------------------------------------
void CLadrilho::Iniciar(TLadrilho &_ladrilho, int _largura, int _altura, BITMAP *_bmp_fonte)
{
	SetarTLadrilho(_ladrilho);

	largura   = _largura;
	altura    = _altura;
	bmp_fonte = _bmp_fonte;
	
	bmp_aux_1 = create_bitmap(largura, altura);
	bmp_aux_2 = create_bitmap(largura, altura);
}

//------------------------------------------------------------
void CLadrilho::Desenhar(BITMAP *_bmp_destino)
{
	/* Se as coordenadas do ladrilho são inválidas ou o 
	arquivo_bmp não foi informado imprime no bmp_destino um 
	ladrilho padrao com fundo preto e bordas verdes */
	if(bmp_x == -1
	|| bmp_y == -1
	|| strlen(arquivo_bmp) == 0
	|| !bmp_fonte)
	{
		rectfill(_bmp_destino, x, y, x + largura, y + altura, makecol(0, 0, 0));
		rect(_bmp_destino, x, y, x + largura, y + altura, makecol(0, 255, 0));
	}
	/* Senão obtem o ladrilho na posição do bmp_fonte e
	imprime no bmp_destino */
	else
	{
		blit(bmp_fonte, bmp_aux_1, bmp_x, bmp_y, 0, 0, largura, altura);

		// Inverte na vertical
		if(v_flip)
		{
			draw_sprite_v_flip(bmp_aux_2, bmp_aux_1, 0, 0);
			draw_sprite(bmp_aux_1, bmp_aux_2, 0, 0);
		}

		// Inverte na horizontal
		if(h_flip)
		{
			draw_sprite_h_flip(bmp_aux_2, bmp_aux_1, 0, 0);
			draw_sprite(bmp_aux_1, bmp_aux_2, 0, 0);			
		}

		// Rotacao
		if (rotacao)
			rotate_scaled_sprite(_bmp_destino, bmp_aux_1, x, y, itofix(rotacao), itofix(1));
		else
			blit(bmp_aux_1, _bmp_destino, 0, 0, x, y, largura, altura);
	}
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
void CLadrilho::SetarTLadrilho(TLadrilho &_ladrilho)
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
void CLadrilho::SetarBmp_fonte(BITMAP *_bmp_fonte)
{
   bmp_fonte = _bmp_fonte;
}

//------------------------------------------------------------
BITMAP *CLadrilho::ObterBmp_fonte(void)
{
   return (BITMAP *) bmp_fonte;
}

//------------------------------------------------------------
void CLadrilho::VirarHorizontal(void)
{
	h_flip = !h_flip;
}

//------------------------------------------------------------
void CLadrilho::VirarVertical(void)
{
	v_flip = !v_flip;
}

//------------------------------------------------------------
void CLadrilho::Rotacionar(void)
{
	rotacao = ((rotacao + 64) <= 256) ? rotacao + 64 : 0;
	//rotacao = (rotacao + 64) % 256;
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
	destroy_bitmap(bmp_aux_1);
	destroy_bitmap(bmp_aux_2);
}