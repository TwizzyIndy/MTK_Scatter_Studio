object frmEdit: TfrmEdit
  Left = 259
  Top = 250
  BorderStyle = bsToolWindow
  Caption = 'Edit'
  ClientHeight = 260
  ClientWidth = 534
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 46
    Top = 32
    Width = 67
    Height = 13
    Alignment = taRightJustify
    Caption = 'PartitionIndex:'
  end
  object Label2: TLabel
    Left = 44
    Top = 56
    Width = 69
    Height = 13
    Alignment = taRightJustify
    Caption = 'PartitionName:'
  end
  object Label3: TLabel
    Left = 66
    Top = 80
    Width = 47
    Height = 13
    Alignment = taRightJustify
    Caption = 'FileName:'
  end
  object Label4: TLabel
    Left = 34
    Top = 104
    Width = 79
    Height = 13
    Alignment = taRightJustify
    Caption = 'IsDownloadable:'
  end
  object Label5: TLabel
    Left = 86
    Top = 128
    Width = 27
    Height = 13
    Alignment = taRightJustify
    Caption = 'Type:'
  end
  object Label6: TLabel
    Left = 21
    Top = 152
    Width = 92
    Height = 13
    Alignment = taRightJustify
    Caption = 'LinearStartAddress:'
  end
  object Label7: TLabel
    Left = 8
    Top = 176
    Width = 102
    Height = 13
    Alignment = taRightJustify
    Caption = 'PhysicalStartAddress:'
  end
  object Label8: TLabel
    Left = 52
    Top = 200
    Width = 61
    Height = 13
    Alignment = taRightJustify
    Caption = 'PartitionSize:'
  end
  object Label9: TLabel
    Left = 356
    Top = 32
    Width = 37
    Height = 13
    Alignment = taRightJustify
    Caption = 'Region:'
  end
  object Label10: TLabel
    Left = 353
    Top = 56
    Width = 40
    Height = 13
    Alignment = taRightJustify
    Caption = 'Storage:'
  end
  object Label11: TLabel
    Left = 314
    Top = 80
    Width = 79
    Height = 13
    Alignment = taRightJustify
    Caption = 'BoundaryCheck:'
  end
  object Label12: TLabel
    Left = 336
    Top = 104
    Width = 57
    Height = 13
    Alignment = taRightJustify
    Caption = 'IsReserved:'
  end
  object Label13: TLabel
    Left = 320
    Top = 128
    Width = 73
    Height = 13
    Alignment = taRightJustify
    Caption = 'OperationType:'
  end
  object Label14: TLabel
    Left = 327
    Top = 152
    Width = 66
    Height = 13
    Alignment = taRightJustify
    Caption = 'IsUpgradable:'
  end
  object Label15: TLabel
    Left = 301
    Top = 176
    Width = 92
    Height = 13
    Alignment = taRightJustify
    Caption = 'EmptyBootNeeded:'
  end
  object Label16: TLabel
    Left = 350
    Top = 200
    Width = 43
    Height = 13
    Alignment = taRightJustify
    Caption = 'Reserve:'
  end
  object edtPartitionIndex: TEdit
    Left = 123
    Top = 29
    Width = 121
    Height = 21
    ReadOnly = True
    TabOrder = 0
  end
  object edtPartitionName: TEdit
    Left = 123
    Top = 53
    Width = 121
    Height = 21
    TabOrder = 1
  end
  object edtFileName: TEdit
    Left = 123
    Top = 77
    Width = 121
    Height = 21
    TabOrder = 2
  end
  object edtIsDownloadable: TEdit
    Left = 123
    Top = 101
    Width = 121
    Height = 21
    TabOrder = 3
  end
  object edtType: TEdit
    Left = 123
    Top = 125
    Width = 121
    Height = 21
    TabOrder = 4
  end
  object edtLinearStartAddr: TEdit
    Left = 123
    Top = 149
    Width = 121
    Height = 21
    TabOrder = 5
  end
  object edtPhysicalStartAddr: TEdit
    Left = 123
    Top = 173
    Width = 121
    Height = 21
    TabOrder = 6
  end
  object edtPartitionSize: TEdit
    Left = 123
    Top = 197
    Width = 121
    Height = 21
    TabOrder = 7
  end
  object edtRegion: TEdit
    Left = 403
    Top = 29
    Width = 121
    Height = 21
    TabOrder = 8
  end
  object edtStorage: TEdit
    Left = 403
    Top = 53
    Width = 121
    Height = 21
    TabOrder = 9
  end
  object edtBoundaryCheck: TEdit
    Left = 403
    Top = 77
    Width = 121
    Height = 21
    TabOrder = 10
  end
  object edtIsReserved: TEdit
    Left = 403
    Top = 101
    Width = 121
    Height = 21
    TabOrder = 11
  end
  object edtOperationType: TEdit
    Left = 403
    Top = 125
    Width = 121
    Height = 21
    TabOrder = 12
  end
  object edtIsUpgradable: TEdit
    Left = 403
    Top = 149
    Width = 121
    Height = 21
    TabOrder = 13
  end
  object edtEmptyBootNeeded: TEdit
    Left = 403
    Top = 173
    Width = 121
    Height = 21
    TabOrder = 14
  end
  object edtReserve: TEdit
    Left = 403
    Top = 197
    Width = 121
    Height = 21
    TabOrder = 15
  end
  object btnSave: TButton
    Left = 448
    Top = 232
    Width = 75
    Height = 25
    Caption = 'Save'
    TabOrder = 16
    OnClick = btnSaveClick
  end
end
