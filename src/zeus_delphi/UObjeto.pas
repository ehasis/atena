unit UObjeto;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Menus, StdCtrls, ExtCtrls, ComCtrls;

type
  TObjeto = record
    tipo: integer;
    subtipo: integer;
    x: integer;
    y: integer;
    energia: integer;
    velocidade: integer;
    arquivo: array[0..255] of char;
  end;

type
  CObjeto = class(TObject)
  private
    m_tipo: integer;      //Atena: m_tipo_objeto
    m_subtipo: integer;   //Atena: m_tipo
    m_x: integer;
    m_y: integer;
    m_energia: integer;
    m_velocidade: integer;
    m_arquivo: string;
    
    m_nome: string;
    m_l: integer;
    m_a: integer;
    m_bmp: TBitmap;
  public
    constructor Create;
    destructor Destroy; override;

    property Tipo: integer read m_tipo write m_tipo;
    property SubTipo: integer read m_subtipo write m_subtipo;
    property X: integer read m_x write m_x;
    property Y: integer read m_y write m_y;
    property L: integer read m_l write m_l;
    property A: integer read m_a write m_a;
    property Energia: integer read m_energia write m_energia;
    property Velocidade: integer read m_velocidade write m_velocidade;
    property Arquivo: string read m_arquivo;// write SetArquivo;
    property Nome: string read m_nome write m_nome;
    property Bitmap: TBitmap read m_bmp write m_bmp;

    procedure Iniciar(const obj: CObjeto); overload;
    procedure Desenhar(tela: TImage; x_real, y_real: integer);
    procedure AbrirBitmap(arquivo: string);

    function GetTObjeto: TObjeto;
    function Colisao(x, y: integer): boolean;

  end;

implementation

constructor CObjeto.Create;
begin
  m_bmp := TBitmap.Create;
  m_bmp.Transparent := true;
  m_bmp.TransparentColor := clFuchsia;
end;

destructor CObjeto.Destroy;
begin
  m_bmp.Free;
end;

procedure CObjeto.Iniciar(const obj: CObjeto);
begin
  m_nome := obj.Nome;
  m_tipo := obj.Tipo;
  m_subtipo := obj.SubTipo;
  m_x := obj.X;
  m_y := obj.Y;
  m_energia := obj.Energia;
  m_velocidade := obj.Velocidade;
  AbrirBitmap(obj.Arquivo);
end;

procedure CObjeto.Desenhar(tela: TImage; x_real, y_real: integer);
begin
  if ((m_y + m_bmp.Height) < y_real) or (m_y > (y_real + 480)) then
    Exit;
  tela.Canvas.Draw(m_x - x_real, m_y - y_real, m_bmp);
end;

procedure CObjeto.AbrirBitmap(arquivo: string);
begin
  m_arquivo := arquivo;
  m_bmp.LoadFromFile(ExtractFilePath(Application.ExeName) + m_arquivo);
  m_l := m_bmp.Width;
  m_a := m_bmp.Height;
end;

function CObjeto.GetTObjeto: TObjeto;
var obj: TObjeto;
begin
  obj.tipo := m_tipo;
  obj.subtipo := m_subtipo;
  obj.x := m_x;
  obj.y := m_y;
  obj.energia := m_energia;
  obj.velocidade := m_velocidade;
  StrCopy(obj.arquivo, PChar(m_arquivo));
  result := obj;
end;

function CObjeto.Colisao(x, y: integer): boolean;
begin
  if (x < m_x) or (x > (m_x + m_l)) or (y < m_y) or (y > (m_y + m_l)) then
    result := false
  else
    result := true;
end;

end.
