object frmZeus: TfrmZeus
  Left = 200
  Top = 110
  Width = 549
  Height = 425
  VertScrollBar.Position = 171
  Caption = 'Zeus 2.0 Turbo'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MenuPrincipal
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 589
    Top = 329
    Width = 32
    Height = 13
    Caption = 'Label1'
  end
  object Label2: TLabel
    Left = 629
    Top = 329
    Width = 32
    Height = 13
    Caption = 'Label2'
  end
  object pagObjetos: TPageControl
    Left = 0
    Top = -171
    Width = 109
    Height = 534
    ActivePage = tabLadrilhos
    TabHeight = 16
    TabOrder = 0
    object tabLadrilhos: TTabSheet
      Caption = 'Fundo'
      object imgLadrilhos: TImage
        Left = 0
        Top = 24
        Width = 96
        Height = 480
        OnMouseDown = imgLadrilhosMouseDown
      end
      object cboLadrilhos: TComboBox
        Left = 0
        Top = 0
        Width = 73
        Height = 22
        Style = csOwnerDrawFixed
        ItemHeight = 16
        TabOrder = 0
        OnChange = cboLadrilhosChange
        Items.Strings = (
          'fundo.bmp')
      end
      object btnAbrirLadrilhos: TButton
        Left = 76
        Top = 0
        Width = 23
        Height = 21
        Caption = '...'
        TabOrder = 1
        OnClick = btnAbrirLadrilhosClick
      end
    end
    object tabAliens: TTabSheet
      Caption = 'Aliens'
      ImageIndex = 1
    end
    object tabVeiculos: TTabSheet
      Caption = 'Veiculos'
      ImageIndex = 2
    end
    object tabConstrucoes: TTabSheet
      Caption = 'Constru'#231#245'es'
      ImageIndex = 3
    end
  end
  object Panel1: TPanel
    Left = 112
    Top = -171
    Width = 558
    Height = 493
    BevelOuter = bvNone
    BorderStyle = bsSingle
    Color = clAppWorkSpace
    TabOrder = 1
    object imgTela: TImage
      Left = 4
      Top = 4
      Width = 544
      Height = 480
      OnMouseMove = imgTelaMouseMove
      OnMouseUp = imgTelaMouseUp
    end
  end
  object sbTelaY: TScrollBar
    Left = 668
    Top = -171
    Width = 16
    Height = 492
    Kind = sbVertical
    LargeChange = 4
    Max = 15
    PageSize = 2
    Position = 15
    TabOrder = 2
    OnChange = sbTelaYChange
  end
  object Panel2: TPanel
    Left = 112
    Top = 324
    Width = 77
    Height = 39
    BevelOuter = bvNone
    BorderStyle = bsSingle
    Color = clAppWorkSpace
    TabOrder = 3
    object imgPincelEsq: TImage
      Left = 1
      Top = 1
      Width = 32
      Height = 32
    end
    object imgPincelDir: TImage
      Left = 37
      Top = 1
      Width = 32
      Height = 32
    end
  end
  object Memo1: TMemo
    Left = 192
    Top = 324
    Width = 376
    Height = 37
    Lines.Strings = (
      'Memo1')
    TabOrder = 4
  end
  object MenuPrincipal: TMainMenu
    Left = 123
    Top = 11
    object mnuArquivo: TMenuItem
      Caption = '&Arquivo'
      object itmNovo: TMenuItem
        Caption = '&Novo'
        OnClick = itmNovoClick
      end
      object itmAbrir: TMenuItem
        Caption = '&Abrir'
        OnClick = itmAbrirClick
      end
      object itmSalvar: TMenuItem
        Caption = '&Salvar'
        OnClick = itmSalvarClick
      end
      object itmFechar: TMenuItem
        Caption = '&Fechar'
        OnClick = itmFecharClick
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object itmSair: TMenuItem
        Caption = 'Sai&r'
        OnClick = itmSairClick
      end
    end
    object mnuEditar: TMenuItem
      Caption = '&Editar'
      object itmPreencherLadrilhos: TMenuItem
        Caption = 'Preencher Ladrilhos'
        OnClick = itmPreencherLadrilhosClick
      end
    end
  end
  object dlgAbrirLadrilhos: TOpenPictureDialog
    Filter = 'Bitmaps (*.bmp)|*.bmp'
    Left = 156
    Top = 11
  end
  object dlgAbrirMapa: TOpenDialog
    Filter = 'Mapa do Atena (*.map)|*.map'
    Left = 188
    Top = 12
  end
  object dlgSalvarMapa: TSaveDialog
    Filter = 'Mapa do Atena (*.map)|*.map'
    Left = 220
    Top = 12
  end
end
