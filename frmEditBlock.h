//---------------------------------------------------------------------------

#ifndef frmEditBlockH
#define frmEditBlockH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmEdit : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TLabel *Label8;
    TLabel *Label9;
    TLabel *Label10;
    TLabel *Label11;
    TLabel *Label12;
    TLabel *Label13;
    TLabel *Label14;
    TLabel *Label15;
    TLabel *Label16;
    TEdit *edtPartitionIndex;
    TEdit *edtPartitionName;
    TEdit *edtFileName;
    TEdit *edtIsDownloadable;
    TEdit *edtType;
    TEdit *edtLinearStartAddr;
    TEdit *edtPhysicalStartAddr;
    TEdit *edtPartitionSize;
    TEdit *edtRegion;
    TEdit *edtStorage;
    TEdit *edtBoundaryCheck;
    TEdit *edtIsReserved;
    TEdit *edtOperationType;
    TEdit *edtIsUpgradable;
    TEdit *edtEmptyBootNeeded;
    TEdit *edtReserve;
    TButton *btnSave;
    void __fastcall btnSaveClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmEdit(TComponent* Owner);

    int m_current_index;
    
    AnsiString m_partition_index;
    AnsiString m_partition_name;
    AnsiString m_file_name;
    AnsiString m_is_downloadable;
    AnsiString m_type;
    AnsiString m_linear_start;
    AnsiString m_physical_start;
    AnsiString m_partition_size;
    AnsiString m_region;
    AnsiString m_storage;
    AnsiString m_boundary_check;
    AnsiString m_is_reserved;
    AnsiString m_operation_type;
    AnsiString m_is_upgradable;
    AnsiString m_empty_boot_needed;
    AnsiString m_reserve;


};
//---------------------------------------------------------------------------
extern PACKAGE TfrmEdit *frmEdit;
//---------------------------------------------------------------------------
#endif
