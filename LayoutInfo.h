//---------------------------------------------------------------------------

#ifndef LayoutInfoH
#define LayoutInfoH

#include <vcl.h>

//---------------------------------------------------------------------------

struct LayoutInfo
{
    __fastcall LayoutInfo();
    __fastcall LayoutInfo(const LayoutInfo& layoutInfo);
    virtual __fastcall ~LayoutInfo();

    LayoutInfo& operator=(const LayoutInfo& layoutInfo);

    int nPartitionIndex;
    AnsiString strPartitionName;
    AnsiString strFileName;
    bool bIsDownload;
    AnsiString strType;
    unsigned __int64 ulLinearStartAddr;
    unsigned __int64 ulPhysicalStartAddr;
    unsigned __int64 ulPartitionSize;
    AnsiString strRegion;
    AnsiString strStorage;
    bool bBoundaryCheck;
    bool bIsReserved;
    AnsiString strOperationType;
    bool bIsUpgradable;
    bool bEmptyBootNeeded;
    unsigned __int64 ulReserve;    

};

#endif
