unit UZeus;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Menus, StdCtrls, ExtCtrls, ComCtrls, UMapa, ExtDlgs;

type
  TfrmZeus = class(TForm)
    MenuPrincipal: TMainMenu;
    mnuArquivo: TMenuItem;
    itmNovo: TMenuItem;
    itmAbrir: TMenuItem;
    itmSalvar: TMenuItem;
    N1: TMenuItem;
    itmSair: TMenuItem;
    mnuEditar: TMenuItem;
    pagObjetos: TPageControl;
    tabLadrilhos: TTabSheet;
    tabAliens: TTabSheet;
    imgLadrilhos: TImage;
    cboLadrilhos: TComboBox;
    btnAbrirLadrilhos: TButton;
    itmFechar: TMenuItem;
    Panel1: TPanel;
    imgTela: TImage;
    sbTelaY: TScrollBar;
    Label1: TLabel;
    Label2: TLabel;
    Panel2: TPanel;
    imgPincelEsq: TImage;
    imgPincelDir: TImage;
    dlgAbrirLadrilhos: TOpenPictureDialog;
    Memo1: TMemo;
    tabVeiculos: TTabSheet;
    tabConstrucoes: TTabSheet;
    itmPreencherLadrilhos: TMenuItem;
    dlgAbrirMapa: TOpenDialog;
    dlgSalvarMapa: TSaveDialog;
    procedure itmNovoClick(Sender: TObject);
    procedure itmFecharClick(Sender: TObject);
    procedure cboLadrilhosChange(Sender: TObject);
    procedure imgTelaMouseMove(Sender: TObject; Shift: TShiftState; X, Y: Integer);
    procedure imgTelaMouseUp(Sender: TObject; Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
    procedure btnAbrirLadrilhosClick(Sender: TObject);
    procedure sbTelaYChange(Sender: TObject);
    procedure itmSairClick(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure imgLadrilhosMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure itmPreencherLadrilhosClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure itmAbrirClick(Sender: TObject);
    procedure itmSalvarClick(Sender: TObject);
  private
    { Private declarations }
    procedure HabilitarControles(habilitar: boolean);
  public
    { Public declarations }
  end;

const
  MAPA_LARGURA  = 17;
  MAPA_ALTURA   = 30;
  TELA_LARGURA  = 17;
  TELA_ALTURA   = 15;

var
  frmZeus: TfrmZeus;
  gRect: TRect;
  gLad: TLadrilho;
  gBmp: TBitmap;
  mapFundo: CMapa;
  mapLadrilhos: CMapa;
  ladPincelEsq: CLadrilho;
  ladPincelDir: CLadrilho;
  ladPincelAtual: CLadrilho;


implementation

{$R *.dfm}

procedure TfrmZeus.HabilitarControles(habilitar: boolean);
begin
  imgTela.Enabled := habilitar;
  tabLadrilhos.Enabled := habilitar;
  //imgLadrilhos.Enabled := habilitar;
  //cboLadrilhos.Enabled := habilitar;
  sbTelaY.Enabled := habilitar;
end;

procedure TfrmZeus.FormShow(Sender: TObject);
begin
  HabilitarControles(false);
end;

procedure TfrmZeus.itmNovoClick(Sender: TObject);
begin
  if imgTela.Enabled then
    itmFechar.Click;

  mapLadrilhos := CMapa.Create(3, 15, 3, 15);
  mapFundo := CMapa.Create(MAPA_LARGURA, MAPA_ALTURA, TELA_LARGURA, TELA_ALTURA);
  mapFundo.Desenhar(imgTela, 0, sbTelaY.Position);

  gBmp := TBitmap.Create;
  gBmp.Width := 32;
  gBmp.Height := 32;

  gRect := Rect(0, 0, 32, 32);

  gLad.x := 0;
  gLad.y := 0;
  gLad.bmp_x := 0;
  gLad.bmp_y := 0;
  gLad.h_flip := false;
  gLad.v_flip := false;
  gLad.arquivo := '';

  ladPincelEsq := CLadrilho.Create;
  ladPincelDir := CLadrilho.Create;
  ladPincelEsq.Iniciar(gLad, gBmp, 0, 0);
  ladPincelDir.Iniciar(gLad, gBmp, 0, 0);

  HabilitarControles(true);
end;

procedure TfrmZeus.itmAbrirClick(Sender: TObject);
begin
  if dlgAbrirMapa.Execute then;
end;

procedure TfrmZeus.itmSalvarClick(Sender: TObject);
begin
  if dlgSalvarMapa.Execute then;
end;

procedure TfrmZeus.itmFecharClick(Sender: TObject);
begin
  HabilitarControles(false);

  mapLadrilhos.Free;
  mapFundo.Free;
  ladPincelEsq.Free;
  gBmp.Free;

  cboLadrilhos.ItemIndex := -1;
  imgLadrilhos.Canvas.FillRect(Rect(0,0, 96, 480));
  imgTela.Canvas.FillRect(Rect(0, 0, 544, 480));

end;

procedure TfrmZeus.cboLadrilhosChange(Sender: TObject);
var
  x, y: integer;
  lad: TLadrilho;
  bmp: TBitmap;
begin

  bmp := TBitmap.Create;
  bmp.LoadFromFile(cboLadrilhos.Text);

  lad.h_flip := false;
  lad.v_flip := false;
  lad.arquivo := cboLadrilhos.Text;

  for x := 0 to 2 do
    for y := 0 to 14 do
    begin
      lad.x := x * 32;
      lad.y := y * 32;
      lad.bmp_x := x * 32;
      lad.bmp_y := y * 32;
      mapLadrilhos.SetLadrilho(x, y, lad, bmp, x * 32, y * 32);
    end;
  mapLadrilhos.Desenhar(imgLadrilhos, 0, 0);

  bmp.Free;
end;

procedure TfrmZeus.imgLadrilhosMouseDown(Sender: TObject; Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
var
  lad_x, lad_y: integer;
begin
  lad_x := (X - (X mod 32)) div 32;
  lad_y := (Y - (Y mod 32)) div 32;

  gLad := mapLadrilhos.GetLadrilho(lad_x, lad_y);
  gBmp.Canvas.Draw(0, 0, mapLadrilhos.GetBitmap(lad_x, lad_y));
  if Button = mbLeft then
  begin
    ladPincelEsq.Iniciar(gLad, gBmp, 0, 0);
    imgPincelEsq.Canvas.BrushCopy(gRect, gBmp, gRect, clBlack);
  end else
  begin
    ladPincelDir.Iniciar(gLad, gBmp, 0, 0);
    imgPincelDir.Canvas.BrushCopy(gRect, gBmp, gRect, clBlack);
  end;

end;

procedure TfrmZeus.imgTelaMouseUp(Sender: TObject; Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
begin
  if Button = mbLeft then
    imgTelaMouseMove(Sender, [ssLeft], X, Y)
  else
    imgTelaMouseMove(Sender, [ssRight], X, Y);
end;

procedure TfrmZeus.imgTelaMouseMove(Sender: TObject; Shift: TShiftState; X, Y: Integer);
var
  lad_x, lad_y: integer;
begin
  if (X >= 544) or (Y >= 480) then
    Exit;

  Label1.Caption := IntToStr(X);
  Label2.Caption := IntToStr(Y);
  if (Shift = [ssLeft]) or (Shift = [ssRight]) then
  begin
    lad_x := (X - (X mod 32)) div 32;
    lad_y := ((Y - (Y mod 32)) div 32);

    if Shift = [ssLeft] then
      ladPincelAtual := ladPincelEsq
    else
      ladPincelAtual := ladPincelDir;

    gLad := ladPincelAtual.GetLadrilho;
    gLad.x := (lad_x * 32);
    gLad.y := (lad_y + sbTelaY.Position) * 32;
    mapFundo.SetLadrilho(lad_x, lad_y + sbTelaY.Position, gLad, ladPincelAtual.Bitmap, 0, 0);
    imgTela.Canvas.Draw(lad_x * 32, lad_y * 32, ladPincelAtual.Bitmap);
  end;
end;

procedure TfrmZeus.btnAbrirLadrilhosClick(Sender: TObject);
begin
  if dlgAbrirLadrilhos.Execute then
      cboLadrilhos.Items.Add(ExtractFileName(dlgAbrirLadrilhos.FileName))
end;

procedure TfrmZeus.sbTelaYChange(Sender: TObject);
begin
  mapFundo.Desenhar(imgTela, 0, sbTelaY.Position);
end;

procedure TfrmZeus.itmSairClick(Sender: TObject);
begin
  frmZeus.Close;
end;

procedure TfrmZeus.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  if imgTela.Enabled then
    itmFechar.Click;

end;

procedure TfrmZeus.itmPreencherLadrilhosClick(Sender: TObject);
var
  x, y: integer;
  lad: TLadrilho;
begin
  for x := 0 to MAPA_LARGURA - 1 do
    for y := 0 to MAPA_ALTURA - 1 do
    begin
      lad := mapFundo.GetLadrilho(x, y);
      if lad.arquivo = '' then
      begin
        gLad := ladPincelAtual.GetLadrilho;
        lad.arquivo := gLad.arquivo;
        mapFundo.SetLadrilho(x, y, lad, ladPincelAtual.Bitmap, 0, 0);
      end;
    end;
  mapFundo.Desenhar(imgTela, 0, sbTelaY.Position);
end;

end.
