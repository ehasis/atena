 /*------------------------------------------------------------*
 *  gados.cpp - Implementação da classe de Dados
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quinta-feira, 28 de junho de 2002
*
*
*------------------------------------------------------------*/

#include "galib.h"

GADados::GADados(): m_dados(NULL)
{
}

GADados::~GADados()
{
	Fechar();
}

void GADados::Abrir(const char *arquivo)
{
	if (m_dados != NULL)
		Fechar();
	m_dados = load_datafile(arquivo);
}

void GADados::Fechar()
{
	if (m_dados != NULL)
		unload_datafile(m_dados);
	m_dados = NULL;
}

//------------------------------------------------------------
void *GADados::Obter(int indice)
{
	return m_dados[indice].dat;
}

void *GADados::Obter(const char *nome)
{
	return find_datafile_object(m_dados, nome)->dat;
}

//------------------------------------------------------------
BITMAP *GADados::ObterBitmap(int indice)
{
	return static_cast<BITMAP *>(m_dados[indice].dat);
}

BITMAP *GADados::ObterBitmap(const char *nome)
{
	return static_cast<BITMAP *>(find_datafile_object(m_dados, nome)->dat);
}

//------------------------------------------------------------
MIDI *GADados::ObterMidi(int indice)
{
	return static_cast<MIDI *>(m_dados[indice].dat);
}

MIDI *GADados::ObterMidi(const char *nome)
{
	return static_cast<MIDI *>(find_datafile_object(m_dados, nome)->dat);
}

//------------------------------------------------------------
SAMPLE *GADados::ObterSample(int indice)
{
	return static_cast<SAMPLE *>(m_dados[indice].dat);
}

SAMPLE *GADados::ObterSample(const char *nome)
{
	return static_cast<SAMPLE *>(find_datafile_object(m_dados, nome)->dat);
}
