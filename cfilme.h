 /*------------------------------------------------------------*
 *  cfilme.h - Definição da Classe de Filmes
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: sábado, 29 de junho de 2002
*
*  Alterações:
*
*  Henrique em 12/07/2002
*   - Modificado para o script do filme através da
*     classe GAScript
*
*------------------------------------------------------------*/

#ifndef cfilme_h_incluido
#define cfilme_h_incluido

#include <allegro.h>
#include "galib.h"

class CFilme: public GAEventoScript
{
public:
	CFilme();
	~CFilme();

	bool Escrever(const char *texto);
	void Executar(const char *arquivo);
	virtual int ExecutarInstrucao(int cmd, const std::string &par);

private:
	GADados m_dados;
};

#endif