 /*------------------------------------------------------------*
 *  cconfig.cpp - Implementação da clasee CConfig
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: sexta-feira, 22 de fevereito de 2002
*
*
*
*------------------------------------------------------------*/

#include <stdio.h>
#include <allegro.h>
#include "cconfig.h"

//------------------------------------------------------------
CConfig::CConfig()
{
	/*
	SetarArquivo("config.ini");
	SetarSecao("config");
	*/
}

//------------------------------------------------------------
CConfig::CConfig(const char * arquivo)
{
	SetarArquivo(arquivo);
	SetarSecao("config");
}

//------------------------------------------------------------
void CConfig::SetarArquivo(const char * arquivo)
{
	sprintf(m_arquivo, arquivo);
	set_config_file(m_arquivo);
}

//------------------------------------------------------------
void CConfig::SetarSecao(const char * secao)
{
	sprintf(m_secao, secao);
}

//------------------------------------------------------------
int CConfig::ObterInt(const char * chave, int padrao)
{
	return get_config_int(m_secao, chave, padrao);
}

//------------------------------------------------------------
int CConfig::ObterInt(const char * secao, const char * chave, int padrao)
{
	SetarSecao(secao);
	return get_config_int(m_secao, chave, padrao);
}

//------------------------------------------------------------
bool CConfig::ObterBool(const char * chave, bool padrao)
{
	if (get_config_int(m_secao, chave, (padrao ? 1: 0)))
	{
		return true;
	}
	return false;
}

//------------------------------------------------------------
bool CConfig::ObterBool(const char * secao, const char * chave, bool padrao)
{
	SetarSecao(secao);
	return ObterBool(chave, padrao);
}

//------------------------------------------------------------
const char *CConfig::ObterStr(const char * chave, const char * padrao)
{
	return get_config_string(m_secao, chave, padrao);
}

//------------------------------------------------------------
const char *CConfig::ObterStr(const char * secao, const char * chave, const char * padrao)
{
	SetarSecao(secao);
	return get_config_string(m_secao, chave, padrao);
}

//------------------------------------------------------------
void CConfig::SetarInt(const char * chave, int valor)
{
	set_config_int(m_secao, chave, valor);
}

//------------------------------------------------------------
void CConfig::SetarInt(const char * secao, const char * chave, int valor)
{
	SetarSecao(secao);
	set_config_int(m_secao, chave, valor);
}

//------------------------------------------------------------
void CConfig::SetarStr(const char * chave, const char * valor)
{
	set_config_string(m_secao, chave, valor);
}

//------------------------------------------------------------
void CConfig::SetarStr(const char * secao, const char * chave, const char * valor)
{
	SetarSecao(secao);
	set_config_string(m_secao, chave, valor);
}

//------------------------------------------------------------
void CConfig::SetarBool(const char * chave, bool valor)
{
	set_config_int(m_secao, chave, (valor ? 1: 0));
}

//------------------------------------------------------------
void CConfig::SetarBool(const char * secao, const char * chave, bool valor)
{
	SetarSecao(secao);
	SetarBool(chave, valor);
}
