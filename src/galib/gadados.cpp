 /*------------------------------------------------------------*
 *  gados.cpp - Implementação da classe de Dados
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quinta-feira, 28 de junho de 2002
*
*
*------------------------------------------------------------*/

#include "gadados.h"

//------------------------------------------------------------
GADados::GADados()
{
#ifndef GADADOS_ABERTO
	m_dados = NULL;
#endif
	m_aberto = false;
}

//------------------------------------------------------------
GADados::~GADados()
{
	Fechar();
}

//------------------------------------------------------------
void GADados::Abrir(const char *arquivo)
{
#ifdef GADADOS_ABERTO

	//converte "arquivo.dat" para "arquivo/indice.txt"
	//-------------------------------------------------
	char tmp_str[64] = "";
	char tmp_arquivo[256] = "";

	strncpy(tmp_str, arquivo, strlen(arquivo) - 4);
	strcat(tmp_str, "/");
	strcpy(m_caminho, tmp_str);
	strcpy(tmp_arquivo, tmp_str);
	strcat(tmp_arquivo, "indice.txt");
	//-------------------------------------------------

	char str[80];
	if (!exists(tmp_arquivo))
	{
		sprintf(str, "Arquivo [%s] nao encontrado.", tmp_arquivo);
		allegro_message(str);
		return;
	}


	VETORPALAVRA lista;

	lista.push_back(GAPalavra(eTipoBMP, "bmp"));
	lista.push_back(GAPalavra(eTipoWAV, "wav"));
	lista.push_back(GAPalavra(eTipoMID, "mid"));
	lista.push_back(GAPalavra(eTipoTTF, "ttf"));

	GAScript script(this, lista);
	script.Carregar(tmp_arquivo);
	script.Executar();
	m_aberto = true;
#else
	if (m_dados != NULL)
		Fechar();
	m_dados = load_datafile(arquivo);

	if (m_dados)
		m_aberto = true;
#endif
}

//------------------------------------------------------------
void GADados::Fechar()
{
#ifdef GADADOS_ABERTO
	m_dados.clear();
#else
	if (m_dados != NULL)
		unload_datafile(m_dados);
	m_dados = NULL;
	m_aberto = false;
#endif
}

//------------------------------------------------------------
bool GADados::Aberto()
{
	return m_aberto;
}

//------------------------------------------------------------
void *GADados::Obter(int indice)
{
	return m_dados[indice].dat;
}

//------------------------------------------------------------
void *GADados::Obter(const char *nome)
{
	return BuscarPorNome(nome);
}

//------------------------------------------------------------
void *GADados::operator[](int indice)
{
	return Obter(indice);
}

//------------------------------------------------------------
void *GADados::operator[](const char *nome)
{
	return Obter(nome);
}

//------------------------------------------------------------
BITMAP *GADados::Bitmap(int indice)
{
	return reinterpret_cast<BITMAP *>(m_dados[indice].dat);
}

//------------------------------------------------------------
BITMAP *GADados::Bitmap(const char *nome)
{
	return reinterpret_cast<BITMAP *>(BuscarPorNome(nome));
}

//------------------------------------------------------------
MIDI *GADados::Midi(int indice)
{
	return reinterpret_cast<MIDI *>(m_dados[indice].dat);
}

//------------------------------------------------------------
MIDI *GADados::Midi(const char *nome)
{
	return reinterpret_cast<MIDI *>(BuscarPorNome(nome));
}

//------------------------------------------------------------
SAMPLE *GADados::Sample(int indice)
{
	return reinterpret_cast<SAMPLE *>(m_dados[indice].dat);
}

//------------------------------------------------------------
SAMPLE *GADados::Sample(const char *nome)
{
	return reinterpret_cast<SAMPLE *>(BuscarPorNome(nome));
}

//------------------------------------------------------------
ALFONT_FONT *GADados::Font(int indice)
{
	return reinterpret_cast<ALFONT_FONT *>(m_dados[indice].dat);
}

//------------------------------------------------------------
ALFONT_FONT *GADados::Font(const char *nome)
{
	return reinterpret_cast<ALFONT_FONT *>(BuscarPorNome(nome));
}


#ifdef GADADOS_ABERTO

int GADados::ExecutarInstrucao(int cmd, const std::string &par)
{    

	switch (cmd)
	{
		//case 0: //caminho
		//	strcpy(m_caminho, par.c_str());
		//	break;

		case eTipoBMP:
		case eTipoWAV:
		case eTipoMID:
		case eTipoTTF:
			m_dados.push_back(GADadosAberto(m_caminho, par.c_str(), (ETipoArquivo)cmd));
			break;
	}
	return TRUE;
}

#endif