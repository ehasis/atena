unit UMapa;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Menus, StdCtrls, ExtCtrls, ComCtrls;

type
  TLadrilho = record
    bmp_x: integer;
    bmp_y: integer;
    x: integer;
    y: integer;
    h_flip: integer;
    v_flip: integer;
    angulo: integer;
    arquivo: array[0..63] of char;
  end;

type
  CLadrilho = class//(TObject)
  private
    m_x: integer;
    m_y: integer;
    m_bmp_x: integer;
    m_bmp_y: integer;
    m_h_flip: integer;
    m_v_flip: integer;
    m_arquivo: string;
    m_bmp: TBitmap;

  public
    constructor Create;
    destructor Destroy; override;
    procedure Iniciar(const lad: TLadrilho; const bmp: TBitmap; bmp_x, bmp_y: integer); overload;
    procedure Iniciar(const lad: CLadrilho); overload;
    procedure Desenhar(tela: TImage; x_real, y_real: integer);
    procedure FlipVertical;
    procedure FlipHorizontal;
    procedure RodarHorario;

    property X: integer read m_x write m_x;
    property Y: integer read m_y write m_y;
    property Bmp_X: integer read m_bmp_x write m_bmp_x;
    property Bmp_Y: integer read m_bmp_y write m_bmp_y;
    property H_Flip: integer read m_h_flip write m_h_flip;
    property V_Flip: integer read m_v_flip write m_v_flip;
    property Arquivo: string read m_arquivo write m_arquivo;
    property Bitmap: TBitmap read m_bmp write m_bmp;

    function GetLadrilho: TLadrilho;

  end;

//------------------------------------------------------------------------------

type
  CMapa = class
  private
    m_lad: array of array of CLadrilho;
    m_largura: integer;
    m_altura: integer;
    m_largura_visivel: integer;
    m_altura_visivel: integer;

  protected
    function GetLadrilho(x, y: integer): CLadrilho;
    //procedure SetLadrilho(x, y: integer; lad: CLadrilho);

  public
    constructor Create(largura, altura, largura_visivel, altura_visivel: integer);
    destructor Destroy; override;

    procedure Desenhar(tela: TImage; x_real, y_real: integer);
    procedure SetTLadrilho(x, y: integer; const lad: TLadrilho; const bmp: TBitmap; bmp_x, bmp_y: integer);
    procedure SetLadrilho(x, y: integer; const lad: CLadrilho);
    procedure Substituir(origem_x, origem_y: integer; const destino: CLadrilho);
    procedure Limpar;

    property Ladrilho[x, y: integer]: CLadrilho read GetLadrilho write SetLadrilho;


    function GetTLadrilho(x, y: integer): TLadrilho;
    function GeTBitmap(x, y: integer): TBitmap;

  end;

implementation

//------------------------------------------------------------------------------
constructor CLadrilho.Create;
begin
  m_bmp := TBitmap.Create;
  m_bmp.Width := 32;
  m_bmp.Height := 32;
end;
//------------------------------------------------------------------------------
destructor CLadrilho.Destroy;
begin
  m_bmp.Free;
  inherited Destroy;
end;

//------------------------------------------------------------------------------
procedure CLadrilho.Iniciar(const lad: TLadrilho; const bmp: TBitmap; bmp_x, bmp_y: integer);
var Origem, Destino: TRect;
begin
  m_arquivo := lad.arquivo;
  m_x := lad.x;
  m_y := lad.y;
  m_bmp_x := lad.bmp_x;
  m_bmp_y := lad.bmp_y;
  m_h_flip := lad.h_flip;
  m_v_flip := lad.v_flip;

  Origem := Rect(bmp_x, bmp_y, bmp_x + 32, bmp_y + 32);
  Destino := Rect(0, 0, 32, 32);
  m_bmp.Canvas.CopyRect(Destino, bmp.Canvas, Origem)

end;

//------------------------------------------------------------------------------
procedure CLadrilho.Iniciar(const lad: CLadrilho);
begin
  m_arquivo := lad.Arquivo;
  m_x := lad.X;
  m_y := lad.Y;
  m_bmp_x := lad.Bmp_X;
  m_bmp_y := lad.Bmp_Y;
  m_h_flip := lad.H_Flip;
  m_v_flip := lad.V_Flip;
  m_bmp.Canvas.Draw(0, 0, lad.Bitmap);
end;

//------------------------------------------------------------------------------
procedure CLadrilho.Desenhar(tela: TImage; x_real, y_real: integer);
begin
  tela.Canvas.Draw(m_x - (x_real * 32), m_y - (y_real * 32), m_bmp);
end;

function CLadrilho.GetLadrilho: TLadrilho;
var lad: TLadrilho;
begin
  lad.x := m_x;
  lad.y := m_y;
  lad.bmp_x := m_bmp_x;
  lad.bmp_y := m_bmp_y;
  lad.h_flip := m_h_flip;
  lad.v_flip := m_v_flip;
  lad.angulo := 0;
  StrCopy(lad.arquivo, PChar(m_arquivo));

  Result := lad;

end;

procedure CLadrilho.FlipVertical;
var
  x, y: integer;
  bmp: TBitmap;
  cor: TColor;
begin
  m_v_flip := not m_v_flip;
  bmp := TBitmap.Create;
  bmp.Width := m_bmp.Width;
  bmp.Height := m_bmp.Height;
  for x := 0 to m_bmp.Width - 1 do
  begin
    for y := 0 to m_bmp.Height - 1 do
    begin
      cor := m_bmp.Canvas.Pixels[x, y];
      bmp.Canvas.Pixels[x, (m_bmp.Height - 1) - y] := cor;
    end;
  end;

  m_bmp.Canvas.Draw(0, 0, bmp);
  bmp.Free;
end;

procedure CLadrilho.FlipHorizontal;
var
  x, y: integer;
  bmp: TBitmap;
  cor: TColor;
begin
  m_h_flip := not m_h_flip;
  bmp := TBitmap.Create;
  bmp.Width := m_bmp.Width;
  bmp.Height := m_bmp.Height;
  for x := 0 to m_bmp.Width - 1 do
  begin
    for y := 0 to m_bmp.Height - 1 do
    begin
      cor := m_bmp.Canvas.Pixels[x, y];
      bmp.Canvas.Pixels[(m_bmp.Width - 1) - x, y] := cor;
    end;
  end;
  m_bmp.Canvas.Draw(0, 0, bmp);
  bmp.Free;
end;

procedure CLadrilho.RodarHorario;
begin

end;

//------------------------------------------------------------------------------
//Classe de CFundo
//------------------------------------------------------------------------------
constructor CMapa.Create(largura, altura, largura_visivel, altura_visivel: integer);
var
  x, y: integer;
  bmp: TBitmap;
  lad: TLadrilho;
begin
  bmp := TBitmap.Create;
  bmp.Width := 32;
  bmp.Height := 32;
  bmp.Canvas.Pixels[ 0, 0] := clSilver;
  bmp.Canvas.Pixels[31, 0] := clSilver;
  bmp.Canvas.Pixels[ 0,31] := clSilver;
  bmp.Canvas.Pixels[31,31] := clSilver;

  m_largura := largura - 1;
  m_altura := altura - 1;


  m_largura_visivel := largura_visivel - 1;
  m_altura_visivel := altura_visivel - 1;

  lad.h_flip := Integer(false);
  lad.v_flip := Integer(false);
  lad.arquivo := '';
  lad.bmp_x := 0;
  lad.bmp_y := 0;

  SetLength(m_lad, largura);
  for x := 0 to m_largura do
  begin
    SetLength(m_lad[x], altura);
    for y := 0 to m_altura do
    begin
      lad.x := x * 32;
      lad.y := y * 32;
      m_lad[x, y] := CLadrilho.Create;
      m_lad[x, y].Iniciar(lad, bmp, 0, 0);
    end;
  end;

  bmp.Free;
end;

destructor CMapa.Destroy;
var x, y: integer;
begin
  for x := 0 to m_largura do
    for y := 0 to m_altura do
      m_lad[x, y].Free;
  inherited Destroy;
end;

//------------------------------------------------------------------------------
procedure CMapa.Desenhar(tela: TImage; x_real, y_real: integer);
var x, y: integer;
begin
  for x := x_real to (x_real + m_largura_visivel) do
    for y := y_real to (y_real + m_altura_visivel) do
      m_lad[x, y].Desenhar(tela, x_real, y_real);
end;

//------------------------------------------------------------------------------
function CMapa.GetLadrilho(x, y: integer): CLadrilho;
begin
  result := m_lad[x, y];
end;

procedure CMapa.SetTLadrilho(x, y: integer; const lad: TLadrilho; const bmp: TBitmap; bmp_x, bmp_y: integer);
begin
  m_lad[x, y].Iniciar(lad, bmp, bmp_x, bmp_y);
end;

procedure CMapa.SetLadrilho(x, y: integer; const lad: CLadrilho);
begin
  m_lad[x, y].Iniciar(lad);
end;

procedure CMapa.Substituir(origem_x, origem_y: integer; const destino: CLadrilho);
var
  x, y: integer;
  origem: CLadrilho;
begin
  origem := CLadrilho.Create;
  origem.Iniciar(m_lad[origem_x, origem_y]);
  for x := 0 to m_largura do
  begin
    for y := 0 to m_altura do
    begin
      if  (m_lad[x, y].Bmp_X = origem.Bmp_X)
      and (m_lad[x, y].Bmp_Y = origem.Bmp_Y)
      and (m_lad[x, y].H_Flip = origem.H_Flip)
      and (m_lad[x, y].V_Flip = origem.V_Flip)
      and (m_lad[x, y].Arquivo = origem.Arquivo) then
      begin
        m_lad[x, y].Iniciar(destino);
        m_lad[x, y].X := x * 32;
        m_lad[x, y].Y := y * 32;
      end;
    end;
  end;
  origem.Free;
end;

procedure CMapa.Limpar;
var
  x, y: integer;
  bmp: TBitmap;
  lad: TLadrilho;
begin
  bmp := TBitmap.Create;
  bmp.Width := 32;
  bmp.Height := 32;
  bmp.Canvas.Pixels[ 0, 0] := clSilver;
  bmp.Canvas.Pixels[31, 0] := clSilver;
  bmp.Canvas.Pixels[ 0,31] := clSilver;
  bmp.Canvas.Pixels[31,31] := clSilver;

  lad.bmp_x := 0;
  lad.bmp_y := 0;
  lad.h_flip := 0;
  lad.v_flip := 0;
  lad.arquivo := '';

  for x := 0 to m_largura do
  begin
    for y := 0 to m_altura do
    begin
      lad.x := x * 32;
      lad.y := y * 32;
      m_lad[x, y].Iniciar(lad, bmp, 0, 0);
    end;
  end;
  bmp.Free;
end;

function CMapa.GeTBitmap(x, y: integer): TBitmap;
begin
  Result := m_lad[x, y].Bitmap;
end;

function CMapa.GetTLadrilho(x, y: integer): TLadrilho;
begin
  Result := m_lad[x, y].GetLadrilho;
end;

end.
