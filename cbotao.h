 /*------------------------------------------------------------*
 *  cbotao.h - Classe CBotao
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: sábado, 23 de fevereiro de 2002
*
*
*------------------------------------------------------------*/


#ifndef cbotao_h_incluido
#define cbotao_h_incluido


#include <stdio.h>
#include <allegro.h>
#include "cobjeto.h"
#include "erro.h"


//------------------------------------------------------------
// Classe para os botoes
class CBotao : public CObjetoAvancado
{
public:
	void Iniciar(char * nome_arquivo_dat, const char * nome_botao, int mouse_botao, int (*_acao) (), int x, int y);
	int Atualizar(int mouse_x, int mouse_y);
	void Desenhar(CTela & tela, ECamada camada);
	void Finalizar();

private:
	DATAFILE *m_dat_botao;
	int m_mouse_botao;	// 0-Ambos os botoes, 1-botao esquerdo, 2-botao direito
	int (*m_acao) ();		// Ponteiro para procedure chamada quando o botao for pressionado
};

#endif