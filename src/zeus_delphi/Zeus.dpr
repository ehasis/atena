program Zeus;

uses
  Forms,
  UZeus in 'UZeus.pas' {frmZeus},
  UMapa in 'UMapa.pas',
  UObjeto in 'UObjeto.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TfrmZeus, frmZeus);
  Application.Run;
end.
