 /*------------------------------------------------------------*
 *  cfilme.cpp - Implementação da Classe de Filmes
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: sábado, 29 de junho de 2002
*
*
*------------------------------------------------------------*/

#include <string.h>
#include "cfilme.h"
#include "galib.h"

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
	m_dados.Fechar();

	//Tem que ser a mesma ordem do enum
	std::string comandos[] =
	{
		"txt",
		"cls",
		"dat",
		"mid",
		"wav",
		"bmp",
		"seg",
		"fim"
	};

	GAScript script(this, comandos, total_opcodes);
	script.Carregar(arquivo);
	script.Executar();
}

//------------------------------------------------------------
void CFilme::Escrever(const char *texto)
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
		
		if (!keypressed())
			rest(25);
	}
}

//------------------------------------------------------------
int CFilme::ExecutarInstrucao(int cmd, const std::string &par)
{
	if (key[KEY_ESC])
	{
		stop_midi();
		return false;
	}

	switch (cmd)
	{
	case op_txt:
		Escrever(par.c_str());
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
		break;

	case op_bmp:
		blit(m_dados.ObterBitmap(par.c_str()), screen, 0, 0, 0, 60, 640, 320);
		break;

	case op_seg:
		{
			int i;
			int segundos = atoi(par.c_str());
			//clear_keybuf();		
			for (i = 0; i < segundos; i++)
			{
				if (key[KEY_ESC]) break;
				if (key[KEY_SPACE])
				{
					rest(1000);
					break;
				}
				else
					rest(1000);
			}
		}
		break;
	
	case op_fim:
		return FALSE;
	}
	return TRUE;
}