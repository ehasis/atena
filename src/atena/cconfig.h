 /*------------------------------------------------------------*
 *  cconfig.h - Manipulação de arquivos de Configuração
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: sexta-feira, 22 de fevereito de 2002
*
*
*
*------------------------------------------------------------*/

#ifndef cconfig_h_incluido
#define cconfig_h_incluido

#include "callegro.h"

class CConfig
{
public:
	//Constructors/Destructor
	CConfig();
	CConfig(const char * arquivo);

	//Propriedades
	void SetarArquivo(const char * arquivo);
	void SetarSecao(const char * secao);

	void SetarBool(const char * chave, bool valor);
	void SetarBool(const char * secao, const char * chave, bool valor);
	void SetarInt(const char * chave, int valor);
	void SetarInt(const char * secao, const char * chave, int valor);
	void SetarStr(const char * chave, const char * valor);
	void SetarStr(const char * secao, const char * chave, const char * valor);

	int ObterInt(const char * chave, int padrao = 0);
	int ObterInt(const char * secao, const char * chave, int padrao = 0);
	bool ObterBool(const char * chave, bool padrao = false);
	bool ObterBool(const char * secao, const char * chave, bool padrao = false);
	const char *ObterStr(const char * chave, const char * padrao = "");
	const char *ObterStr(const char * secao, const char * chave, const char * padrao = "");

private:
	char m_arquivo[64];
	char m_secao[64];

};

#endif

