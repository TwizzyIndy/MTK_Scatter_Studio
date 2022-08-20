//---------------------------------------------------------------------------


#pragma hdrstop

#include "LayoutInfo.h"
#include <vcl.h>


//---------------------------------------------------------------------------

#pragma package(smart_init)

LayoutInfo layoutInfo;

__fastcall LayoutInfo::LayoutInfo()
{
}

__fastcall LayoutInfo::LayoutInfo(const LayoutInfo& layoutInfo)
{
}

__fastcall LayoutInfo::~LayoutInfo()
{
}

LayoutInfo& LayoutInfo::operator=(const LayoutInfo& layoutInfo)
{
    this->nPartitionIndex = layoutInfo.nPartitionIndex;
    this->strPartitionName = layoutInfo.strPartitionName;
    this->strFileName = layoutInfo.strFileName;
    this->bIsDownload = layoutInfo.bIsDownload;
    this->strType = layoutInfo.strType;
    this->ulLinearStartAddr = layoutInfo.ulLinearStartAddr;
    this->ulPhysicalStartAddr = layoutInfo.ulPhysicalStartAddr;
    this->ulPartitionSize = layoutInfo.ulPartitionSize;
    this->strRegion = layoutInfo.strRegion;
    this->strStorage = layoutInfo.strStorage;
    this->bBoundaryCheck = layoutInfo.bBoundaryCheck;
    this->bIsReserved = layoutInfo.bIsReserved;
    this->strOperationType = layoutInfo.strOperationType;
    this->bIsUpgradable = layoutInfo.bIsUpgradable;
    this->bEmptyBootNeeded = layoutInfo.bEmptyBootNeeded;
    this->ulReserve = layoutInfo.ulReserve;

    return *this;
}
