program Zeus;

uses
  Forms,
  UZeus in 'UZeus.pas' {frmZeus},
  UMapa in 'UMapa.pas',
  UObjeto in 'UObjeto.pas',
  UPaleta in 'UPaleta.pas' {frmPaleta},
  UPropObj in 'UPropObj.pas' {frmPropObj},
  UAbertura in 'UAbertura.pas' {frmAbertura};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TfrmZeus, frmZeus);
  Application.CreateForm(TfrmAbertura, frmAbertura);
  Application.CreateForm(TfrmPaleta, frmPaleta);
  Application.CreateForm(TfrmPropObj, frmPropObj);
  Application.Run;
end.
