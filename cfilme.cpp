 /*------------------------------------------------------------*
 *  cfilme.cpp - Implementação da Classe de Filmes
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: sábado, 29 de junho de 2002
*
*
*------------------------------------------------------------*/

#include "cfilme.h"
#include "galib.h"

enum EOPCodeFilme
{
	op_txt = 0,
	op_cls,
	op_dat,
	op_mid,
	op_wav,
	op_bmp,
	op_seg
};


//------------------------------------------------------------
CFilme::CFilme()
{
}

//------------------------------------------------------------
CFilme::~CFilme()
{
	m_dados.Fechar();
}

//------------------------------------------------------------
void CFilme::Executar(const char *arquivo)
{

	VETORPALAVRA lista;

	lista.push_back(GAPalavra(op_txt, "txt"));
	lista.push_back(GAPalavra(op_cls, "cls"));
	lista.push_back(GAPalavra(op_dat, "dat"));
	lista.push_back(GAPalavra(op_mid, "mid"));
	lista.push_back(GAPalavra(op_wav, "wav"));
	lista.push_back(GAPalavra(op_bmp, "bmp"));
	lista.push_back(GAPalavra(op_seg, "seg"));

	GAScript script(this, lista);
	script.Carregar(arquivo);
	script.Executar();
}

//------------------------------------------------------------
bool CFilme::Escrever(const char *texto)
{
	int i;
	int coluna = 0;
	int linha = 400;
	bool saltar = false;

	rectfill(screen, 0, 400, 640, 480, 0);
	for (i = 0; i <= static_cast<int>(strlen(texto)); i++)
	{
		if ((i > 0) && ((i % 62) == 0))
			saltar = true;

		//Saltar apenas quando encontrar um espaço
		if (saltar && texto[i] == ' ')
		{
			coluna = -1;
			linha += 10;
			saltar = false;
		}
		
		textprintf(screen,
				   font, (coluna * 8) + 50, linha,
				   makecol(255,255,0), "%c", texto[i]);

		coluna++;
		

		if (keypressed())
		{
			if (key[KEY_ESC])
				return false;
		}
		else
			rest(25);
	}
	return true;
}

//------------------------------------------------------------
int CFilme::ExecutarInstrucao(int cmd, const std::string &par)
{
	if (key[KEY_ESC])
	{
		stop_midi();
		return FALSE;
	}

	switch (cmd)
	{
	case op_txt:
		if (!Escrever(par.c_str()))
			return FALSE;
		break;

	case op_cls:
		clear(screen);
		break;

	case op_dat:
		m_dados.Abrir(par.c_str());
		break;

	case op_mid:
		if (par.c_str()[0] == '.')
			stop_midi();
		else
			play_midi(m_dados.ObterMidi(par.c_str()), 1);

		break;

	case op_wav:
		play_sample(m_dados.ObterSample(par.c_str()), 100, 128, 1000, 0);
		break;

	case op_bmp:
		blit(m_dados.ObterBitmap(par.c_str()), screen, 0, 0, 0, 60, 640, 320);
		break;

	case op_seg:
		{
			int i;
			int segundos = atoi(par.c_str());
			for (i = 0; i < segundos * 2; i++)
			{
				if (keypressed())
				{
					if (key[KEY_ESC])
					{
						stop_midi();
						return FALSE;
					}
					clear_keybuf();
					break;
				}
				else
					rest(500);
			}
		}
		break;
	}
	return TRUE;
}