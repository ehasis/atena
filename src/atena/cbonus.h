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

#include "callegro.h"

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
		static void CarregarArquivoDados(const char *arquivo);
		static void DescarregarArquivoDados();
		void Iniciar(int tipo, int x, int y, CColecaoAvancada< cls > * alvo);
		void Desenhar(CTela & tela, int x_real, int y_real);
		void Atualizar(TRect area);
		void Sonorizar();
		void Finalizar();
	
	protected:
		int m_tipo;	// EBonus;
		EStatusBonus m_status;
		static GADados m_dat_arquivo;
		CColecaoAvancada< cls > * m_alvo;
		int dir_x, dir_y;
};

//------------------------------------------------------------
// Membros static
template< class cls >
GADados CBonus< cls >::m_dat_arquivo;


//------------------------------------------------------------
template< class cls >
void CBonus< cls >::CarregarArquivoDados(const char *arquivo)
{
	Log("CBonus::CarregarArquivoDados();");
	m_dat_arquivo.Abrir(arquivo);
}


//------------------------------------------------------------
template< class cls >
void CBonus< cls >::DescarregarArquivoDados()
{
	Log("CBonus::DescarregarArquivoDados();");
	m_dat_arquivo.Fechar();
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
			tela.MaskedBlit(m_dat_arquivo.Bitmap((m_tipo * 2)), eCamadaEfeitos, m_quadro * m_largura, 0, m_x - x_real, m_y - y_real, m_largura, m_altura);
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

