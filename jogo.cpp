 /*------------------------------------------------------------*
 *  jogo.cpp - Rotinas basicas do jogo
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: terça-feira, 04 de setembro de 2001
*
*  Contem a execucao das funcoes de inicializacao
*  relacionadas ao jogo.
*
*
*------------------------------------------------------------*/

#include <allegro.h>

#include "jogo.h"
#include "graficos.h"
#include "nucleo.h"
#include "entrada.h"
#include "vglobal.h"


/*************************************************************/

int final_jogo;

/* Inicializacao do Jogo */
void IniciarJogo()
{
	final_jogo = 0;

	IniciarEntrada();
	IniciarGraficos();
	IniciarObjetos();
	
}

/* Desligamento do Jogo */
void DesligarJogo()
{
	DesligarEntrada();
	DesligarObjetos();
	DesligarGraficos();
}

/* Laco Principal */
void ExecutarJogo()
{
	while(!final_jogo)
	{		
		AtualizarEntrada();
		AtualizarObjetos();
		AtualizarGraficos();
	}
}