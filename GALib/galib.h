 /*------------------------------------------------------------*
 *  galib.h - Biblioteca do Grupo Atena
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quinta-feira, 28 de junho de 2002
*
*  Alterações:
*
*  Henrique em 10/07/2002
*   - Implementado manipulação de script, com as classes:
*	  GAInstrucao, GATradutor, GAScript e GAEventoScript
*
*------------------------------------------------------------*/
#ifndef GALIB_H_INCLUIDO
#define GALIB_H_INCLUIDO

// desabilita as mensagens de warning de identificador
// muito grande para o debug (está no msdn)
#ifdef _DEBUG
#pragma warning (disable : 4786)
#endif

#include <allegro.h>
#include <string>
#include <vector>

//------------------------------------------------------------
// Classe para manipulação de Arquivos de Dados
//------------------------------------------------------------
class GADados
{
public:
	GADados();
	virtual ~GADados();

public:
	void Abrir(const char *arquivo);
	void Fechar();

	void *Obter(int indice);
	void *Obter(const char *nome);

	BITMAP *ObterBitmap(int indice);
	BITMAP *ObterBitmap(const char *nome);

	MIDI *ObterMidi(int indice);
	MIDI *ObterMidi(const char *nome);

	SAMPLE *ObterSample(int indice);
	SAMPLE *ObterSample(const char *nome);

private:
	DATAFILE *m_dados;

};

//------------------------------------------------------------
// Classe para manipulação de Arquivos de Dados
//------------------------------------------------------------
// - Utilizando o Metodo Antigo da Allegro
class GAConfig
{
public:
	GAConfig();
	virtual ~GAConfig();

public:
	void Abrir(const char *arquivo);
	void Fechar();

	void FixarSecao(const char *secao);
	void FixarBool(const char *chave, bool valor);
	void FixarBool(const char *secao, const char *chave, bool valor);
	void FixarInt(const char *chave, int valor);
	void FixarInt(const char *secao, const char *chave, int valor);
	void FixarStr(const char *chave, const char *valor);
	void FixarStr(const char *secao, const char *chave, const char *valor);

	bool ObterBool(const char *chave, bool padrao = false);
	bool ObterBool(const char *secao, const char *chave, bool padrao = false);
	int	ObterInt(const char *chave, int padrao = 0);
	int ObterInt(const char *secao, const char *chave, int padrao = 0);
	const char *ObterStr(const char *chave, const char *padrao = "");
	const char *ObterStr(const char *secao, const char *chave, const char *padrao = "");

private:
	char m_arquivo[256];
	char m_secao[64];
};


//------------------------------------------------------------
// Manipulação de Script
//------------------------------------------------------------

typedef std::vector<std::string> LISTASTRING;

//------------------------------------------------------------
// Classe da Instrucao
//------------------------------------------------------------
class GAInstrucao
{
public:
	GAInstrucao();
	GAInstrucao(int comando);
	GAInstrucao(int comando, const std::string &parametros);
	GAInstrucao(const GAInstrucao &instrucao);

public:
	int Comando() const;
	std::string Parametros() const;

private:
	int m_comando;
	std::string m_parametros;
};
typedef std::vector<GAInstrucao> LISTAINSTRUCAO;


//------------------------------------------------------------
// Classe do Tradutor
//------------------------------------------------------------
class GATradutor
{
public:
	GATradutor(const LISTASTRING &comandos);
	GATradutor(const std::string *comandos, int numero);

public:
	bool Traduzir(const std::string &linha);

public:
	int Comando() const;
	std::string Parametros() const;
	GAInstrucao Instrucao() const;

private:
	bool PularEspacos(const std::string &linha);
	bool ProcurarComando(const std::string &linha);
	bool ValidarComando(const std::string &palavra);

private:
	int	m_posicao, m_comando;
	std::string m_parametros;
	LISTASTRING m_comandos;
};

//------------------------------------------------------------
// Classe Base para Eventos de Scripts
//------------------------------------------------------------
class GAEventoScript
{
public:
	virtual int ExecutarInstrucao(int cmd, const std::string &par) = 0;
};

//------------------------------------------------------------
// Classe de Scripts
//------------------------------------------------------------
class GAScript
{
public:
	GAScript();
	GAScript(GAEventoScript *evento);
	GAScript(GAEventoScript *evento, LISTASTRING comandos);
	GAScript(GAEventoScript *evento, const std::string *comandos, int numero);

public:
	void FixarEvento(GAEventoScript *evento);
	void FixarComandos(const std::string *comandos, int numero);
	void Carregar(const char *arquivo);
	virtual void Executar();

public:
	GAInstrucao Instrucao(int numero) const;

private:
	GAEventoScript *m_evento;
	LISTAINSTRUCAO 	m_instrucoes;
	LISTASTRING 	m_comandos;
};

#endif
