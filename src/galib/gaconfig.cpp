 /*------------------------------------------------------------*
 *  config.cpp - Implementação da classe de configuracao
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quinta-feira, 28 de junho de 2002
*
*
*------------------------------------------------------------*/

#include "gaconfig.h"
#include <stdio.h>

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
void GAConfig::SetarSecao(const char *secao)
{
	sprintf(m_secao, secao);
}

//------------------------------------------------------------
void GAConfig::SetarBool(const char *chave, bool valor)
{
	set_config_int(m_secao, chave, (valor ? 1: 0));
}

void GAConfig::SetarBool(const char *secao, const char *chave, bool valor)
{
	SetarSecao(secao);
	SetarBool(chave, valor);
}

void GAConfig::SetarInt(const char *chave, int valor)
{
	set_config_int(m_secao, chave, valor);
}

void GAConfig::SetarInt(const char *secao, const char *chave, int valor)
{
	SetarSecao(secao);
	SetarInt(chave, valor);
}

void GAConfig::SetarStr(const char *chave, const char *valor)
{
	set_config_string(m_secao, chave, valor);
}

void GAConfig::SetarStr(const char *secao, const char *chave, const char *valor)
{
	SetarSecao(secao);
	SetarStr(chave, valor);
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
	SetarSecao(secao);
	return ObterBool(chave, padrao);
}

int	GAConfig::ObterInt(const char *chave, int padrao)
{
	return get_config_int(m_secao, chave, padrao);
}

int GAConfig::ObterInt(const char *secao, const char *chave, int padrao)
{
	SetarSecao(secao);
	return ObterInt(chave, padrao);
}

const char *GAConfig::ObterStr(const char *chave, const char *padrao)
{
	return get_config_string(m_secao, chave, padrao);
}

const char *GAConfig::ObterStr(const char *secao, const char *chave, const char *padrao)
{
	SetarSecao(secao);
	return get_config_string(m_secao, chave, padrao);
}

