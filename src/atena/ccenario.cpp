#include "ccenario.h"

//------------------------------------------------------------
//Constructor
CCenario::CCenario()
{
	m_bitmap = NULL;
}

//------------------------------------------------------------
//Destructor
CCenario::~CCenario()
{
	Finalizar();
}

//------------------------------------------------------------
void CCenario::Iniciar(TObjeto &obj)
{
	m_tipo_objeto	= (EObjeto)obj.tipo;
	//m_subtipo		= obj.subtipo;
	m_x				= obj.x;
	m_y				= obj.y;
	//m_energia		= obj.energia;
	//m_velocidade	= obj.velocidade;
	m_bitmap		= load_bitmap(obj.arquivo, NULL);
	m_largura		= m_bitmap->w;
	m_altura		= m_bitmap->h;

	//m_quadro		= 0;
	m_ativo			= 1;
	m_visivel		= 1;
	m_angulo		= 0;
	//m_tempo			= 0;
	//m_status		= eInimigoNormal;
}

//------------------------------------------------------------
void CCenario::Finalizar()
{
	if (m_bitmap != NULL)
		destroy_bitmap(m_bitmap);
	m_bitmap = NULL;
}

