 /*------------------------------------------------------------*
 *  cjogo.h - Implementação da Classe do Jogo
*------------------------------------------------------------*
*  Nome: Edison Henrique Andreassy
*  Data: sabado, 23 de fevereito de 2001
*
*  Alterações:
*
*  Henrique em 29/06/2002
*   - Adicionado classe para filmes
*  
*------------------------------------------------------------*/

#include "cjogo.h"
#include "atena.h"
#include "cmenu.h"
#include "cfilme.h"
#include "cexplosao.h"

//----- EM TESTE
volatile int contador;
void Temporizador()
{
	contador++;

} END_OF_FUNCTION(Temporizador);
/**/

//------------------------------------------------------------
void CJogo::ChecarArquivo(const char * arquivo)
{
	char str[80];
	if (!exists(arquivo))
	{
		sprintf(str, "Arquivo [%s] nao encontrado.", arquivo);
		allegro_message(str);
		Erro(str, 0);
	}
}

//------------------------------------------------------------
void CJogo::CarregarConfiguracao()
{
	int modo_video;
	int resolucao_x, resolucao_y;

	m_cfg_velocidade	= m_cfg.ObterInt("jogo", "velocidade");
	m_cfg_musica		= m_cfg.ObterBool("som", "musica");
	m_cfg_efeitos		= m_cfg.ObterBool("som", "efeitos");

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

//------------------------------------------------------------
void CJogo::Iniciar()
{
	//Verifica se existe os arquivos necessarios
	ChecarArquivo("atena.ini");
	ChecarArquivo("atena.dat");
	ChecarArquivo("nave.dat");
	ChecarArquivo("aliens.dat");
	ChecarArquivo("tiros.dat");
	ChecarArquivo("armas.dat");
	ChecarArquivo("construcoes.dat");

	srand(1);
	text_mode(-1);
	clear_keybuf();
	m_cfg.SetarArquivo("atena.ini");
	m_data = load_datafile("atena.dat");

	CarregarConfiguracao();

	m_final_jogo = false;
	m_final_partida = false;

	// ----- EM TESTE
	LOCK_VARIABLE(contador);
	LOCK_FUNCTION(Temporizador);
	install_int_ex(Temporizador, SECS_TO_TIMER(1));
	/**/

}

//------------------------------------------------------------
void CJogo::IniciarPartida()
{
	int nome_comprimento;
	char arquivo_selecionado[256], m_caminho[256];

	// Código provisório para selecionar as fases
	show_mouse(screen);
	position_mouse(320, 240);
	get_executable_name(arquivo_selecionado, sizeof(arquivo_selecionado));
	nome_comprimento = strlen(arquivo_selecionado);
	strncpy(m_caminho, arquivo_selecionado, nome_comprimento - 8);
	strcpy(m_caminho, "fases//");
	strcpy(arquivo_selecionado, m_caminho);

	if((file_select_ex("Selecione o m_arquivo do mapa:", arquivo_selecionado, "map", sizeof(arquivo_selecionado), 400, 300)) != NULL)
	{
		//unscare_mouse();
		strcat(m_caminho, get_filename(arquivo_selecionado));
		show_mouse(NULL);
		textout_centre(screen, font, "aguarde, carregando mapa...", SCREEN_W/2, SCREEN_H/2, makecol(255,255,0));
		m_fase.Iniciar(m_caminho, 96, 0, 544, 480);
	}
	else
	{
		return;
	}

	if (m_cfg_musica)
	{
		play_midi((MIDI *)m_data[MID_FUNDO1].dat, 1);
	}
}

//------------------------------------------------------------
void CJogo::ExecutarPartida()
{
    char bff[101];
	int linha = 270;
	DATAFILE *m_data = load_datafile("atena.dat");
	FONT *fonte = (FONT *)m_data[TAHOMA7].dat;

	//m_tela.SetarEscreverSombra(true);
	while (m_fase.Atualizar(1))
	{
		m_tela.Limpar();
		m_fase.Desenhar(m_tela);
		m_fase.Sonorizar();
						
		m_tela.MaskedBlit((BITMAP *)m_data[PAINEL].dat, eCamadaEfeitos);

		m_tela.Escrever("[Informacoes]",    10, linha - 220, makecol16(0, 255, 0), fonte);
		m_tela.Escrever("Isto e um teste",  10, linha - 200, makecol16(0, 255, 0), fonte);
		m_tela.Escrever("para saber se",    10, linha - 190, makecol16(0, 255, 0), fonte);
		m_tela.Escrever("o texto fica bom", 10, linha - 180, makecol16(0, 255, 0), fonte);
		m_tela.Escrever("nesta posicao",    10, linha - 170, makecol16(0, 255, 0), fonte);

		
		sprintf(bff, "Pontos: %d", m_fase.ObterNave().ObterPontos());
		m_tela.Escrever(bff,    10, linha - 150, makecol16(0, 255, 0), fonte);
		// Display 
		// Nave
		m_tela.Escrever("[Nave]", 10, linha + 10, makecol(0, 255, 0), fonte);
		
		//sprintf(bff, "Energia:%3i", m_fase.ObterNave().ObterEnergia());
		//m_tela.Escrever(bff, 20, linha + 20, makecol(0, 255, 0), fonte);
		barra_progresso_atena2(m_tela, 10, linha + 23, 76, m_fase.ObterNave().ObterEnergia());
		
		//sprintf(bff, "Casco  :%3i", m_fase.ObterNave().ObterCasco());
		//m_tela.Escrever(bff, 20, linha + 30, makecol(0, 255, 0), fonte);
		barra_progresso_atena2(m_tela, 10, linha + 33, 76, m_fase.ObterNave().ObterCasco());

		// Arma esquerda
		m_tela.Escrever("[Arma Esquerda]", 10, linha + 50, makecol(0, 255, 0), fonte);
		
		sprintf(bff, "Energia:%3i", m_fase.ObterNave().ObterArmas().Obter(1).ObterEnergia());
		m_tela.Escrever(bff, 20, linha + 60, makecol(0, 255, 0), fonte);

		// Arma centro
		m_tela.Escrever("[Arma Centro]", 10, linha + 80, makecol(0, 255, 0), fonte);
		sprintf(bff, "Energia:%3i", m_fase.ObterNave().ObterArmas().Obter(2).ObterEnergia());
		m_tela.Escrever(bff, 20, linha + 90, makecol(0, 255, 0), fonte);

		m_tela.Escrever("[Arma Direita]", 10, linha + 110, makecol(0, 255, 0), fonte);
		sprintf(bff, "Energia:%3i", m_fase.ObterNave().ObterArmas().Obter(3).ObterEnergia());
		m_tela.Escrever(bff, 20, linha + 120, makecol(0, 255, 0), fonte);
		/**/

		// Calculo de FPS
		sprintf(bff, "FPS:%i", CalcularFPS());
		m_tela.Escrever(bff, 580, 472, makecol(0, 255, 0));

		m_tela.AtualizarNaTela();

		
		if (m_cfg_velocidade > 0) rest(m_cfg_velocidade);
	}
	unload_datafile(m_data);
}

//------------------------------------------------------------
void CJogo::DesligarPartida()
{
	stop_midi();
	m_fase.Finalizar();
}


//------------------------------------------------------------
void CJogo::Executar()
{
	CFilme filme;

	/* 
	// TESTE
	CExplosao explosao;

	DATAFILE *m_data = load_datafile("atena.dat");

	CExplosao::Iniciar(640, 480);
	explosao.IniciarExplosao(320, 240, 200, 1000);
	for(register int i = 0; i < 150; i++)
	{
		explosao.IniciarExplosao(320, 240, 200 + i, 1000);
		//explosao.IniciarExplosaoRadial(320, 240, 25 + i);
		//explosao.IniciarExplosaoRadial(320, 240, 50 + i);
		explosao.IniciarExplosaoRadial(320, 240, 75 + i);
		//if (!(i % 10))
		//	explosao.InserirSprite((BITMAP *)m_data[LOGO_GA].dat, 0, 240); 
		
		
		explosao.Desenhar(m_tela);
		m_tela.AtualizarNaTela();
	}

    /**/
	filme.Executar("filmes//abertura.txt");
	
	
	while (!m_final_jogo)
	{
		ExibirMenuPrincipal();

		while (!m_final_partida & !m_final_jogo)
		{
			IniciarPartida();
			ExecutarPartida();
			DesligarPartida();

			m_final_partida = true;
		}
	}
}

void CJogo::ExibirMenuPrincipal()
{
	/* <EM TESTE> */

	bool sair = false;
	DATAFILE *m_data = load_datafile("atena.dat");
	CMenuH m;

	m_tela.Blit((BITMAP *)m_data[ABERTURA].dat, eCamadaScreen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

	//Propriedades do Menu
	m.SetarFonte((FONT *)m_data[BANKGOTIC].dat);
	m.SetarCorTexto(makecol(0,0,255));
	m.SetarCorSelecao(makecol(255,255,0));
	m.SetarAlinhamento(eAlinharCentro);
	m.SetarX(SCREEN_W/2);
	m.SetarY(100);

	m.Adicionar("Iniciar");
	m.Adicionar("Demo");
	m.Adicionar("Configurar");
	m.Adicionar("Creditos");
	m.Adicionar("Sair");

	

	while (!sair)
	{
		switch (m.Executar())
		{
		case 0:
			m_final_jogo	  = false;
			m_final_partida = false;
			sair		  = true;
			break;
		case 1:
			//m_fase.Iniciar("fases//m_fase.map", 0, 0, 640, 480);
			//ExecutarPartida();
			//DesligarPartida();
			//m_tela.Blit((BITMAP *)m_data[ABERTURA].dat, eCamadaScreen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
			break;
		case 2:
			ExibirMenuConfiguracao();
			break;
		
		case 3:
			{
				BITMAP *bmp = create_bitmap(SCREEN_W, SCREEN_H);
				blit(screen, bmp, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
				CFilme filme;
				filme.Executar("filmes//creditos.txt");
				blit(bmp, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
				destroy_bitmap(bmp);
			}
			break;

		case 4:
			m_final_jogo	  = true;
			m_final_partida = true;
			sair          = true;
			break;
		}
	}

	unload_datafile(m_data);

	/**/
}

void CJogo::ExibirMenuConfiguracao()
{
	char	str[80];
	int		valor;
	bool sair = false;

	CMenuH m;
	CConfig m_cfg("atena.ini");

	m.SetarFonte(font);
	m.SetarCorTexto(makecol(0,0,255));
	m.SetarCorSelecao(makecol(255,255,0));
	m.SetarAlinhamento(eAlinharEsquerda);
	m.SetarX(50);
	m.SetarY(80);
	m.SetarNumeroItens(9);

	while (!sair)
	{
		sprintf(str, "Abertura     %d", m_cfg.ObterInt("jogo", "abertura"));
		m.SetarTexto(0, str);

		m_cfg.SetarSecao("video");
		sprintf(str, "Modo         %d", m_cfg.ObterInt("modo"));
		m.SetarTexto(1, str);
		sprintf(str, "Resolucao    %d", m_cfg.ObterInt("resolucao"));
		m.SetarTexto(2, str);
		sprintf(str, "Sincronizar  %d", m_cfg.ObterInt("vsync"));
		m.SetarTexto(3, str);
		sprintf(str, "Suavizar     %d", m_cfg.ObterInt("suavizar"));
		m.SetarTexto(4, str);

		m_cfg.SetarSecao("som");
		sprintf(str, "Musica       %d", m_cfg.ObterInt("musica"));
		m.SetarTexto(5, str);
		sprintf(str, "Efeitos      %d", m_cfg.ObterInt("efeitos"));
		m.SetarTexto(6, str);

		sprintf(str, "Aplicar");
		m.SetarTexto(7, str);

		sprintf(str, "Sair");
		m.SetarTexto(8, str);


		switch (m.Executar())
		{
		case 0:
			valor = !m_cfg.ObterInt("jogo", "abertura");
			m_cfg.SetarInt("abertura", valor);
			break;

		case 1:
			valor = (m_cfg.ObterInt("video", "modo") + 1) % 11;
			m_cfg.SetarInt("modo", valor);
			break;

		case 2:
			valor = (m_cfg.ObterInt("video", "resolucao") + 1) % 3;
			m_cfg.SetarInt("resolucao", valor);
			break;

		case 3:
			valor = !m_cfg.ObterInt("video", "vsync");
			m_cfg.SetarInt("vsync", valor);
			break;

		case 4:
			valor = !m_cfg.ObterInt("video", "suavizar");
			m_cfg.SetarInt("suavizar", valor);
			break;

		case 5:
			valor = !m_cfg.ObterInt("som", "musica");
			m_cfg.SetarInt("musica", valor);
			break;

		case 6:
			valor = !m_cfg.ObterInt("som", "efeitos");
			m_cfg.SetarInt("efeitos", valor);
			break;

		case 7:
			CarregarConfiguracao();
			break;

		case 8:
			sair = true;
			break;
		}
	}
}

//------------------------------------------------------------
void CJogo::Desligar()
{
	m_tela.Desligar();
	unload_datafile(m_data);
}

//------------------------------------------------------------
int CJogo::CalcularFPS()
{
	static int tempo_anterior = 0;
	static int FPS_anterior = 0;
	static int FPS = 0;
	
	FPS++;

	if((contador - tempo_anterior) > 0)
	{
		tempo_anterior = contador;
		FPS_anterior = FPS;
		FPS = 0;
	}
	return FPS_anterior;
}
	

