 /*------------------------------------------------------------*
 *  cladrilho.h - Classe CLadrilho
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: sexta-feira, 19 de outubro de 2001
*
*  Alterações:
*  Diego Giacomelli em 02/01/2002
*   - Classe CLadrilho declarada com herança de CObjeto;
*   - Alterações nos membros de dados da estrutura TLadrilho
*     e na classe CLadrilho;
*   - Implementação dos métodos VirarHorizontal, VirarVertical,
*	  Rotacionar, ObterHFlip, ObterVFlip e ObterRotacao;
*
*  Henrique em 23/01/2002
*   - bmp_aux_1 e 2 agora pertecem a toda a classe
*   - Chamada de SetarTLadrilho() a partir de Iniciar()
*   - Implementado metodo CLadrilho::Finalizar()
*
*  Henrique em 18/01/2002
*   - Corrigido erro na rotação do bitmap com "itofix(rotacao)"
*   - Modificado metodo Rotacionar
*
*  Diego Giacomelli em 24/01/2002
*   - Retirado o método SetarBmp_fonte (obsoleto);
*	- Criado m_bmp_ladrilho;
*   - Alterado os métodos Iniciar, Desenhar
*
*  Diego Giacomelli em 13/02/2002
*   - Alterado o método Desenhar para aceitar CTela e
*     posicionamento relativo;
*
*  Diego Giacomelli em 28/02/2002
*   - Renomeado o campo rotacao para angulo na estrutura TLadrilho;
*
*  Diego Giacomelli em 08/03/2002
*   - Retirados os métodos SetarTLadrilho (Obsoletos);
*------------------------------------------------------------*/

#ifndef cladrilho_h_incluido
#define cladrilho_h_incluido

#include "callegro.h"

#include "cobjeto.h"

#define LADRILHO_LARGURA		 32	// Largura do m_ladrilho em pixel
#define LADRILHO_ALTURA			 32 // Altura do m_ladrilho em pixel


// Estrutura dos ladrilhos para armazenamento no m_arquivo binário
 typedef struct {
	int bmp_x;  			// Coordenadas do m_ladrilho no bitmap
	int bmp_y;
	int x;					// Coordenadas do m_ladrilho no mapa
	int y;
	int h_flip;				// Flip horizontal
	int v_flip;				// Flip vertical
	int angulo;				// angulo do m_ladrilho 0-90-180-360
	char arquivo_bmp[64];	// Path do bmp associado ao m_ladrilho
} TLadrilho;


//------------------------------------------------------------
// Classe para manipulacao do m_ladrilho
class CLadrilho : public CObjeto
{
public:
	CLadrilho();
	void Iniciar(TLadrilho ladrilho, int largura, int altura, BITMAP * bmp_fonte);
	void Finalizar();
	void Desenhar(CTela & tela, int x_real, int y_real);;

	void SetarXBmp(int bmp_x);
	int ObterXBmp();

	void SetarYBmp(int bmp_y);
	int ObterYBmp();

	TLadrilho ObterTLadrilho();

	void SetarArquivoBmp(char * arquivo_bmp);
	char *ObterArquivoBmp();

	void VirarHorizontal();
	void VirarVertical();
	void Rotacionar(int rotacoes);
	int ObterHFlip();
	int ObterVFlip();

	BITMAP *ObterBmpFonte();

private:
	int m_bmp_x;				// Coordenadas do m_ladrilho no bitmap
	int m_bmp_y;    		    // Coordenadas do m_ladrilho no mapa
	int m_h_flip;				// Flip horizontal
	int m_v_flip;				// Flip vertical
	char m_arquivo_bmp[100];	// Path do bmp associado ao m_arquivo
	BITMAP *m_bmp_fonte;
	BITMAP *m_bmp_ladrilho, *m_bmp_aux;
};

//------------------------------------------------------------
inline void CLadrilho::Desenhar(CTela & tela, int x_real, int y_real)
{
	tela.DrawSprite(eCamadaFundo, m_bmp_ladrilho, m_x - x_real, m_y - y_real);
}

#endif

