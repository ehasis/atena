 /*------------------------------------------------------------*
 *  gaconfig.h - Manipulação de Arquivos de Configurações
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quarta-feira, 09 de abril de 2003
*
*  Alterações:
*
*------------------------------------------------------------*/
#ifndef GACONFIG_H_INCLUIDO
#define GACONFIG_H_INCLUIDO

#include "galib.h"

// - Utilizando o Metodo Antigo da Allegro
class GAConfig
{
public:
	GAConfig();
	virtual ~GAConfig();

public:
	void Abrir(const char *arquivo);
	void Fechar();

	void FixarSecao(const char *secao);
	void FixarBool(const char *chave, bool valor);
	void FixarBool(const char *secao, const char *chave, bool valor);
	void FixarInt(const char *chave, int valor);
	void FixarInt(const char *secao, const char *chave, int valor);
	void FixarStr(const char *chave, const char *valor);
	void FixarStr(const char *secao, const char *chave, const char *valor);

	bool ObterBool(const char *chave, bool padrao = false);
	bool ObterBool(const char *secao, const char *chave, bool padrao = false);
	int	ObterInt(const char *chave, int padrao = 0);
	int ObterInt(const char *secao, const char *chave, int padrao = 0);
	const char *ObterStr(const char *chave, const char *padrao = "");
	const char *ObterStr(const char *secao, const char *chave, const char *padrao = "");

private:
	char m_arquivo[256];
	char m_secao[64];
};

#endif
