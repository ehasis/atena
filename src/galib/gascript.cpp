 /*------------------------------------------------------------*
 *  script.cpp - Implementação da classe de Script
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quarta-feira, 10 de julho de 2002
*
*
*------------------------------------------------------------*/

#include "galib.h"
#include <fstream>

#define CODIGO_INICIO 1000
#define CODIGO_FIM    1001

//------------------------------------------------------------
// Classe GAInstrucao
//------------------------------------------------------------
GAInstrucao::GAInstrucao()
: m_comando(-1)
{
}

//------------------------------------------------------------
GAInstrucao::GAInstrucao(int comando)
: m_comando(comando)
{
}

//------------------------------------------------------------
GAInstrucao::GAInstrucao(int comando, const std::string &parametros)
: m_comando(comando), m_parametros(parametros)
{
}

//------------------------------------------------------------
GAInstrucao::GAInstrucao(const GAInstrucao &instrucao)
: m_comando(instrucao.m_comando), m_parametros(instrucao.m_parametros)
{
}

//------------------------------------------------------------
int GAInstrucao::Comando() const
{
	return m_comando;
}

//------------------------------------------------------------
std::string GAInstrucao::Parametros() const
{
	return m_parametros;
}


//------------------------------------------------------------
// Classe GATradutor
//------------------------------------------------------------
GATradutor::GATradutor(const VETORPALAVRA &palavras)
: m_palavras(palavras)
{
}

//------------------------------------------------------------
bool GATradutor::Traduzir(const std::string &linha)
{
	m_codigo = -1;
	m_parametros = "";
	m_posicao = 0;

	if (linha.empty())
		return false;

	if (!PularEspacos(linha))
		return false;

	if (!ProcurarPalavra(linha))
		return false;

	int tamanho = linha.length();
	if (m_posicao < tamanho)
	{
		if (!PularEspacos(linha))
			return true;
		m_parametros = linha.substr(m_posicao);
	}
	return true;
}

//------------------------------------------------------------
int GATradutor::Codigo() const
{
	return m_codigo;
}

//------------------------------------------------------------
std::string GATradutor::Parametros() const
{
	return m_parametros;
}

//------------------------------------------------------------
GAInstrucao GATradutor::Instrucao() const
{
	return GAInstrucao(m_codigo, m_parametros);
}

//------------------------------------------------------------
bool GATradutor::PularEspacos(const std::string &linha)
{
	while (isspace(linha.c_str()[m_posicao]))
		m_posicao++;

	if (linha.c_str()[m_posicao] == '\0')
		return false;

	if (linha.c_str()[m_posicao] == ';')
		return false;

	return true;
}

//------------------------------------------------------------
bool GATradutor::ProcurarPalavra(const std::string &linha)
{
	int pos_inicial = m_posicao;
	while (isalpha(linha.c_str()[m_posicao]))
		m_posicao++;

	return ValidarPalavra(std::string(linha, pos_inicial, m_posicao - pos_inicial));
}

//------------------------------------------------------------
bool GATradutor::ValidarPalavra(const std::string &palavra)
{
	VETORPALAVRA::iterator itr;
    
	for (itr = m_palavras.begin(); itr != m_palavras.end(); ++itr)
	{	    
		if (palavra == itr->Palavra())
		{
			m_codigo = itr->Codigo();
			return true;
		}
	}
	return false;
}

//------------------------------------------------------------
// Classe GAScript
//------------------------------------------------------------
GAScript::GAScript()
: m_evento(0)
{
}

//------------------------------------------------------------
GAScript::GAScript(GAEventoScript *evento)
: m_evento(evento)
{
}

//------------------------------------------------------------
GAScript::GAScript(GAEventoScript *evento, const VETORPALAVRA &palavras)
: m_evento(evento)
{
	FixarPalavras(palavras);
}

//------------------------------------------------------------
void GAScript::FixarEvento(GAEventoScript *evento)
{
	m_evento = evento;
}

//------------------------------------------------------------
void GAScript::FixarPalavras(const VETORPALAVRA &palavras)
{
	m_palavras = palavras;
	m_palavras.push_back(GAPalavra(CODIGO_INICIO, "inicio"));
	m_palavras.push_back(GAPalavra(CODIGO_FIM, "fim"));
}

//------------------------------------------------------------
void GAScript::Carregar(const char *arquivo)
{
	const int NUM_CARACTERES = 512;
	char linha[NUM_CARACTERES];
	GATradutor tradutor(m_palavras);
	std::ifstream arq(arquivo);

	while (!arq.eof())
	{
		arq.getline(linha, NUM_CARACTERES);
		if (tradutor.Traduzir(linha))
		{
			m_instrucoes.push_back(tradutor.Instrucao());
		}
	}
	arq.close();
}

//------------------------------------------------------------
void GAScript::Executar()
{
	int indice;
	bool iniciou = false;

	VETORINSTRUCAO::iterator itr = m_instrucoes.begin();
	for (indice = 0; itr != m_instrucoes.end(); ++itr, ++indice)
	{
		switch (itr->Comando())
		{
		case CODIGO_INICIO:
			iniciou = true;
			break;

		case CODIGO_FIM:
			return;

		default:
			if (iniciou)
			{
				if (!m_evento->ExecutarInstrucao(itr->Comando(), itr->Parametros()))
					break;
			}
		}
	}
}

//------------------------------------------------------------
GAInstrucao GAScript::Instrucao(int numero) const
{
	return m_instrucoes[numero];
}

//------------------------------------------------------------
