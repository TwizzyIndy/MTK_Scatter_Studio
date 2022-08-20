//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Main.cpp", frmMain);
USEFORM("frmEditBlock.cpp", frmEdit);
USEFORM("AboutDlg.cpp", frmAbout);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
         Application->Initialize();
         Application->CreateForm(__classid(TfrmMain), &frmMain);
         Application->CreateForm(__classid(TfrmEdit), &frmEdit);
         Application->CreateForm(__classid(TfrmAbout), &frmAbout);
         Application->Run();
    }
    catch (Exception &exception)
    {
         //Application->ShowException(&exception);
         ShowMessage(exception.Message);
    }
    catch (...)
    {
         try
         {
             throw Exception("");
         }
         catch (Exception &exception)
         {
             //Application->ShowException(&exception);
             ShowMessage(exception.Message);
         }
    }
    return 0;
}
//---------------------------------------------------------------------------
