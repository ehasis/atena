unit UObjeto;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Menus, StdCtrls, ExtCtrls, ComCtrls;

type
  CObjeto = class(TObject)
  private
//    m_tipo: integer;
//    m_x: integer;
//    m_y: integer;
//    m_bitmap: TBitmap;
  public
    constructor Create;
    destructor Destroy; override;
    procedure Desenhar(tela: TImage);

  end;

implementation

constructor CObjeto.Create;
begin

end;

destructor CObjeto.Destroy;
begin

end;

procedure CObjeto.Desenhar(tela: TImage);
begin

end;

end.
