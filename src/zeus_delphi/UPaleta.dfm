object frmPaleta: TfrmPaleta
  Left = 596
  Top = 159
  Width = 129
  Height = 294
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSizeToolWin
  Caption = 'Paleta'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object imgLadrilhos: TImage
    Left = 4
    Top = 29
    Width = 96
    Height = 480
    OnMouseDown = imgLadrilhosMouseDown
  end
  object bvlLadrilhos: TShape
    Left = 56
    Top = 48
    Width = 34
    Height = 34
    Brush.Style = bsClear
    Enabled = False
    Pen.Color = clLime
    Visible = False
  end
  object btnAbrirLadrilhos: TSpeedButton
    Left = 78
    Top = 4
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
    OnClick = btnAbrirLadrilhosClick
  end
  object cboLadrilhos: TComboBox
    Left = 4
    Top = 4
    Width = 71
    Height = 22
    Style = csOwnerDrawFixed
    ItemHeight = 16
    TabOrder = 0
    OnChange = cboLadrilhosChange
    Items.Strings = (
      'fases\fase.bmp')
  end
  object dlgAbrirLadrilhos: TOpenPictureDialog
    Filter = 'Bitmaps (*.bmp)|*.bmp'
    Left = 12
    Top = 35
  end
  object popLadrilho: TPopupMenu
    Left = 48
    Top = 108
    object itmFlipVertical: TMenuItem
      Caption = 'Flip &Vertical'
      OnClick = itmFlipVerticalClick
    end
    object itmFlipHorizontal: TMenuItem
      Caption = 'Flip &Horizontal'
    end
  end
end
