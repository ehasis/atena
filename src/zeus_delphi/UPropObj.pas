unit UPropObj;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, UObjeto, ComCtrls, Buttons, ExtDlgs, Mask;

type
  TfrmPropObj = class(TForm)
    PageControl1: TPageControl;
    TabSheet1: TTabSheet;
    btnCancelar: TButton;
    btnOk: TButton;
    btnAplicar: TButton;
    txtBitmap: TLabeledEdit;
    btnAbrirBitmap: TSpeedButton;
    dlgAbrirBitmap: TOpenPictureDialog;
    Bevel1: TBevel;
    panBitmap: TPanel;
    imgBitmap: TImage;
    cboTipo: TComboBox;
    Label1: TLabel;
    mskSubTipo: TMaskEdit;
    Label2: TLabel;
    TabSheet2: TTabSheet;
    MemoScript: TMemo;
    mskX: TMaskEdit;
    mskY: TMaskEdit;
    mskEnergia: TMaskEdit;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    txtNome: TLabeledEdit;
    mskVelocidade: TMaskEdit;
    Label6: TLabel;
    procedure FormShow(Sender: TObject);
    procedure btnAplicarClick(Sender: TObject);
    procedure btnOkClick(Sender: TObject);
    procedure btnCancelarClick(Sender: TObject);
    procedure btnAbrirBitmapClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    Objeto: CObjeto;

  end;

var
  frmPropObj: TfrmPropObj;

implementation

{$R *.dfm}

procedure TfrmPropObj.FormShow(Sender: TObject);
begin
  if Objeto.Tipo = 3 then
  begin
    cboTipo.Enabled := false;
    mskSubTipo.Enabled := false;
    mskEnergia.Enabled := false;
    mskVelocidade.Enabled := false;
  end;
  txtNome.Text := Objeto.Nome;
  cboTipo.ItemIndex := Integer(Objeto.Tipo);
  mskSubTipo.Text := IntToStr(Objeto.SubTipo);
  txtBitmap.Text := Objeto.Arquivo;
  mskX.Text := IntToStr(Objeto.X);
  mskY.Text := IntToStr(Objeto.Y);
  mskEnergia.Text := IntToStr(Objeto.Energia);
  mskVelocidade.Text := IntToStr(Objeto.Velocidade);
  imgBitmap.Picture.LoadFromFile(ExtractFilePath(Application.ExeName) + txtBitmap.Text);
end;

procedure TfrmPropObj.btnAplicarClick(Sender: TObject);
begin
  Objeto.Nome := txtNome.Text;
  Objeto.Tipo := cboTipo.ItemIndex;
  Objeto.SubTipo := StrToInt(mskSubTipo.Text);
  Objeto.X := StrToInt(mskX.Text);
  Objeto.Y := StrToInt(mskY.Text);
  Objeto.Energia := StrToInt(mskEnergia.Text);
  Objeto.Velocidade := StrToInt(mskVelocidade.Text);
  Objeto.AbrirBitmap(txtBitmap.Text);
end;

procedure TfrmPropObj.btnOkClick(Sender: TObject);
begin
  btnAplicar.Click;
  frmPropObj.Close;
end;

procedure TfrmPropObj.btnCancelarClick(Sender: TObject);
begin
    frmPropObj.Close;
end;

procedure TfrmPropObj.btnAbrirBitmapClick(Sender: TObject);
var
  sApp, sArq: string;
  i: integer;
begin
  dlgAbrirBitmap.InitialDir := ExtractFilePath(Application.ExeName) + 'dat\';
  if not dlgAbrirBitmap.Execute then
    Exit;

  sArq := dlgAbrirBitmap.FileName;
  sApp := ExtractFilePath(Application.ExeName);
  if Pos(UpperCase(sApp), UpperCase(sArq)) = 0 then
  begin
    ShowMessage('o arquivo deve estar em um diretório de nivel superior ao executável.');
    Exit;
  end;

  i := Length(sApp);
  sArq := Copy(sArq, i + 1, Length(sArq));

  txtBitmap.Text := sArq;
  imgBitmap.Picture.LoadFromFile(ExtractFilePath(Application.ExeName) + txtBitmap.Text);
end;

end.
