 /*------------------------------------------------------------*
 *  galib.h - Biblioteca do Grupo Atena
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: quinta-feira, 28 de junho de 2002
*
*  Alterações:
*
*  Henrique em 10/07/2002
*   - Implementado manipulação de script, com as classes:
*	  GAInstrucao, GATradutor, GAScript e GAEventoScript
*
*  Henrique em 14/07/2002
*	- Adicionado sobrecarga do operador [] na classe GADados
*
*  Henrique em 09/04/2003
*	- Cabeçalhos separados em arquivos diferentes
*
*  Henrique em 03/07/2003
*	- Incluido classe GABarraProgresso
*
*------------------------------------------------------------*/
#ifndef GALIB_H_INCLUIDO
#define GALIB_H_INCLUIDO

// desabilita as mensagens de warning de identificador
// muito grande para o debug (está no msdn)
//#ifdef _DEBUG
//#pragma warning (disable : 4786)
//#endif

//Allegro Font
#include "../alfont/alfont.h"

#include "gascript.h"
#include "gaconfig.h"
#include "gadados.h"
#include "gabarra.h"

#endif

