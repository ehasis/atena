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
	SetarArquivo("config.ini");
	SetarSecao("config");
}

//------------------------------------------------------------
CConfig::CConfig(const char *_arquivo)
{
	SetarArquivo(_arquivo);
	SetarSecao("config");
}

//------------------------------------------------------------
void CConfig::SetarArquivo(const char *_arquivo)
{
	sprintf(arquivo, _arquivo);
	set_config_file(arquivo);
}

//------------------------------------------------------------
void CConfig::SetarSecao(const char *_secao)
{
	sprintf(secao, _secao);
}

//------------------------------------------------------------
int CConfig::ObterInt(const char *_chave, int _padrao)
{
	return get_config_int(secao, _chave, _padrao);
}

//------------------------------------------------------------
int CConfig::ObterInt(const char *_secao, const char *_chave, int _padrao)
{
	SetarSecao(_secao);
	return get_config_int(secao, _chave, _padrao);
}

//------------------------------------------------------------
const char *CConfig::ObterStr(const char *_chave, const char *_padrao)
{
	return get_config_string(secao, _chave, _padrao);
}

//------------------------------------------------------------
const char *CConfig::ObterStr(const char *_secao, const char *_chave, const char *_padrao)
{
	SetarSecao(_secao);
	return get_config_string(secao, _chave, _padrao);
}

//------------------------------------------------------------
void CConfig::SetarInt(const char *_chave, int _valor)
{
	set_config_int(secao, _chave, _valor);
}

//------------------------------------------------------------
void CConfig::SetarInt(const char *_secao, const char *_chave, int _valor)
{
	SetarSecao(_secao);
	set_config_int(secao, _chave, _valor);
}

//------------------------------------------------------------
void CConfig::SetarStr(const char *_chave, const char *_valor)
{
	set_config_string(secao, _chave, _valor);
}

//------------------------------------------------------------
void CConfig::SetarStr(const char *_secao, const char *_chave, const char *_valor)
{
	SetarSecao(_secao);
	set_config_string(secao, _chave, _valor);
}
