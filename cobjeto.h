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

#include "ctela.h"
#include "erro.h"
#include "cexplosao.h"

//-----------------------------------------------
// Enumeracoes
typedef enum
{
	eBonus,
	eConstrucao,
	eAlien,
	eSeresVivo,
	eFundo,
	eVeiculo,
	eTiro
} EObjeto;

typedef struct
{
	EObjeto tipo;
	int subtipo;
	int x;
	int y;
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
// Classe básica para manipulação de objetos
class CObjetoBasico
{
	public:
		void Iniciar(int x, int y, int largura, int altura);
		int ChecarColisao(TRect rect);
		int ChecarColisao(int x1, int y1, int x2, int y2);
		int ChecarColisao(int x, int y);
		int ChecarColisaoX(int x1, int x2);
		int ChecarColisaoY(int y1, int y2);

		TRect ObterRect();

		void SetarX(int x);
		int ObterX();
		int ObterPMX();
		int ObterX2();
		void IncX(int incremento);
		void DecX(int decremento);

		void SetarY(int y);
		int ObterY();
		int ObterPMY();
		int ObterY2();
		void IncY(int incremento);
		void DecY(int decremento);

		void SetarXY(int x, int y);
		void SetarLargura(int largura);
		int ObterLargura();
		void SetarAltura(int altura);
		int ObterAltura();

		void SetarTipoObjeto(EObjeto tipo_objeto);
		EObjeto ObterTipoObjeto();
		CObjetoBasico *RetornarObjetoBasico();

	protected:
		int m_x, m_y;
		int m_largura, m_altura;
		EObjeto m_tipo_objeto;
};


//------------------------------------------------------------
// Classe intermediária para manipulação de objetos

class CObjeto : public CObjetoBasico
{
	public:
		void SetarAngulo(int angulo);
		int ObterAngulo();
	protected:
		int m_angulo;
		int m_raio;
};


//------------------------------------------------------------
// Classe avançada para manipulação de objetos
class CObjetoAvancado : public CObjeto
{
	public:
		void SetarAtivo(int ativo);
		int ObterAtivo();
		int ObterVisivel();
		void SetarVisivel(int visivel);
		void DesenharExplosao(CTela &m_tela, int x_real, int y_real, int x, int y, int raio, int num_particulas);
		void DesenharExplosaoRadial(int x_real, int y_real, int x, int y, int raio);
		CObjetoAvancado *RetornarObjetoAvancado();
		int ObterEnergia();
		void IncEnergia(int incremento);
		void DecEnergia(int decremento);
		
	protected:
		int m_ativo;		// Se o objeto esta ativo
		int m_visivel;		// Se o objeto esta visivel
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
		virtual void Atualizar(TRect area, CObjetoAvancado * const alvo);
		virtual void Desenhar(CTela & tela, int x_real, int y_real);
		virtual void Sonorizar();
		virtual void Finalizar();	
};
#endif