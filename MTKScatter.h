//---------------------------------------------------------------------------

#ifndef MTKScatterH
#define MTKScatterH

#include <stdio.h>
#include <vcl.h>
#include "LayoutInfo.h"
#include "ScatterGeneralInfo.h"
#include <fstream.h>
#include <sstream.h>
#include <string.h>
/*
typedef struct GENERAL_INFO
{
    const char* strGeneralName;
    const char* strConfigVersion;
    const char* strPlatform;
    const char* strProject;
    const char* strStorage;
    const char* strBootChannel;
    unsigned __int64 ulBlockSize;

} GENERAL_INFO;
*/
/*
typedef struct LAYOUT_INFO
{
    int nPartitionIndex;
    const char* strPartitionName;
    const char* strFileName;
    bool bIsDownload;
    const char* strType;
    unsigned __int64 ulLinearStartAddr;
    unsigned __int64 ulPhysicalStartAddr;
    unsigned __int64 ulPartitionSize;
    const char* strRegion;
    const char* strStorage;
    bool bBoundaryCheck;
    bool bIsReserved;
    const char* strOperationType;
    unsigned __int64 ulReserved;
    
} LAYOUT_INFO;
*/

class MTKScatter
{

public:
    MTKScatter(const char* strInputFile);
    ~MTKScatter();

    int StartRead();

    const char* m_file;
    TList* m_list_partitions;
    GeneralInfo* general_info;
    int m_total_partitions;
    
};


extern MTKScatter mtkScatter;

//---------------------------------------------------------------------------
#endif
