 /*------------------------------------------------------------*
 *  cveiculo.h - Classe CVeiculo
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: terça-feira, 09 de julho de 2002
*
*  Alterações:
*
*  Diego Giacomelli em 20/07/2002
*	- Substituido m_tiros por m_armas; 
*------------------------------------------------------------*/

#ifndef cveiculo_h_incluido
#define cveiculo_h_incluido

#include "cinimigo.h"

typedef enum
{
	eVeiculoCarro,
	eVeiculoTanque
} EVeiculo;


//------------------------------------------------------------
// Classe para as veiculos
class CVeiculo : public CInimigo
{
public:
	virtual void Iniciar(TObjeto &obj);
	virtual void Finalizar();

	void Desenhar(CTela &tela, int x_real, int y_real);
	void Atualizar(TRect &area, CObjetoAvancado * const alvo);

protected:
	int m_flag_x;
	int m_flag_y;
	int m_dir_x;
	int m_dir_y;
	int m_dir_r;		
};

#endif

