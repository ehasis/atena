unit UFundo;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Menus, StdCtrls, ExtCtrls, ComCtrls;

type
  TLadrilho = record
    x: integer;
    y: integer;
    bmp_x: integer;
    bmp_y: integer;
    h_flip: boolean;
    v_flip: boolean;
    arquivo: string;
  end;

type
  CLadrilho = class
  private
    m_x: integer;
    m_y: integer;
    m_bmp_x: integer;
    m_bmp_y: integer;
    m_h_flip: boolean;
    m_v_flip: boolean;
    m_arquivo: string;
    m_bmp: TBitmap;
  public
    constructor Create;
    destructor Destroy; override;
    procedure Iniciar(lad: TLadrilho; bmp: TBitmap; bmp_x, bmp_y: integer);
    procedure Desenhar(tela: TImage; x_real, y_real: integer);

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
//    m_bitmap: TBitmap;

  public
    constructor Create(largura, altura, largura_visivel, altura_visivel: integer);
    destructor Destroy; override;

    procedure Desenhar(tela: TImage; x_real, y_real: integer);
    procedure SetLadrilho(x, y: integer; lad: TLadrilho; bmp: TBitmap; bmp_x, bmp_y: integer);

    function GetLadrilho(x, y: integer): TLadrilho;
    function GetBitmap(x, y: integer): TBitmap;

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
procedure CLadrilho.Iniciar(lad: TLadrilho; bmp: TBitmap; bmp_x, bmp_y: integer);
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
  m_bmp.Canvas.BrushCopy(Destino, bmp, Origem, clBlack);

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
  lad.arquivo := m_arquivo;

  Result := lad;

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

  m_largura := largura - 1;
  m_altura := altura - 1;


  m_largura_visivel := largura_visivel - 1;
  m_altura_visivel := altura_visivel - 1;

  lad.h_flip := false;
  lad.v_flip := false;
  lad.arquivo := '';
  lad.bmp_x := 0;
  lad.bmp_y := 0;

  SetLength(m_lad, largura);
  for x := 0 to m_largura do
    for y := 0 to m_altura do
    begin
      SetLength(m_lad[x], altura);
      lad.x := x * 32;
      lad.y := y * 32;
      m_lad[x][y] := CLadrilho.Create;
      m_lad[x][y].Iniciar(lad, bmp, 0, 0);
    end;

  bmp.Free;
end;

destructor CMapa.Destroy;
var x, y: integer;
begin
  for x := 0 to m_largura do
    for y := 0 to m_altura do
      m_lad[x][y].Free;
  inherited Destroy;
end;

//------------------------------------------------------------------------------
procedure CMapa.Desenhar(tela: TImage; x_real, y_real: integer);
var x, y: integer;
begin
  for x := x_real to (x_real + m_largura_visivel) do
    for y := y_real to (y_real + m_altura_visivel) do
      m_lad[x][y].Desenhar(tela, x_real, y_real);
end;

//------------------------------------------------------------------------------
procedure CMapa.SetLadrilho(x, y: integer; lad: TLadrilho; bmp: TBitmap; bmp_x, bmp_y: integer);
begin
  m_lad[x][y].Iniciar(lad, bmp, bmp_x, bmp_y);
end;

function CMapa.GetBitmap(x, y: integer): TBitmap;
begin
  Result := m_lad[x][y].Bitmap;
end;

function CMapa.GetLadrilho(x, y: integer): TLadrilho;
begin
  Result := m_lad[x][y].GetLadrilho;
end;

end.
