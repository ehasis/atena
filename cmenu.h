/*------------------------------------------------------------*
 *  menu.hpp - Interface com o Modulo de Menu
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quinta-feira, 19 de julho de 2001
*
*  Henrique em 21/02/2002
*   - Adicionado possibilidade alinhamento
*   - Adicionado propriedades
*
*------------------------------------------------------------*/

#ifndef cmenu_h_incluido
#define cmenu_h_incluido

#define NUMERO_OPCOES_MENU 20

enum EAlinhamentoMenu
{
	eAlinharEsquerda,
	eAlinharDireita,
	eAlinharCentro
};

class CMenuH
{
public:
	//Constructor/Destructor
	CMenuH();
	CMenuH(FONT *_fonte, int _cor_texto, int _cor_selecao);
	CMenuH(FONT *_fonte, int _cor_texto, int _cor_selecao, int _x, int _y);
	~CMenuH();
	
	//Propriedades
	void SetarAlinhamento(EAlinhamentoMenu _alinhamento);
	void SetarFonte(FONT *_fonte);
	void SetarCorTexto(int _cor_texto);
	void SetarCorSelecao(int _cor_selecao);
	void SetarX(int _x);
	void SetarY(int _y);
	void SetarTexto(int _indice, const char *_texto);
	void SetarNumeroItens(int _numero_itens);

	//Metodos
	void Adicionar(const char *_texto);
	int Executar();

private:
	FONT *fonte;
	BITMAP *cp_screen, *bmp_menu;
	char menu[NUMERO_OPCOES_MENU][80];
	int x, y;
	int num_itens;
	int pos_atual;
	int largura, altura;
	int cor_texto, cor_selecao;
	EAlinhamentoMenu alinhamento;
	
	//Metodos
	void Escrever(BITMAP *_bmp, char *_texto, int _linha, int _cor);
};

#endif