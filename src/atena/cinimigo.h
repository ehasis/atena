 /*------------------------------------------------------------*
 *  calien.h - Classe CAlien
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: terça-feira, 13 de dezembro de 2001
*
*  Alterações:
*
*-----------------------------------------------------------*/


#ifndef CINIMIGO_H_INCLUIDO
#define CINIMIGO_H_INCLUIDO

#include "callegro.h"

#include "cobjeto.h"
#include "ccolecaoavancada.h"
#include "carma.h"


enum EStatusInimigo
{
	eInimigoNormal = 0,
	eInimigoEscudo,
	eInimigoAtingido,
	eInimigoExplosao,
	eInimigoInativo
};

class CInimigo : public CObjetoAvancado
{
public:

	CInimigo();
	~CInimigo();

	virtual void Iniciar(TObjeto &obj);
	virtual void Finalizar();

	CColecaoAvancada< CArma > & ObterArmas();

	bool Colidir(TRect &area, int energia);
	void Sonorizar();
	void DecEnergia(int decremento);
	void SetarStatus(EStatusInimigo status);
	EStatusInimigo ObterStatus();

protected:
	EStatusInimigo m_status;
	int m_subtipo;
	int m_velocidade;
	BITMAP *m_bitmap;
	CColecaoAvancada< CArma > m_armas;
};

//------------------------------------------------------------
inline void CInimigo::DecEnergia(int decremento)
{
	m_energia -= decremento;

	if(m_energia <= 0)
	{
		m_status = eInimigoExplosao;
		m_quadro = 0;
	}
}

//------------------------------------------------------------
inline bool CInimigo::Colidir(TRect &area, int energia)
{
	if(m_status != eInimigoInativo
	&& m_status != eInimigoExplosao
	&& ChecarColisao(area))
	{
		DecEnergia(energia);
		return true;
	}
	return false;
}

#endif