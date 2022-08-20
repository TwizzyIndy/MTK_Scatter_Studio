//---------------------------------------------------------------------------

#ifndef ScatterGeneralInfoH
#define ScatterGeneralInfoH

#include <vcl.h>
//---------------------------------------------------------------------------

struct GeneralInfo
{
    __fastcall GeneralInfo();
    __fastcall GeneralInfo(const GeneralInfo& generalInfo);
    virtual __fastcall ~GeneralInfo();

    GeneralInfo& operator=(const GeneralInfo& generalInfo);
    
    AnsiString strGeneralName;
    AnsiString strConfigVersion;
    AnsiString strPlatform;
    AnsiString strProject;
    AnsiString strStorage;
    AnsiString strBootChannel;
    unsigned __int64 ulBlockSize;

};

#endif
