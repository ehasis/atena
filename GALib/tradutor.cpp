 /*------------------------------------------------------------*
 *  tradutor.cpp - Implementação da classe de Tradução
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quarta-feira, 10 de julho de 2002
*
*
*------------------------------------------------------------*/

#include "galib.h"

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

	if (linha.c_str()[m_posicao] == NULL)
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
