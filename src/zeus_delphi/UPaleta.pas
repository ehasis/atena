unit UPaleta;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, UMapa, UObjeto, StdCtrls, ExtDlgs, Menus, Buttons;

type
  TfrmPaleta = class(TForm)
    imgLadrilhos: TImage;
    cboLadrilhos: TComboBox;
    dlgAbrirLadrilhos: TOpenPictureDialog;
    popLadrilho: TPopupMenu;
    itmFlipVertical: TMenuItem;
    itmFlipHorizontal: TMenuItem;
    bvlLadrilhos: TShape;
    btnAbrirLadrilhos: TSpeedButton;
    procedure imgLadrilhosMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure cboLadrilhosChange(Sender: TObject);
    procedure btnAbrirLadrilhosClick(Sender: TObject);
    procedure itmFlipVerticalClick(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
  private
    { Private declarations }
    ladX, ladY: integer;
  public
    { Public declarations }
  end;

var
  frmPaleta: TfrmPaleta;

implementation

{$R *.dfm}

uses UZeus;

procedure TfrmPaleta.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  frmZeus.ExibirPaletaLadrilhos.Checked := false;
end;

procedure TfrmPaleta.imgLadrilhosMouseDown(Sender: TObject; Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
var
  lad: TLadrilho;
begin

  //Obtem a coordenada x, y do ladrilho
  ladX := (X - (X mod 32)) div 32;
  ladY := (Y - (Y mod 32)) div 32;

  if Button = mbRight then
  begin
    popLadrilho.Popup(Mouse.CursorPos.X, Mouse.CursorPos.Y);
    Exit;
  end;

  //Move o Bevel para cima do ladrilho selecionado
  bvlLadrilhos.Visible := True;
  bvlLadrilhos.Top := (ladY * 32) + imgLadrilhos.Top - 1;
  bvlLadrilhos.Left := (ladX * 32) + imgLadrilhos.Left - 1;

  //Obtem as caracterísicas do ladirlho selecionado
  lad := mapLadrilhos.GetTLadrilho(ladX, ladY);

  //Transfere as características para o pincel
  if Button = mbLeft then
  begin
    ladPincel.Iniciar(lad, mapLadrilhos.Ladrilho[ladX, ladY].Bitmap, 0, 0);
    if frmZeus.sbtLadrilhos.Down then
      frmZeus.DesenharPrevisao(ladPincel.Bitmap);
  end;

end;

procedure TfrmPaleta.cboLadrilhosChange(Sender: TObject);
var
  x, y: integer;
  lad: TLadrilho;
  bmp: TBitmap;
begin

  //Carrega o Bitmap selecionado
  bmp := TBitmap.Create;
  bmp.LoadFromFile(ExtractFilePath(Application.ExeName) + cboLadrilhos.Text);

  //Define as as propriedades dos ladrilhos
  lad.h_flip := Integer(false);
  lad.v_flip := Integer(false);
  StrCopy(lad.arquivo, PChar(cboLadrilhos.Text));

  //Carrega os ladrilhos da paleta
  for x := 0 to 2 do
    for y := 0 to 14 do
    begin
      lad.x := x * 32;
      lad.y := y * 32;
      lad.bmp_x := x * 32;
      lad.bmp_y := y * 32;
      mapLadrilhos.SetTLadrilho(x, y, lad, bmp, x * 32, y * 32);
    end;
  mapLadrilhos.Desenhar(imgLadrilhos, 0, 0);
  bmp.Free;

end;

procedure TfrmPaleta.btnAbrirLadrilhosClick(Sender: TObject);
var
  sApp, sArq: string;
  i: integer;
begin
  if not dlgAbrirLadrilhos.Execute then
    Exit;
  sArq := dlgAbrirLadrilhos.FileName;
  sApp := ExtractFilePath(Application.ExeName);
  if Pos(UpperCase(sApp), UpperCase(sArq)) = 0 then
  begin
    ShowMessage('o arquivo deve estar em um diretório de nivel superior ao executável.');
    Exit;
  end;

  i := Length(sApp);
  sArq := Copy(sArq, i + 1, Length(sArq));
  cboLadrilhos.Items.Add(sArq)
end;

procedure TfrmPaleta.itmFlipVerticalClick(Sender: TObject);
begin
  mapLadrilhos.Ladrilho[ladX, ladY].FlipVertical;
  mapLadrilhos.Desenhar(imgLadrilhos, 0, 0);
end;

end.
