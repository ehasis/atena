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

class CConfig
{
public:
	//Constructors/Destructor
	CConfig();
	CConfig(const char *_arquivo);
	
	//Propriedades
	void SetarArquivo(const char *_arquivo);
	void SetarSecao(const char *_secao);
	
	void SetarInt(const char *_chave, int _valor);
	void SetarInt(const char *_secao, const char *_chave, int _valor);
	void SetarStr(const char *_chave, const char *_valor);
	void SetarStr(const char *_secao, const char *_chave, const char *_valor);
		
	int ObterInt(const char *_chave, int _padrao = 0);
	int ObterInt(const char *_secao, const char *_chave, int _padrao = 0);
	const char *ObterStr(const char *_chave, const char *_padrao = "");
	const char *ObterStr(const char *_secao, const char *_chave, const char *_padrao = "");

private:
	char arquivo[64];
	char secao[64];

};


#endif