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

#define CODIGO_INICIO 1000
#define CODIGO_FIM    1001


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
	ifstream arq(arquivo);

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
