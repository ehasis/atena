 /*------------------------------------------------------------*
 *  cbonus.h - Implementação da Classe para bonus
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: domingo, 14 de julho de 2002
*
*  Alterações:
*
*------------------------------------------------------------*/

#ifndef cbonus_h_incluido
#define cbonus_h_incluido


#include "cobjeto.h"
#include "ccolecaoavancada.h"


typedef enum
{
	eBonusEnergiaTotal
} EBonus;


typedef enum
{
	eBonusNormal,
	eBonusInativo
} EStatusBonus;


//------------------------------------------------------------
template< class cls >
class CBonus : public CObjetoAvancado
{
	public:
		CBonus();
		static void CarregarArquivoDados(DATAFILE * dat_arquivo);
		static void DescarregarArquivoDados();
		void Iniciar(int tipo, int x, int y, CColecaoAvancada< cls > * alvo);
		void Desenhar(CTela & tela, int x_real, int y_real);
		void Atualizar(TRect area);
		void Sonorizar();
		void Finalizar();
	
	protected:
		int m_tipo;	// EBonus;
		EStatusBonus m_status;
		static DATAFILE *m_dat_arquivo;
		CColecaoAvancada< cls > * m_alvo;
		int dir_x, dir_y;
};

//------------------------------------------------------------
// Membros static
template< class cls >
DATAFILE *CBonus< cls >::m_dat_arquivo = NULL;


//------------------------------------------------------------
template< class cls >
void CBonus< cls >::CarregarArquivoDados(DATAFILE * dat_arquivo)
{
	Log("CBonus::CarregarArquivoDados();");
	if(m_dat_arquivo) DescarregarArquivoDados();
	m_dat_arquivo = dat_arquivo;
	if (!m_dat_arquivo) Erro("Código do erro:", "1000");
}


//------------------------------------------------------------
template< class cls >
void CBonus< cls >::DescarregarArquivoDados()
{
	Log("CBonus::DescarregarArquivoDados();");
	unload_datafile(m_dat_arquivo);
	m_dat_arquivo = NULL;
}


//------------------------------------------------------------
// Construtor
template< class cls >
CBonus< cls >::CBonus< cls >()
{
}
	

//------------------------------------------------------------
template< class cls >
void CBonus< cls >::Iniciar(int tipo, int x, int y, CColecaoAvancada< cls > * alvo)
{
	m_tipo	 = tipo;
	m_x		 = x;
	m_y		 = y;
	m_quadro = 0;
	m_largura = 50;
	m_altura = 50;
	m_alvo = alvo;
	m_status = eBonusNormal;
	dir_x = (rand() % 2) * -5 + 1;
	dir_y = (rand() % 2) * -5 + 1;
}


//------------------------------------------------------------
template< class cls >
void CBonus< cls >::Desenhar(CTela &tela, int x_real, int y_real)
{
	switch(m_status)
	{
		case eBonusNormal:
			tela.MaskedBlit((BITMAP *) m_dat_arquivo[(m_tipo * 2)].dat, eCamadaEfeitos, m_quadro * m_largura, 0, m_x - x_real, m_y - y_real, m_largura, m_altura);
			break;
	}
}


//------------------------------------------------------------
template< class cls >
void CBonus< cls >::Atualizar(TRect area)
{
	if(ChecarColisao(area))
	{
		if(m_x < area.x1 ) dir_x = 5;
		else if(ObterX2() > area.x2) dir_x = -5;

		if(m_y < area.y1 ) dir_y = 5;
		else if(ObterY2() > area.y2) dir_y = -5;

		m_x += dir_x;
		m_y += dir_y;

		if(m_status == eBonusNormal)
		{
			m_quadro = m_quadro == 3 ? 0 : m_quadro + 1;
			if(m_alvo->ChecarColisao(ObterRect())) 
			{
				m_status = eBonusInativo;
				m_alvo->Obter().SetarBonus(m_tipo);
			}
		}
	}
}


//------------------------------------------------------------
template< class cls >
void CBonus< cls >::Sonorizar()
{
	
}


//------------------------------------------------------------
template< class cls >
void CBonus< cls >::Finalizar()
{
	
}
#endif