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
*  Henrique em 14/07/2002
*	- Adicionado sobrecarga do operador [] na classe GADados
*
*------------------------------------------------------------*/
#ifndef GASCRIPT_H_INCLUIDO
#define GASCRIPT_H_INCLUIDO

#include <allegro.h>
#include <winalleg.h>
#include <string>
#include <vector>


//------------------------------------------------------------
// Classe de Palavra Reservada e Codigo
//------------------------------------------------------------
class GAPalavra
{
public:
	GAPalavra(int codigo, std::string palavra)
		: m_codigo(codigo), m_palavra(palavra) { }

	int Codigo() const			{ return m_codigo; }
	std::string Palavra() const { return m_palavra; }

private:
	int	m_codigo;
	std::string m_palavra;
};

typedef std::vector<GAPalavra> VETORPALAVRA;

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
typedef std::vector<GAInstrucao> VETORINSTRUCAO;

//------------------------------------------------------------
// Classe do Tradutor
//------------------------------------------------------------

class GATradutor
{
public:
	GATradutor(const VETORPALAVRA &palavras);

public:
	bool Traduzir(const std::string &linha);

public:
	int Codigo() const;
	std::string Parametros() const;
	GAInstrucao Instrucao() const;

private:
	bool PularEspacos(const std::string &linha);
	bool ProcurarPalavra(const std::string &linha);
	bool ValidarPalavra(const std::string &palavra);

private:
	int	m_posicao, m_codigo;
	std::string m_parametros;
	VETORPALAVRA m_palavras;
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
	GAScript(GAEventoScript *evento, const VETORPALAVRA &palavras);

public:
	void FixarEvento(GAEventoScript *evento);
	void FixarPalavras(const VETORPALAVRA &palavras);
	void Carregar(const char *arquivo);
	virtual void Executar();

public:
	GAInstrucao Instrucao(int numero) const;

private:
	GAEventoScript *m_evento;
	VETORINSTRUCAO 	m_instrucoes;
	VETORPALAVRA 	m_palavras;
};

#endif
