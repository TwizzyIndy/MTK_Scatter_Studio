//---------------------------------------------------------------------------


#pragma hdrstop

#include "ScatterGeneralInfo.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

GeneralInfo generalInfo;

__fastcall GeneralInfo::GeneralInfo()
{
}

__fastcall GeneralInfo::GeneralInfo(const GeneralInfo& generalInfo)
{
}

__fastcall GeneralInfo::~GeneralInfo()
{
}

GeneralInfo& GeneralInfo::operator=(const GeneralInfo& generalInfo)
{
    this->strGeneralName = generalInfo.strGeneralName;
    this->strConfigVersion = generalInfo.strConfigVersion;
    this->strPlatform = generalInfo.strPlatform;
    this->strProject = generalInfo.strProject;
    this->strStorage = generalInfo.strStorage;
    this->strBootChannel = generalInfo.strBootChannel;
    this->ulBlockSize = generalInfo.ulBlockSize;
    
    return *this;
}
