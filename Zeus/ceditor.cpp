 /*------------------------------------------------------------*
 *  ceditor.c - Implementação da classe do editor de fases
*------------------------------------------------------------*
*  Nome: Diego Giacomelli
*  Data: sexta-feira, 19 de outubro de 2001
*
*
*------------------------------------------------------------*/

#include "ceditor.h"

//------------------------------------------------------------
// Inicia o editor
void CEditor::Iniciar()
{
	Log("");
	Log("[INICIO]:CEditor::Iniciar();");

	char arquivo_selecionado[ARQUIVO_NOME_COMPRIMENTO];
	TLadrilho lad;
	int nome_comprimento;

	ChecarArquivo("zeus.ini");
	ChecarArquivo("nave.dat");
	ChecarArquivo("aliens.dat");
	ChecarArquivo("armas.dat");
	ChecarArquivo("construcoes.dat");
	ChecarArquivo("imagem.dat");
	ChecarArquivo("fases\\novo.dft");
	ChecarArquivo("fases\\novo.bmp");

	m_menu_exibir[0].text  = "&Bonus";
	m_menu_exibir[0].proc  = NULL;
	m_menu_exibir[0].child = NULL;
	m_menu_exibir[0].flags = 0;
	m_menu_exibir[0].dp    = NULL;

	m_menu_exibir[1].text  = "&Construcoes";
	m_menu_exibir[1].proc  = NULL;
	m_menu_exibir[1].child = NULL;
	m_menu_exibir[1].flags = 0;
	m_menu_exibir[1].dp    = NULL;

	m_menu_exibir[2].text  = "&Aliens";
	m_menu_exibir[2].proc  = NULL;
	m_menu_exibir[2].child = NULL;
	m_menu_exibir[2].flags = 0;
	m_menu_exibir[2].dp    = NULL;

	m_menu_exibir[3].text  = "&Seres Vivos";
	m_menu_exibir[3].proc  = NULL;
	m_menu_exibir[3].child = NULL;
	m_menu_exibir[3].flags = 0;
	m_menu_exibir[3].dp    = NULL;

	m_menu_exibir[4].text  = "&Fundo";
	m_menu_exibir[4].proc  = NULL;
	m_menu_exibir[4].child = NULL;
	m_menu_exibir[4].flags = 0;
	m_menu_exibir[4].dp    = NULL;

	m_menu_exibir[5].text  = "&Veiculos";
	m_menu_exibir[5].proc  = NULL;
	m_menu_exibir[5].child = NULL;
	m_menu_exibir[5].flags = 0;
	m_menu_exibir[5].dp    = NULL;

	m_menu_exibir[6].text  = NULL;
	m_menu_exibir[6].proc  = NULL;
	m_menu_exibir[6].child = NULL;
	m_menu_exibir[6].flags = 0;
	m_menu_exibir[6].dp    = NULL;

	m_cfg.SetarArquivo("zeus.ini");
	CarregarConfiguracao();

	m_tela.Limpar();

	CAlien::CarregarArquivoDados(load_datafile("aliens.dat"));
	CConstrucao::CarregarArquivoDados(load_datafile("construcoes.dat"));
	CTiro::CarregarArquivoDados(load_datafile("tiros.dat"));
	CArma::CarregarArquivoDados(load_datafile("armas.dat"));

	m_bmp_fundo		= NULL;
	m_dat_aliens		= NULL;
	m_dat_construcoes = NULL;
	m_tam_pincel_ladrilho = 1;

	m_flag_fase		= false;
	m_flag_obj		= false;
	m_flag_desenhar	= true;
	m_flag_alterado	= false;
	m_flag_apagar		= false;
	m_exibir_obj		= -1;

	m_dat_imagem = load_datafile("imagem.dat");
	if(!m_dat_imagem)
	{
		Erro("ERRO - Arquivo de imagem nao foi carregado!", "imagem.dat");
		alert("ERRO - Arquivo de imagem nao foi carregado!", NULL, NULL, "OK", NULL, NULL, NULL);
		return;
	}

	strcpy(m_arquivo_fase, "");
	strcpy(m_arquivo_fundo, "");

	get_executable_name(arquivo_selecionado, sizeof(arquivo_selecionado));
	nome_comprimento = strlen(arquivo_selecionado);
	strncpy(m_caminho, arquivo_selecionado, nome_comprimento - 8);
	strcpy(m_caminho, "fases\\");

	m_botao_virar_h.Iniciar("imagem.dat", "BOTAO_H_FLIP",  0, NULL, BOTAO_H_FLIP_X, BOTAO_H_FLIP_Y);
	m_botao_virar_v.Iniciar("imagem.dat", "BOTAO_V_FLIP",  0, NULL, BOTAO_V_FLIP_X, BOTAO_V_FLIP_Y);
	m_botao_rotacionar.Iniciar("imagem.dat", "BOTAO_ROTACAO", 0, NULL, BOTAO_ROTACAO_X, BOTAO_ROTACAO_Y);
	m_botao_apagar.Iniciar("imagem.dat", "BOTAO_APAGAR",  0, NULL, BOTAO_APAGAR_X, BOTAO_APAGAR_Y);
	m_botao_inc_pincel.Iniciar("imagem.dat", "BOTAO_INC_PINCEL",  0, NULL, BOTAO_INC_PINCEL_X, BOTAO_INC_PINCEL_Y);
	m_botao_dec_pincel.Iniciar("imagem.dat", "BOTAO_DEC_PINCEL",  0, NULL, BOTAO_DEC_PINCEL_X, BOTAO_DEC_PINCEL_Y);

	lad.bmp_x = 0;
	lad.bmp_y = 0;
	lad.x = LADRILHO_SEL_ESQUERDO_X;
	lad.y = LADRILHO_SEL_ESQUERDO_Y;
	lad.h_flip = 0;
	lad.v_flip = 0;
	lad.angulo = 0;
	m_ladrilho.Iniciar(lad, LADRILHO_LARGURA, LADRILHO_ALTURA, (BITMAP*)m_dat_imagem[LAD_BRANCO].dat);
	m_ladrilho_sel_esquerdo.Iniciar(lad, LADRILHO_LARGURA, LADRILHO_ALTURA, (BITMAP*)m_dat_imagem[LAD_BRANCO].dat);
	lad.x = LADRILHO_SEL_DIREITO_X;
	lad.y = LADRILHO_SEL_DIREITO_Y;
	m_ladrilho_sel_direito.Iniciar(lad, LADRILHO_LARGURA, LADRILHO_ALTURA, (BITMAP*)m_dat_imagem[LAD_BRANCO].dat);
	DesenharTela();
	show_mouse(screen);


	Log("[FIM]:CEditor::Iniciar();");
	Log("");
}


//------------------------------------------------------------
// Execucao geral do Zeus
void CEditor::Executar()
{
	for(;;)
	{
		// Fixa as coordenadas do mouse caso alguma da teclas ctrl esteja pressionada
		if(!key[KEY_LCONTROL]) m_zeus_mouse_x = mouse_x;
		if(!key[KEY_RCONTROL]) m_zeus_mouse_y = mouse_y;

		if(m_flag_desenhar)
		{
			scare_mouse();
			m_tela.Limpar();
			if(m_flag_fase)
			{
				m_fase.Desenhar(m_tela);
				DesenharQuadrado();
			}
			DesenharTela();
			m_tela.AtualizarNaTela();
			unscare_mouse();
			m_flag_desenhar = false;
		}

		if(key[KEY_ESC])
		{
			if(Sair())
				break;
		}

		// Menu
		if(m_zeus_mouse_y > 0
		&& m_zeus_mouse_y < MENU_ALTURA
		&& (mouse_b & 1
		|| mouse_b & 2))
		{
			if(!VerificarMenuArquivo())
				if(!VerificarMenuObjetos())
					if(!VerificarMenuExibir())
						VerificarMenuFerramentas();
		}

		if(m_flag_obj
		&& (mouse_b & 1
		|| mouse_b & 2))
		{
			// Menu de objetos
     		if(m_zeus_mouse_x > MENU_OBJ_X1
            && m_zeus_mouse_x < MENU_OBJ_X2
			&& m_zeus_mouse_y > MENU_OBJ_Y1
            && m_zeus_mouse_y < MENU_OBJ_Y2)
			{
				m_flag_apagar = false;
				VerificarMenuObj();
			}
			else
			{
				// Menu Aux
				VerificarMenuAux();
			}
		}

		// Mapa do Editor
		if(m_flag_fase)
		{
			VerificarRolaTecla();

			if(m_flag_obj
			&& m_zeus_mouse_x > MAPA_EDITOR_X1
			&& m_zeus_mouse_x < MAPA_EDITOR_X2
			&& m_zeus_mouse_y > MAPA_EDITOR_Y1
			&& m_zeus_mouse_y < MAPA_EDITOR_Y2)
			{
				VerificarRolaMouse();

				if(m_zeus_mouse_x != mouse_x
				|| m_zeus_mouse_y != mouse_y)
				{
					m_flag_desenhar = true;
				}
				if(!m_flag_apagar)
				{
					switch(m_exibir_obj)
					{
						case eAlien:
							VerificarAlien();
							break;

						case eFundo:
							VerificarLadrilho();
							break;

						case eConstrucao:
							VerificarConstrucao();
							break;
					}
				}
				else if(mouse_b & 1
					 || mouse_b & 2)
				{
					VerificarApagar();
				}

			}
		}
	}
}


//------------------------------------------------------------
// Libera memoria e desliga o Zeus
void CEditor::Finalizar()
{
	Log("");
	Log("[INICIO]:CEditor::Finalizar()");

	if(m_flag_fase) m_fase.Finalizar();
	else
	{
		Log("oi nois aqui travez!");
		CAlien::DescarregarArquivoDados();
		CConstrucao::DescarregarArquivoDados();
		CTiro::DescarregarArquivoDados();
		CArma::DescarregarArquivoDados();
	}

	if(m_bmp_fundo)
	{
		destroy_bitmap(m_bmp_fundo);
		m_bmp_fundo = NULL;
	}

	if(m_dat_aliens)
	{
		unload_datafile(m_dat_aliens);
		m_dat_aliens = NULL;
	}

	if(m_dat_construcoes)
	{
		unload_datafile(m_dat_construcoes);
		m_dat_construcoes = NULL;
	}

	m_tela.Desligar();

	m_botao_virar_h.Finalizar();
	m_botao_virar_v.Finalizar();
	m_botao_rotacionar.Finalizar();
	m_botao_apagar.Finalizar();
	m_botao_inc_pincel.Finalizar();
	m_botao_dec_pincel.Finalizar();

	Log("[FIM]:CEditor::Finalizar()");
}

//------------------------------------------------------------
// Monta o menu dos objetos
// Modo 0 = nao inicar selecionados
// Modo 1 = inicar selecionados
void CEditor::MontarMenuObj(int modo)
{
	register int x, y;
	int  num_obj;
	TLadrilho lad;

	m_flag_desenhar = true;
	m_tela.RectFill(eCamadaFundo, 0, 0, MENU_OBJ_LARGURA, MENU_OBJ_ALTURA, makecol(0, 0, 0));
	m_tela.RectFill(eCamadaObjetos, 0, 0, MENU_OBJ_LARGURA, MENU_OBJ_ALTURA, makecol(255, 0, 255));
	m_tela.RectFill(eCamadaEfeitos, 0, 0, MENU_OBJ_LARGURA, MENU_OBJ_ALTURA, makecol(255, 0, 255));

	// Desmarca todas as opcoes do menu exibir
	m_menu_exibir[0].flags = 0;
	m_menu_exibir[1].flags = 0;
	m_menu_exibir[2].flags = 0;
	m_menu_exibir[3].flags = 0;
	m_menu_exibir[4].flags = 0;
	m_menu_exibir[5].flags = 0;

	// Marca a opcao selecionada
	if(m_exibir_obj > -1) m_menu_exibir[m_exibir_obj].flags = 1;
	if(modo) m_flag_apagar = false;
    num_obj = 0;
	switch(m_exibir_obj)
	{
		case eAlien:
				for(x = 0; x < MENU_OBJ_LARGURA_LADRILHO; x++)
				{
					for(y = 0; y < MENU_OBJ_ALTURA_LADRILHO; y++)
					{
						lad.bmp_x = 0;
						lad.bmp_y = 0;
						lad.x = x * LADRILHO_LARGURA;
						lad.y = y * LADRILHO_ALTURA;
						lad.h_flip = 0;
						lad.v_flip = 0;
						lad.angulo = 0;
						strcpy(lad.arquivo_bmp, "m_arquivo_aliens");
						m_menu_obj_ladrilhos[x] [y].Iniciar(lad, LADRILHO_LARGURA, LADRILHO_ALTURA, (BITMAP*)m_dat_aliens[num_obj].dat);
						m_menu_obj_ladrilhos[x] [y].Desenhar(m_tela, 0, 0);
						m_tela.Rect(eCamadaFundo, m_menu_obj_ladrilhos[x][y].ObterX(), m_menu_obj_ladrilhos[x][y].ObterY(), m_menu_obj_ladrilhos[x][y].ObterX() + LADRILHO_LARGURA, m_menu_obj_ladrilhos[x][y].ObterY() + LADRILHO_ALTURA, makecol(100, 100, 100));

						num_obj += 2;
						if(num_obj > 12)
						{
							if(modo)
							{
								lad.x = LADRILHO_SEL_ESQUERDO_X;
								lad.y = LADRILHO_SEL_ESQUERDO_Y;
								// Ladrilho auxiliar
								m_ladrilho.Finalizar();
								m_ladrilho.Iniciar(lad, LADRILHO_LARGURA, LADRILHO_ALTURA, (BITMAP *) m_dat_aliens[0].dat);
								// Ladrilhos selecionados
								m_ladrilho_sel_esquerdo.Finalizar();
								m_ladrilho_sel_esquerdo.Iniciar(lad, LADRILHO_LARGURA, LADRILHO_ALTURA, (BITMAP *) m_dat_aliens[0].dat);
								lad.x = LADRILHO_SEL_DIREITO_X;
								lad.y = LADRILHO_SEL_DIREITO_Y;
								m_ladrilho_sel_direito.Finalizar();
								m_ladrilho_sel_direito.Iniciar(lad, LADRILHO_LARGURA, LADRILHO_ALTURA, (BITMAP *) m_dat_aliens[2].dat);
								m_alien_sel_esquerdo.Iniciar(0, 0, 0);
								m_alien_sel_direito.Iniciar(1, 0, 0);

							}
							m_ladrilho_sel_esquerdo.Desenhar(m_tela, 0, 0);
							m_ladrilho_sel_direito.Desenhar(m_tela, 0, 0);

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
						lad.h_flip = 0;
						lad.v_flip = 0;
						lad.angulo = 0;
						strcpy(lad.arquivo_bmp, m_arquivo_fundo);

						m_menu_obj_ladrilhos[x] [y].Iniciar(lad, LADRILHO_LARGURA, LADRILHO_ALTURA, m_bmp_fundo);
						m_menu_obj_ladrilhos[x] [y].Desenhar(m_tela, 0, 0);
						m_tela.Rect(eCamadaFundo, m_menu_obj_ladrilhos[x][y].ObterX(), m_menu_obj_ladrilhos[x][y].ObterY(), m_menu_obj_ladrilhos[x][y].ObterX() + LADRILHO_LARGURA, m_menu_obj_ladrilhos[x][y].ObterY() + LADRILHO_ALTURA, makecol(100, 100, 100));
					}
				}

				if(modo)
				{
					// Ladrilho auxiliar
					m_ladrilho.Finalizar();
					m_ladrilho.Iniciar(m_menu_obj_ladrilhos[0][0].ObterTLadrilho(), LADRILHO_LARGURA, LADRILHO_ALTURA, m_bmp_fundo);
					// Ladrilhos selecionados
					m_ladrilho_sel_esquerdo.Finalizar();
					m_ladrilho_sel_esquerdo.Iniciar(m_menu_obj_ladrilhos[0][0].ObterTLadrilho(), LADRILHO_LARGURA, LADRILHO_ALTURA, m_bmp_fundo);
					m_ladrilho_sel_esquerdo.SetarX(LADRILHO_SEL_ESQUERDO_X);
					m_ladrilho_sel_esquerdo.SetarY(LADRILHO_SEL_ESQUERDO_Y);
					m_ladrilho_sel_direito.Finalizar();
					m_ladrilho_sel_direito.Iniciar(m_menu_obj_ladrilhos[0][1].ObterTLadrilho(), LADRILHO_LARGURA, LADRILHO_ALTURA, m_bmp_fundo);
					m_ladrilho_sel_direito.SetarX(LADRILHO_SEL_DIREITO_X);
					m_ladrilho_sel_direito.SetarY(LADRILHO_SEL_DIREITO_Y);
				}
				m_ladrilho_sel_esquerdo.Desenhar(m_tela, 0, 0);
				m_ladrilho_sel_direito.Desenhar(m_tela, 0, 0);
				break;

		case eConstrucao:
				for(x = 0; x < MENU_OBJ_LARGURA_LADRILHO; x++)
				{
					for(y = 0; y < MENU_OBJ_ALTURA_LADRILHO; y++)
					{
						lad.bmp_x = 0;
						lad.bmp_y = 0;
						lad.x = x * LADRILHO_LARGURA;
						lad.y = y * LADRILHO_ALTURA;
						lad.h_flip = 0;
						lad.v_flip = 0;
						lad.angulo = 0;
						strcpy(lad.arquivo_bmp, "m_arquivo_aliens");
						m_menu_obj_ladrilhos[x] [y].Iniciar(lad, LADRILHO_LARGURA, LADRILHO_ALTURA, (BITMAP*)m_dat_construcoes[num_obj].dat);
						m_menu_obj_ladrilhos[x] [y].Desenhar(m_tela, 0, 0);
						m_tela.Rect(eCamadaFundo, m_menu_obj_ladrilhos[x][y].ObterX(), m_menu_obj_ladrilhos[x][y].ObterY(), m_menu_obj_ladrilhos[x][y].ObterX() + LADRILHO_LARGURA, m_menu_obj_ladrilhos[x][y].ObterY() + LADRILHO_ALTURA, makecol(100, 100, 100));

						num_obj++;
						if(num_obj > 5)
						{
							if(modo)
							{
								lad.x = LADRILHO_SEL_ESQUERDO_X;
								lad.y = LADRILHO_SEL_ESQUERDO_Y;
								// Ladrilho auxiliar
								m_ladrilho.Finalizar();
								m_ladrilho.Iniciar(lad, LADRILHO_LARGURA, LADRILHO_ALTURA, (BITMAP *) m_dat_construcoes[0].dat);
								// Ladrilhos selecionados
								m_ladrilho_sel_esquerdo.Finalizar();
								m_ladrilho_sel_esquerdo.Iniciar(lad, LADRILHO_LARGURA, LADRILHO_ALTURA, (BITMAP *) m_dat_construcoes[0].dat);
								lad.x = LADRILHO_SEL_DIREITO_X;
								lad.y = LADRILHO_SEL_DIREITO_Y;
								m_ladrilho_sel_direito.Finalizar();
								m_ladrilho_sel_direito.Iniciar(lad, LADRILHO_LARGURA, LADRILHO_ALTURA, (BITMAP *) m_dat_construcoes[1].dat);
								m_construcao_sel_esquerdo.Iniciar(0, 0, 0);
								m_construcao_sel_direito.Iniciar(1, 0, 0);
							}

							m_ladrilho_sel_esquerdo.Desenhar(m_tela, 0, 0);
							m_ladrilho_sel_direito.Desenhar(m_tela, 0, 0);
							return;
						}
					}
				}

				break;

		default:
			for(x = 0; x < MENU_OBJ_LARGURA_LADRILHO; x++)
				for(y = 0; y < MENU_OBJ_ALTURA_LADRILHO; y++)
					m_tela.Rect(eCamadaFundo, x * 32, y * 32, x * 32 + LADRILHO_LARGURA, y * 32 + LADRILHO_ALTURA, makecol(100, 100, 100));
			break;
	}
}


//------------------------------------------------------------
// Abre uma m_fase jah existente
bool CEditor::AbrirFase()
{
	char arquivo_selecionado[ARQUIVO_NOME_COMPRIMENTO], aux[ARQUIVO_NOME_COMPRIMENTO];
	int opcao, verificados;

	if(m_flag_alterado)
	{
		opcao = alert3("Deseja salvar a fase atual?", NULL, NULL, "Sim", "Nao", "Cancelar", NULL, NULL, NULL);
		if(opcao == 1)
			SalvarFase();
		else if(opcao == 3)
			return false;
	}

	strcpy(arquivo_selecionado, m_caminho);
	if((file_select_ex("Selecione o m_arquivo do mapa:", arquivo_selecionado, "map", sizeof(arquivo_selecionado), DIALOGO_LARGURA, DIALOGO_ALTURA)) != NULL)
	{
		verificados = 0;

		strcpy(aux, "fases\\");
		strcat(aux, get_filename(arquivo_selecionado));
		strcpy(m_arquivo_fase, aux);

		verificados += 100;
		//barra_progresso_zeus(screen, BARRA_PROGRESSO_X, BARRA_PROGRESSO_Y, BARRA_PROGRESSO_X + BARRA_PROGRESSO_LARGURA, BARRA_PROGRESSO_Y + BARRA_PROGRESSO_ALTURA, 300, verificados - 1, verificados, BARRA_PROGRESSO_COR);

		if(m_flag_fase) m_fase.Finalizar();

		m_fase.Iniciar(aux, MAPA_EDITOR_X1, MAPA_EDITOR_Y1, MAPA_EDITOR_LARGURA, MAPA_EDITOR_ALTURA);

		verificados += 100;
//		barra_progresso_zeus(screen, BARRA_PROGRESSO_X, BARRA_PROGRESSO_Y, BARRA_PROGRESSO_X + BARRA_PROGRESSO_LARGURA, BARRA_PROGRESSO_Y + BARRA_PROGRESSO_ALTURA, 300, verificados - 1, verificados, BARRA_PROGRESSO_COR);

		verificados += 100;
//		barra_progresso_zeus(screen, BARRA_PROGRESSO_X, BARRA_PROGRESSO_Y, BARRA_PROGRESSO_X + BARRA_PROGRESSO_LARGURA, BARRA_PROGRESSO_Y + BARRA_PROGRESSO_ALTURA, 300, verificados - 1, verificados, BARRA_PROGRESSO_COR);

		m_flag_fase     = true;
		m_flag_desenhar = true;
		m_flag_alterado = false;
		return true;
	}
	return false;
}


//------------------------------------------------------------
// Inicia uma nova m_fase
bool CEditor::NovaFase()
{
	int opcao, verificados;

	Log("bool CEditor::NovaFase();");
	if(m_flag_alterado)
	{
		opcao = alert3("Deseja salvar a fase atual?", NULL, NULL, "Sim", "Nao", "Cancelar", NULL, NULL, NULL);
		if(opcao == 1)
			SalvarFase();
		else if(opcao == 3)
			return false;
	}

	scare_mouse();
	strcpy(m_arquivo_fase, "fases\\novo.dft");

	verificados = 0;
	verificados += 100;
//	barra_progresso_zeus(screen, BARRA_PROGRESSO_X, BARRA_PROGRESSO_Y, BARRA_PROGRESSO_X + BARRA_PROGRESSO_LARGURA, BARRA_PROGRESSO_Y + BARRA_PROGRESSO_ALTURA, 300, verificados - 1, verificados, BARRA_PROGRESSO_COR);
	if(m_flag_fase) m_fase.Finalizar();

	m_fase.Iniciar(m_arquivo_fase, MAPA_EDITOR_X1, MAPA_EDITOR_Y1, MAPA_EDITOR_LARGURA, MAPA_EDITOR_ALTURA);

	verificados += 100;
//	barra_progresso_zeus(screen, BARRA_PROGRESSO_X, BARRA_PROGRESSO_Y, BARRA_PROGRESSO_X + BARRA_PROGRESSO_LARGURA, BARRA_PROGRESSO_Y + BARRA_PROGRESSO_ALTURA, 300, verificados - 1, verificados, BARRA_PROGRESSO_COR);

	verificados += 100;
//	barra_progresso_zeus(screen, BARRA_PROGRESSO_X, BARRA_PROGRESSO_Y, BARRA_PROGRESSO_X + BARRA_PROGRESSO_LARGURA, BARRA_PROGRESSO_Y + BARRA_PROGRESSO_ALTURA, 300, verificados - 1, verificados, BARRA_PROGRESSO_COR);

	m_flag_fase = true;
	m_flag_desenhar = true;
	m_flag_alterado = false;
	unscare_mouse();
	return true;
}


//------------------------------------------------------------
// Salva a m_fase corrente
bool CEditor::SalvarFase()
{
	if((strcmp(m_arquivo_fase, "fases\\novo.dft") != 0))
	{
		m_fase.SalvarFase();
		m_flag_alterado = false;
		return true;
	}
	else
		return SalvarComoFase();
	return false;
}


//------------------------------------------------------------
// Salvar a m_fase com o nome selecionado
bool CEditor::SalvarComoFase()
{
	char arquivo_selecionado[ARQUIVO_NOME_COMPRIMENTO], aux[ARQUIVO_NOME_COMPRIMENTO];


	if(strlen(m_arquivo_fase) > 0)
	{
		strcpy(arquivo_selecionado, m_caminho);
		if((file_select_ex("Informe o nome para o m_arquivo da m_fase:", arquivo_selecionado, "map", sizeof(arquivo_selecionado), DIALOGO_LARGURA, DIALOGO_ALTURA)) != NULL)
		{
			strcpy(aux, "fases\\");
			strcat(aux, get_filename(arquivo_selecionado));
			strcpy(m_arquivo_fase, aux);
			m_fase.SetarArquivoFase(m_arquivo_fase);
			return SalvarFase();
		}
	}
	return false;
}


//------------------------------------------------------------
// Fechar a m_fase corrente
bool CEditor::FecharFase()
{
	if(strlen(m_arquivo_fase) > 0)
		return NovaFase();

	return false;
}


//------------------------------------------------------------
// Abre o fundo e mostra no menu obj
bool CEditor::AbrirFundo()
{
	char arquivo_selecionado[ARQUIVO_NOME_COMPRIMENTO];
	BITMAP *m_bmp_aux;

	strcpy(arquivo_selecionado, m_caminho);;
	if((file_select_ex("Selecione o m_arquivo bitmap para o fundo:", arquivo_selecionado, "bmp", sizeof(arquivo_selecionado), DIALOGO_LARGURA, DIALOGO_ALTURA)) != NULL)
	{

		strcpy(m_arquivo_fundo, "fases\\");
		strcat(m_arquivo_fundo, get_filename(arquivo_selecionado));

		m_bmp_aux = load_bmp(m_arquivo_fundo, NULL);
		if(!m_bmp_aux)
		{
			Erro("ERRO - Arquivo de fundo nao foi carregado!", m_arquivo_fundo);
			alert("ERRO - Arquivo de Fundo nao foi carregado!", NULL, NULL, "OK", NULL, NULL, NULL);
			return false;
		}

		// Testa se as dimensões do bitmap são as válidas
        if(m_bmp_aux->w != BMP_FUNDO_L || m_bmp_aux->h != BMP_FUNDO_A)
		{
			alert("ERRO - Arquivo de Fundo com dimensoes invalidas", NULL, NULL, "OK", NULL, NULL, NULL);
			return false;
		}
		if(m_bmp_fundo) destroy_bitmap(m_bmp_fundo);
		m_bmp_fundo = m_bmp_aux;

		scare_mouse();
		m_exibir_obj = eFundo;
		MontarMenuObj(1);
		unscare_mouse();
		m_flag_obj = 1;
		m_flag_desenhar = true;
		return true;
	}
	return false;

}


//------------------------------------------------------------
// Abre o m_arquivo dat dos aliens e mostra no menu obj
bool CEditor::AbrirAliens()
{
	m_dat_aliens = load_datafile("aliens.dat");
	if(!m_dat_aliens)
	{
		Erro("ERRO - Arquivo de Aliens nao foi carregado!", m_arquivo_aliens);
		alert("ERRO - Arquivo de Aliens nao foi carregado!", NULL, NULL, "OK", NULL, NULL, NULL);
		return false;
	}

	m_alien_sel_esquerdo.Iniciar(0, 0, 0);
	m_alien_sel_direito.Iniciar(1, 0, 0);

	scare_mouse();
	m_exibir_obj = eAlien;
	MontarMenuObj(1);
	unscare_mouse();
	m_flag_obj = 1;
	m_flag_desenhar = true;
	return true;
}


//------------------------------------------------------------
// Abre o m_arquivo dat das construcoes e mostra no menu obj
bool CEditor::AbrirConstrucoes()
{
	m_dat_construcoes = load_datafile("construcoes.dat");
	if(!m_dat_construcoes)
	{
		Erro("ERRO - Arquivo de Construcoes nao foi carregado!", m_arquivo_construcoes);
		alert("ERRO - Arquivo de Construcoes nao foi carregado!", NULL, NULL, "OK", NULL, NULL, NULL);
		return false;
	}

	m_construcao_sel_esquerdo.Iniciar(0, 0, 0);
	m_construcao_sel_direito.Iniciar(1, 0, 0);

	scare_mouse();
	m_exibir_obj = eConstrucao;
	MontarMenuObj(1);
	unscare_mouse();
	m_flag_obj = 1;
	m_flag_desenhar = true;
	return true;
}


//------------------------------------------------------------
// Preenche todos os ladrilhos nulos (padrao) pelo m_ladrilho_sel_esquerdo
bool CEditor::PreencherNulos()
{
	register int x, y, verificados;

	if(m_flag_fase
	&& m_flag_obj
	&& m_exibir_obj == eFundo)
	{
		verificados = 0;
		m_ladrilho.Finalizar();
		m_ladrilho.Iniciar(m_ladrilho_sel_esquerdo.ObterTLadrilho(), LADRILHO_LARGURA, LADRILHO_ALTURA, m_ladrilho_sel_esquerdo.ObterBmpFonte());
		for(x = 0; x < MAPA_LARGURA_LADRILHOS; x++)
		{
			for(y = 0; y < MAPA_ALTURA_LADRILHOS; y++)
			{
				if(strcmp(m_fase.ObterLadrilho(x, y).ObterArquivoBmp(), "fases\\novo.bmp") == 0)
				{
					m_ladrilho.SetarX(m_fase.ObterLadrilho(x, y).ObterX());
					m_ladrilho.SetarY(m_fase.ObterLadrilho(x, y).ObterY());
					m_fase.SetarLadrilho(x, y, m_ladrilho.ObterTLadrilho(), m_bmp_fundo);
				}
				verificados++;
//				barra_progresso_zeus(screen, BARRA_PROGRESSO_X, BARRA_PROGRESSO_Y, BARRA_PROGRESSO_X + BARRA_PROGRESSO_LARGURA, BARRA_PROGRESSO_Y + BARRA_PROGRESSO_ALTURA, MAPA_TOTAL_LADRILHOS, verificados - 1, verificados, BARRA_PROGRESSO_COR);
			}
		}
		if(verificados)
		{
			m_flag_desenhar = true;
			m_flag_alterado = true;
			return true;
		}
	}
	return false;
}


//------------------------------------------------------------
// Troca os ladrilhos iguais ao m_ladrilho_sel_esquerdo para
// m_ladrilho_sel_direito, sem considerar m_h_flip, m_v_flip e angulo
bool CEditor::TrocarLadrilhos()
{
	register int x, y, verificados;

	if(m_flag_fase
	&& m_flag_obj
	&& m_exibir_obj == eFundo)
	{
		verificados = 0;
		m_ladrilho.Finalizar();
		m_ladrilho.Iniciar(m_ladrilho_sel_direito.ObterTLadrilho(), LADRILHO_LARGURA, LADRILHO_ALTURA, m_ladrilho_sel_direito.ObterBmpFonte());
		for(x = 0; x < MAPA_LARGURA_LADRILHOS; x++)
		{
			for(y = 0; y < MAPA_ALTURA_LADRILHOS; y++)
			{
				if(strcmp(m_fase.ObterLadrilho(x, y).ObterArquivoBmp(), m_ladrilho_sel_esquerdo.ObterArquivoBmp()) == 0 && m_fase.ObterLadrilho(x, y).ObterXBmp() == m_ladrilho_sel_esquerdo.ObterXBmp() && m_fase.ObterLadrilho(x, y).ObterYBmp() == m_ladrilho_sel_esquerdo.ObterYBmp())
				{
					m_ladrilho.SetarX(m_fase.ObterLadrilho(x, y).ObterX());
					m_ladrilho.SetarY(m_fase.ObterLadrilho(x, y).ObterY());
					m_fase.SetarLadrilho(x, y, m_ladrilho.ObterTLadrilho(), m_ladrilho.ObterBmpFonte());
				}
				verificados++;
//				barra_progresso_zeus(screen, BARRA_PROGRESSO_X, BARRA_PROGRESSO_Y, BARRA_PROGRESSO_X + BARRA_PROGRESSO_LARGURA, BARRA_PROGRESSO_Y + BARRA_PROGRESSO_ALTURA, MAPA_TOTAL_LADRILHOS, verificados - 1, verificados, BARRA_PROGRESSO_COR);
			}
		}
		if(verificados)
		{
			m_flag_desenhar = true;
			m_flag_alterado = true;
			return true;
		}
	}
	return false;
}


//------------------------------------------------------------
// Verifica se ha m_fase para salvar e finaliza o Zeus
bool CEditor::Sair()
{
	int opcao;

	if(m_flag_alterado)
	{
		opcao = alert3("Deseja salvar a fase atual?", NULL, NULL, "Sim", "Nao", "Cancelar", NULL, NULL, NULL);
		if(opcao == 1)
			SalvarFase();
		else if(opcao == 3)
			return false;
	}
	return true;
}


//------------------------------------------------------------
// Desenha os componentes da m_tela
void CEditor::DesenharTela()
{
	char buf[30];

	// Menu Superior
	if(!m_flag_fase) m_tela.RectFill(eCamadaEfeitos, MAPA_EDITOR_X1, MAPA_EDITOR_Y1, MAPA_EDITOR_X2, MAPA_EDITOR_Y2, makecol(0, 0, 0));

	m_tela.RectFill(eCamadaEfeitos, MENU_ARQUIVO_X1, 0, SCREEN_W, MENU_ALTURA, makecol(0, 0, 0));
	m_tela.Escrever(eCamadaEfeitos, "Arquivo", MENU_ARQUIVO_X1, 0, makecol(255, 255, 255));
	m_tela.Escrever(eCamadaEfeitos, "Objetos", MENU_OBJETOS_X1, 0, makecol(255, 255, 255));
	m_tela.Escrever(eCamadaEfeitos, "Exibir", MENU_EXIBIR_X1, 0, makecol(255, 255, 255));
	m_tela.Escrever(eCamadaEfeitos, "Ferramentas", MENU_FERRAMENTAS_X1, 0, makecol(255, 255, 255));

	// Display das coordenadas do mapa da m_fase
	if(m_flag_fase)
	{
		sprintf(buf, "[x: %4i][y: %4i]", m_fase.ObterX1Fonte(), m_fase.ObterY1Fonte());
		m_tela.Escrever(eCamadaEfeitos, buf, 495, 1, makecol(255, 255, 255));
	}

	MontarMenuObj(0);

	// Menu aux
	m_tela.RectFill(eCamadaFundo, MENU_AUX_X, MENU_AUX_Y, SCREEN_W, SCREEN_H, makecol(0, 0, 0));
	m_tela.RectFill(eCamadaObjetos, MENU_AUX_X, MENU_AUX_Y, SCREEN_W, SCREEN_H, makecol(255, 0, 255));
	m_tela.RectFill(eCamadaEfeitos, MENU_AUX_X, MENU_AUX_Y, SCREEN_W, SCREEN_H, makecol(255, 0, 255));

	m_ladrilho_sel_esquerdo.Desenhar(m_tela, 0, 0);
	m_ladrilho_sel_direito.Desenhar(m_tela, 0, 0);

	switch(m_exibir_obj)
	{
		case eFundo:
			m_botao_virar_h.SetarAtivo(1);
			m_botao_virar_v.SetarAtivo(1);
			m_botao_rotacionar.SetarAtivo(1);
			m_botao_apagar.SetarAtivo(0);
			m_botao_inc_pincel.SetarAtivo(1);
			m_botao_dec_pincel.SetarAtivo(1);
		break;

		case eAlien:
		case eConstrucao:
			m_botao_virar_h.SetarAtivo(0);
			m_botao_virar_v.SetarAtivo(0);
				m_botao_rotacionar.SetarAtivo(0);
				m_botao_apagar.SetarAtivo(1);
				m_botao_inc_pincel.SetarAtivo(0);
				m_botao_dec_pincel.SetarAtivo(0);
				break;

		default:
			m_botao_virar_h.SetarAtivo(0);
			m_botao_virar_v.SetarAtivo(0);
			m_botao_rotacionar.SetarAtivo(0);
			m_botao_apagar.SetarAtivo(0);
			m_botao_inc_pincel.SetarAtivo(0);
			m_botao_dec_pincel.SetarAtivo(0);

			break;
	}

	m_botao_virar_h.Desenhar(m_tela, eCamadaEfeitos);
	m_botao_virar_v.Desenhar(m_tela, eCamadaEfeitos);
	m_botao_rotacionar.Desenhar(m_tela, eCamadaEfeitos);
	m_botao_apagar.Desenhar(m_tela, eCamadaEfeitos);
	m_botao_inc_pincel.Desenhar(m_tela, eCamadaEfeitos);
	m_botao_dec_pincel.Desenhar(m_tela, eCamadaEfeitos);
	sprintf(buf, "%i", m_tam_pincel_ladrilho);
	m_tela.Escrever(eCamadaEfeitos, buf, BOTAO_INC_PINCEL_X + 38, BOTAO_INC_PINCEL_Y + 11, makecol(0, 255, 0));

	if(m_flag_fase)
	{
		sprintf(buf, "     Aliens: %3i", CAlien::ObterNumeroAliens());
		m_tela.Escrever(eCamadaEfeitos, buf, BOTAO_INC_PINCEL_X + 230, BOTAO_APAGAR_Y + 5, makecol(0, 255, 0));
		sprintf(buf, "Construcoes: %3i", CConstrucao::ObterNumeroConstrucoes());
		m_tela.Escrever(eCamadaEfeitos, buf, BOTAO_INC_PINCEL_X + 230, BOTAO_APAGAR_Y + 16, makecol(0, 255, 0));
	}
	///m_tela.hline(m_tela, MENU_AUX_X, MENU_AUX_Y, SCREEN_W, LADRILHO_NAO_SELECIONADO_COR);
}


//------------------------------------------------------------
// Verifica se deve ser inserido um m_ladrilho no mapa
void CEditor::VerificarLadrilho()
{
	register int x, y, i_x, i_y;

	x = (m_zeus_mouse_x - 97 + m_fase.ObterX1Fonte()) / LADRILHO_LARGURA;
	y = (m_zeus_mouse_y - 11 + m_fase.ObterY1Fonte()) / LADRILHO_ALTURA;

	if(mouse_b & 1)
	{
		// Quando pressiona a tecla shift
        // e o botão esquerdo
		if(key[KEY_LSHIFT] || key[KEY_RSHIFT])
		{
			m_ladrilho_sel_esquerdo.Finalizar();
			m_ladrilho_sel_esquerdo.Iniciar(m_fase.ObterLadrilho(x, y).ObterTLadrilho(), LADRILHO_LARGURA, LADRILHO_ALTURA, m_fase.ObterLadrilho(x, y).ObterBmpFonte());
			m_ladrilho_sel_esquerdo.SetarX(LADRILHO_SEL_ESQUERDO_X);
			m_ladrilho_sel_esquerdo.SetarY(LADRILHO_SEL_ESQUERDO_Y);
			m_ladrilho_sel_esquerdo.Desenhar(m_tela, 0, 0);
			m_flag_desenhar = true;
		}
		else
		if((strcmp(m_fase.ObterLadrilho(x, y).ObterArquivoBmp(), m_ladrilho_sel_esquerdo.ObterArquivoBmp()) != 0)
		|| m_fase.ObterLadrilho(x, y).ObterXBmp()    != m_ladrilho_sel_esquerdo.ObterXBmp()
		|| m_fase.ObterLadrilho(x, y).ObterYBmp()    != m_ladrilho_sel_esquerdo.ObterYBmp()
		|| m_fase.ObterLadrilho(x, y).ObterHFlip()  != m_ladrilho_sel_esquerdo.ObterHFlip()
		|| m_fase.ObterLadrilho(x, y).ObterVFlip()  != m_ladrilho_sel_esquerdo.ObterVFlip()
		|| m_fase.ObterLadrilho(x, y).ObterAngulo() != m_ladrilho_sel_esquerdo.ObterAngulo())
		{
			m_ladrilho.Finalizar();
			m_ladrilho.Iniciar(m_ladrilho_sel_esquerdo.ObterTLadrilho(), LADRILHO_LARGURA, LADRILHO_ALTURA, m_ladrilho_sel_esquerdo.ObterBmpFonte());
			m_ladrilho.SetarX(m_fase.ObterLadrilho(x, y).ObterX());
			m_ladrilho.SetarY(m_fase.ObterLadrilho(x, y).ObterY());
			m_fase.SetarLadrilho(x, y, m_ladrilho.ObterTLadrilho(), m_ladrilho.ObterBmpFonte());
			for(i_x = (m_tam_pincel_ladrilho - 1) / -2; i_x <= (m_tam_pincel_ladrilho - 1) / 2; i_x++)
			{
				for(i_y = (m_tam_pincel_ladrilho - 1) / -2; i_y <= (m_tam_pincel_ladrilho - 1) / 2; i_y++)
				{
					if(x + i_x >= 0 && x + i_x < MAPA_LARGURA_LADRILHOS
					&& y + i_y >= 0 && y + i_y < MAPA_ALTURA_LADRILHOS)
					{
						m_ladrilho.SetarX(m_fase.ObterLadrilho(x + i_x, y + i_y).ObterX());
						m_ladrilho.SetarY(m_fase.ObterLadrilho(x + i_x, y + i_y).ObterY());
						m_fase.SetarLadrilho(x + i_x, y + i_y, m_ladrilho.ObterTLadrilho(), m_ladrilho.ObterBmpFonte());
					}
				}
			}
			m_flag_alterado = true;
			m_flag_desenhar = true;
		}
	}
	else
	if(mouse_b & 2)
	{
		// Quando pressiona a tecla shift
		// e o botão direito do mouse
		if(key[KEY_LSHIFT] || key[KEY_RSHIFT])
		{
			m_ladrilho_sel_direito.Finalizar();
			m_ladrilho_sel_direito.Iniciar(m_fase.ObterLadrilho(x, y).ObterTLadrilho(), LADRILHO_LARGURA, LADRILHO_ALTURA, m_fase.ObterLadrilho(x, y).ObterBmpFonte());
			m_ladrilho_sel_direito.SetarX(LADRILHO_SEL_DIREITO_X);
			m_ladrilho_sel_direito.SetarY(LADRILHO_SEL_DIREITO_Y);
			m_ladrilho_sel_direito.Desenhar(m_tela, 0, 0);
			m_flag_desenhar = true;
		}
		else
		if(strcmp(m_fase.ObterLadrilho(x, y).ObterArquivoBmp(), m_ladrilho_sel_direito.ObterArquivoBmp()) != 0
		|| m_fase.ObterLadrilho(x, y).ObterXBmp() != m_ladrilho_sel_direito.ObterXBmp()
		|| m_fase.ObterLadrilho(x, y).ObterYBmp() != m_ladrilho_sel_direito.ObterYBmp()
		|| m_fase.ObterLadrilho(x, y).ObterHFlip()  != m_ladrilho_sel_direito.ObterHFlip()
		|| m_fase.ObterLadrilho(x, y).ObterVFlip()  != m_ladrilho_sel_direito.ObterVFlip()
		|| m_fase.ObterLadrilho(x, y).ObterAngulo() != m_ladrilho_sel_direito.ObterAngulo())
		{
			m_ladrilho.Finalizar();
			m_ladrilho.Iniciar(m_ladrilho_sel_direito.ObterTLadrilho(), LADRILHO_LARGURA, LADRILHO_ALTURA, m_ladrilho_sel_direito.ObterBmpFonte());
			m_ladrilho.SetarX(m_fase.ObterLadrilho(x, y).ObterX());
			m_ladrilho.SetarY(m_fase.ObterLadrilho(x, y).ObterY());

			for(i_x = (m_tam_pincel_ladrilho - 1) / -2; i_x <= (m_tam_pincel_ladrilho - 1) / 2; i_x++)
			{
				for(i_y = (m_tam_pincel_ladrilho - 1) / -2; i_y <= (m_tam_pincel_ladrilho - 1) / 2; i_y++)
				{
					if(x + i_x >= 0 && x + i_x < MAPA_LARGURA_LADRILHOS
					&& y + i_y >= 0 && y + i_y < MAPA_ALTURA_LADRILHOS)
					{
						m_ladrilho.SetarX(m_fase.ObterLadrilho(x + i_x, y + i_y).ObterX());
						m_ladrilho.SetarY(m_fase.ObterLadrilho(x + i_x, y + i_y).ObterY());
						m_fase.SetarLadrilho(x + i_x, y + i_y, m_ladrilho.ObterTLadrilho(), m_ladrilho.ObterBmpFonte());
					}
				}
			}
			m_flag_desenhar = true;
			m_flag_alterado = true;
		}
	}
}


//------------------------------------------------------------
// Verifica se deve ser inserido um alien no mapa
void CEditor::VerificarAlien()
{
	if(mouse_b & 1)
	{
		// Exclui os aliens já incluidos no mapa que colidirem
		// com a novo alien adicionado
		// m_fase.ExcluirAliens(m_fase.ObterX1Fonte() + (m_zeus_mouse_x - 97 - (m_alien_sel_esquerdo.ObterLargura() / 2)), m_fase.ObterY1Fonte() + (m_zeus_mouse_y - MAPA_EDITOR_Y1 - (m_alien_sel_esquerdo.ObterAltura() / 2)), m_fase.ObterX1Fonte() + (m_zeus_mouse_x - 97 + m_alien_sel_esquerdo.ObterLargura() / 2), m_fase.ObterY1Fonte() + (m_zeus_mouse_y - MAPA_EDITOR_Y1 + m_alien_sel_esquerdo.ObterAltura() / 2));

		if(m_alien_sel_esquerdo.ObterX() != m_fase.ObterX1Fonte() + (m_zeus_mouse_x - 97 - (m_alien_sel_esquerdo.ObterLargura() / 2))
		|| m_alien_sel_esquerdo.ObterY() != m_fase.ObterY1Fonte() + (m_zeus_mouse_y - MAPA_EDITOR_Y1 - (m_alien_sel_esquerdo.ObterAltura() / 2)))
		{
			m_alien_sel_esquerdo.SetarX(m_fase.ObterX1Fonte() + (m_zeus_mouse_x - 97 - (m_alien_sel_esquerdo.ObterLargura() / 2)));
			m_alien_sel_esquerdo.SetarY(m_fase.ObterY1Fonte() + (m_zeus_mouse_y - MAPA_EDITOR_Y1 - (m_alien_sel_esquerdo.ObterAltura() / 2)));
			m_fase.AdicionarAlien(m_alien_sel_esquerdo.ObterTipo(), m_alien_sel_esquerdo.ObterX(), m_alien_sel_esquerdo.ObterY());
			m_flag_alterado = true;
			m_flag_desenhar = true;
		}
	}
	else
	if(mouse_b & 2)
	{
		// Exclui os aliens já incluidos no mapa que colidirem
		// com a novo alien adicionado

		if(m_alien_sel_direito.ObterX() != m_fase.ObterX1Fonte() + (m_zeus_mouse_x - 97 - (m_alien_sel_direito.ObterLargura() / 2))
		|| m_alien_sel_direito.ObterY() != m_fase.ObterY1Fonte() + (m_zeus_mouse_y - MAPA_EDITOR_Y1 - (m_alien_sel_direito.ObterAltura() / 2)))
		{
			m_alien_sel_direito.SetarX(m_fase.ObterX1Fonte() + (m_zeus_mouse_x - 97 - (m_alien_sel_direito.ObterLargura() / 2)));
			m_alien_sel_direito.SetarY(m_fase.ObterY1Fonte() + (m_zeus_mouse_y - MAPA_EDITOR_Y1 - (m_alien_sel_direito.ObterAltura() / 2)));
			m_fase.AdicionarAlien(m_alien_sel_direito.ObterTipo(), m_fase.ObterX1Fonte() + (m_zeus_mouse_x - 97 - (m_alien_sel_direito.ObterLargura() / 2)), m_fase.ObterY1Fonte() + (m_zeus_mouse_y - MAPA_EDITOR_Y1 - (m_alien_sel_direito.ObterAltura() / 2)));
			m_flag_desenhar = true;
			m_flag_alterado = true;
		}
	}
}


//------------------------------------------------------------
// Verifica se deve ser inserido uma nova construcao no mapa
void CEditor::VerificarConstrucao()
{
	if(mouse_b & 1)
	{
		// Exclui as construcoes já incluidos no mapa que colidirem
		// com a novo construcao adicionada

		if(m_construcao_sel_esquerdo.ObterX() != m_fase.ObterX1Fonte() + (m_zeus_mouse_x - 97 - (m_construcao_sel_esquerdo.ObterLargura() / 2))
		|| m_construcao_sel_esquerdo.ObterY() != m_fase.ObterY1Fonte() + (m_zeus_mouse_y - MAPA_EDITOR_Y1 - (m_construcao_sel_esquerdo.ObterAltura() / 2)))
		{
			m_construcao_sel_esquerdo.SetarX(m_fase.ObterX1Fonte() + (m_zeus_mouse_x - 97 - (m_construcao_sel_esquerdo.ObterLargura() / 2)));
			m_construcao_sel_esquerdo.SetarY(m_fase.ObterY1Fonte() + (m_zeus_mouse_y - MAPA_EDITOR_Y1 - (m_construcao_sel_esquerdo.ObterAltura() / 2)));
			m_fase.AdicionarConstrucao(m_construcao_sel_esquerdo.ObterTipo(), m_fase.ObterX1Fonte() + (m_zeus_mouse_x - 97 - (m_construcao_sel_esquerdo.ObterLargura() / 2)), m_fase.ObterY1Fonte() + (m_zeus_mouse_y - MAPA_EDITOR_Y1 - (m_construcao_sel_esquerdo.ObterAltura() / 2)));
			m_flag_alterado = true;
			m_flag_desenhar = true;
		}
	}
	else
	if(mouse_b & 2)
	{
		// Exclui as construcoes já incluidos no mapa que colidirem
		// com a nova construcao adicionado

		if(m_construcao_sel_direito.ObterX() != m_fase.ObterX1Fonte() + (m_zeus_mouse_x - 97 - (m_construcao_sel_direito.ObterLargura() / 2))
		|| m_construcao_sel_direito.ObterY() != m_fase.ObterY1Fonte() + (m_zeus_mouse_y - MAPA_EDITOR_Y1 - (m_construcao_sel_direito.ObterAltura() / 2)))
		{
			m_construcao_sel_direito.SetarX(m_fase.ObterX1Fonte() + (m_zeus_mouse_x - 97 - (m_construcao_sel_direito.ObterLargura() / 2)));
			m_construcao_sel_direito.SetarY(m_fase.ObterY1Fonte() + (m_zeus_mouse_y - MAPA_EDITOR_Y1 - (m_construcao_sel_direito.ObterAltura() / 2)));
			m_fase.AdicionarConstrucao(m_construcao_sel_direito.ObterTipo(), m_fase.ObterX1Fonte() + (m_zeus_mouse_x - 97 - (m_construcao_sel_direito.ObterLargura() / 2)), m_fase.ObterY1Fonte() + (m_zeus_mouse_y - MAPA_EDITOR_Y1 - (m_construcao_sel_direito.ObterAltura() / 2)));
			m_flag_desenhar = true;
			m_flag_alterado = true;
		}
	}
}

//------------------------------------------------------------
// Desenha um quadrado com as diminsões do objeto selecionado
// esquerdo
void CEditor::DesenharQuadrado()
{
	int x = (m_zeus_mouse_x - 97 + m_fase.ObterX1Fonte()) / LADRILHO_LARGURA;
	int y = (m_zeus_mouse_y - 11 + m_fase.ObterY1Fonte()) / LADRILHO_ALTURA;

	// Destaca com um quadrado a area para o objeto
	if(m_flag_apagar)
	{
		m_tela.RectFill(eCamadaEfeitos, m_zeus_mouse_x - (LADRILHO_LARGURA / 2), m_zeus_mouse_y - (LADRILHO_ALTURA / 2), m_zeus_mouse_x + (LADRILHO_LARGURA / 2), m_zeus_mouse_y + (LADRILHO_ALTURA / 2), makecol(128, 128, 128));
		if((m_fase.ObterAliens().ChecarColisaoAliens(m_zeus_mouse_x - 97 + m_fase.ObterX1Fonte() - (LADRILHO_LARGURA  / 2), m_zeus_mouse_y - 11 + m_fase.ObterY1Fonte() - (LADRILHO_ALTURA  / 2), m_zeus_mouse_x - 97 + m_fase.ObterX1Fonte() + (LADRILHO_LARGURA / 2), m_zeus_mouse_y - 11 + m_fase.ObterY1Fonte() + (LADRILHO_ALTURA / 2))
		&& m_exibir_obj == eAlien)
		|| (m_fase.ChecarColisaoConstrucoes(m_zeus_mouse_x - 97 + m_fase.ObterX1Fonte() - (m_construcao_sel_esquerdo.ObterLargura() / 2), m_zeus_mouse_y - 11 + m_fase.ObterY1Fonte() - (m_construcao_sel_esquerdo.ObterAltura() / 2), m_zeus_mouse_x - 97 + m_fase.ObterX1Fonte() + (m_construcao_sel_esquerdo.ObterLargura() / 2), m_zeus_mouse_y - 11 + m_fase.ObterY1Fonte() + (m_construcao_sel_esquerdo.ObterAltura() / 2))
		&& m_exibir_obj == eConstrucao))
		{
			m_tela.Rect(eCamadaEfeitos, m_zeus_mouse_x - (LADRILHO_LARGURA / 2), m_zeus_mouse_y - (LADRILHO_ALTURA / 2), m_zeus_mouse_x + (LADRILHO_LARGURA / 2), m_zeus_mouse_y + (LADRILHO_ALTURA / 2), makecol(255, 0, 0));
		}
		else
		{
			m_tela.Rect(eCamadaEfeitos, m_zeus_mouse_x - (LADRILHO_LARGURA / 2), m_zeus_mouse_y - (LADRILHO_ALTURA / 2), m_zeus_mouse_x + (LADRILHO_LARGURA / 2), m_zeus_mouse_y + (LADRILHO_ALTURA / 2), makecol(255, 255, 255));
		}
	}
	else
	if(m_exibir_obj == eAlien)
	{
		if(m_fase.ObterAliens().ChecarColisaoAliens(m_zeus_mouse_x - 97 + m_fase.ObterX1Fonte() - (m_alien_sel_esquerdo.ObterLargura() / 2), m_zeus_mouse_y - 11 + m_fase.ObterY1Fonte() - (m_alien_sel_esquerdo.ObterAltura() / 2), m_zeus_mouse_x - 97 + m_fase.ObterX1Fonte() + (m_alien_sel_esquerdo.ObterLargura() / 2), m_zeus_mouse_y - 11 + m_fase.ObterY1Fonte() + (m_alien_sel_esquerdo.ObterAltura() / 2)))
		{

			m_tela.Rect(eCamadaEfeitos, m_zeus_mouse_x - (m_alien_sel_esquerdo.ObterLargura() / 2), m_zeus_mouse_y - (m_alien_sel_esquerdo.ObterAltura() / 2), m_zeus_mouse_x + (m_alien_sel_esquerdo.ObterLargura() / 2), m_zeus_mouse_y + (m_alien_sel_esquerdo.ObterAltura() / 2), makecol(255, 0, 0));
		}
		else
		{
			m_tela.Rect(eCamadaEfeitos, m_zeus_mouse_x - (m_alien_sel_esquerdo.ObterLargura() / 2), m_zeus_mouse_y - (m_alien_sel_esquerdo.ObterAltura() / 2), m_zeus_mouse_x + (m_alien_sel_esquerdo.ObterLargura() / 2), m_zeus_mouse_y + (m_alien_sel_esquerdo.ObterAltura() / 2), SOBRE_LADRILHO_COR);
		}
	}
	else
	if(m_exibir_obj == eConstrucao)
	{
		if(m_fase.ChecarColisaoConstrucoes(m_zeus_mouse_x - 97 + m_fase.ObterX1Fonte() - (m_construcao_sel_esquerdo.ObterLargura() / 2), m_zeus_mouse_y - 11 + m_fase.ObterY1Fonte() - (m_construcao_sel_esquerdo.ObterAltura() / 2), m_zeus_mouse_x - 97 + m_fase.ObterX1Fonte() + (m_construcao_sel_esquerdo.ObterLargura() / 2), m_zeus_mouse_y - 11 + m_fase.ObterY1Fonte() + (m_construcao_sel_esquerdo.ObterAltura() / 2)))
		{

			m_tela.Rect(eCamadaEfeitos, m_zeus_mouse_x - (m_construcao_sel_esquerdo.ObterLargura() / 2), m_zeus_mouse_y - (m_construcao_sel_esquerdo.ObterAltura() / 2), m_zeus_mouse_x + (m_construcao_sel_esquerdo.ObterLargura() / 2), m_zeus_mouse_y + (m_construcao_sel_esquerdo.ObterAltura() / 2), makecol(255, 0, 0));
		}
		else
		{
			m_tela.Rect(eCamadaEfeitos, m_zeus_mouse_x - (m_construcao_sel_esquerdo.ObterLargura() / 2), m_zeus_mouse_y - (m_construcao_sel_esquerdo.ObterAltura() / 2), m_zeus_mouse_x + (m_construcao_sel_esquerdo.ObterLargura() / 2), m_zeus_mouse_y + (m_construcao_sel_esquerdo.ObterAltura() / 2), SOBRE_LADRILHO_COR);
		}
	}
	else
	if(m_exibir_obj == eFundo)
	{
		m_tela.Rect(eCamadaEfeitos, (m_fase.ObterLadrilho(x, y).ObterX() - (LADRILHO_LARGURA * (m_tam_pincel_ladrilho / 2)) + MAPA_EDITOR_X1 - m_fase.ObterX1Fonte()), (m_fase.ObterLadrilho(x, y).ObterY() - (LADRILHO_ALTURA * (m_tam_pincel_ladrilho / 2)) + MAPA_EDITOR_Y1 -  m_fase.ObterY1Fonte()), (m_fase.ObterLadrilho(x, y).ObterX() + (LADRILHO_LARGURA * ((m_tam_pincel_ladrilho / 2) + 1)) + MAPA_EDITOR_X1 - m_fase.ObterX1Fonte()) - 1, (m_fase.ObterLadrilho(x, y).ObterY() + (LADRILHO_ALTURA * ((m_tam_pincel_ladrilho / 2) + 1)) + MAPA_EDITOR_Y1 - m_fase.ObterY1Fonte()) - 1, SOBRE_LADRILHO_COR);
	}
}


//------------------------------------------------------------
// Verifica o rolamento da m_fase através do pressionamento das
// teclas do teclado
bool CEditor::VerificarRolaTecla()
{
	if(key[KEY_UP])
	{
		if(m_fase.Rolar(eCima, LADRILHO_ALTURA))
		{
			m_flag_desenhar = true;
		}
	}
	else
	if(key[KEY_DOWN])
	{
		if(m_fase.Rolar(eBaixo, LADRILHO_ALTURA))
		{
			m_flag_desenhar = true;
		}
	}

	if(key[KEY_RIGHT])
	{
		if(m_fase.Rolar(eDireita, LADRILHO_LARGURA))
		{
			m_flag_desenhar = true;
		}
	}
	else
	if(key[KEY_LEFT])
	{
		if(m_fase.Rolar(eEsquerda, LADRILHO_LARGURA))
		{
			m_flag_desenhar = true;
		}
	}
	else
	if(key[KEY_PGUP])
	{
		if(m_fase.Rolar(eCima, MENU_OBJ_ALTURA))
		{
			m_flag_desenhar = true;
		}
	}
	else
	if(key[KEY_PGDN])
	{
		if(m_fase.Rolar(eBaixo, MENU_OBJ_ALTURA))
		{
			m_flag_desenhar = true;
		}
	}
	else
	if(key[KEY_HOME])
	{
		if(m_fase.Rolar(eCima,MAPA_ALTURA))
		{
			m_flag_desenhar = true;
		}
	}
	else
	if(key[KEY_END])
	{
		if(m_fase.Rolar(eBaixo, MAPA_ALTURA))
		{
			m_flag_desenhar = true;
		}
	}

	if(m_flag_desenhar)
	{
		return true;
	}
	return false;
}


//------------------------------------------------------------
// Verifica o rolamento da m_fase através do pressionamento das
// teclas do mouse
bool CEditor::VerificarRolaMouse()
{
	// Se for pressionado o botão esquerdo ou botão direito do mouse
	if((mouse_b & 1) || (mouse_b & 2))
	{
		// Se mouse esta passando nos extremos do mapa e sendo pressionado
		if(m_zeus_mouse_x < (MENU_OBJ_LARGURA + (LADRILHO_LARGURA/2))
           && m_zeus_mouse_x > MENU_OBJ_LARGURA
           && m_zeus_mouse_y > MENU_ALTURA)
		{
			if(m_fase.Rolar(eEsquerda, LADRILHO_LARGURA))
			{
				m_flag_desenhar = true;
			}
		}
		else
		if(m_zeus_mouse_x > ((MAPA_EDITOR_X2) - (LADRILHO_LARGURA/2))
           && m_zeus_mouse_x < MAPA_EDITOR_X2
           && m_zeus_mouse_y > MENU_ALTURA)
		{
			if(m_fase.Rolar(eDireita, LADRILHO_LARGURA))
			{
				m_flag_desenhar = true;
			}
		}
		else
		if(m_zeus_mouse_x > MENU_OBJ_LARGURA
           && m_zeus_mouse_y < (MENU_ALTURA + (LADRILHO_ALTURA/2))
           && m_zeus_mouse_y > MENU_ALTURA)
		{
			if(m_fase.Rolar(eCima, LADRILHO_ALTURA))
			{
				m_flag_desenhar = true;
			}
		}
		else
		if(m_zeus_mouse_x > MENU_OBJ_LARGURA
           && m_zeus_mouse_y > (MENU_AUX_Y - (LADRILHO_ALTURA/2))
           && m_zeus_mouse_y < MENU_AUX_Y)
		{
			if(m_fase.Rolar(eBaixo, LADRILHO_ALTURA))
			{
				m_flag_desenhar = true;
			}
		}
	}
	if(m_flag_desenhar)
	{
		return true;
	}
	return false;
}

//------------------------------------------------------------
// Menu Arquivo
bool CEditor::VerificarMenuArquivo()
{
	int opcao;
	MENU menu_arquivo[] =
	{
		{ "&Novo",				NULL,   NULL,	0,	NULL },
		{ "&Abrir",				NULL,   NULL,	0,	NULL },
		{ "&Salvar",			NULL,   NULL,	0,	NULL },
		{ "Salvar &Como",		NULL,   NULL,	0,	NULL },
		{ "&Fechar",			NULL,   NULL,	0,	NULL },
		{ "",					NULL,   NULL,	0,	NULL },
		{ "&Sair",				NULL,   NULL,	0,	NULL },
		{ NULL,					NULL,	NULL,   0,	NULL }
	};

	if(m_zeus_mouse_x > MENU_ARQUIVO_X1
	&& m_zeus_mouse_x < MENU_ARQUIVO_X2)
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
			if(Sair())
				Finalizar();
		}
		return true;
	}
	return false;
}


//------------------------------------------------------------
// Menu Objetos
bool CEditor::VerificarMenuObjetos()
{
	int opcao;
    MENU menu_objetos[] =
	{
		{ "&Bonus",			NULL,   NULL,	0,	NULL },
		{ "&Construcoes",   NULL,   NULL,	0,	NULL },
		{ "&Aliens",		NULL,   NULL,	0,	NULL },
		{ "&Seres Vivos",   NULL,   NULL,	0,	NULL },
		{ "&Fundo",			NULL,   NULL,	0,	NULL },
		{ "&Veiculos",		NULL,   NULL,	0,	NULL },
		{ NULL,				NULL,	NULL,   0,	NULL }
	};

	if(m_zeus_mouse_x > MENU_OBJETOS_X1  &&  m_zeus_mouse_x < MENU_OBJETOS_X2)
	{
		opcao = do_menu(menu_objetos, MENU_OBJETOS_X1, MENU_ALTURA);
		switch(opcao)
		{
			case 1: AbrirConstrucoes();
					break;

			case 2: AbrirAliens();
					break;

			case 4:	AbrirFundo();
					break;
		}
		return true;
	}
	return false;
}


//------------------------------------------------------------
// Menu Exibir
bool CEditor::VerificarMenuExibir()
{
	int opcao = -1;

	if(m_zeus_mouse_x > MENU_EXIBIR_X1  && m_zeus_mouse_x < MENU_EXIBIR_X2)
	{
		opcao = do_menu(m_menu_exibir, MENU_EXIBIR_X1, MENU_ALTURA);
		switch(opcao)
		{
			case 1:	if (!m_dat_construcoes)
					{
						AbrirConstrucoes();
					}
					break;

			case 2:	if (!m_dat_aliens)
					{
						AbrirAliens();
					}
					break;
			case 4: if(!m_bmp_fundo)
					{
						AbrirFundo();
					}
					break;
		}

		if ((  opcao == 1
			|| opcao == 2
			|| opcao == 4)
			&& m_exibir_obj > -1
			&& opcao > -1
			&& m_exibir_obj != opcao)
		{
			// Redesenha o menu de objetos
			m_exibir_obj  = opcao;
			MontarMenuObj(1);
		}
		return true;
	}
	return false;
}


//------------------------------------------------------------
// Menu Ferramentas
bool CEditor::VerificarMenuFerramentas()
{
	int opcao;

	MENU menu_ferramentas[] =
	{
		{ "&Preencher ladrilhos nulos por selecionado esquerdo",	NULL,   NULL,	0,	NULL },
		{ "&Trocar ladrilhos do selecionado esquerdo pelo do direito",	NULL,   NULL,	0,	NULL },
		{ NULL,				NULL,	NULL,   0,	NULL }
	};

	if(m_zeus_mouse_x > MENU_FERRAMENTAS_X1 && m_zeus_mouse_x < MENU_FERRAMENTAS_X2)
	{
		opcao = do_menu(menu_ferramentas, MENU_FERRAMENTAS_X1, MENU_ALTURA);
		switch(opcao)
		{
			case 0:	PreencherNulos();
					break;
			case 1:	TrocarLadrilhos();
					break;
		}
		return true;
	}
	return false;
}


//------------------------------------------------------------
// Menu Obj
void CEditor::VerificarMenuObj()
{
	int x = m_zeus_mouse_x / LADRILHO_LARGURA;
	int y = m_zeus_mouse_y / LADRILHO_ALTURA;

	// Se o botão esquerdo do mouse foi pressionado
	if(mouse_b & 1)
	{
		m_ladrilho_sel_esquerdo.Finalizar();
		switch(m_exibir_obj)
		{
			case eConstrucao:
				// Este calculo { ((x * 15) + y) } localiza o bitmap do construcao no m_arquivo dat
				m_ladrilho_sel_esquerdo.Iniciar(m_menu_obj_ladrilhos[x][y].ObterTLadrilho(), LADRILHO_LARGURA, LADRILHO_ALTURA, (BITMAP *) m_dat_construcoes[(x * 15) + y].dat);
				// Este calculo { ((x * 15) + y) } informa o m_tipo de construcao
				m_construcao_sel_esquerdo.Iniciar(((x * 15) + y), 0, 0);
				break;

			case eAlien:
				// Este calculo { ((x * 15) + y) * 2 } localiza o bitmap do alien no m_arquivo dat
				m_ladrilho_sel_esquerdo.Iniciar(m_menu_obj_ladrilhos[x][y].ObterTLadrilho(), LADRILHO_LARGURA, LADRILHO_ALTURA, (BITMAP *) m_dat_aliens[((x * 15) + y) * 2].dat);

				// Este calculo { ((x * 15) + y) } informa o m_tipo de alien
				m_alien_sel_esquerdo.Iniciar(((x * 15) + y), 0, 0);
				break;

			case eFundo:
				m_ladrilho_sel_esquerdo.Iniciar(m_menu_obj_ladrilhos[x][y].ObterTLadrilho(), LADRILHO_LARGURA, LADRILHO_ALTURA, m_bmp_fundo);
				break;
		}
		m_ladrilho_sel_esquerdo.SetarX(LADRILHO_SEL_ESQUERDO_X);
		m_ladrilho_sel_esquerdo.SetarY(LADRILHO_SEL_ESQUERDO_Y);
		m_tela.RectFill(eCamadaFundo, LADRILHO_SEL_ESQUERDO_X, LADRILHO_SEL_ESQUERDO_Y, LADRILHO_SEL_ESQUERDO_X + LADRILHO_LARGURA, LADRILHO_SEL_ESQUERDO_Y + LADRILHO_LARGURA, makecol(0, 0, 0));
		m_tela.Rect(eCamadaFundo, LADRILHO_SEL_ESQUERDO_X, LADRILHO_SEL_ESQUERDO_Y, LADRILHO_SEL_ESQUERDO_X + LADRILHO_LARGURA, LADRILHO_SEL_ESQUERDO_Y + LADRILHO_LARGURA, makecol(100, 100, 100));
		m_ladrilho_sel_esquerdo.Desenhar(m_tela, 0, 0);
		m_flag_desenhar = true;
	}
	// Se o botão esquerdo do mouse foi pressionado
	else
	if(mouse_b & 2)
	{
		m_ladrilho_sel_direito.Finalizar();
		switch(m_exibir_obj)
		{
			case eConstrucao:
				// Este calculo { ((x * 15) + y) * 2 } localiza o bitmap do construcao no m_arquivo dat
				m_ladrilho_sel_direito.Iniciar(m_menu_obj_ladrilhos[x][y].ObterTLadrilho(), LADRILHO_LARGURA, LADRILHO_ALTURA, (BITMAP *) m_dat_construcoes[((x * 15) + y) * 2].dat);
				// Este calculo { ((x * 15) + y) } informa o m_tipo de construcao
				m_construcao_sel_direito.Iniciar(((x * 15) + y), 0, 0);
				break;

			case eAlien:
				// Este calculo { ((x * 15) + y) * 2 } localiza o bitmap do alien no m_arquivo dat
				m_ladrilho_sel_direito.Iniciar(m_menu_obj_ladrilhos[x][y].ObterTLadrilho(), LADRILHO_LARGURA, LADRILHO_ALTURA, (BITMAP *) m_dat_aliens[((x * 15) + y) * 2].dat);
				// Este calculo { ((x * 15) + y) } informa o m_tipo de alien
				m_alien_sel_direito.Iniciar(((x * 15) + y), 0, 0);
				break;

			case eFundo:
				m_ladrilho_sel_direito.Iniciar(m_menu_obj_ladrilhos[x][y].ObterTLadrilho(), LADRILHO_LARGURA, LADRILHO_ALTURA, m_bmp_fundo);
				break;
		}
		m_ladrilho_sel_direito.SetarX(LADRILHO_SEL_DIREITO_X);
		m_ladrilho_sel_direito.SetarY(LADRILHO_SEL_DIREITO_Y);
		m_tela.RectFill(eCamadaEfeitos, LADRILHO_SEL_DIREITO_X, LADRILHO_SEL_DIREITO_Y, LADRILHO_SEL_DIREITO_X + LADRILHO_LARGURA, LADRILHO_SEL_DIREITO_Y + LADRILHO_LARGURA, makecol(0, 0, 0));
		m_tela.Rect(eCamadaEfeitos, LADRILHO_SEL_DIREITO_X, LADRILHO_SEL_DIREITO_Y, LADRILHO_SEL_DIREITO_X + LADRILHO_LARGURA, LADRILHO_SEL_DIREITO_Y + LADRILHO_LARGURA, makecol(100, 100, 100));
		m_ladrilho_sel_direito.Desenhar(m_tela, 0, 0);
		m_flag_desenhar = true;
	}
}


//------------------------------------------------------------
// Menu Aux
void CEditor::VerificarMenuAux()
{
	if(m_exibir_obj == eFundo)
	{

		if(m_botao_virar_h.Atualizar(m_zeus_mouse_x, m_zeus_mouse_y))    VirarHLadrilho();
		if(m_botao_virar_v.Atualizar(m_zeus_mouse_x, m_zeus_mouse_y))    VirarVLadrilho();
		if(m_botao_rotacionar.Atualizar(m_zeus_mouse_x, m_zeus_mouse_y)) RotacionarLadrilho();
		if(m_botao_inc_pincel.Atualizar(m_zeus_mouse_x, m_zeus_mouse_y)) IncrementarPincel();
		if(m_botao_dec_pincel.Atualizar(m_zeus_mouse_x, m_zeus_mouse_y)) DecrementarPincel();
	}
	if(m_botao_apagar.Atualizar(m_zeus_mouse_x, m_zeus_mouse_y)) HabilitarApagarObjetos();

	if(m_ladrilho_sel_esquerdo.ChecarColisao(m_zeus_mouse_x, m_zeus_mouse_y)
	|| m_ladrilho_sel_direito.ChecarColisao(m_zeus_mouse_x, m_zeus_mouse_y))
	{
		m_flag_apagar = false;
	}
}


//------------------------------------------------------------
// Apagar
void CEditor::VerificarApagar()
{
	switch(m_exibir_obj)
	{
		case eAlien:
			m_fase.ExcluirAliens(m_zeus_mouse_x - 97 + m_fase.ObterX1Fonte() - (LADRILHO_LARGURA  / 2), m_zeus_mouse_y - 11 + m_fase.ObterY1Fonte() - (LADRILHO_ALTURA  / 2), m_zeus_mouse_x - 97 + m_fase.ObterX1Fonte() + (LADRILHO_LARGURA / 2), m_zeus_mouse_y - 11 + m_fase.ObterY1Fonte() + (LADRILHO_ALTURA / 2));
			m_flag_alterado = true;
			m_flag_desenhar = true;
			break;
		case eConstrucao:
			m_fase.ExcluirConstrucoes(m_zeus_mouse_x - 97 + m_fase.ObterX1Fonte() - (LADRILHO_LARGURA  / 2), m_zeus_mouse_y - 11 + m_fase.ObterY1Fonte() - (LADRILHO_ALTURA  / 2), m_zeus_mouse_x - 97 + m_fase.ObterX1Fonte() + (LADRILHO_LARGURA / 2), m_zeus_mouse_y - 11 + m_fase.ObterY1Fonte() + (LADRILHO_ALTURA / 2));
			m_flag_alterado = true;
			m_flag_desenhar = true;
			break;
	}
}


//------------------------------------------------------------
bool CEditor::RotacionarLadrilho()
{
	if(mouse_b & 1)
	{
		m_ladrilho_sel_esquerdo.Rotacionar(1);
	}
	else
	if(mouse_b & 2)
	{
		m_ladrilho_sel_direito.Rotacionar(1);
	}
	m_flag_desenhar = true;
	rest(100);
	return true;
}


//------------------------------------------------------------
bool CEditor::VirarHLadrilho()
{
	if(mouse_b & 1)
	{
		m_ladrilho_sel_esquerdo.VirarHorizontal();
	}
	else if(mouse_b & 2)
	{
		m_ladrilho_sel_direito.VirarHorizontal();
	}
	m_flag_desenhar = true;
	rest(100);
	return true;
}


//------------------------------------------------------------
bool CEditor::VirarVLadrilho()
{
	if(mouse_b & 1)
	{
		m_ladrilho_sel_esquerdo.VirarVertical();
	}
	else if(mouse_b & 2)
	{
		m_ladrilho_sel_direito.VirarVertical();
	}
	m_flag_desenhar = true;
	rest(100);
	return true;
}


//------------------------------------------------------------
bool CEditor::HabilitarApagarObjetos()
{
	m_flag_apagar = true;
	rest(100);
	return true;
}


//------------------------------------------------------------
bool CEditor::IncrementarPincel()
{
	if(m_tam_pincel_ladrilho < 9) m_tam_pincel_ladrilho += 2;
	m_flag_desenhar = true;
	rest(100);
	return true;
}


//------------------------------------------------------------
bool CEditor::DecrementarPincel()
{
	if(m_tam_pincel_ladrilho > 1)	m_tam_pincel_ladrilho -= 2;
	m_flag_desenhar = true;
	rest(100);
	return true;
}


//------------------------------------------------------------
void CEditor::ChecarArquivo(const char *_arquivo)
{
	char str[80];
	if (!exists(_arquivo))
	{
		sprintf(str, "Arquivo [%s] nao encontrado.", _arquivo);
		allegro_message(str);
		Erro(str, 0);
	}
}


//------------------------------------------------------------
void CEditor::CarregarConfiguracao()
{
	int modo_video;
	int resolucao_x, resolucao_y;

	// definicao do modo de video
	switch(m_cfg.ObterInt("video", "modo"))
	{
		case  1: modo_video = GFX_AUTODETECT_FULLSCREEN; break;
		case  2: modo_video = GFX_AUTODETECT_WINDOWED; break;
		case  3: modo_video = GFX_DIRECTX; break;
		case  4: modo_video = GFX_DIRECTX_OVL; break;
		case  5: modo_video = GFX_DIRECTX_WIN; break;
		case  6: modo_video = GFX_DIRECTX_SAFE; break;
		case  7: modo_video = GFX_DIRECTX_SOFT; break;
		case  8: modo_video = GFX_DIRECTX_ACCEL; break;
		case  9: modo_video = GFX_GDI; break;
		case 10: modo_video = GFX_SAFE; break;
		default: modo_video = GFX_AUTODETECT;
	}

	// definicao da resolucao
	switch (m_cfg.ObterInt("video", "resolucao", 1))
	{
		case 0:	 resolucao_x=320; resolucao_y=240; break;
		case 2:	 resolucao_x=800; resolucao_y=600; break;
		default: resolucao_x=640; resolucao_y=480;
	}

	m_tela.Iniciar(modo_video, resolucao_x, resolucao_y, 16);
	m_tela.SetarVsync(m_cfg.ObterBool("video", "vsyc"));
	m_tela.SetarSuavizar(m_cfg.ObterBool("video", "suavizar"));
	m_tela.SetarTransBlender(0, 0, 0, 96);
}

