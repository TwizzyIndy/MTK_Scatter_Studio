//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include "sSkinManager.hpp"
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>

#include "MTKScatter.h"
#include "sSkinProvider.hpp"
#include <NMSTRM.hpp>
#include <Psock.hpp>

//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
    TMainMenu *MainMenu1;
    TMenuItem *menuFile;
    TMenuItem *menuHelp;
    TMenuItem *menuOpen;
    TMenuItem *menuSave;
    TMenuItem *menuExit;
    TMenuItem *menuAbout;
    TLabel *Label1;
    TLabel *Label2;
    TGroupBox *grpInfo;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TListView *lstLayoutSetting;
    TsSkinManager *sSkinManager1;
    TOpenDialog *OpenScatter;
    TPanel *Panel1;
    TEdit *edt_General;
    TEdit *edt_ConfigVer;
    TEdit *edt_BootChannel;
    TEdit *edt_Storage;
    TEdit *edt_Platform;
    TEdit *edt_BlockSize;
    TLabel *Label6;
    TStatusBar *StatusBar;
    TEdit *edt_Project;
    TLabel *Label7;
    TSaveDialog *SaveDialog;
    TMenuItem *menuSaveas;
    void __fastcall FormResize(TObject *Sender);
    void __fastcall menuExitClick(TObject *Sender);
    void __fastcall menuOpenClick(TObject *Sender);
    void __fastcall lstLayoutSettingDblClick(TObject *Sender);
    void __fastcall menuSaveClick(TObject *Sender);
    void __fastcall edt_GeneralChange(TObject *Sender);
    void __fastcall edt_ConfigVerChange(TObject *Sender);
    void __fastcall edt_BootChannelChange(TObject *Sender);
    void __fastcall edt_StorageChange(TObject *Sender);
    void __fastcall edt_PlatformChange(TObject *Sender);
    void __fastcall edt_BlockSizeChange(TObject *Sender);
    void __fastcall menuAboutClick(TObject *Sender);
    void __fastcall menuSaveasClick(TObject *Sender);
private:	// User declarations

public:		// User declarations
    __fastcall TfrmMain(TComponent* Owner);

    MTKScatter* m_mtk_scatter;

    bool m_is_edited;
    
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
