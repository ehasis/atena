 /*------------------------------------------------------------*
 *  cfundo.cpp - Implementacao da Classe de Fundo
*  Nome: Edison Henrique Andreassy
*  Data: quarta-feira, 10 de outubro de 2001
*
*
*------------------------------------------------------------*/


#include "cfundo.h"


//------------------------------------------------------------
int CFundo::Iniciar(TLadrilho mapa_ladrilhos[MAPA_LARGURA_LADRILHOS][MAPA_ALTURA_LADRILHOS], int x_fonte, int y_fonte, int mapa_largura_ladrilhos, int mapa_altura_ladrilhos, int ladrilho_largura, int ladrilho_altura, int x_destino, int y_destino, int largura_destino, int altura_destino)
{
   register int x, y;
   int quant_bmp = 0, flag_load = FALSE;
   TBmp **aux_bmp = NULL;

   m_bmp_arquivos = NULL;

   m_x_fonte = x_fonte;
   m_y_fonte = y_fonte;
   m_mapa_largura_ladrilhos = mapa_largura_ladrilhos;
   m_mapa_altura_ladrilhos = mapa_altura_ladrilhos;
   m_ladrilho_largura = ladrilho_largura;
   m_ladrilho_altura = ladrilho_altura;
   m_x_destino = x_destino;
   m_y_destino = y_destino;
   m_largura_destino = largura_destino;
   m_altura_destino = altura_destino;

    // Loop para inicializar cada CLadrilho do fundo
	for (x = 0; x < mapa_largura_ladrilhos; x++)
	{
		for (y = 0; y < mapa_altura_ladrilhos; y++)
		{

			flag_load = TRUE;
			for(aux_bmp = &m_bmp_arquivos; *aux_bmp; aux_bmp = &(*aux_bmp)->p_TBmp)
			{
				if((strcmp((*aux_bmp)->arquivo_bmp, mapa_ladrilhos[x][y].arquivo_bmp) == 0))
				{
					flag_load = FALSE;
					m_mapa_ladrilho[x][y].Iniciar(mapa_ladrilhos[x][y], m_ladrilho_largura, m_ladrilho_altura, (*aux_bmp)->bmp_bmp);
					break;
				}
			}
			/* Se o bitmap para o m_ladrilho ainda
			não foi alocado, faz a alocação */
			if(flag_load)
			{
				*aux_bmp = (TBmp *)malloc(sizeof(TBmp));
				strcpy((*aux_bmp)->arquivo_bmp, mapa_ladrilhos[x][y].arquivo_bmp);
				(*aux_bmp)->bmp_bmp = load_bmp(mapa_ladrilhos[x][y].arquivo_bmp, NULL);
				(*aux_bmp)->p_TBmp = NULL;
				/* Inicia e pinta no bitmap do fundo
				o m_ladrilho corrente */
				m_mapa_ladrilho[x][y].Iniciar(mapa_ladrilhos[x][y], m_ladrilho_largura, m_ladrilho_altura, (*aux_bmp)->bmp_bmp);
			}

      }
   }
   return TRUE;
}


//------------------------------------------------------------
void CFundo::Desenhar(CTela & tela, int x_real, int y_real)
{
	Log("[INICIO]:CFundo::Desenhar();");
	register int x, y;
	int lim_x1, lim_y1, lim_x2, lim_y2;

	m_x_fonte = x_real;
	m_y_fonte = y_real;
	lim_x1  = m_x_fonte / LADRILHO_LARGURA;
	lim_x2  = (m_x_fonte + m_largura_destino) / LADRILHO_LARGURA + 1;
	lim_y1  = m_y_fonte / LADRILHO_ALTURA;
	lim_y2  = (m_y_fonte + m_altura_destino) / LADRILHO_ALTURA + 1;

	for (x = lim_x1; x < lim_x2 && x < MAPA_LARGURA_LADRILHOS; x++)
	{
		for (y = lim_y1; y < lim_y2 && y < MAPA_ALTURA_LADRILHOS; y++)
		{
			m_mapa_ladrilho[x][y].Desenhar(tela, x_real - m_x_destino, y_real - m_y_destino);
		}
	}
	Log("[FIM]:CFundo::Desenhar();");
}


//------------------------------------------------------------
/*
Movimenta o fundo na direcao indicada e pela quantidade
informada em pixels.
Retorna TRUE se for possível rolar o fundo senão retorna
FALSE
*/
int CFundo::Rolar(EDirecao direcao, int pixels)
{
	switch(direcao)
	{
		case eCima:
			if((m_y_fonte - pixels) > 0)
				m_y_fonte -= pixels;
            else
            if(m_y_fonte == 0)
                     return FALSE;
                  else
                     m_y_fonte = 0;

                  break;

      case eDireita: if((m_x_fonte + m_largura_destino + pixels) < MAPA_LARGURA)
                     m_x_fonte += pixels;
                  else
                  if(m_x_fonte + m_largura_destino == MAPA_LARGURA)
                     return FALSE;
                  else
                     m_x_fonte = MAPA_LARGURA - m_largura_destino;
                  break;

      case eBaixo:   if((m_y_fonte + m_altura_destino + pixels) < MAPA_ALTURA)
                     m_y_fonte += pixels;
                  else
                  if(m_y_fonte + m_altura_destino == MAPA_ALTURA)
                     return FALSE;
                  else
                     m_y_fonte = MAPA_ALTURA - m_altura_destino;
                  break;

      case eEsquerda:   if((m_x_fonte - pixels) > 0)
                     m_x_fonte -= pixels;
                  else
                  if(m_x_fonte == 0)
                     return FALSE;
                  else
                     m_x_fonte = 0;
                  break;
	}
    return TRUE;
}


//------------------------------------------------------------
CLadrilho CFundo::ObterLadrilho(int x, int y)
{
	return m_mapa_ladrilho[x][y];
}


//------------------------------------------------------------
void CFundo::SetarLadrilho(int x, int y, TLadrilho ladrilho, BITMAP * bmp_fonte)
{
	m_mapa_ladrilho[x][y].Iniciar(ladrilho, m_mapa_ladrilho[x][y].ObterLargura(), m_mapa_ladrilho[x][y].ObterAltura(), bmp_fonte);
}


//------------------------------------------------------------
void CFundo::SalvarFundo(char * fase)
{
   register int x, y;
   TLadrilho m_ladrilho;
   FILE *m_arquivo;

   if((m_arquivo = fopen(fase, "wb")) != NULL)
   {
      for(x = 0; x < m_mapa_largura_ladrilhos; x++)
         for(y = 0; y < m_mapa_altura_ladrilhos; y++)
         {
            m_ladrilho = m_mapa_ladrilho[x][y].ObterTLadrilho();
            fwrite(&m_ladrilho, sizeof(TLadrilho), 1, m_arquivo);
         }
      fclose(m_arquivo);
   }

}


//------------------------------------------------------------
void CFundo::Finalizar()
{
	register int x, y;
	TBmp *aux_bmp;

	for(; m_bmp_arquivos;)
	{
		aux_bmp = m_bmp_arquivos;
		m_bmp_arquivos = m_bmp_arquivos->p_TBmp;
		free(aux_bmp);
	}

	for (x = 0; x < m_mapa_largura_ladrilhos; x++)
	{
		for (y = 0; y < m_mapa_altura_ladrilhos; y++)
		{
			m_mapa_ladrilho[x][y].Finalizar();
		}
	}
}