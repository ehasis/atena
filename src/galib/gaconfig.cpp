 /*------------------------------------------------------------*
 *  config.cpp - Implementação da classe de configuracao
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quinta-feira, 28 de junho de 2002
*
*
*------------------------------------------------------------*/

#include <stdio.h>
#include "galib.h"

GAConfig::GAConfig()
{
}

GAConfig::~GAConfig()
{
}

void GAConfig::Abrir(const char *arquivo)
{
	sprintf(m_arquivo, arquivo);
	set_config_file(m_arquivo);
}

void GAConfig::Fechar()
{
}

//------------------------------------------------------------
void GAConfig::FixarSecao(const char *secao)
{
	sprintf(m_secao, secao);
}

//------------------------------------------------------------
void GAConfig::FixarBool(const char *chave, bool valor)
{
	set_config_int(m_secao, chave, (valor ? 1: 0));
}

void GAConfig::FixarBool(const char *secao, const char *chave, bool valor)
{
	FixarSecao(secao);
	FixarBool(chave, valor);
}

void GAConfig::FixarInt(const char *chave, int valor)
{
	set_config_int(m_secao, chave, valor);
}

void GAConfig::FixarInt(const char *secao, const char *chave, int valor)
{
	FixarSecao(secao);
	FixarInt(chave, valor);
}

void GAConfig::FixarStr(const char *chave, const char *valor)
{
	set_config_string(m_secao, chave, valor);
}

void GAConfig::FixarStr(const char *secao, const char *chave, const char *valor)
{
	FixarSecao(secao);
	FixarStr(chave, valor);
}

//------------------------------------------------------------
bool GAConfig::ObterBool(const char *chave, bool padrao)
{
	if (get_config_int(m_secao, chave, (padrao ? 1: 0)))
	{
		return true;
	}
	return false;
}

bool GAConfig::ObterBool(const char *secao, const char *chave, bool padrao)
{
	FixarSecao(secao);
	return ObterBool(chave, padrao);
}

int	GAConfig::ObterInt(const char *chave, int padrao)
{
	return get_config_int(m_secao, chave, padrao);
}

int GAConfig::ObterInt(const char *secao, const char *chave, int padrao)
{
	FixarSecao(secao);
	return ObterInt(chave, padrao);
}

const char *GAConfig::ObterStr(const char *chave, const char *padrao)
{
	return get_config_string(m_secao, chave, padrao);
}

const char *GAConfig::ObterStr(const char *secao, const char *chave, const char *padrao)
{
	FixarSecao(secao);
	return get_config_string(m_secao, chave, padrao);
}

