 /*------------------------------------------------------------*
 *  gadados.h - Manipulação de Arquivos de Dados
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quarta-feira, 09 de abril de 2003
*
*  Alterações:
*
*------------------------------------------------------------*/
#ifndef GADADOS_H_INCLUIDO
#define GADADOS_H_INCLUIDO

#include "galib.h"

//Este preprocessamento define a utilização de arquivos de
//dados aberto, somente quando for modo debug.
//#ifdef _DEBUG
#define GADADOS_ABERTO
//#endif

//-------------------------------------
#ifdef GADADOS_ABERTO

enum ETipoArquivo
{
	eTipoBMP = 0,
	eTipoWAV,
	eTipoMID,
	eTipoTTF
};

class GADadosAberto
{
public:
	GADadosAberto(const char *caminho, const char *nome, ETipoArquivo tipo)
	{
		Abrir(caminho, nome, tipo);
	}

	GADadosAberto(const GADadosAberto &obj)
	{
		Abrir(obj.m_caminho, obj.m_nome, obj.m_tipo);
	}

	~GADadosAberto()
	{
		switch (m_tipo)
		{
			case eTipoBMP:
				destroy_bitmap(reinterpret_cast<BITMAP *>(dat));
				break;
			case eTipoWAV:
				destroy_sample(reinterpret_cast<SAMPLE *>(dat));
				break;
			case eTipoMID:
				destroy_midi(reinterpret_cast<MIDI *>(dat));
				break;
			case eTipoTTF:
				alfont_destroy_font(reinterpret_cast<ALFONT_FONT *>(dat));
				break;

		}
		dat = NULL;
	}

	void Abrir(const char *caminho, const char *nome, ETipoArquivo tipo)
	{
		char arquivo[260];

		m_tipo = tipo;

		strcpy(m_nome, nome);
		strcpy(m_caminho, caminho);

		strcpy(arquivo, m_caminho);
		strcat(arquivo, m_nome);
		
		switch (m_tipo)
		{
			case eTipoBMP:
				strcat(arquivo, ".bmp");
				dat = reinterpret_cast<void *>(load_bitmap(arquivo, NULL));
				break;
			case eTipoWAV:
				strcat(arquivo, ".wav");
				dat = reinterpret_cast<void *>(load_sample(arquivo));
				break;
			case eTipoMID:
				strcat(arquivo, ".mid");
				dat = reinterpret_cast <void *>(load_midi(arquivo));
				break;
			case eTipoTTF:
				strcat(arquivo, ".ttf");
				dat = reinterpret_cast <void *>(alfont_load_font(arquivo));
				break;
		}
	}

	const char *Nome()
	{
		return m_nome;
	}

	void *dat;

protected:
	ETipoArquivo m_tipo;
	char m_nome[64];
	char m_caminho[192];
};

typedef std::vector<GADadosAberto> VETOR_GADADOSABERTO;
#endif


#ifdef GADADOS_ABERTO
class GADados: public GAEventoScript
#else
class GADados
#endif
{
public:
	GADados();
	virtual ~GADados();

public:
	void Abrir(const char *arquivo);
	void Fechar();
	bool Aberto();

	void *Obter(int indice);
	void *Obter(const char *nome);
	void *operator[](int indice);
	void *operator[](const char *nome);

	BITMAP *Bitmap(int indice);
	BITMAP *Bitmap(const char *nome);

	MIDI *Midi(int indice);
	MIDI *Midi(const char *nome);

	SAMPLE *Sample(int indice);
	SAMPLE *Sample(const char *nome);

	ALFONT_FONT *Font(int indice);
	ALFONT_FONT *Font(const char *nome);

#ifdef GADADOS_ABERTO
	virtual int ExecutarInstrucao(int cmd, const std::string &par);
#endif

private:
	bool m_aberto;

#ifdef GADADOS_ABERTO
	char m_caminho[192];
	VETOR_GADADOSABERTO m_dados;
#else
	DATAFILE *m_dados;
#endif

	void *BuscarPorNome(const char *nome)
	{
#ifdef GADADOS_ABERTO
		VETOR_GADADOSABERTO::iterator itr;
		for (itr = m_dados.begin(); itr != m_dados.end(); ++itr)
		{
			if (strcmp(nome, itr->Nome()) == 0)
				return itr->dat;
		}
		return NULL;
#else
		return find_datafile_object(m_dados, nome)->dat;
#endif
	}

};


#endif
