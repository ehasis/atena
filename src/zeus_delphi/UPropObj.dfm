object frmPropObj: TfrmPropObj
  Left = 289
  Top = 130
  BorderStyle = bsDialog
  Caption = 'Propriedade'
  ClientHeight = 404
  ClientWidth = 406
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  DesignSize = (
    406
    404)
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 4
    Top = 4
    Width = 397
    Height = 364
    ActivePage = TabSheet1
    Anchors = [akLeft, akTop, akRight, akBottom]
    TabOrder = 3
    object TabSheet1: TTabSheet
      Caption = 'Geral'
      object btnAbrirBitmap: TSpeedButton
        Left = 360
        Top = 60
        Width = 23
        Height = 22
        Flat = True
        Glyph.Data = {
          F6000000424DF600000000000000760000002800000010000000100000000100
          04000000000080000000C40E0000C40E00001000000000000000000000000000
          8000008000000080800080000000800080008080000080808000C0C0C0000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDDDDD
          DDDD00000000000DDDDD003333333330DDDD0B03333333330DDD0FB033333333
          30DD0BFB03333333330D0FBFB000000000000BFBFBFBFB0DDDDD0FBFBFBFBF0D
          DDDD0BFB0000000DDDDDD000DDDDDDDD000DDDDDDDDDDDDDD00DDDDDDDDD0DDD
          0D0DDDDDDDDDD000DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD}
        OnClick = btnAbrirBitmapClick
      end
      object Bevel1: TBevel
        Left = 4
        Top = 128
        Width = 381
        Height = 17
        Shape = bsTopLine
      end
      object Label1: TLabel
        Left = 8
        Top = 148
        Width = 24
        Height = 13
        Caption = 'Tipo:'
      end
      object Label2: TLabel
        Left = 8
        Top = 176
        Width = 39
        Height = 13
        Caption = 'Subtipo:'
      end
      object Label3: TLabel
        Left = 8
        Top = 204
        Width = 10
        Height = 13
        Caption = 'X:'
      end
      object Label4: TLabel
        Left = 8
        Top = 232
        Width = 10
        Height = 13
        Caption = 'Y:'
      end
      object Label5: TLabel
        Left = 8
        Top = 260
        Width = 39
        Height = 13
        Caption = 'Energia:'
      end
      object Label6: TLabel
        Left = 8
        Top = 288
        Width = 56
        Height = 13
        Caption = 'Velocidade:'
      end
      object txtBitmap: TLabeledEdit
        Left = 124
        Top = 60
        Width = 233
        Height = 21
        EditLabel.Width = 40
        EditLabel.Height = 13
        EditLabel.Caption = 'Imagem:'
        ReadOnly = True
        TabOrder = 1
      end
      object panBitmap: TPanel
        Left = 4
        Top = 4
        Width = 113
        Height = 117
        BevelOuter = bvLowered
        TabOrder = 8
        object imgBitmap: TImage
          Left = 1
          Top = 1
          Width = 111
          Height = 115
          Align = alClient
          Center = True
          Transparent = True
        end
      end
      object cboTipo: TComboBox
        Left = 72
        Top = 144
        Width = 105
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 2
        Items.Strings = (
          'Aliens'
          'Ve'#237'culos'
          'Constru'#231#245'es'
          'Cen'#225'rio')
      end
      object mskSubTipo: TMaskEdit
        Left = 72
        Top = 172
        Width = 65
        Height = 21
        TabOrder = 3
      end
      object mskX: TMaskEdit
        Left = 72
        Top = 200
        Width = 65
        Height = 21
        TabOrder = 4
      end
      object mskY: TMaskEdit
        Left = 72
        Top = 228
        Width = 65
        Height = 21
        TabOrder = 5
      end
      object mskEnergia: TMaskEdit
        Left = 72
        Top = 256
        Width = 65
        Height = 21
        TabOrder = 6
      end
      object txtNome: TLabeledEdit
        Left = 124
        Top = 20
        Width = 137
        Height = 21
        EditLabel.Width = 31
        EditLabel.Height = 13
        EditLabel.Caption = 'Nome:'
        TabOrder = 0
      end
      object mskVelocidade: TMaskEdit
        Left = 72
        Top = 284
        Width = 65
        Height = 21
        TabOrder = 7
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Script'
      ImageIndex = 1
      object MemoScript: TMemo
        Left = 4
        Top = 44
        Width = 377
        Height = 285
        TabOrder = 0
      end
    end
  end
  object btnCancelar: TButton
    Left = 244
    Top = 375
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Cancel = True
    Caption = 'Cancelar'
    TabOrder = 1
    OnClick = btnCancelarClick
  end
  object btnOk: TButton
    Left = 164
    Top = 375
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = 'OK'
    Default = True
    TabOrder = 0
    OnClick = btnOkClick
  end
  object btnAplicar: TButton
    Left = 324
    Top = 375
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = 'Aplicar'
    TabOrder = 2
    OnClick = btnAplicarClick
  end
  object dlgAbrirBitmap: TOpenPictureDialog
    Left = 52
    Top = 80
  end
end
