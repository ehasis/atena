 /*------------------------------------------------------------*
 *  cfundo.cpp - Implementacao da Classe de Fundo
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quarta-feira, 10 de outubro de 2001
*
*  Henrique em 23/01/2002
*  - Modificado metodo Desligar();
*
*------------------------------------------------------------*/


#include "cfundo.h"

//------------------------------------------------------------
int CFundo::Iniciar(TLadrilho _mapa_ladrilhos[MAPA_LARGURA_LADRILHOS][MAPA_ALTURA_LADRILHOS], int _x_fonte, int _y_fonte, int _mapa_largura_ladrilhos, int _mapa_altura_ladrilhos, int _ladrilho_largura, int _ladrilho_altura, int _x_destino, int _y_destino, int _largura_destino, int _altura_destino)
{
   register int x, y, i;
   int quant_bmp = 0, flag_load = FALSE;

   x_fonte					= _x_fonte;
   y_fonte					= _y_fonte;
   mapa_largura_ladrilhos	= _mapa_largura_ladrilhos;
   mapa_altura_ladrilhos	= _mapa_altura_ladrilhos;
   ladrilho_largura			= _ladrilho_largura;
   ladrilho_altura			= _ladrilho_altura;
   x_destino				= _x_destino;
   y_destino				= _y_destino;
   largura_destino			= _largura_destino;
   altura_destino			= _altura_destino;

   /* Cria o bitmap com o tamanho total do mapa */
   fundo_screen = create_bitmap(_largura_destino, _altura_destino);
   /* Loop para inicializar cada CLadrilho do fundo */
   for (x = 0; x < _mapa_largura_ladrilhos; x++)
   {
      for (y = 0; y < _mapa_altura_ladrilhos; y++)
      {
         /* Se o ladrilho não for válido, obtem o ladrilho
         padrão */
		 //if(_mapa_ladrilhos[x][y].bmp_x < 0 || _mapa_ladrilhos[x][y].bmp_y < 0 || _mapa_ladrilhos[x][y].bmp_x > SCREEN_W || _mapa_ladrilhos[x][y].bmp_y > SCREEN_H)
		 if(_mapa_ladrilhos[x][y].bmp_x < 0 || _mapa_ladrilhos[x][y].bmp_y < 0 || _mapa_ladrilhos[x][y].bmp_x > 640 || _mapa_ladrilhos[x][y].bmp_y > 480)
         {
            _mapa_ladrilhos[x][y].bmp_x = 0;
            _mapa_ladrilhos[x][y].bmp_y = 0;
            _mapa_ladrilhos[x][y].x =  x * 32;
            _mapa_ladrilhos[x][y].y =  y * 32;
			_mapa_ladrilhos[x][y].h_flip = FALSE;
			_mapa_ladrilhos[x][y].v_flip = FALSE;
			_mapa_ladrilhos[x][y].rotacao = 0;
            strcpy(_mapa_ladrilhos[x][y].arquivo_bmp, "fases\\novo.bmp");
         }

         /* Loop para verificar se o bitmap do ladrilho
         já foi alocado ou não */
         flag_load = TRUE;
         for(i = 0; i < quant_bmp && i < ARQUIVOS_BMP_QUANT; i++)
         {
            if((strcmp(bmp_arquivos[i].arquivo_bmp, _mapa_ladrilhos[x][y].arquivo_bmp) == 0))
            {
               flag_load = FALSE;
               break;
            }
         }

         /* Se o bitmap para o ladrilho ainda
         não foi alocado, faz a alocação */
         if(flag_load == TRUE)
         {
            strcpy(bmp_arquivos[quant_bmp].arquivo_bmp, _mapa_ladrilhos[x][y].arquivo_bmp);
            bmp_arquivos[quant_bmp].bmp_bmp = load_bmp(bmp_arquivos[quant_bmp].arquivo_bmp, NULL);
            i = quant_bmp;
            quant_bmp++;
         }
         /* Inicia e pinta no bitmap do fundo
         o ladrilho corrente */
         mapa_ladrilho[x][y].Iniciar(_mapa_ladrilhos[x][y], ladrilho_largura, ladrilho_altura, bmp_arquivos[i].bmp_bmp);
      }
   }
   return TRUE;
}

//------------------------------------------------------------ 
void CFundo::Desenhar(BITMAP * _bmp_destino, int _x_fonte, int _y_fonte)
{ 
	register int x, y; 
	int lim_x1, lim_y1, lim_x2, lim_y2; 

	x_fonte = _x_fonte; 
	y_fonte = _y_fonte; 
	lim_x1  = x_fonte / LADRILHO_LARGURA; 
	lim_x2  = (x_fonte + largura_destino) / LADRILHO_LARGURA + 1; 
	lim_y1  = y_fonte / LADRILHO_ALTURA; 
	lim_y2  = (y_fonte + altura_destino) / LADRILHO_ALTURA + 1; 

	for (x = lim_x1; x < lim_x2 && x < MAPA_LARGURA_LADRILHOS; x++) 
	{ 
		for (y = lim_y1; y < lim_y2 && y < MAPA_ALTURA_LADRILHOS; y++) 
		{ 
			mapa_ladrilho[x][y].Desenhar(_bmp_destino); 
		} 
	} 
} 

//------------------------------------------------------------
/*
Movimenta o fundo o na direcao indicada e pela quantidade
informada em pixels.
Retorna TRUE se for possível rolar o fundo senão retorna
FALSE
*/
int CFundo::Rolar(EDirecao _direcao, int _pixels)
{
	switch(_direcao)
	{
		case eCima:
			if((y_fonte - _pixels) > 0)
				y_fonte -= _pixels;
            else
            if(y_fonte == 0)
                     return FALSE;
                  else
                     y_fonte = 0;

                  break;

      case eDireita: if((x_fonte + largura_destino + _pixels) < MAPA_LARGURA)
                     x_fonte += _pixels;
                  else
                  if(x_fonte + largura_destino == MAPA_LARGURA)
                     return FALSE;
                  else
                     x_fonte = MAPA_LARGURA - largura_destino;
                  break;

      case eBaixo:   if((y_fonte + altura_destino + _pixels) < MAPA_ALTURA)
                     y_fonte += _pixels;
                  else
                  if(y_fonte + altura_destino == MAPA_ALTURA)
                     return FALSE;
                  else
                     y_fonte = MAPA_ALTURA - altura_destino;
                  break;

      case eEsquerda:   if((x_fonte - _pixels) > 0)
                     x_fonte -= _pixels;
                  else
                  if(x_fonte == 0)
                     return FALSE;
                  else
                     x_fonte = 0;
                  break;
	}
    return TRUE;
}


//------------------------------------------------------------
CLadrilho CFundo::ObterLadrilho(int _x, int _y)
{
	return mapa_ladrilho[_x][_y];
}


//------------------------------------------------------------
void CFundo::SetarLadrilho(int _x, int _y, CLadrilho _ladrilho)
{
	mapa_ladrilho[_x][_y] = _ladrilho;
}


//------------------------------------------------------------
void CFundo::SetarTLadrilho(int _x, int _y, TLadrilho _ladrilho)
{
   mapa_ladrilho[_x][_y].SetarTLadrilho(_ladrilho);
}


//------------------------------------------------------------
BITMAP *CFundo::ObterFundo_screen(void)
{
   return (BITMAP *)fundo_screen;
}


//------------------------------------------------------------
int CFundo::ObterX_fonte(void)
{
   return x_fonte;
}


//------------------------------------------------------------
int CFundo::ObterY_fonte(void)
{
   return y_fonte;
}


//------------------------------------------------------------
int CFundo::ObterX_destino(void)
{
   return x_destino;
}


//------------------------------------------------------------
int CFundo::ObterY_destino(void)
{
   return y_destino;
}


//------------------------------------------------------------
void CFundo::SalvarFundo(char *_fase)
{
   register int x, y;
   TLadrilho ladrilho;
   FILE *arquivo;

   if((arquivo = fopen(_fase, "wb")) != NULL)
   {
      for(x = 0; x < mapa_largura_ladrilhos; x++)
         for(y = 0; y < mapa_altura_ladrilhos; y++)
         {
            ladrilho = mapa_ladrilho[x][y].ObterTLadrilho();
            fwrite(&ladrilho, sizeof(TLadrilho), 1, arquivo);
         }
      fclose(arquivo);
   }

}


//------------------------------------------------------------
void CFundo::Desligar(void)
{
	register int x, y;
	
	for (x = 0; x < mapa_largura_ladrilhos; x++)
	{
		for (y = 0; y < mapa_altura_ladrilhos; y++)
		{
			mapa_ladrilho[x][y].Desligar();
		}
	}
	destroy_bitmap(fundo_screen);
}