 /*------------------------------------------------------------*
 *  script.cpp - Implementação da classe de Script
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quarta-feira, 10 de julho de 2002
*
*
*------------------------------------------------------------*/

#include <fstream.h>
#include "galib.h"

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
GAScript::GAScript(GAEventoScript *evento, LISTASTRING comandos)
: m_evento(evento), m_comandos(comandos)
{
}

//------------------------------------------------------------
GAScript::GAScript(GAEventoScript *evento, const std::string *comandos, int numero)
: m_evento(evento)
{
	FixarComandos(comandos, numero);
}

//------------------------------------------------------------
void GAScript::FixarEvento(GAEventoScript *evento)
{
	m_evento = evento;
}

//------------------------------------------------------------
void GAScript::FixarComandos(const std::string *comandos, int numero)
{
	const std::string *final = comandos + numero;
	m_comandos.resize(numero);
	std::copy(comandos, final, m_comandos.begin());
}

//------------------------------------------------------------
void GAScript::Carregar(const char *arquivo)
{
	const int NUM_CARACTERES = 512;
	char linha[NUM_CARACTERES];
	GATradutor tradutor(m_comandos);
	ifstream arq(arquivo);

	while (!arq.eof())
	{
		arq.getline(linha, NUM_CARACTERES);
		if (tradutor.Traduzir(linha))
		{
			//mudar isto depois
			m_instrucoes.push_back(GAInstrucao(tradutor.Comando(), tradutor.Parametros()));
		}
	}
	arq.close();
}

//------------------------------------------------------------
void GAScript::Executar()
{
	int indice;
	LISTAINSTRUCAO::iterator itr = m_instrucoes.begin();
	for (indice = 0; itr != m_instrucoes.end(); ++itr, ++indice)
	{
		if (!m_evento->ExecutarInstrucao(itr->Comando(), itr->Parametros()))
		{
			break;
		}
	}
}

//------------------------------------------------------------
GAInstrucao GAScript::Instrucao(int numero) const
{
	return m_instrucoes[numero];
}


//------------------------------------------------------------
// Classe da instrucao
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
// Classe do Script
//------------------------------------------------------------


//------------------------------------------------------------
