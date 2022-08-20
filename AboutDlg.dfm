object frmAbout: TfrmAbout
  Left = 241
  Top = 147
  BorderStyle = bsToolWindow
  Caption = 'About'
  ClientHeight = 126
  ClientWidth = 356
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnClick = FormClick
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 104
    Top = 24
    Width = 144
    Height = 15
    Caption = 'MTK Scatter Studio'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Fixedsys'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 8
    Top = 72
    Width = 344
    Height = 15
    Caption = 'Developed by TwizzyIndy [ Lockify Myanmar ]'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Fixedsys'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 152
    Top = 48
    Width = 32
    Height = 15
    Caption = 'V1.0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Fixedsys'
    Font.Style = []
    ParentFont = False
  end
  object Label4: TLabel
    Left = 100
    Top = 96
    Width = 164
    Height = 14
    Cursor = crHandPoint
    Caption = 'https://twitter.com/TwizzyIndy'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -11
    Font.Name = 'Arial'
    Font.Style = [fsBold, fsUnderline]
    ParentFont = False
    OnClick = Label4Click
  end
end
