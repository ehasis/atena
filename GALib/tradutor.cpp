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
GATradutor::GATradutor(const LISTASTRING &comandos)
: m_comandos(comandos)
{
}

//------------------------------------------------------------
GATradutor::GATradutor(const std::string *comandos, int numero)
{
	const std::string *final = comandos + numero;
	m_comandos.resize(numero);
	std::copy(comandos, final, m_comandos.begin());
}

//------------------------------------------------------------
bool GATradutor::Traduzir(const std::string &linha)
{
	m_comando = -1;
	m_parametros = "";
	m_posicao = 0;
	
	if (linha.empty())
		return false;

	if (!PularEspacos(linha))
		return false;

	if (!ProcurarComando(linha))
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
int GATradutor::Comando() const
{
	return m_comando;
}

//------------------------------------------------------------
std::string GATradutor::Parametros() const
{
	return m_parametros;
}

//------------------------------------------------------------
GAInstrucao GATradutor::Instrucao() const
{
	return GAInstrucao(m_comando, m_parametros);
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
bool GATradutor::ProcurarComando(const std::string &linha)
{
	int pos_inicial = m_posicao;
	while (isalpha(linha.c_str()[m_posicao]))
		m_posicao++;

	return ValidarComando(std::string(linha, pos_inicial, m_posicao - pos_inicial));
}

//------------------------------------------------------------
bool GATradutor::ValidarComando(const std::string &palavra)
{
	int comando;
	LISTASTRING::iterator itr = m_comandos.begin();
	for (comando = 0; itr != m_comandos.end(); ++itr, ++comando)
	{
		if (palavra == *itr)
		{
			m_comando = comando;
			return true;
		}
	}
	return false;
}

//------------------------------------------------------------
