 /*------------------------------------------------------------*
 *  zeus.cpp - Implementacao do editor de fases
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: sexta-feira, 19 de outubro de 2001
*
*
*
*------------------------------------------------------------*/

#include "zeus.h"
#include "..\vglobal.h"

int flag_fase, flag_obj, flag_desenhar, flag_alterado;
CFase fase;
BITMAP *zeus_screen;	/* BITMAP auxiliar para o double buffering */
BITMAP *bmp_fundo;      /* BITMAP para o fundo atualmente aberto */
DATAFILE *dat_aliens;   /* DATAFILE para os aliens atualmente abertos */
DATAFILE *dat_imagem;   /* DATAFILE para as imagens da interface do Zeus - NAO SAO OBJETOS DAS FASES */
CLadrilho menu_obj_ladrilhos[MENU_OBJ_LARGURA_LADRILHO][MENU_OBJ_ALTURA_LADRILHO];	/* CLadrilho's para o menu dos objetos */
CLadrilho ladrilho, ladrilho_sel_esquerdo, ladrilho_sel_direito, ladrilho_h_flip, ladrilho_v_flip, ladrilho_rotacao;
CAlien alien_sel_esquerdo, alien_sel_direito;
char arquivo_fundo[ARQUIVO_NOME_COMPRIMENTO];
char arquivo_fase[ARQUIVO_NOME_COMPRIMENTO];
char arquivo_aliens[ARQUIVO_NOME_COMPRIMENTO];
char caminho[ARQUIVO_NOME_COMPRIMENTO];
int exibir_obj; //EObjeto

MENU menu_exibir[] =
{
	{ "&Bonus",			NULL,   NULL,	FALSE,	NULL },
	{ "&Construcoes",   NULL,   NULL,	FALSE,	NULL },
	{ "&Aliens",		NULL,   NULL,	FALSE,	NULL },
	{ "&Seres Vivos",   NULL,   NULL,	FALSE,	NULL },
	{ "&Fundo",			NULL,   NULL,	FALSE,	NULL },
	{ "&Veiculos",		NULL,   NULL,	FALSE,	NULL },
	{ NULL,				NULL,	NULL,   FALSE,	NULL }
};


//------------------------------------------------------------
/* Inicializa  Zeus */
void IniciarZeus(void)
{
	int nome_comprimento;
	char arquivo_selecionado[ARQUIVO_NOME_COMPRIMENTO];
	TLadrilho lad;

	zeus_screen = create_bitmap(SCREEN_W, SCREEN_H);

	flag_fase = FALSE;
	flag_obj = FALSE;
	flag_desenhar = TRUE;
	flag_alterado = FALSE;
	exibir_obj = -1;

	dat_imagem = load_datafile("imagem.dat");
	if(!dat_imagem)
	{
		Erro("ERRO - Arquivo de imagem nao foi carregado!", "imagem.dat");
		alert("ERRO - Arquivo de imagem nao foi carregado!", NULL, NULL, "OK", NULL, NULL, NULL);
		return;
	}

	strcpy(arquivo_fase, "");
	strcpy(arquivo_fundo, "");

	get_executable_name(arquivo_selecionado, sizeof(arquivo_selecionado));
	nome_comprimento = strlen(arquivo_selecionado);
	strncpy(caminho, arquivo_selecionado, nome_comprimento - 8);
	strcpy(caminho, "fases\\");

	lad.bmp_x = 0;
	lad.bmp_y = 0;
	lad.x = LADRILHO_H_FLIP_X;
	lad.y = LADRILHO_H_FLIP_Y;
	lad.h_flip = FALSE;
	lad.v_flip = FALSE;
	lad.rotacao = 0;

	strcpy(lad.arquivo_bmp, "dat_imagem.dat");
	ladrilho_h_flip.Iniciar(lad, LADRILHO_LARGURA, LADRILHO_ALTURA, (BITMAP*)dat_imagem[BOT_H_FLIP].dat);

	lad.x = LADRILHO_V_FLIP_X;
	lad.y = LADRILHO_V_FLIP_Y;
	ladrilho_v_flip.Iniciar(lad, LADRILHO_LARGURA, LADRILHO_ALTURA, (BITMAP*)dat_imagem[BOT_V_FLIP].dat);

	/*lad.x = LADRILHO_ROTACAO_X;
	lad.y = LADRILHO_ROTACAO_Y;
	ladrilho_rotacao.Iniciar(lad, LADRILHO_LARGURA, LADRILHO_ALTURA, (BITMAP*)dat_imagem[BOT_ROTACAO].dat);
	*/
	lad.bmp_x = -1;
	lad.bmp_y = -1;
	lad.x = LADRILHO_SEL_ESQUERDO_X;
	lad.y = LADRILHO_SEL_ESQUERDO_Y;
	lad.h_flip = FALSE;
	lad.v_flip = FALSE;
	lad.rotacao = 0;

	DesenharTela();
	show_mouse(screen);
}


//------------------------------------------------------------
/* Execucao geral do Zeus */
void ExecutarZeus(void)
{
	for(;;)
	{
		if(flag_desenhar)
		{
			scare_mouse();
			DesenharTela();
			draw_sprite(screen, zeus_screen, 0, 0);
			unscare_mouse();
			flag_desenhar = FALSE;
		}

		if(key[KEY_ESC])
		{
			if(Sair())
				break;
		}

		/* Menu */
		if(mouse_y > 0 
		&& mouse_y < MENU_ALTURA
		&& (mouse_b & 1 
		|| mouse_b & 2))
		{
			if(!VerificarMenuArquivo())
				if(!VerificarMenuObjetos())
					if(!VerificarMenuExibir())
						VerificarMenuFerramentas();
		}

		if(flag_obj
		&& (mouse_b & 1
		|| mouse_y & 2))
		{
			/* Menu de objetos */
     		if(mouse_x > MENU_OBJ_X1
            && mouse_x < MENU_OBJ_X2
			&& mouse_y > MENU_OBJ_Y1
            && mouse_y < MENU_OBJ_Y2)
			{
				VerificarMenuObj();
			}

			/* Menu Aux */
			if(exibir_obj == eFundo)
			{
				VerificarMenuAux();
			}
		}

		/* Mapa do Editor */
		if(flag_fase)
		{
			VerificarRolaTecla();

			if(flag_obj
			&& mouse_x > MAPA_EDITOR_X1
			&& mouse_x < MAPA_EDITOR_X2
			&& mouse_y > MAPA_EDITOR_Y1
			&& mouse_y < MAPA_EDITOR_Y2)
			{
				VerificarRolaMouse();
				DesenharQuadrado();
				switch(exibir_obj)
				{
					case eAliens:
						VerificarAlien();
						break;
					case eFundo:
						VerificarLadrilho();
						break;
				}
			}
		}		
	}
}


//------------------------------------------------------------
/* Libera memoria e desliga o Zeus*/
void DesligarZeus()
{
	fase.Desligar();
	destroy_bitmap(zeus_screen);
	destroy_bitmap(bmp_fundo);
	unload_datafile(dat_aliens);
	allegro_exit();
	exit(EXIT_SUCCESS);
}


//------------------------------------------------------------
/* Monta o menu dos objetos
Modo 0 = nao inicar selecionados
Modo 1 = inicar selecionados */
void MontarMenuObj(int modo)
{
	register int x, y;
	int  num_obj;
	TLadrilho lad;

	flag_desenhar = TRUE;
	rectfill(zeus_screen, 0, 0, MENU_OBJ_LARGURA, MENU_OBJ_ALTURA, makecol(0, 0, 0));

	/* Desmarca todas as opcoes do menu exibir */
	menu_exibir[0].flags = FALSE;
	menu_exibir[1].flags = FALSE;
	menu_exibir[2].flags = FALSE;
	menu_exibir[3].flags = FALSE;
	menu_exibir[4].flags = FALSE;
	menu_exibir[5].flags = FALSE;

	/* Marca a opcao selecionada */
	if(exibir_obj > -1) menu_exibir[exibir_obj].flags = TRUE;

    num_obj = 0;
	switch(exibir_obj)
	{
		case eAliens:
				for(x = 0; x < MENU_OBJ_LARGURA_LADRILHO; x++)
				{
					for(y = 0; y < MENU_OBJ_ALTURA_LADRILHO; y++)
					{
						lad.bmp_x = 0;
						lad.bmp_y = 0;
						lad.x = x * LADRILHO_LARGURA;
						lad.y = y * LADRILHO_ALTURA;
						lad.h_flip = FALSE;
						lad.v_flip = FALSE;
						lad.rotacao = 0;
						strcpy(lad.arquivo_bmp, "arquivo_aliens");
						menu_obj_ladrilhos[x] [y].Iniciar(lad, LADRILHO_LARGURA, LADRILHO_ALTURA, (BITMAP*)dat_aliens[num_obj].dat);
						menu_obj_ladrilhos[x] [y].Desenhar(zeus_screen);
						rect(zeus_screen, menu_obj_ladrilhos[x][y].ObterX(), menu_obj_ladrilhos[x][y].ObterY(), menu_obj_ladrilhos[x][y].ObterX() + LADRILHO_LARGURA, menu_obj_ladrilhos[x][y].ObterY() + LADRILHO_ALTURA, makecol(100, 100, 100));

						num_obj += 2;
						if(num_obj > 12)
						{
							if(modo)
							{
								lad.x = LADRILHO_SEL_ESQUERDO_X;
								lad.y = LADRILHO_SEL_ESQUERDO_Y;
								// Ladrilho auxiliar
								ladrilho.Iniciar(lad, LADRILHO_LARGURA, LADRILHO_ALTURA, (BITMAP *) dat_aliens[0].dat);
								// Ladrilhos selecionados
								ladrilho_sel_esquerdo.Iniciar(lad, LADRILHO_LARGURA, LADRILHO_ALTURA, (BITMAP *) dat_aliens[0].dat);
								lad.x = LADRILHO_SEL_DIREITO_X;
								lad.y = LADRILHO_SEL_DIREITO_Y;
								ladrilho_sel_direito.Iniciar(lad, LADRILHO_LARGURA, LADRILHO_ALTURA, (BITMAP *) dat_aliens[2].dat);
							}

							ladrilho_sel_esquerdo.Desenhar(zeus_screen);
							ladrilho_sel_direito.Desenhar(zeus_screen);
							return;
						}
					}
				}

				break;

		case eFundo:
			for(x = 0; x < MENU_OBJ_LARGURA_LADRILHO; x++)
				{
					for(y = 0; y < MENU_OBJ_ALTURA_LADRILHO; y++)
					{
						lad.bmp_x = x * LADRILHO_LARGURA;;
						lad.bmp_y = y * LADRILHO_ALTURA;;
						lad.x = x * LADRILHO_LARGURA;
						lad.y = y * LADRILHO_ALTURA;
						lad.h_flip = FALSE;
						lad.v_flip = FALSE;
						lad.rotacao = 0;
						strcpy(lad.arquivo_bmp, arquivo_fundo);

						menu_obj_ladrilhos[x] [y].Iniciar(lad, LADRILHO_LARGURA, LADRILHO_ALTURA, bmp_fundo);
						menu_obj_ladrilhos[x] [y].Desenhar(zeus_screen);
						rect(zeus_screen, menu_obj_ladrilhos[x][y].ObterX(), menu_obj_ladrilhos[x][y].ObterY(), menu_obj_ladrilhos[x][y].ObterX() + LADRILHO_LARGURA, menu_obj_ladrilhos[x][y].ObterY() + LADRILHO_ALTURA, makecol(100, 100, 100));
					}
				}

				if(modo)
				{
					// Ladrilho auxiliar
					ladrilho.Iniciar(menu_obj_ladrilhos[0][0].ObterTLadrilho(), LADRILHO_LARGURA, LADRILHO_ALTURA, bmp_fundo);
					// Ladrilhos selecionados
					ladrilho_sel_esquerdo.Iniciar(menu_obj_ladrilhos[0][0].ObterTLadrilho(), LADRILHO_LARGURA, LADRILHO_ALTURA, bmp_fundo);
					ladrilho_sel_esquerdo.SetarX(LADRILHO_SEL_ESQUERDO_X);
					ladrilho_sel_esquerdo.SetarY(LADRILHO_SEL_ESQUERDO_Y);
					ladrilho_sel_direito.Iniciar(menu_obj_ladrilhos[0][1].ObterTLadrilho(), LADRILHO_LARGURA, LADRILHO_ALTURA, bmp_fundo);
					ladrilho_sel_direito.SetarX(LADRILHO_SEL_DIREITO_X);
					ladrilho_sel_direito.SetarY(LADRILHO_SEL_DIREITO_Y);
				}
				ladrilho_sel_esquerdo.Desenhar(zeus_screen);
				ladrilho_sel_direito.Desenhar(zeus_screen);
				break;
		default:
			for(x = 0; x < MENU_OBJ_LARGURA_LADRILHO; x++)
				for(y = 0; y < MENU_OBJ_ALTURA_LADRILHO; y++)
					rect(zeus_screen, x * 32, y * 32, x * 32 + LADRILHO_LARGURA, y * 32 + LADRILHO_ALTURA, makecol(100, 100, 100));
			break;
	}
}


//------------------------------------------------------------
/* Abre uma fase jah existente */
int AbrirFase(void)
{
	char arquivo_selecionado[ARQUIVO_NOME_COMPRIMENTO], aux[ARQUIVO_NOME_COMPRIMENTO];
	int opcao, verificados;

	if(flag_alterado)
	{
		opcao = alert3("Deseja salvar a fase atual?", NULL, NULL, "Sim", "Nao", "Cancelar", NULL, NULL, NULL);
		if(opcao == 1)
			SalvarFase();
		else if(opcao == 3)
			return FALSE;
	}

	strcpy(arquivo_selecionado, caminho);
	if((file_select_ex("Selecione o arquivo do mapa:", arquivo_selecionado, "map", sizeof(arquivo_selecionado), DIALOGO_LARGURA, DIALOGO_ALTURA)) != NULL)
	{
		verificados = 0;
		scare_mouse();

		strcpy(aux, "fases\\");
		strcat(aux, get_filename(arquivo_selecionado));
		strcpy(arquivo_fase, aux);

		verificados += 100;
		barra_progresso_zeus(screen, BARRA_PROGRESSO_X, BARRA_PROGRESSO_Y, BARRA_PROGRESSO_X + BARRA_PROGRESSO_LARGURA, BARRA_PROGRESSO_Y + BARRA_PROGRESSO_ALTURA, 300, verificados - 1, verificados, BARRA_PROGRESSO_COR);

		if(flag_fase) fase.Desligar();
		fase.Iniciar(aux, MAPA_EDITOR_X1, MAPA_EDITOR_Y1, MAPA_EDITOR_LARGURA, MAPA_EDITOR_ALTURA);

		verificados += 100;
		barra_progresso_zeus(screen, BARRA_PROGRESSO_X, BARRA_PROGRESSO_Y, BARRA_PROGRESSO_X + BARRA_PROGRESSO_LARGURA, BARRA_PROGRESSO_Y + BARRA_PROGRESSO_ALTURA, 300, verificados - 1, verificados, BARRA_PROGRESSO_COR);
     	fase.Desenhar(zeus_screen);

		verificados += 100;
		barra_progresso_zeus(screen, BARRA_PROGRESSO_X, BARRA_PROGRESSO_Y, BARRA_PROGRESSO_X + BARRA_PROGRESSO_LARGURA, BARRA_PROGRESSO_Y + BARRA_PROGRESSO_ALTURA, 300, verificados - 1, verificados, BARRA_PROGRESSO_COR);

		flag_fase = TRUE;
		flag_desenhar = TRUE;
		flag_alterado = FALSE;
	    unscare_mouse();
		return TRUE;
	}
	return FALSE;
}


//------------------------------------------------------------
/* Inicia uma nova fase */
int NovaFase(void)
{
	int opcao, verificados;

	if(flag_alterado)
	{
		opcao = alert3("Deseja salvar a fase atual?", NULL, NULL, "Sim", "Nao", "Cancelar", NULL, NULL, NULL);
		if(opcao == 1)
			SalvarFase();
		else if(opcao == 3)
			return FALSE;
	}

	scare_mouse();
	strcpy(arquivo_fase, "fases\\novo.dft");

	verificados = 0;
	verificados += 100;
	barra_progresso_zeus(screen, BARRA_PROGRESSO_X, BARRA_PROGRESSO_Y, BARRA_PROGRESSO_X + BARRA_PROGRESSO_LARGURA, BARRA_PROGRESSO_Y + BARRA_PROGRESSO_ALTURA, 300, verificados - 1, verificados, BARRA_PROGRESSO_COR);
	if(flag_fase) fase.Desligar();
	fase.Iniciar(arquivo_fase, MENU_OBJ_LARGURA + 1, MENU_ALTURA + 1, MAPA_EDITOR_LARGURA, MAPA_EDITOR_ALTURA);

	verificados += 100;
	barra_progresso_zeus(screen, BARRA_PROGRESSO_X, BARRA_PROGRESSO_Y, BARRA_PROGRESSO_X + BARRA_PROGRESSO_LARGURA, BARRA_PROGRESSO_Y + BARRA_PROGRESSO_ALTURA, 300, verificados - 1, verificados, BARRA_PROGRESSO_COR);
   	fase.Desenhar(zeus_screen);

	verificados += 100;
	barra_progresso_zeus(screen, BARRA_PROGRESSO_X, BARRA_PROGRESSO_Y, BARRA_PROGRESSO_X + BARRA_PROGRESSO_LARGURA, BARRA_PROGRESSO_Y + BARRA_PROGRESSO_ALTURA, 300, verificados - 1, verificados, BARRA_PROGRESSO_COR);

	flag_fase = TRUE;
	flag_desenhar = TRUE;
	flag_alterado = FALSE;
	unscare_mouse();
	return TRUE;
}


//------------------------------------------------------------
/* Salva a fase corrente */
int SalvarFase(void)
{
	if(flag_alterado)
	{
		if((strcmp(arquivo_fase, "fases\\novo.dft") != 0))
		{
			fase.SalvarFase();
			flag_alterado = FALSE;
			return TRUE;
		}
		else
			return SalvarComoFase();

	}
	return FALSE;
}


//------------------------------------------------------------
/* Salvar a fase com o nome selecionado */
int SalvarComoFase(void)
{
	char arquivo_selecionado[ARQUIVO_NOME_COMPRIMENTO], aux[ARQUIVO_NOME_COMPRIMENTO];


	if(strlen(arquivo_fase) > 0)
	{
		strcpy(arquivo_selecionado, caminho);
		if((file_select_ex("Informe o nome para o arquivo da fase:", arquivo_selecionado, "map", sizeof(arquivo_selecionado), DIALOGO_LARGURA, DIALOGO_ALTURA)) != NULL)
		{
			strcpy(aux, "fases\\");
			strcat(aux, get_filename(arquivo_selecionado));
			strcpy(arquivo_fase, aux);
			fase.SetarArquivo_fase(arquivo_fase);
			return SalvarFase();
		}
	}
	return FALSE;
}


//------------------------------------------------------------
/* Fechar a fase corrente */
int FecharFase(void)
{
	if(strlen(arquivo_fase) > 0)
		return NovaFase();

	return FALSE;
}


//------------------------------------------------------------
/* Abre o fundo e mostra no menu obj */
int AbrirFundo(void)
{
	char arquivo_selecionado[ARQUIVO_NOME_COMPRIMENTO];

	strcpy(arquivo_selecionado, caminho);;
	if((file_select_ex("Selecione o arquivo bitmap para o fundo:", arquivo_selecionado, "bmp", sizeof(arquivo_selecionado), DIALOGO_LARGURA, DIALOGO_ALTURA)) != NULL)
	{

		strcpy(arquivo_fundo, "fases\\");
		strcat(arquivo_fundo, get_filename(arquivo_selecionado));
		bmp_fundo = load_bmp(arquivo_fundo, NULL);
		if(!bmp_fundo)
		{
			Erro("ERRO - Arquivo de fundo nao foi carregado!", arquivo_fundo);
			alert("ERRO - Arquivo de Fundo nao foi carregado!", NULL, NULL, "OK", NULL, NULL, NULL);
			return FALSE;
		}

		scare_mouse();
		exibir_obj = eFundo;
		MontarMenuObj(1);
		unscare_mouse();
		flag_obj = TRUE;
		flag_desenhar = TRUE;
		return TRUE;
	}
	return FALSE;

}


//------------------------------------------------------------
/* Abre o arquivo dat dos aliens e mostra no menu obj */
int AbrirAliens(void)
{
	char arquivo_selecionado[ARQUIVO_NOME_COMPRIMENTO];

	/*
	strcpy(arquivo_selecionado, caminho);;
	if((file_select_ex("Selecione o arquivo dat para os aliens:", arquivo_selecionado, "dat", sizeof(arquivo_selecionado), DIALOGO_LARGURA, DIALOGO_ALTURA)) != NULL)
	{

		strcpy(arquivo_aliens, arquivo_selecionado);
	*/
		dat_aliens = load_datafile("aliens.dat");
		if(!dat_aliens)
		{
			Erro("ERRO - Arquivo de Aliens nao foi carregado!", arquivo_aliens);
			alert("ERRO - Arquivo de Aliens nao foi carregado!", NULL, NULL, "OK", NULL, NULL, NULL);
			return FALSE;
		}

		alien_sel_esquerdo.Iniciar(0, 0, 0, dat_aliens);
		alien_sel_direito.Iniciar(1, 0, 0, dat_aliens);

		scare_mouse();
		exibir_obj = eAliens;
		MontarMenuObj(1);
		unscare_mouse();
		flag_obj = TRUE;
		flag_desenhar = TRUE;
		return TRUE;
	//}
	return FALSE;
}


//------------------------------------------------------------
/* Preenche todos os ladrilhos nulos (padrao) pelo ladrilho_sel_esquerdo */
int PreencherNulos(void)
{
	register int x, y, verificados;

	if(flag_fase
	&& flag_obj
	&& exibir_obj == eFundo)
	{
		verificados = 0;
		for(x = 0; x < MAPA_LARGURA_LADRILHOS; x++)
		{
			for(y = 0; y < MAPA_ALTURA_LADRILHOS; y++)
			{
				if(strcmp(fase.ObterLadrilho(x, y).ObterArquivo_bmp(), "fases\\novo.bmp") == 0)
				{
					ladrilho = ladrilho_sel_esquerdo;
					ladrilho.SetarX(fase.ObterLadrilho(x, y).ObterX());
					ladrilho.SetarY(fase.ObterLadrilho(x, y).ObterY());
					fase.SetarLadrilho(x, y, ladrilho);
				}
				verificados++;
				barra_progresso_zeus(screen, BARRA_PROGRESSO_X, BARRA_PROGRESSO_Y, BARRA_PROGRESSO_X + BARRA_PROGRESSO_LARGURA, BARRA_PROGRESSO_Y + BARRA_PROGRESSO_ALTURA, MAPA_TOTAL_LADRILHOS, verificados - 1, verificados, BARRA_PROGRESSO_COR);
			}
		}
		if(verificados)
		{
			fase.Desenhar(zeus_screen);
			flag_desenhar = TRUE;
			flag_alterado = TRUE;
			return TRUE;
		}
	}
	return FALSE;
}


//------------------------------------------------------------
/* Troca os ladrilhos iguais ao ladrilho_sel_esquerdo para
ladrilho_sel_direito, sem considerar h_flip, v_flip e rotacao */
int TrocarLadrilhos(void)
{
	register int x, y, verificados;

	if(flag_fase
	&& flag_obj
	&& exibir_obj == eFundo)
	{
		verificados = 0;
		ladrilho = ladrilho_sel_direito;
		for(x = 0; x < MAPA_LARGURA_LADRILHOS; x++)
		{
			for(y = 0; y < MAPA_ALTURA_LADRILHOS; y++)
			{
				if(strcmp(fase.ObterLadrilho(x, y).ObterArquivo_bmp(), ladrilho_sel_esquerdo.ObterArquivo_bmp()) == 0 && fase.ObterLadrilho(x, y).ObterBmp_x() == ladrilho_sel_esquerdo.ObterBmp_x() && fase.ObterLadrilho(x, y).ObterBmp_y() == ladrilho_sel_esquerdo.ObterBmp_y())
				{
					ladrilho.SetarX(fase.ObterLadrilho(x, y).ObterX());
					ladrilho.SetarY(fase.ObterLadrilho(x, y).ObterY());
					fase.SetarLadrilho(x, y, ladrilho);
				}
				verificados++;
				barra_progresso_zeus(screen, BARRA_PROGRESSO_X, BARRA_PROGRESSO_Y, BARRA_PROGRESSO_X + BARRA_PROGRESSO_LARGURA, BARRA_PROGRESSO_Y + BARRA_PROGRESSO_ALTURA, MAPA_TOTAL_LADRILHOS, verificados - 1, verificados, BARRA_PROGRESSO_COR);
			}
		}
		if(verificados)
		{
			fase.Desenhar(zeus_screen);
			flag_desenhar = TRUE;
			flag_alterado = TRUE;
			return TRUE;
		}
	}
	return FALSE;
}


//------------------------------------------------------------
/* Verifica se ha fase para salvar e finaliza o Zeus */
int Sair(void)
{
	int opcao;

	if(flag_alterado)
	{
		opcao = alert3("Deseja salvar a fase atual?", NULL, NULL, "Sim", "Nao", "Cancelar", NULL, NULL, NULL);
		if(opcao == 1)
			SalvarFase();
		else if(opcao == 3)
			return FALSE;
	}
	return TRUE;
}


//------------------------------------------------------------
/* Desenha os componentes da tela */
void DesenharTela(void)
{
	char buf[30];

	/* Menu Superior */
	rectfill(zeus_screen, MENU_ARQUIVO_X1, 0, SCREEN_W, MENU_ALTURA, makecol(0, 0, 0));
	escrever(zeus_screen, "Arquivo", MENU_ARQUIVO_X1, 0, makecol(255, 255, 255));
	escrever(zeus_screen, "Objetos", MENU_OBJETOS_X1, 0, makecol(255, 255, 255));
	escrever(zeus_screen, "Exibir", MENU_EXIBIR_X1, 0, makecol(255, 255, 255));
	escrever(zeus_screen, "Ferramentas", MENU_FERRAMENTAS_X1, 0, makecol(255, 255, 255));

	/* Display das coordenadas do mapa da fase */
	if(flag_fase
	&& flag_obj
	&& mouse_x > MAPA_EDITOR_X1
	&& mouse_x < MAPA_EDITOR_X2
	&& mouse_y > MAPA_EDITOR_Y1
	&& mouse_y < MAPA_EDITOR_Y2)
	{
		sprintf(buf, "[x: %4i][y: %4i]", (mouse_x - MENU_OBJ_LARGURA) + fase.ObterX1_fonte(), (mouse_y - MENU_ALTURA) + fase.ObterY1_fonte());
		escrever(zeus_screen, buf, 495, 1, makecol(255, 255, 255));
	}

	MontarMenuObj(0);

	/* Menu aux */
	rectfill(zeus_screen, MENU_AUX_X, MENU_AUX_Y, SCREEN_W, SCREEN_H, makecol(0, 0, 0));
	ladrilho_sel_esquerdo.Desenhar(zeus_screen);
	ladrilho_sel_direito.Desenhar(zeus_screen);
	ladrilho_h_flip.Desenhar(zeus_screen);
	ladrilho_v_flip.Desenhar(zeus_screen);
	//ladrilho_rotacao.Desenhar(zeus_screen);
	hline(zeus_screen, MENU_AUX_X, MENU_AUX_Y, SCREEN_W, LADRILHO_NAO_SELECIONADO_COR);
}


//------------------------------------------------------------
/* Verifica se deve ser inserido um ladrilho no mapa */
void VerificarLadrilho(void)
{
	int x, y;
	
	x = (mouse_x - 97 + fase.ObterX1_fonte()) / LADRILHO_LARGURA;
	y = (mouse_y - 11 + fase.ObterY1_fonte()) / LADRILHO_ALTURA;
   
	if(mouse_b & 1)
	{
		/* Quando pressiona a tecla shift
		e o botão esquerdo */
		if(key[KEY_LSHIFT] || key[KEY_RSHIFT])
		{
			ladrilho_sel_esquerdo = fase.ObterLadrilho(x, y);
			ladrilho_sel_esquerdo.SetarX(LADRILHO_SEL_ESQUERDO_X);
			ladrilho_sel_esquerdo.SetarY(LADRILHO_SEL_ESQUERDO_Y);
			ladrilho_sel_esquerdo.Desenhar(zeus_screen);
			flag_desenhar = TRUE;
		}
		else
		if((strcmp(fase.ObterLadrilho(x, y).ObterArquivo_bmp(), ladrilho_sel_esquerdo.ObterArquivo_bmp()) != 0)
		|| fase.ObterLadrilho(x, y).ObterBmp_x()    != ladrilho_sel_esquerdo.ObterBmp_x()
		|| fase.ObterLadrilho(x, y).ObterBmp_y()    != ladrilho_sel_esquerdo.ObterBmp_y()
		|| fase.ObterLadrilho(x, y).ObterH_flip()  != ladrilho_sel_esquerdo.ObterH_flip()
		|| fase.ObterLadrilho(x, y).ObterV_flip()  != ladrilho_sel_esquerdo.ObterV_flip()
		|| fase.ObterLadrilho(x, y).ObterRotacao() != ladrilho_sel_esquerdo.ObterRotacao())
		{
			ladrilho = ladrilho_sel_esquerdo;
			ladrilho.SetarX(fase.ObterLadrilho(x, y).ObterX());
			ladrilho.SetarY(fase.ObterLadrilho(x, y).ObterY());
			fase.SetarLadrilho(x, y, ladrilho);
			fase.Desenhar(zeus_screen);
			flag_alterado = TRUE;
			flag_desenhar = TRUE;
		}
	}
	else
	if(mouse_b & 2)
	{
		/* Quando pressiona a tecla shift
		e o botão direito do mouse */
		if(key[KEY_LSHIFT] || key[KEY_RSHIFT])
		{
			ladrilho_sel_direito = fase.ObterLadrilho(x, y);
			ladrilho_sel_direito.SetarX(LADRILHO_SEL_DIREITO_X);
			ladrilho_sel_direito.SetarY(LADRILHO_SEL_DIREITO_Y);
			ladrilho_sel_direito.Desenhar(zeus_screen);
			flag_desenhar = TRUE;
		}
		else
		if(strcmp(fase.ObterLadrilho(x, y).ObterArquivo_bmp(), ladrilho_sel_direito.ObterArquivo_bmp()) != 0
		|| fase.ObterLadrilho(x, y).ObterBmp_x() != ladrilho_sel_direito.ObterBmp_x()
		|| fase.ObterLadrilho(x, y).ObterBmp_y() != ladrilho_sel_direito.ObterBmp_y()
		|| fase.ObterLadrilho(x, y).ObterH_flip()  != ladrilho_sel_direito.ObterH_flip()
		|| fase.ObterLadrilho(x, y).ObterV_flip()  != ladrilho_sel_direito.ObterV_flip()
		|| fase.ObterLadrilho(x, y).ObterRotacao() != ladrilho_sel_direito.ObterRotacao())
		{
			ladrilho = ladrilho_sel_direito;
			ladrilho.SetarX(fase.ObterLadrilho(x, y).ObterX());
			ladrilho.SetarY(fase.ObterLadrilho(x, y).ObterY());
			fase.SetarLadrilho(x, y, ladrilho);
			fase.Desenhar(zeus_screen);
			flag_desenhar = TRUE;
			flag_alterado = TRUE;
		}
	}
}


//------------------------------------------------------------
/* Verifica se deve ser inserido um alien no mapa */
void VerificarAlien(void)
{
	if(mouse_b & 1)
	{
		/* Exclui os aliens já incluidos no mapa que colidirem
		com a novo alien adicionado */
		fase.ExcluirAliens(fase.ObterX1_fonte() + (mouse_x - 97 - (alien_sel_esquerdo.ObterLargura() / 2)), fase.ObterY1_fonte() + (mouse_y - MAPA_EDITOR_Y1 - (alien_sel_esquerdo.ObterAltura() / 2)), fase.ObterX1_fonte() + (mouse_x - 97 + alien_sel_esquerdo.ObterLargura() / 2), fase.ObterY1_fonte() + (mouse_y - MAPA_EDITOR_Y1 + alien_sel_esquerdo.ObterAltura() / 2));
		fase.AdicionarAlien(alien_sel_esquerdo.ObterTipo(), fase.ObterX1_fonte() + (mouse_x - 97 - (alien_sel_esquerdo.ObterLargura() / 2)), fase.ObterY1_fonte() + (mouse_y - MAPA_EDITOR_Y1 - (alien_sel_esquerdo.ObterAltura() / 2)));
		fase.Desenhar(zeus_screen);
		flag_alterado = TRUE;
		flag_desenhar = TRUE;
	}
	else
	if(mouse_b & 2)
	{
		/* Exclui os aliens já incluidos no mapa que colidirem
		com a novo alien adicionado */
		fase.ExcluirAliens(fase.ObterX1_fonte() + (mouse_x - 97 - (alien_sel_direito.ObterLargura() / 2)), fase.ObterY1_fonte() + (mouse_y - MAPA_EDITOR_Y1 - (alien_sel_direito.ObterAltura() / 2)), fase.ObterX1_fonte() + (mouse_x - 97 + alien_sel_direito.ObterLargura() / 2), fase.ObterY1_fonte() + (mouse_y - MAPA_EDITOR_Y1 + alien_sel_direito.ObterAltura() / 2));
		fase.AdicionarAlien(alien_sel_direito.ObterTipo(), fase.ObterX1_fonte() + (mouse_x - 97 - (alien_sel_direito.ObterLargura() / 2)), fase.ObterY1_fonte() + (mouse_y - MAPA_EDITOR_Y1 - (alien_sel_direito.ObterAltura() / 2)));
		fase.Desenhar(zeus_screen);
		flag_desenhar = TRUE;
		flag_alterado = TRUE;
	}
}


//------------------------------------------------------------
/* Desenha um quadrado com as diminsões do objeto selecionado 
esquerdo */
void DesenharQuadrado(void)
{
	int x = (mouse_x - 97 + fase.ObterX1_fonte()) / LADRILHO_LARGURA, y = (mouse_y - 11 + fase.ObterY1_fonte()) / LADRILHO_ALTURA;
	static int bk_mouse_x = mouse_x, bk_mouse_y = mouse_y;
	static int bk_x = x, bk_y = y;

	/* Destaca com um quadrado a area para o objeto */
	if((mouse_x != bk_mouse_x
	|| mouse_y != bk_mouse_y)
	&& exibir_obj == eAliens)
	{
		fase.Desenhar(zeus_screen);
		if(fase.ChecarColisaoAliens(mouse_x - 97 + fase.ObterX1_fonte() - (alien_sel_esquerdo.ObterLargura() / 2), mouse_y - 11 + fase.ObterY1_fonte() - (alien_sel_esquerdo.ObterAltura() / 2), mouse_x - 97 + fase.ObterX1_fonte() + (alien_sel_esquerdo.ObterLargura() / 2), mouse_y - 11 + fase.ObterY1_fonte() + (alien_sel_esquerdo.ObterAltura() / 2)))
		{
			rect(zeus_screen, mouse_x - (alien_sel_esquerdo.ObterLargura() / 2), mouse_y - (alien_sel_esquerdo.ObterAltura() / 2), mouse_x + (alien_sel_esquerdo.ObterLargura() / 2), mouse_y + (alien_sel_esquerdo.ObterAltura() / 2), makecol(255, 0, 0));
		}
			else
		{
			rect(zeus_screen, mouse_x - (alien_sel_esquerdo.ObterLargura() / 2), mouse_y - (alien_sel_esquerdo.ObterAltura() / 2), mouse_x + (alien_sel_esquerdo.ObterLargura() / 2), mouse_y + (alien_sel_esquerdo.ObterAltura() / 2), SOBRE_LADRILHO_COR);
		}
		flag_desenhar = TRUE;
	}
	else 
	if((x != bk_x
	|| y != bk_y)
	&& exibir_obj == eFundo)
	{
		fase.Desenhar(zeus_screen);
		rect(zeus_screen, (fase.ObterLadrilho(x, y).ObterX() + MAPA_EDITOR_X1 - fase.ObterX1_fonte()), (fase.ObterLadrilho(x, y).ObterY() + MAPA_EDITOR_Y1 -  fase.ObterY1_fonte()), (fase.ObterLadrilho(x, y).ObterX() + LADRILHO_LARGURA + MAPA_EDITOR_X1 - fase.ObterX1_fonte()) - 1, (fase.ObterLadrilho(x, y).ObterY() + LADRILHO_ALTURA + MAPA_EDITOR_Y1 - fase.ObterY1_fonte()) - 1, SOBRE_LADRILHO_COR);
		flag_desenhar = TRUE;
	}
	
	bk_mouse_x = mouse_x;
	bk_mouse_y = mouse_y;
	bk_x = x;
	bk_y = y;
		
	
}


//------------------------------------------------------------
/* Verifica o rolamento da fase através do pressionamento das 
teclas do teclado*/
void VerificarRolaTecla(void)
{
	if(key[KEY_UP])
	{
		if(fase.Rolar(eCima, LADRILHO_ALTURA) == TRUE)
		{
			fase.Desenhar(zeus_screen);
			flag_desenhar = TRUE;
		}
	}
	else
	if(key[KEY_DOWN])
	{
		if(fase.Rolar(eBaixo, LADRILHO_ALTURA) == TRUE)
		{
			fase.Desenhar(zeus_screen);
			flag_desenhar = TRUE;
		}
	}

	if(key[KEY_RIGHT])
	{
		if(fase.Rolar(eDireita, LADRILHO_LARGURA) == TRUE)
		{
			fase.Desenhar(zeus_screen);
			flag_desenhar = TRUE;
		}
	}
	else
	if(key[KEY_LEFT])
	{
		if(fase.Rolar(eEsquerda, LADRILHO_LARGURA) == TRUE)
		{
			fase.Desenhar(zeus_screen);
			flag_desenhar = TRUE;
		}
	}
	else
	if(key[KEY_PGUP])
	{
		if(fase.Rolar(eCima, MENU_OBJ_ALTURA) == TRUE)
		{
			fase.Desenhar(zeus_screen);
			flag_desenhar = TRUE;
		}
	}
	else
	if(key[KEY_PGDN])
	{
		if(fase.Rolar(eBaixo, MENU_OBJ_ALTURA) == TRUE)
		{
			fase.Desenhar(zeus_screen);
			flag_desenhar = TRUE;
		}
	}
	else
	if(key[KEY_HOME])
	{
		if(fase.Rolar(eCima,MAPA_ALTURA) == TRUE)
		{
			fase.Desenhar(zeus_screen);
			flag_desenhar = TRUE;
		}
	}
	else
	if(key[KEY_END])
	{
		if(fase.Rolar(eBaixo, MAPA_ALTURA) == TRUE)
		{
			fase.Desenhar(zeus_screen);
			flag_desenhar = TRUE;
		}
	}
}


//------------------------------------------------------------
/* Verifica o rolamento da fase através do pressionamento das 
teclas do mouse*/
void VerificarRolaMouse(void)
{
	/* Se for pressionado o botão esquerdo ou botão direito do mouse */
	if((mouse_b & 1) || (mouse_b & 2))
	{
		/* Se mouse esta passando nos extremos do mapa e sendo pressionado */
		if(mouse_x < (MENU_OBJ_LARGURA + (LADRILHO_LARGURA/2))
           && mouse_x > MENU_OBJ_LARGURA
           && mouse_y > MENU_ALTURA)
		{
			if(fase.Rolar(eEsquerda, LADRILHO_LARGURA) == TRUE)
			{
				fase.Desenhar(zeus_screen);
				flag_desenhar = TRUE;
			}
		}
		else
		if(mouse_x > ((MAPA_EDITOR_X2) - (LADRILHO_LARGURA/2))
           && mouse_x < MAPA_EDITOR_X2
           && mouse_y > MENU_ALTURA)
		{
			if(fase.Rolar(eDireita, LADRILHO_LARGURA) == TRUE)
			{
				fase.Desenhar(zeus_screen);
				flag_desenhar = TRUE;
			}
		}
		else
		if(mouse_x > MENU_OBJ_LARGURA
           && mouse_y < (MENU_ALTURA + (LADRILHO_ALTURA/2))
           && mouse_y > MENU_ALTURA)
		{
			if(fase.Rolar(eCima, LADRILHO_ALTURA) == TRUE)
			{
				fase.Desenhar(zeus_screen);
				flag_desenhar = TRUE;
			}
		}
		else
		if(mouse_x > MENU_OBJ_LARGURA
           && mouse_y > (MENU_AUX_Y - (LADRILHO_ALTURA/2))
           && mouse_y < MENU_AUX_Y)
		{
			if(fase.Rolar(eBaixo, LADRILHO_ALTURA) == TRUE)
			{
				fase.Desenhar(zeus_screen);
				flag_desenhar = TRUE;
			}
		}
	}
}

//------------------------------------------------------------
/* Menu Arquivo */
int VerificarMenuArquivo(void)
{
	int opcao;
	MENU menu_arquivo[] =
	{
		{ "&Novo",				NULL,   NULL,	FALSE,	NULL },
		{ "&Abrir",				NULL,   NULL,	FALSE,	NULL },
		{ "&Salvar",			NULL,   NULL,	FALSE,	NULL },
		{ "Salvar &Como",		NULL,   NULL,	FALSE,	NULL },
		{ "&Fechar",			NULL,   NULL,	FALSE,	NULL },
		{ "",					NULL,   NULL,	FALSE,	NULL },
		{ "&Sair",				NULL,   NULL,	FALSE,	NULL },
		{ NULL,					NULL,	NULL,   FALSE,	NULL }
	};

	if(mouse_x > MENU_ARQUIVO_X1  
	&& mouse_x < MENU_ARQUIVO_X2)
	{
		opcao = do_menu(menu_arquivo, MENU_ARQUIVO_X1, MENU_ALTURA);
		switch(opcao)
		{
			case 0:	NovaFase();
					break;
			case 1:	AbrirFase();
					break;
			case 2:	SalvarFase();
					break;
			case 3:	SalvarComoFase();
					break;
			case 4:	FecharFase();
					break;
		}
		if(opcao == 6)
		{
			if(Sair() == TRUE)
				DesligarZeus();
		}
		return TRUE;
	}
	return FALSE;
}
			

//------------------------------------------------------------
/* Menu Objetos */
int VerificarMenuObjetos(void)
{
	int opcao;
    MENU menu_objetos[] =
	{
		{ "&Bonus",			NULL,   NULL,	FALSE,	NULL },
		{ "&Construcoes",   NULL,   NULL,	FALSE,	NULL },
		{ "&Aliens",		NULL,   NULL,	FALSE,	NULL },
		{ "&Seres Vivos",   NULL,   NULL,	FALSE,	NULL },
		{ "&Fundo",			NULL,   NULL,	FALSE,	NULL },
		{ "&Veiculos",		NULL,   NULL,	FALSE,	NULL },
		{ NULL,				NULL,	NULL,   FALSE,	NULL }
	};

	if(mouse_x > MENU_OBJETOS_X1  && mouse_x < MENU_OBJETOS_X2)
	{
		opcao = do_menu(menu_objetos, MENU_OBJETOS_X1, MENU_ALTURA);
		switch(opcao)
		{
			case 2: AbrirAliens();
					break;
			case 4:	AbrirFundo();
					break;
		}
		return TRUE;
	}
	return FALSE;
}


//------------------------------------------------------------
/* Menu Exibir */
int VerificarMenuExibir(void)
{
	int opcao = -1;

	if(mouse_x > MENU_EXIBIR_X1  && mouse_x < MENU_EXIBIR_X2)
	{
		opcao = do_menu(menu_exibir, MENU_EXIBIR_X1, MENU_ALTURA);
		switch(opcao)
		{
			case 2:	if (!dat_aliens)
					{
						AbrirAliens();
					}
					break;
			case 4: if(!bmp_fundo)
					{
						AbrirFundo();
					}
					break;
		}

		if ((opcao == 2 || opcao == 4) 
			&& exibir_obj > -1
			&& opcao > -1
			&& exibir_obj != opcao)
		{
			/* Redesenha o menu de objetos */
			exibir_obj = opcao;
			MontarMenuObj(1);
		}
		return TRUE;
	}
	return FALSE;
}


//------------------------------------------------------------
/* Menu Ferramentas */
int VerificarMenuFerramentas(void)
{
	int opcao;

	MENU menu_ferramentas[] =
	{
		{ "&Preencher ladrilhos nulos por selecionado esquerdo",	NULL,   NULL,	FALSE,	NULL },
		{ "&Trocar ladrilhos do selecionado esquerdo pelo do direito",	NULL,   NULL,	FALSE,	NULL },
		{ NULL,				NULL,	NULL,   FALSE,	NULL }
	};

	if(mouse_x > MENU_FERRAMENTAS_X1 && mouse_x < MENU_FERRAMENTAS_X2)
	{
		opcao = do_menu(menu_ferramentas, MENU_FERRAMENTAS_X1, MENU_ALTURA);
		switch(opcao)
		{
			case 0:	PreencherNulos();
					break;
			case 1:	TrocarLadrilhos();
					break;
		}
		return TRUE;
	}
	return FALSE;
}


//------------------------------------------------------------
/* Menu Obj */
void VerificarMenuObj(void)
{
	int x = mouse_x / LADRILHO_LARGURA;
	int y = mouse_y / LADRILHO_ALTURA;
	
	/* Se o botão esquerdo do mouse foi pressionado	*/
	if(mouse_b & 1)
	{
		ladrilho_sel_esquerdo.SetarTLadrilho(menu_obj_ladrilhos[x][y].ObterTLadrilho());
		ladrilho_sel_esquerdo.SetarX(LADRILHO_SEL_ESQUERDO_X);
		ladrilho_sel_esquerdo.SetarY(LADRILHO_SEL_ESQUERDO_Y);
		switch(exibir_obj)
		{
			case eAliens:
				/* Este calculo { ((x * 15) + y) * 2 } localiza o bitmap do alien no arquivo dat */
				ladrilho_sel_esquerdo.SetarBmp_fonte((BITMAP *) dat_aliens[((x * 15) + y) * 2].dat);
				/* Este calculo { ((x * 15) + y) } informa o tipo de alien */
				alien_sel_esquerdo.Iniciar(((x * 15) + y), 0, 0, dat_aliens);
				break;
			
			case eFundo:
				ladrilho_sel_esquerdo.SetarBmp_fonte(bmp_fundo);
				break;
		}
		rectfill(screen, LADRILHO_SEL_ESQUERDO_X, LADRILHO_SEL_ESQUERDO_Y, LADRILHO_SEL_ESQUERDO_X + LADRILHO_LARGURA, LADRILHO_SEL_ESQUERDO_Y + LADRILHO_LARGURA, makecol(0, 0, 0));
		ladrilho_sel_esquerdo.Desenhar(screen);
	}
	/* Se o botão esquerdo do mouse foi pressionado */
	else
	if(mouse_b & 2)
	{
		ladrilho_sel_direito.SetarTLadrilho(menu_obj_ladrilhos[x][y].ObterTLadrilho());
		ladrilho_sel_direito.SetarX(LADRILHO_SEL_DIREITO_X);
		ladrilho_sel_direito.SetarY(LADRILHO_SEL_DIREITO_Y);
		switch(exibir_obj)
		{
			case eAliens:
				/* Este calculo { ((x * 15) + y) * 2 } localiza o bitmap do alien no arquivo dat */
				ladrilho_sel_direito.SetarBmp_fonte((BITMAP *) dat_aliens[((x * 15) + y) * 2].dat);
				/* Este calculo { ((x * 15) + y) } informa o tipo de alien */
				alien_sel_direito.Iniciar(((x * 15) + y), 0, 0, dat_aliens);
				break;
			
			case eFundo:
				ladrilho_sel_direito.SetarBmp_fonte(bmp_fundo);
				break;
		}
		rectfill(screen, LADRILHO_SEL_DIREITO_X, LADRILHO_SEL_DIREITO_Y, LADRILHO_SEL_DIREITO_X + LADRILHO_LARGURA, LADRILHO_SEL_DIREITO_Y + LADRILHO_LARGURA, makecol(0, 0, 0));
		ladrilho_sel_direito.Desenhar(screen);
	}
}


//------------------------------------------------------------
/* Menu Aux */
void VerificarMenuAux(void)
{
	if(ladrilho_h_flip.ChecarColisao(mouse_x, mouse_y, mouse_x, mouse_y))
	{
		if(mouse_b & 1)
		{
			ladrilho_sel_esquerdo.VirarHorizontal();
			flag_desenhar = TRUE;
		}
		else if(mouse_b & 2)
		{
			ladrilho_sel_direito.VirarHorizontal();
			flag_desenhar = TRUE;
		}
	}
	
	/* v_flip */
	else if(ladrilho_v_flip.ChecarColisao(mouse_x, mouse_y, mouse_x, mouse_y))
	{
		if(mouse_b & 1)
		{
			ladrilho_sel_esquerdo.VirarVertical();
			flag_desenhar = TRUE;
		}
		else if(mouse_b & 2)
		{
			ladrilho_sel_direito.VirarVertical();
			flag_desenhar = TRUE;
		}
	}
	
	/* rotacao */
	/*else if(ladrilho_rotacao.ChecarColisao(mouse_x, mouse_y, mouse_x, mouse_y))
	{
		if(mouse_b & 1)
		{
			ladrilho_sel_esquerdo.Rotacionar();
			flag_desenhar = TRUE;
		}
		else if(mouse_b & 2)
		{
			ladrilho_sel_direito.Rotacionar();
			flag_desenhar = TRUE;
		}
	}*/
}