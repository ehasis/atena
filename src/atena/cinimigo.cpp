#include "cinimigo.h"

//------------------------------------------------------------
//Constructor
CInimigo::CInimigo()
{
	m_bitmap = NULL;
}

//------------------------------------------------------------
//Destructor
CInimigo::~CInimigo()
{
	Finalizar();
}

//------------------------------------------------------------
void CInimigo::Iniciar(TObjeto &obj)
{
	m_tipo_objeto	= (EObjeto)obj.tipo;
	m_subtipo		= obj.subtipo;
	m_x				= obj.x;
	m_y				= obj.y;
	m_energia		= obj.energia;
	m_velocidade	= obj.velocidade;
	m_bitmap		= load_bitmap(obj.arquivo, NULL);
	m_largura		= m_bitmap->w;
	m_altura		= m_bitmap->h;

	m_quadro		= 0;
	m_ativo			= 1;
	m_visivel		= 1;
	m_angulo		= 0;
	m_tempo			= 0;
	m_status		= eInimigoNormal;

	m_armas.Adicionar();
	m_armas.Obter().Iniciar(eArmaInvisivel, m_x, m_y);
}

//------------------------------------------------------------
void CInimigo::Finalizar()
{
	m_armas.Finalizar();

	if (m_bitmap != NULL)
		destroy_bitmap(m_bitmap);
	m_bitmap = NULL;
}

//------------------------------------------------------------
void CInimigo::Sonorizar()
{
	/*
	if(m_status == eAlienExplosao
	&& m_quadro == 0)
	{
		play_sample(m_dat_arquivo.Sample(WAV_ALIEN_EXPLOSAO), 128, 128, 1000, 0);
	}
	/**/

	m_armas.Sonorizar();
}

//------------------------------------------------------------
CColecaoAvancada< CArma > & CInimigo::ObterArmas()
{
	return m_armas;
}

//------------------------------------------------------------
void CInimigo::SetarStatus(EStatusInimigo status)
{
	m_status = status;
}

//------------------------------------------------------------
EStatusInimigo CInimigo::ObterStatus()
{
	return m_status;
}
