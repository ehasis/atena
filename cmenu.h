/*------------------------------------------------------------*
 *  menu.hpp - Interface com o Modulo de Menu
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quinta-feira, 19 de julho de 2001
*
*  Henrique em 21/02/2002
*   - Adicionado possibilidade m_alinhamento
*   - Adicionado propriedades
*
*------------------------------------------------------------*/

#ifndef cmenu_h_incluido
#define cmenu_h_incluido

#define NUMERO_ITENS 30

//------------------------------------------------------------
enum EAlinhamentoMenu
{
	eAlinharEsquerda,
	eAlinharDireita,
	eAlinharCentro
};

//------------------------------------------------------------
class CMenuH
{
public:
	//Constructor/Destructor
	CMenuH();
	CMenuH(FONT * fonte, int cor_texto, int cor_selecao);
	CMenuH(FONT * fonte, int cor_texto, int cor_selecao, int x, int y);
	~CMenuH();

	//Propriedades
	void SetarAlinhamento(EAlinhamentoMenu alinhamento);
	void SetarFonte(FONT * fonte);
	void SetarCorTexto(int cor_texto);
	void SetarCorSelecao(int cor_selecao);
	void SetarX(int x);
	void SetarY(int y);
	void SetarTexto(int indice, const char * texto);
	void SetarNumeroItens(int numero_itens);

	//Metodos
	void Adicionar(const char * texto);
	void Adicionar(const char * texto, int linha, int coluna);

	int Executar();

private:
	int m_x, m_y;
	int m_num_itens;
	int m_pos_atual;
	int m_largura, m_altura;
	int m_cor_texto, m_cor_selecao;
	int m_altura_caractere;
	char m_item[NUMERO_ITENS][80];
	EAlinhamentoMenu m_alinhamento;

	FONT *m_fonte;
	BITMAP *m_cp_screen, *m_bmp_menu;


	//Metodos
	void Escrever(BITMAP * bmp, const char * texto, int linha, int cor);
};

#endif