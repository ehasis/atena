/*------------------------------------------------------------*
 *  menu.hpp - Interface com o Modulo de Menu
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quinta-feira, 19 de julho de 2001
*
*  
*
*
*------------------------------------------------------------*/

#ifndef cmenu_h_incluido
#define cmenu_h_incluido

class CMenuH
{
public:
	CMenuH(FONT *_fonte, int _cor_texto, int _cor_selecao);
	~CMenuH();
	void Adicionar(const char *texto);
	int Executar();

private:
	FONT *fonte;
	BITMAP *cp_screen, *bmp_menu;
	char menu[10][80];
	int num_itens;
	int pos_atual;
	int largura, altura;
	int cor_texto, cor_selecao;
};

#endif