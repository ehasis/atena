 /*------------------------------------------------------------*
 *  cobjeto.h - Definicao da Classe Base
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: terça-feira, 22 de Setembro de 2001
*
*  Alteracoes:
*  Diego Giacomelli em 01/01/2002
*   - Alterações na estrutura TRect;
*
*  Diego Giacomelli em 02/01/2002
*   - Implementação dos métodos Colisao(x1, y1, x2, y2),
*     SetarX, ObterX, IncX, DecX, SetarY, ObterY, IncY, DecY,
*     SetarLargura, ObterLargura, SetarAltura, ObterAltura;
*
*  Diego Giacomelli em 04/01/2002
*   - Declaração dos membros de dados (x, y,largura, altura,
*     vi, vx, vy) como protected;
*
*  Diego Giacomelli em 07/01/2002
*   - Alteração do nome do método Colisão para ChecarColisao
*     para adaptar-se aos padrões de nomenclatura;
*
*  Diego Giacomelli em 13/02/2002
*   - Alterado o método DesenharExplosao para aceitar CTela e
*     posicionamento relativo;
*
*  Diego Giacomelli em 15/02/2002
*   - Incluido o membro de dados ativo;
*   - Retirados os membros de dados vi, vx e vy;
*
*  Diego Giacomelli em 28/02/2002
*   - Incluído os membros de dados angulo e raio;
*	- Particionamento de CObjeto em 3 Classes: CObjetoBasico,
*     CObjeto e CObjetoAvancado;
*	- Implementado os métodos Iniciar para CObjetoBasico,
*	  CObjeto e CObjetoAvancado;
*
*  Diego Giacomelli em 01/05/2002
*	- Inserido o membro de dado m_tipo;
*
*  Diego Giacomelli em 22/06/2002
*   - Alterado a nomenclatura dos membros de dados e parâmetros para o padrão
*	  m_<nome do membro de dados> e <nome do parâmetro>, respectivamente.
*
*  Diego Giacomelli em 06/07/2002
*	- Inserido o método SetarVisivel;
*
*  Diego Giacomelli em 07/07/2002
*	- Inseridos os métodos ObterEnergia, IncEnergia e DecEnergia;
*
*  Diego Giacomelli em 20/07/2002
*	- Inseridos os métodos SetatTipoObjeto e ObterTipoObjeto;
*	- Renomeado o membro de dado m_objeto para m_tipo_objeto;
*	- Inserido método SetarXY;
*------------------------------------------------------------*/


#ifndef cobjeto_h_incluido
#define cobjeto_h_incluido

#include "callegro.h"

#include "ctela.h"
#include "erro.h"
#include "cexplosao.h"

//-----------------------------------------------
// Enumeracoes
typedef enum
{
	eAlien = 0,
	eVeiculo,
	eConstrucao,
	eCenario,
	eBonus,
	eFundo,
	eTiro
} EObjeto;

typedef struct
{
	int tipo;
	int subtipo;
	int x;
	int y;
	int energia;
	int velocidade;
	char arquivo[256];
} TObjeto;

typedef enum
{
	eObjetoNormal,
	eObjetoAtingido,
	eObjetoExplosao
};


// Estrutura de um retangulo
typedef struct
{
	int x1, y1;
	int x2, y2;
} TRect;


//------------------------------------------------------------
// CObjetoBasico
//------------------------------------------------------------
class CObjetoBasico
{
public:
	CObjetoBasico();
	void Iniciar(int x, int y, int largura, int altura);

	int ObterX();
	int ObterY();
	int ObterX2();
	int ObterY2();
	int ObterPMX();
	int ObterPMY();
	int	ObterLargura();
	int	ObterAltura();

	void SetarX(int x);
	void SetarY(int y);
	void SetarXY(int x, int y);
	void SetarLargura(int largura);
	void SetarAltura(int altura);

	void IncX(int incremento);
	void IncY(int incremento);
	void DecX(int decremento);
	void DecY(int decremento);

	bool ChecarColisao(int x, int y);
	bool ChecarColisao(int x1, int y1, int x2, int y2);
	bool ChecarColisao(TRect &rect);
	bool ChecarColisao(CObjetoBasico const *obj);
	bool ChecarColisaoX(int x1, int x2);
	bool ChecarColisaoY(int y1, int y2);

	TRect& ObterRect();

	CObjetoBasico *ObterObjetoBasico();

protected:
	int		m_x;
	int		m_y;
	int		m_altura;
	int		m_largura;
	TRect	m_rect;
};


//------------------------------------------------------------
// CObjeto
//------------------------------------------------------------
class CObjeto : public CObjetoBasico
{
public:
	int		ObterAngulo();
	void	SetarAngulo(int angulo);
	void	SetarTipoObjeto(EObjeto tipo_objeto);
	EObjeto ObterTipoObjeto();
	
protected:
	int		m_angulo;
	int		m_raio;
	EObjeto m_tipo_objeto;
};


//------------------------------------------------------------
// CObjetoEstatico
//------------------------------------------------------------
class CObjetoEstatico: public CObjeto
{
public:
	int ObterAtivo();
	int ObterVisivel();
	void SetarAtivo(int ativo);
	void SetarVisivel(int visivel);

protected:
	int m_ativo;		// Se o objeto esta ativo
	int m_visivel;		// Se o objeto esta visivel

};

//------------------------------------------------------------
// CObjetoAvancado
//------------------------------------------------------------
class CObjetoAvancado : public CObjetoEstatico
{
public:
	int ObterEnergia();

	void IncEnergia(int incremento);
	void DecEnergia(int decremento);
	
	void DesenharExplosao(CTela &m_tela, int x_real, int y_real, int x, int y, int raio, int num_particulas);
	void DesenharExplosaoRadial(int x_real, int y_real, int x, int y, int raio);
	
	CObjetoAvancado *ObterObjetoAvancado();
	
protected:
	int m_energia;
	int m_quadro;		// Frame de animação atual
	int m_tempo;		// Contador do n. de iterações que o objeto já passou
	CExplosao m_explosao;

};


//------------------------------------------------------------
// Classe para manipulação de objetos animados
class CObjetoAnimado : public CObjetoAvancado
{
public:
	virtual bool Adicionar(int tipo, int x, int y);
	virtual void Atualizar(TRect &area, CObjetoAvancado * const alvo);
	virtual void Desenhar(CTela & tela, int x_real, int y_real);
	virtual void Sonorizar();
	virtual void Finalizar();	
};



//------------------------------------------------------------
// Métodos INLINE
//------------------------------------------------------------

//------------------------------------------------------------
// retorna os vertices do retangulo do objeto
inline TRect& CObjetoBasico::ObterRect()
{
	m_rect.x1 = m_x;
	m_rect.y1 = m_y;
	m_rect.x2 = m_x + m_largura;
	m_rect.y2 = m_y + m_altura;

	return m_rect;
}

//------------------------------------------------------------
// retorna se ha colisao com o objeto passado como parametro
inline bool CObjetoBasico::ChecarColisao(TRect &rect)
{
	if ((m_x + m_largura < rect.x1)
	||  (m_y + m_altura  < rect.y1)
	||  (m_x           > rect.x2)
	||  (m_y           > rect.y2))
	{
		return false;
	}
	else
	{
		return true;
	}
}

//------------------------------------------------------------
inline bool CObjetoBasico::ChecarColisao(CObjetoBasico const *obj)
{
	if ((m_x + m_largura < obj->m_x)
	||  (m_y + m_altura  < obj->m_y)
	||  (m_x > obj->m_x + obj->m_largura)
	||  (m_y > obj->m_y + obj->m_altura))
	{
		return false;
	}
	else
	{
		return true;
	}
}

//------------------------------------------------------------
inline bool CObjetoBasico::ChecarColisao(int x1, int y1, int x2, int y2)
{
	if ((m_x + m_largura < x1)
	||  (m_y + m_altura  < y1)
	||  (m_x           > x2)
	||  (m_y           > y2))
	{
		return false;
	}
	else
	{
		return true;
	}
}

//------------------------------------------------------------
inline bool CObjetoBasico::ChecarColisao(int x, int y)
{
	if ((m_x + m_largura < x)
	||  (m_y + m_altura  < y)
	||  (m_x           > x)
	||  (m_y           > y))
	{
		return false;
	}
	else
	{
		return true;
	}
}

//------------------------------------------------------------
inline bool CObjetoBasico::ChecarColisaoX(int x1, int x2)
{
	if ((m_x + m_largura < x1)
	||  (m_x           > x2))
	{
		return false;
	}
	else
	{
		return true;
	}
}


//------------------------------------------------------------
inline bool CObjetoBasico::ChecarColisaoY(int y1, int y2)
{
	if ((m_y + m_altura < y1)
	||  (m_y          > y2))
	{
		return false;
	}
	else
	{
		return true;
	}
}

//------------------------------------------------------------
inline void CObjetoBasico::SetarX(int x)
{
	m_x = x;
}

//------------------------------------------------------------
inline int CObjetoBasico::ObterX()
{
	return m_x;
}

//------------------------------------------------------------
inline int CObjetoBasico::ObterPMX()
{
	return (m_x + m_largura / 2);
}

//------------------------------------------------------------
inline int CObjetoBasico::ObterX2()
{
	return (m_x + m_largura);
}

//------------------------------------------------------------
inline void CObjetoBasico::IncX(int incremento)
{
	m_x += incremento;
}

//------------------------------------------------------------
inline void CObjetoBasico::DecX(int decremento)
{
	m_x -= decremento;
}

//------------------------------------------------------------
inline void CObjetoBasico::SetarY(int y)
{
	m_y = y;
}

//------------------------------------------------------------
inline int CObjetoBasico::ObterY()
{
	return m_y;
}

//------------------------------------------------------------
inline int CObjetoBasico::ObterPMY()
{
	return (m_y + m_altura / 2);
}

//------------------------------------------------------------
inline int CObjetoBasico::ObterY2()
{
	return (m_y + m_altura);
}

//------------------------------------------------------------
inline void CObjetoBasico::IncY(int incremento)
{
	m_y += incremento;
}

//------------------------------------------------------------
inline void CObjetoBasico::DecY(int decremento)
{
	m_y -= decremento;
}

//------------------------------------------------------------
inline void CObjetoBasico::SetarXY(int x, int y)
{
	m_x = x;
	m_y = y;
}

//------------------------------------------------------------
inline void CObjetoBasico::SetarLargura(int largura)
{
	m_largura = largura;
}


//------------------------------------------------------------
inline int CObjetoBasico::ObterLargura()
{
	return m_largura;
}


//------------------------------------------------------------
inline void CObjetoBasico::SetarAltura(int altura)
{
	m_altura = altura;
}


//------------------------------------------------------------
inline int CObjetoBasico::ObterAltura()
{
	return m_altura;
}


//------------------------------------------------------------
inline CObjetoBasico *CObjetoBasico::ObterObjetoBasico()
{
	return (CObjeto *)this;
}


//------------------------------------------------------------
// CObjeto
//------------------------------------------------------------
inline int CObjeto::ObterAngulo()
{
	return m_angulo;
}

//------------------------------------------------------------
inline void CObjeto::SetarAngulo(int angulo)
{
	m_angulo = angulo;
}

//------------------------------------------------------------
inline void CObjeto::SetarTipoObjeto(EObjeto tipo_objeto)
{
	m_tipo_objeto = tipo_objeto;
}


//------------------------------------------------------------
inline EObjeto CObjeto::ObterTipoObjeto()
{
	return m_tipo_objeto;
}

//------------------------------------------------------------
// CObjetoEstatico
//------------------------------------------------------------
inline void CObjetoEstatico::SetarAtivo(int ativo)
{
	m_ativo = ativo;
}

//------------------------------------------------------------
inline int CObjetoEstatico::ObterAtivo()
{
	return m_ativo;
}

//------------------------------------------------------------
inline int CObjetoEstatico::ObterVisivel()
{
	return m_visivel;
}

//------------------------------------------------------------
inline void CObjetoEstatico::SetarVisivel(int visivel)
{
	m_visivel = visivel;
}


//------------------------------------------------------------
// CObjetoAvancado
//------------------------------------------------------------
inline void CObjetoAvancado::DesenharExplosao(CTela &m_tela, int x_real, int y_real, int x, int y, int raio, int num_particulas)
{
	m_explosao.IniciarExplosao(x - x_real, y - y_real, raio, num_particulas);
}


//------------------------------------------------------------
inline void CObjetoAvancado::DesenharExplosaoRadial(int x_real, int y_real, int x, int y, int raio)
{
	m_explosao.IniciarExplosaoRadial (x - x_real, y - y_real, raio);
}


//------------------------------------------------------------
inline CObjetoAvancado *CObjetoAvancado::ObterObjetoAvancado()
{
	return (CObjetoAvancado *)this;
}


//------------------------------------------------------------
inline int CObjetoAvancado::ObterEnergia() 
{
	return m_energia;
}


//------------------------------------------------------------
inline void CObjetoAvancado::IncEnergia(int incremento)
{
	m_energia += incremento;
}


//------------------------------------------------------------
inline void CObjetoAvancado::DecEnergia(int decremento)
{
	m_energia -= decremento;
}

#endif

