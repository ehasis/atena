 /*------------------------------------------------------------*
 *  cfundo.h - Definicao da Classe de Fundo
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: terça-feira, 25 de setembro de 2001
*
*  
*
*------------------------------------------------------------*/

#ifndef cfundo_h_incluido
#define cfundo_h_incluido

#include "atena.h"

class CFundo
{
public:
	CFundo();
	void Atualizar();
	void Desenhar(BITMAP *bmp);
	void SetArquivoDat(DATAFILE *arquivo);
	void Desligar();
private:
	DATAFILE *data;
	int ry1, ry2, ry3;
};

//------------------------------------------------------------
// Construtor da Classe
CFundo::CFundo()
{
	ry1 = -1;
	ry2 = -2;
	//ry3 = -3;
}

//------------------------------------------------------------
// Destruicao dos dados
void CFundo::Desligar()
{
	unload_datafile(data);
}

//------------------------------------------------------------
// Definicao do arquivo de dados
void CFundo::SetArquivoDat(DATAFILE *arquivo)
{
	data = arquivo;
}

//------------------------------------------------------------
// Atualiza variaveis de rolagem
void CFundo::Atualizar()
{
	ry1 += 1;
	ry2 += 2;
	//ry3 += 3;
	
	if (ry1 >= 480) ry1 = 0;
	if (ry2 >= 480) ry2 = 0;
	//if (ry3 >= 480) ry3 = 0;
}

//------------------------------------------------------------
// Atualizacao do bitmap
void CFundo::Desenhar(BITMAP *bmp)
{
	
	//Fundo Estatico
	blit((BITMAP *)data[SOL].dat, bmp, 0, 0, 0, 0,640, 480);
	
	//Camada 1
	masked_blit((BITMAP *)data[ESTRELAS1].dat, bmp, 0, 0, 0, ry1 - 480, 640, 480);
	masked_blit((BITMAP *)data[ESTRELAS1].dat, bmp, 0, 0, 0, ry1,       640, 480);

	//Camada 2
	masked_blit((BITMAP *)data[ESTRELAS2].dat, bmp, 0, 0, 0, ry2 - 480, 640, 480);
	masked_blit((BITMAP *)data[ESTRELAS2].dat, bmp, 0, 0, 0, ry2,       640, 480);
	
	//Camada 3 (depois)
	//masked_blit((BITMAP *)data[FUNDO3].dat, bmp, 0, 0, 0, ry3 - 480,640, 480);
	//masked_blit((BITMAP *)data[FUNDO3].dat, bmp, 0, 0, 0, ry3,      640, 480);
}

#endif