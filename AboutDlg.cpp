//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AboutDlg.h"
//#include <Vcl\ExtActns.hpp>
#include <windows.h>
#include <tchar.h>
#include <urlmon.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmAbout *frmAbout;
//---------------------------------------------------------------------------
__fastcall TfrmAbout::TfrmAbout(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmAbout::FormClick(TObject *Sender)
{
    Close();    
}
//---------------------------------------------------------------------------
void __fastcall TfrmAbout::Label4Click(TObject *Sender)
{
    //ShellExecute(NULL, "open", "https://twitter.com/TwizzyIndy", NULL
    //            , NULL, SW_SHOWNORMAL );

    system("start https://twitter.com/TwizzyIndy");
    

}
//---------------------------------------------------------------------------
