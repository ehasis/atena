{-------------------------------------------------------------------------------
  Projeto:   Zeus II Turbo
  Autor:     Edison Henrique Andreassy
  Data:      20/05/2003
  Descrição: Novo editor de fases do Jogo Atena.

  Detalhes do arquivo:
   - Métodos Próprios
   - Eventos do Form
   - Eventos do Menu principal
   - Eventos dos controles
-------------------------------------------------------------------------------}

unit UZeus;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Menus, StdCtrls, ExtCtrls, ComCtrls, ExtDlgs, xmldom,
  XMLIntf, msxmldom, XMLDoc, ToolWin, Buttons, Contnrs, UMapa, UObjeto,
  ImgList, ActnList;

type
  TfrmZeus = class(TForm)
    MenuPrincipal: TMainMenu;
    mnuArquivo: TMenuItem;
    itmNovo: TMenuItem;
    itmAbrir: TMenuItem;
    itmSalvar: TMenuItem;
    N1: TMenuItem;
    itmSair: TMenuItem;
    mnuLadrilho: TMenuItem;
    itmFechar: TMenuItem;
    dlgAbrirMapa: TOpenDialog;
    dlgSalvarMapa: TSaveDialog;
    Panel2: TPanel;
    Panel4: TPanel;
    imgPrevisao: TImage;
    panCentro: TPanel;
    Panel5: TPanel;
    imgTela: TImage;
    ScrollBarY: TScrollBar;
    BarraProgresso: TProgressBar;
    BarraStatus: TStatusBar;
    ToolBar1: TToolBar;
    popObjetos: TPopupMenu;
    itmObjetosExcluir: TMenuItem;
    N2: TMenuItem;
    itmObjetosPropriedades: TMenuItem;
    imlBarra: TImageList;
    tvObjetos: TTreeView;
    itmExportar: TMenuItem;
    N3: TMenuItem;
    itmFlipVertical: TMenuItem;
    itmFlipHorizontal: TMenuItem;
    mnuExibir: TMenuItem;
    itmPaletadeLadrilhos: TMenuItem;
    alZeus: TActionList;
    ExibirPaletaLadrilhos: TAction;
    sbtLadrilhos: TToolButton;
    sbtObjetos: TToolButton;
    mnuObjeto: TMenuItem;
    itmPropriedades: TMenuItem;
    itmExibirObjetos: TMenuItem;
    imlObjetos: TImageList;
    mnuAjuda: TMenuItem;
    itmConteudo: TMenuItem;
    N4: TMenuItem;
    itmSobre: TMenuItem;
    N5: TMenuItem;
    itmAtualizarTela: TMenuItem;
    sbtCenario: TToolButton;
    itmExibirCenario: TMenuItem;
    procedure itmNovoClick(Sender: TObject);
    procedure itmFecharClick(Sender: TObject);
    procedure imgTelaMouseMove(Sender: TObject; Shift: TShiftState; X, Y: Integer);
    procedure ScrollBarYChange(Sender: TObject);
    procedure itmSairClick(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure FormShow(Sender: TObject);
    procedure itmAbrirClick(Sender: TObject);
    procedure itmSalvarClick(Sender: TObject);
    procedure imgTelaMouseDown(Sender: TObject; Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
    procedure itmObjetosExcluirClick(Sender: TObject);
    procedure itmObjetosPropriedadesClick(Sender: TObject);
    procedure sbtLadrilhosClick(Sender: TObject);
    procedure sbtObjetosClick(Sender: TObject);
    procedure imgPrevisaoClick(Sender: TObject);
    procedure tvObjetosClick(Sender: TObject);
    procedure itmExportarClick(Sender: TObject);
    procedure itmFlipVerticalClick(Sender: TObject);
    procedure itmFlipHorizontalClick(Sender: TObject);
    procedure ExibirPaletaLadrilhosExecute(Sender: TObject);
    procedure itmExibirObjetosClick(Sender: TObject);
    procedure itmSobreClick(Sender: TObject);
    procedure itmConteudoClick(Sender: TObject);
    procedure itmAtualizarTelaClick(Sender: TObject);
    procedure itmExibirCenarioClick(Sender: TObject);

  private
    procedure RedesenhaMapa;
    procedure HabilitarControles(habilitar: boolean);

  public
    procedure DesenharPrevisao(const bmp: TBitmap);

  end;

//------------------------------------------------------------------------------
// Constantes
//------------------------------------------------------------------------------
const
  MAPA_LARGURA  = 17;
  MAPA_ALTURA   = 200;
  TELA_LARGURA  = 17;
  TELA_ALTURA   = 15;


//------------------------------------------------------------------------------
// Variaveis Globais
//------------------------------------------------------------------------------
var
  frmZeus:      TfrmZeus;
  mapFundo:     CMapa;
  mapLadrilhos: CMapa;
  ladPincel:    CLadrilho;
  objPincel:    CObjeto;
  lstObjetos:   TObjectList;
  lstCenario:   TObjectList;
  glbAlterado:  boolean;

implementation

{$R *.dfm}

uses UAbertura, UPaleta, UPropObj;

//------------------------------------------------------------------------------
// Métodos Próprios
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// Desenha a Previsão do Objeto
procedure TfrmZeus.DesenharPrevisao(const bmp: TBitmap);
var x, y: integer;
begin
  x := (imgPrevisao.Width div 2) - (bmp.Width div 2);
  y := (imgPrevisao.Height div 2) - (bmp.Height div 2);
  imgPrevisao.Canvas.FillRect(Rect(0,0, imgPrevisao.Width, imgPrevisao.Height));
  imgPrevisao.Canvas.Draw(x, y, bmp);
end;

////////////////////////////////////////////////////////////////////////////////
// Redesenha a area visível do Mapa
procedure TfrmZeus.RedesenhaMapa;
var i: integer;
begin
  if not imgTela.Enabled then
    Exit;

  //Desenha o Fundo
  mapFundo.Desenhar(imgTela, 0, ScrollBarY.Position);

  //Desenha o cenario
  if itmExibirCenario.Checked then
    for i := 0 to lstCenario.Count - 1 do
      CObjeto(lstCenario[i]).Desenhar(imgTela, 0, ScrollBarY.Position * 32);

  //Desenha os Objetos
  if itmExibirObjetos.Checked then
    for i := 0 to lstObjetos.Count - 1 do
      CObjeto(lstObjetos[i]).Desenhar(imgTela, 0, ScrollBarY.Position * 32);

end;

////////////////////////////////////////////////////////////////////////////////
// Muda a propriedade Enabled dos componentes importantes
procedure TfrmZeus.HabilitarControles(habilitar: boolean);
begin
  //do frmPaleta
  frmPaleta.imgLadrilhos.Enabled := habilitar;
  frmPaleta.cboLadrilhos.Enabled := habilitar;

  //do frmZeus
  panCentro.Enabled := habilitar;
  imgTela.Enabled := habilitar;
  sbtLadrilhos.Enabled := habilitar;
  sbtObjetos.Enabled := habilitar;
  ScrollBarY.Enabled := habilitar;
end;

//------------------------------------------------------------------------------
// Eventos do Form
//------------------------------------------------------------------------------
procedure TfrmZeus.FormShow(Sender: TObject);
var
  i, iTipos: integer;
  objNovo: CObjeto;
  xmlDoc1: TXMLDocument;
  nRoot, nObjetos, nAtual: IXMLNode;
  nTVObjetos: TTreeNode;
begin
  //Mostra o form de Abertura
  frmAbertura.Show;
  frmAbertura.Refresh;

  //Desabilita os controles básicos
  HabilitarControles(false);

  //Cria os Objetos
  mapFundo      := CMapa.Create(MAPA_LARGURA, MAPA_ALTURA, TELA_LARGURA, TELA_ALTURA);
  mapLadrilhos  := CMapa.Create(10, 10, 10, 10);
  ladPincel     := CLadrilho.Create;
  objPincel     := CObjeto.Create;
  lstObjetos    := TObjectList.Create;
  lstCenario    := TObjectList.Create;

  //Abre o XML contendo a lista de objetos
  xmlDoc1 := TXMLDocument.Create(self);
  xmlDoc1.LoadFromFile('objetos.xobj');
  xmlDoc1.Active := true;

  nRoot        := xmlDoc1.ChildNodes['Objetos'];

  tvObjetos.Items.Clear;

  for iTipos := 0 to nRoot.ChildNodes.Count - 1 do
  begin
    //Pega a lista de objetos e transfere para o TreeView
    nTVObjetos := tvObjetos.Items.Add(nil, nRoot.ChildNodes[iTipos].NodeName);
    nObjetos := nRoot.ChildNodes[iTipos];
    for i := 0 to nObjetos.ChildNodes.Count - 1 do
    begin
      nAtual          := nObjetos.ChildNodes[i];
      objNovo         := CObjeto.Create;
      objNovo.Nome    := nAtual.Attributes['nome'];
      objNovo.Tipo    := StrToInt(nAtual.Attributes['tipo']);
      objNovo.SubTipo := StrToInt(nAtual.Attributes['subtipo']);
      objNovo.X       := StrToInt(nAtual.Attributes['x']);
      objNovo.Y       := StrToInt(nAtual.Attributes['y']);
      objNovo.Energia := StrToInt(nAtual.Attributes['energia']);
      objNovo.Velocidade := StrToInt(nAtual.Attributes['velocidade']);
      objNovo.AbrirBitmap(nAtual.Attributes['arquivo']);
      objNovo.Desenhar(imgTela, 0, ScrollBarY.Position * 32);
      tvObjetos.Items.AddChildObject(nTVObjetos, objNovo.Nome, objNovo);
    end;
    nTVObjetos.Expanded := True;
  end;
  xmlDoc1.Free;

  //Redefine a barra de Rolagem de acordo como tamanho do Mapa;
  ScrollBarY.Max := MAPA_ALTURA - 15;
  ScrollBarY.Position := ScrollBarY.Max;

  frmPaleta.Show;
  frmAbertura.Close;
end;

procedure TfrmZeus.FormClose(Sender: TObject; var Action: TCloseAction);
var i: integer;
begin
  //Libera a memória alocada
  lstObjetos.Clear;
  lstCenario.Clear;
  mapFundo.Free;
  mapLadrilhos.Free;
  ladPincel.Free;
  objPincel.Free;
  lstObjetos.Free;
  lstCenario.Free;
  for i := 0 to tvObjetos.Items.Count - 1 do
  begin
    if not tvObjetos.Items[i].HasChildren then
      CObjeto(tvObjetos.Items[i].Data).Free;
  end;
end;




//------------------------------------------------------------------------------
// Eventos do Menu Principal
//------------------------------------------------------------------------------
procedure TfrmZeus.itmNovoClick(Sender: TObject);
begin
  if imgTela.Enabled then
  begin
    mapFundo.Limpar;
    itmFechar.Click;
  end;

  //Redesenha a Tela
  mapFundo.Desenhar(imgTela, 0, ScrollBarY.Position);

  //Zera o Pincel de Ladrilhos
  ladPincel.X := 0;
  ladPincel.Y := 0;
  ladPincel.Bmp_X := 0;
  ladPincel.Bmp_Y := 0;
  ladPincel.H_Flip := Integer(false);
  ladPincel.V_Flip := Integer(false);
  ladPincel.Arquivo := '';

  //Zera o Pincel de Objetos
  objPincel.Tipo := 0;
  objPincel.SubTipo := 7;
  objPincel.X := 0;
  objPincel.Y := 0;
  objPincel.AbrirBitmap('dat\aliens\alien_07.bmp');

  HabilitarControles(true);
end;

procedure TfrmZeus.itmAbrirClick(Sender: TObject);
var
  s: string;
  i, x, y: integer;
  lad: TLadrilho;
  bmp: TBitmap;
  objNovo: CObjeto;
  nRoot, nBitmap, nMapa, nObjetos, nColuna, nAtual: IXMLNode;
  xmlDoc1: TXMLDocument;
begin
  if not dlgAbrirMapa.Execute then
    Exit;

  BarraProgresso.Max := MAPA_LARGURA - 1;

  //Limpa os Objetos usando o menu Arquivo/Novo
  imgTela.Enabled := False;
  itmNovo.Click;
  imgTela.Enabled := True;


  //Codificação temporária
  frmPaleta.cboLadrilhos.Items.Clear;


  //Abertura do XML
  xmlDoc1  := TXMLDocument.Create(self);
  xmlDoc1.LoadFromFile(dlgAbrirMapa.FileName);
  xmlDoc1.Active := true;
  nRoot    := xmlDoc1.ChildNodes['Atena'];
  nBitmap  := nRoot.ChildNodes['Bitmap'];
  nMapa    := nRoot.ChildNodes['Mapa'];
  nObjetos := nRoot.ChildNodes['Objetos'];

  //Carrega a lista de bitmaps utilizados
  for i := 0 to nBitmap.ChildNodes.Count - 1 do
  begin
    nAtual := nBitmap.ChildNodes[i];
    bmp := TBitmap.Create;
    bmp.LoadFromFile(ExtractFilePath(Application.ExeName) + nAtual.Attributes['nome']);
    frmPaleta.cboLadrilhos.Items.AddObject(nAtual.Attributes['nome'], TObject(bmp));
  end;

  //Carrega o Mapa
  for x := 0 to MAPA_LARGURA - 1 do
  begin
    BarraProgresso.Position := x;
    nColuna := nMapa.ChildNodes[x];
    for y := 0 to MAPA_ALTURA - 1 do
    begin
      nAtual      := nColuna.ChildNodes[y];
      lad.x       := StrToInt(nAtual.Attributes['x']);
      lad.y       := StrToInt(nAtual.Attributes['y']);
      lad.bmp_x   := StrToInt(nAtual.Attributes['bmp_x']);
      lad.bmp_y   := StrToInt(nAtual.Attributes['bmp_y']);
      lad.h_flip  := StrToInt(nAtual.Attributes['h_flip']);
      lad.v_flip  := StrToInt(nAtual.Attributes['v_flip']);
      s := nAtual.Attributes['arquivo'];
      StrCopy(lad.arquivo, PChar(s));

      with frmPaleta.cboLadrilhos do
        for i := 0 to Items.Count - 1 do
          if Items[i] = s then
            mapFundo.SetTLadrilho(x, y, lad, TBitmap(Items.Objects[i]), lad.bmp_x, lad.bmp_y);

      if Boolean(lad.h_flip) then
      begin
        mapFundo.Ladrilho[x, y].FlipHorizontal;
        mapFundo.Ladrilho[x, y].H_Flip := Integer(true);
      end;

      if Boolean(lad.v_flip) then
      begin
        mapFundo.Ladrilho[x, y].FlipVertical;
        mapFundo.Ladrilho[x, y].V_Flip := Integer(true);
      end;

    end;
  end;
  mapFundo.Desenhar(imgTela, 0, ScrollBarY.Position);

  //Carrega os Objetos
  lstObjetos.Clear;
  lstCenario.Clear;
  for i := 0 to nObjetos.ChildNodes.Count - 1 do
  begin
    nAtual          := nObjetos.ChildNodes[i];
    objNovo         := CObjeto.Create;
    objNovo.Nome    := nAtual.Attributes['nome'];
    objNovo.Tipo    := StrToInt(nAtual.Attributes['tipo']);
    objNovo.SubTipo := StrToInt(nAtual.Attributes['subtipo']);
    objNovo.X       := StrToInt(nAtual.Attributes['x']);
    objNovo.Y       := StrToInt(nAtual.Attributes['y']);
    objNovo.Energia := StrToInt(nAtual.Attributes['energia']);
    objNovo.Velocidade := StrToInt(nAtual.Attributes['velocidade']);
    objNovo.AbrirBitmap(nAtual.Attributes['arquivo']);
    objNovo.Desenhar(imgTela, 0, ScrollBarY.Position * 32);
    if objNovo.Tipo = 3 then
      lstCenario.Add(objNovo)
    else
      lstObjetos.Add(objNovo);
  end;

  //Libera a memoria
  for i := 0 to frmPaleta.cboLadrilhos.Items.Count - 1 do
    TBitmap(frmPaleta.cboLadrilhos.Items.Objects[i]).Free;

  xmlDoc1.Active := false;
  xmlDoc1.Free;
  BarraProgresso.Position := 0;
end;

procedure TfrmZeus.itmSalvarClick(Sender: TObject);
var
  i, x, y: integer;
  lad: TLadrilho;
  obj: CObjeto;
  nRoot, nBitmap, nMapa, nObjetos, nColuna, nAtual: IXMLNode;
  xmlDoc1: TXMLDocument;
begin
  dlgSalvarMapa.FilterIndex := 2;
  if not dlgSalvarMapa.Execute then
    Exit;

  BarraProgresso.Max := MAPA_LARGURA - 1;

  //Configura o XML
  xmlDoc1         := TXMLDocument.Create(self);
  xmlDoc1.Options := [doNodeAutoCreate,doNodeAutoIndent,doAttrNull,doAutoPrefix,doNamespaceDecl];
  xmlDoc1.Active  := true;
  nRoot    := xmlDoc1.AddChild('Atena');
  nBitmap  := nRoot.AddChild('Bitmap');
  nMapa    := nRoot.AddChild('Mapa');
  nObjetos := nRoot.AddChild('Objetos');

  //Informações sobre o Mapa
  nRoot.Attributes['versao']  := '1.0';
  nMapa.Attributes['largura'] := IntToStr(MAPA_LARGURA);
  nMapa.Attributes['altura']  := IntToStr(MAPA_ALTURA);

  //Salva a lista de Bitmaps
  for i := 0 to frmPaleta.cboLadrilhos.Items.Count - 1 do
  begin
    nAtual := nBitmap.AddChild('Arquivo');
    nAtual.Attributes['nome'] := frmPaleta.cboLadrilhos.Items[i];
  end;

  //Salva o Mapa
  for x := 0 to MAPA_LARGURA - 1 do
  begin
    BarraProgresso.Position := x;
    nColuna := nMapa.AddChild('Coluna');
    for y := 0 to MAPA_ALTURA - 1 do
    begin
      lad := mapFundo.GetTLadrilho(x, y);
      nAtual := nColuna.AddChild('Ladrilho');
      nAtual.Attributes['x'] := IntToStr(lad.x);
      nAtual.Attributes['y'] := IntToStr(lad.y);
      nAtual.Attributes['bmp_x'] := IntToStr(lad.bmp_x);
      nAtual.Attributes['bmp_y'] := IntToStr(lad.bmp_y);
      nAtual.Attributes['h_flip'] := IntToStr(lad.h_flip);
      nAtual.Attributes['v_flip'] := IntToStr(lad.v_flip);
      nAtual.Attributes['arquivo'] := string(lad.arquivo);
    end;
  end;

  //Salva o Cenario
  for i := 0 to lstCenario.Count - 1 do
  begin
    obj := CObjeto(lstCenario[i]);
    nAtual := nObjetos.AddChild('Objeto');
    nAtual.Attributes['nome'] := obj.Nome;
    nAtual.Attributes['tipo'] := IntToStr(obj.Tipo);
    nAtual.Attributes['subtipo'] := IntToStr(obj.SubTipo);
    nAtual.Attributes['x'] := IntToStr(obj.X);
    nAtual.Attributes['y'] := IntToStr(obj.Y);
    nAtual.Attributes['energia'] := IntToStr(obj.Energia);
    nAtual.Attributes['velocidade'] := IntToStr(obj.Velocidade);
    nAtual.Attributes['arquivo'] := obj.Arquivo;
  end;

  //Salva os Objetos
  for i := 0 to lstObjetos.Count - 1 do
  begin
    obj := CObjeto(lstObjetos[i]);
    nAtual := nObjetos.AddChild('Objeto');
    nAtual.Attributes['nome'] := obj.Nome;
    nAtual.Attributes['tipo'] := IntToStr(obj.Tipo);
    nAtual.Attributes['subtipo'] := IntToStr(obj.SubTipo);
    nAtual.Attributes['x'] := IntToStr(obj.X);
    nAtual.Attributes['y'] := IntToStr(obj.Y);
    nAtual.Attributes['energia'] := IntToStr(obj.Energia);
    nAtual.Attributes['velocidade'] := IntToStr(obj.Velocidade);
    nAtual.Attributes['arquivo'] := obj.Arquivo;
  end;

  //Salva o XML em arquivo e libera a memória
  xmlDoc1.SaveToFile(dlgSalvarMapa.FileName);
  xmlDoc1.Active := false;
  xmlDoc1.Free;
  BarraProgresso.Position := 0;
end;

procedure TfrmZeus.itmFecharClick(Sender: TObject);
begin
  HabilitarControles(false);

  //Limpa os objetos
  lstObjetos.Clear;
  lstCenario.Clear;
  frmPaleta.cboLadrilhos.ItemIndex := -1;
  frmPaleta.imgLadrilhos.Canvas.FillRect(Rect(0,0, 96, 480));
  imgTela.Canvas.FillRect(Rect(0,0, imgTela.Width, imgTela.Height));
  imgTela.Canvas.FillRect(Rect(0, 0, imgTela.Width, imgTela.Height));
  imgPrevisao.Canvas.FillRect(Rect(0, 0, imgPrevisao.Width, imgPrevisao.Height));
end;

procedure TfrmZeus.itmExportarClick(Sender: TObject);
var
  arq: file;
  i, x, y: integer;
  lad: TLadrilho;
  obj: TObjeto;
begin
  dlgSalvarMapa.FilterIndex := 3;
  if not dlgSalvarMapa.Execute then
    Exit;

  //Abre o arquivo
  AssignFile(arq, dlgSalvarMapa.FileName);
  Rewrite(arq, 1);

  //Grava o mapa de ladrilhos
  for x := 0 to MAPA_LARGURA - 1 do
    for y := 0 to MAPA_ALTURA - 1 do
    begin
      lad := mapFundo.GetTLadrilho(x, y);
      BlockWrite(arq, lad, SizeOf(lad));
    end;

  //Grava o cenario
  for i := 0 to lstCenario.Count - 1 do
  begin
    obj := CObjeto(lstCenario[i]).GetTObjeto;
    BlockWrite(arq, obj, SizeOf(obj));
  end;

  //Grava os objetos
  for i := 0 to lstObjetos.Count - 1 do
  begin
    obj := CObjeto(lstObjetos[i]).GetTObjeto;
    BlockWrite(arq, obj, SizeOf(obj));
  end;
  CloseFile(arq);
end;

procedure TfrmZeus.itmSairClick(Sender: TObject);
begin
  Self.Close;
end;

procedure TfrmZeus.itmFlipVerticalClick(Sender: TObject);
begin
  if sbtLadrilhos.Down then
  begin
    ladPincel.FlipVertical;
    DesenharPrevisao(ladPincel.Bitmap);
  end;
end;

procedure TfrmZeus.itmFlipHorizontalClick(Sender: TObject);
begin
  if sbtLadrilhos.Down then
  begin
    ladPincel.FlipHorizontal;
    DesenharPrevisao(ladPincel.Bitmap);
  end;
end;

procedure TfrmZeus.ExibirPaletaLadrilhosExecute(Sender: TObject);
begin
  frmPaleta.Visible := itmPaletadeLadrilhos.Checked;
end;

procedure TfrmZeus.itmExibirCenarioClick(Sender: TObject);
begin
  RedesenhaMapa;
end;

procedure TfrmZeus.itmExibirObjetosClick(Sender: TObject);
begin
  RedesenhaMapa;
end;

//------------------------------------------------------------------------------
//Eventos dos Controles
//------------------------------------------------------------------------------
procedure TfrmZeus.imgTelaMouseDown(Sender: TObject; Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
var
  i: integer;
  objNovo: CObjeto;
  lad_x, lad_y: integer;
begin
  //Se estiver editando os Objetos
  if (sbtObjetos.Down) and (itmExibirObjetos.Checked) then
  begin
    //Se clicar o botão direito, abre o PopUp
    if Button = mbRight then
    begin
      for i := lstObjetos.Count - 1 downto 0 do
        if CObjeto(lstObjetos[i]).Colisao(X, Y + (ScrollBarY.Position * 32)) then
        begin
          //O Tag do PopUp indica o indice do objeto a ser alterado
          popObjetos.Tag := i;
          popObjetos.Popup(Mouse.CursorPos.X, Mouse.CursorPos.Y);
          Break;
        end;
    end else
    begin
      //Procura o centro do objeto
      objPincel.x := x - (objPincel.L div 2);
      objPincel.y := y + (ScrollBarY.Position * 32) - (objPincel.A div 2);

      //Cria o objeto novo e adiciona na lista
      objNovo := CObjeto.Create;
      objNovo.Iniciar(objPincel);
      objNovo.Desenhar(imgTela, 0, ScrollBarY.Position * 32);
      lstObjetos.Add(objNovo);

      //Desenha os objetos visiveis
      //for i := 0 to lstObjetos.Count - 1 do
      //  CObjeto(lstObjetos[i]).Desenhar(imgTela, 0, ScrollBarY.Position * 32);
    end;
  end;

  //Se estiver editando os Objetos
  if (sbtCenario.Down) and (itmExibirCenario.Checked) then
  begin
    //Se clicar o botão direito, abre o PopUp
    if Button = mbRight then
    begin
      for i := lstCenario.Count - 1 downto 0 do
        if CObjeto(lstCenario[i]).Colisao(X, Y + (ScrollBarY.Position * 32)) then
        begin
          //O Tag do PopUp indica o indice do objeto a ser alterado
          popObjetos.Tag := i;
          popObjetos.Popup(Mouse.CursorPos.X, Mouse.CursorPos.Y);
          Break;
        end;
    end else
    begin
      //Procura o centro do objeto
      objPincel.x := x - (objPincel.L div 2);
      objPincel.y := y + (ScrollBarY.Position * 32) - (objPincel.A div 2);

      //Cria o objeto novo e adiciona na lista
      objNovo := CObjeto.Create;
      objNovo.Iniciar(objPincel);
      objNovo.Desenhar(imgTela, 0, ScrollBarY.Position * 32);
      lstCenario.Add(objNovo);
    end;
  end;

  //Se estiver editando os ladrilhos e clicou o botão direto
  if sbtLadrilhos.Down then
  begin
    lad_x := (X - (X mod 32)) div 32;
    lad_y := (Y - (Y mod 32)) div 32;

    if (Button = mbLeft) and (ssCtrl in Shift)then
    begin
      Screen.Cursor := crHourGlass;
      mapFundo.Substituir(lad_x, lad_y + ScrollBarY.Position, ladPincel);
      RedesenhaMapa;
      Screen.Cursor := crDefault;
    end;

    if Button = mbRight then
    begin
      //Copia o ladrilho no mapa para o Pincel
      ladPincel.Iniciar(mapFundo.Ladrilho[lad_x, lad_y + ScrollBarY.Position]);
      ladPincel.X := 0;
      ladPincel.Y := 0;
      DesenharPrevisao(ladPincel.Bitmap);
    end;
  end;
  //Dispara o evento MouseMove do imgTela
  imgTelaMouseMove(Sender, Shift, X, Y);
end;

procedure TfrmZeus.imgTelaMouseMove(Sender: TObject; Shift: TShiftState; X, Y: Integer);
var lad_x, lad_y: integer;
begin
  //Mostra a coordenada do cursor
  BarraStatus.Panels[0].Text := ' X: ' + IntToStr(X) + '    Y: ' + IntToStr(Y);

  //Verifica se esta em uma área válida
  if (not sbtLadrilhos.Down)
  or (X >= imgTela.Width)
  or (Y >= imgTela.Height)
  or (X < 0) or (Y < 0) then
    Exit;

  //Transforma X e Y em coordenadas na matriz de ladrilhos
  lad_x := (X - (X mod 32)) div 32;
  lad_y := (Y - (Y mod 32)) div 32;

  //Se clicar o botão esquerdo
  if (ssLeft in Shift) then
  begin
      //Atribui o conteudo do Pincel ao ladrilho no Mapa
      mapFundo.Ladrilho[lad_x, lad_y + ScrollBarY.Position] := ladPincel;
      mapFundo.Ladrilho[lad_x, lad_y + ScrollBarY.Position].X := lad_x * 32;
      mapFundo.Ladrilho[lad_x, lad_y + ScrollBarY.Position].Y := (lad_y + ScrollBarY.Position) * 32;
      //Desenha na tela o ladrilho corrente
      imgTela.Canvas.Draw(lad_x * 32, lad_y * 32, ladPincel.Bitmap);
  end;

end;

procedure TfrmZeus.ScrollBarYChange(Sender: TObject);
begin
  //Se clicou na barra de rolagem, redesenha o mapa
  RedesenhaMapa;
end;

procedure TfrmZeus.itmObjetosExcluirClick(Sender: TObject);
begin
  if sbtCenario.Down then
    lstCenario.Delete(popObjetos.Tag)
  else
    lstObjetos.Delete(popObjetos.Tag);

  RedesenhaMapa;
end;

procedure TfrmZeus.itmObjetosPropriedadesClick(Sender: TObject);
begin
  if sbtCenario.Down then
    frmPropObj.Objeto := CObjeto(lstCenario[popObjetos.Tag])
  else
    frmPropObj.Objeto := CObjeto(lstObjetos[popObjetos.Tag]);

  frmPropObj.ShowModal;
  RedesenhaMapa;
end;

procedure TfrmZeus.sbtLadrilhosClick(Sender: TObject);
begin
  DesenharPrevisao(ladPincel.Bitmap);
end;

procedure TfrmZeus.sbtObjetosClick(Sender: TObject);
begin
  DesenharPrevisao(objPincel.Bitmap);
end;

procedure TfrmZeus.imgPrevisaoClick(Sender: TObject);
begin
  if sbtObjetos.Down then
  begin
    frmPropObj.Objeto := objPincel;
    frmPropObj.ShowModal;
    DesenharPrevisao(objPincel.Bitmap);
  end;
end;

procedure TfrmZeus.tvObjetosClick(Sender: TObject);
begin
  if tvObjetos.SelectionCount = 0 then
    Exit;

  if tvObjetos.Selected.HasChildren then
    Exit;

  objPincel.Iniciar(CObjeto(tvObjetos.Selected.Data));

  if objPincel.Tipo = 3 then
    sbtCenario.Down := true
  else
    sbtObjetos.Down := true;

  DesenharPrevisao(objPincel.Bitmap);
end;

procedure TfrmZeus.itmAtualizarTelaClick(Sender: TObject);
begin
  RedesenhaMapa;
end;

procedure TfrmZeus.itmSobreClick(Sender: TObject);
begin
  ShowMessage('Zeus 2.0 - Editor de Mapas para o Atena');
end;

procedure TfrmZeus.itmConteudoClick(Sender: TObject);
begin
  ShowMessage('Clique nos botões para alternar entre a edição de ladrilhos e objetos'
      + #13 + 'Clique Ctrl + botão do mouse para preencher os ladrilhos'
      + #13 + 'Clique o botão direito sobre um objeto para editar as propriedades dele'
      + #13 + 'Pressione H para virar o ladrilho horizontalmente'
      + #13 + 'Pressione V para virar o ladrilho verticalmente');
end;

end.
