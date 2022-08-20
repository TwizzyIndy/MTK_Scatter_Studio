//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmEditBlock.h"
#include "Main.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmEdit *frmEdit;

//---------------------------------------------------------------------------
__fastcall TfrmEdit::TfrmEdit(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmEdit::btnSaveClick(TObject *Sender)
{
    TListItem * item = frmMain->lstLayoutSetting->Items->operator [](this->m_current_index);


    item->Caption = edtPartitionIndex->Text;

    item->SubItems->Strings[0] = edtPartitionName->Text;
    item->SubItems->Strings[1] = edtFileName->Text;
    item->SubItems->Strings[2] = edtIsDownloadable->Text;
    item->SubItems->Strings[3] = edtType->Text;
    item->SubItems->Strings[4] = edtLinearStartAddr->Text;
    item->SubItems->Strings[5] = edtPhysicalStartAddr->Text;
    item->SubItems->Strings[6] = edtPartitionSize->Text;
    item->SubItems->Strings[7] = edtRegion->Text;
    item->SubItems->Strings[8] = edtStorage->Text;
    item->SubItems->Strings[9] = edtBoundaryCheck->Text;
    item->SubItems->Strings[10] = edtIsReserved->Text;
    item->SubItems->Strings[11] = edtOperationType->Text;
    item->SubItems->Strings[12] = edtIsUpgradable->Text;
    item->SubItems->Strings[13] = edtEmptyBootNeeded->Text;
    item->SubItems->Strings[14] = edtReserve->Text;

    frmMain->lstLayoutSetting->Update();
    this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEdit::FormShow(TObject *Sender)
{
    this->m_current_index = StrToInt(m_partition_index);
    this->Caption = "Edit - " + m_partition_name;

    edtPartitionIndex->Text = m_partition_index;
    edtPartitionName->Text = m_partition_name;
    edtFileName->Text = m_file_name;
    edtIsDownloadable->Text = m_is_downloadable;
    edtType->Text = m_type;
    edtLinearStartAddr->Text = m_linear_start;
    edtPhysicalStartAddr->Text = m_physical_start;
    edtPartitionSize->Text = m_partition_size;
    edtRegion->Text = m_region;
    edtStorage->Text = m_storage;
    edtBoundaryCheck->Text = m_boundary_check;
    edtIsReserved->Text = m_is_reserved;
    edtOperationType->Text = m_operation_type;
    edtIsUpgradable->Text = m_is_upgradable;
    edtEmptyBootNeeded->Text = m_empty_boot_needed;
    edtReserve->Text = m_reserve;
}
//---------------------------------------------------------------------------
