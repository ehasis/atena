 /*------------------------------------------------------------*
 *  ctiro.cpp - Implementação da Classe de tiro
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: terça-feira, 13 de janeiro de 2002
*
*
*------------------------------------------------------------*/

#include "erro.h"
#include "ctiro.h"


//------------------------------------------------------------
// Membros static
GADados CTiro::m_dat_arquivo;


//------------------------------------------------------------
void CTiro::CarregarArquivoDados(const char *arquivo)
{
	m_dat_arquivo.Abrir(arquivo);
}


//------------------------------------------------------------
void CTiro::DescarregarArquivoDados()
{
	m_dat_arquivo.Fechar();
}

//------------------------------------------------------------
CTiro::CTiro()
{
}