//---------------------------------------------------------------------------


#pragma hdrstop

#include "MTKScatter.h"



//---------------------------------------------------------------------------

#pragma package(smart_init)


MTKScatter::MTKScatter(const char* strInputFile)
{
    this->m_file = strInputFile;

    // list
    this->m_list_partitions = new TList;

    //int result = StartRead();
    
}

MTKScatter::~MTKScatter()
{
    delete m_list_partitions;
    m_list_partitions = NULL;
}


int MTKScatter::StartRead()
{
    std::string line;

    // i just know more about stdio :3
    // =============================
    // ===== header check ==========
    // =============================
    FILE* fp = fopen(m_file, "r");
    if(fp == NULL)
        return 1;

    fseek(fp, 0, SEEK_END);
    long lSize = ftell(fp);
    rewind(fp);

    char header[107];
    char* strHeader = "############################################################################################################";

    fread(&header, sizeof(header), 1, fp);
    if(memcmp( header, strHeader, sizeof(header)) != 0)
    {
        
        MessageDlg( "Unsupported or invalid scatter.", mtError, TMsgDlgButtons() << mbOK, 0);
        fclose(fp);
        return 1;
    }
    // ===== header check ==========

    std::ifstream infile(m_file);
    if(!infile.is_open() )
    {
        return 1;
    }
    
    // =============================
    // vars for general infos
    // =============================
    
    std::string strGeneralName;
    std::string strConfigVersion;
    std::string strPlatform;
    std::string strProject;

    std::string strStorage;   // ******
    bool bGeneralInfoStorageAdded = false;

    std::string strBootChannel;
    std::string strBlockSize;
    unsigned __int64 ulBlockSize;

    //GENERAL_INFO general_info;
    this->general_info = new GeneralInfo;

    // =============================
    // vars for layout setting infos
    // =============================
    //int nCurrentPartitionIndex = 0;
    std::string strPartitionIndex;
    int nScatterPartitionIndex;
    this->m_total_partitions = 0;

    std::string strPartitionName;
    std::string strFileName;
    std::string strIsDownload;
    std::string strType;

    std::string strLinearStartAddr;
    unsigned __int64 ulLinearStartAddr;

    std::string strPhysicalStartAddr;
    unsigned __int64 ulPhysicalStartAddr;

    std::string strPartitionSize;
    unsigned __int64 ulPartitionSize;

    std::string strRegion;
    std::string strPartStorage;   // ******* partition storage
    std::string strBoundaryCheck;
    std::string strIsReserved;
    std::string strOperationType;
    std::string strIsUpgradable;
    std::string strEmptyBootNeeded;

    std::string strReserve;
    unsigned __int64 ulReserve;

    LayoutInfo* layout_info = new LayoutInfo;

    while (std::getline(infile, line))
    {
        //std::istringstream iss(line);
        //int a,b;

        //if(!(iss >> a >> b))
        //    break;
        
        // starts parse General Info

        unsigned int pos = line.find("general:");
        if( pos == std::string::npos )
        {
            
        } else
        {
            strGeneralName = line.substr(pos + 8 + 1, 30);
            general_info->strGeneralName = AnsiString(strGeneralName.c_str());

        }

        // config_version
        pos = line.find("config_version:");


        if( pos == std::string::npos)
        {
        } else
        {
            strConfigVersion = line.substr(pos + 15 + 1, 8);
            general_info->strConfigVersion = AnsiString(strConfigVersion.c_str());
        }

        // platform
        pos = line.find("platform:");

        if( pos == std::string::npos )
        {
        } else
        {
            strPlatform = line.substr(pos + 9 + 1, 8);
            general_info->strPlatform = AnsiString(strPlatform.c_str());
        }

        // project
        pos = line.find("project:");

        if(pos == std::string::npos)
        {
        } else
        {
            strProject = line.substr(pos + 8 + 1, 30);
            general_info->strProject = AnsiString(strProject.c_str());
        }

        // storage ** general_info


        pos = line.find("storage:");

        if( pos == std::string::npos || bGeneralInfoStorageAdded)
        {
        } else
        {
            strStorage = line.substr(pos + 8 + 1, 20);
            general_info->strStorage = AnsiString(strStorage.c_str());
            bGeneralInfoStorageAdded = true;

        }

        // boot_channel
        pos = line.find("boot_channel:");

        if( pos == std::string::npos )
        {
        } else
        {
            strBootChannel = line.substr(pos + 13 + 1, 10);
            general_info->strBootChannel = AnsiString(strBootChannel.c_str());
        }

        // block size
        pos = line.find("block_size:");

        if( pos == std::string::npos )
        {
        } else
        {
            std::string x = line.substr(pos + 11 + 1, 18);
            //unsigned long ul = strtoul( x.c_str(), NULL, 16);
            ulBlockSize = (unsigned __int64) StrToInt64(AnsiString(x.c_str()));
            general_info->ulBlockSize = ulBlockSize;

        }

        // starts parse Layout Setting

        // partition_index
        pos = line.find("partition_index:");
        if( pos == std::string::npos )
        {
        } else
        {
            //std::string sys = line.substr(pos + 16 + 1, 4);
            unsigned int nSysPos = line.find("SYS");
            if ( nSysPos != std::string::npos )
            {
                std::string strNum = line.substr(nSysPos +3 , 3);
                nScatterPartitionIndex = atoi(strNum.c_str());
                layout_info->nPartitionIndex = nScatterPartitionIndex;

                // continue next line ..
                std::string linePartName;
                std::string lineFileName;
                std::string lineIsDownload;
                std::string lineType;
                std::string lineLinearStartAddr;
                std::string linePhyAddr;
                std::string linePartSize;
                std::string lineRegion;
                std::string lineStorage;
                std::string lineBoundCheck;
                std::string lineIsRes;
                std::string lineOptType;
                std::string lineIsUpgrade;
                std::string lineEmptyBoot;
                std::string lineReserve;


                
                // partition_name
                std::getline(infile, linePartName);

                pos = linePartName.find("partition_name:");
                if( pos == std::string::npos )
                {
                } else
                {
                    m_total_partitions += 1;
                    strPartitionName = linePartName.substr(pos + 15 +1, 40);
                    layout_info->strPartitionName = AnsiString(strPartitionName.c_str());
                }
                // ----

                // file_name
                std::getline(infile, lineFileName);
                pos = lineFileName.find("file_name:");
                if( pos == std::string::npos )
                {
                } else
                {
                    
                    strFileName = lineFileName.substr(pos + 10 +1, 40);
                    layout_info->strFileName = AnsiString(strFileName.c_str());
                }
                // ----
                // is_download
                std::getline(infile, lineIsDownload);
                
                pos = lineIsDownload.find("is_download:");
                if( pos == std::string::npos )
                {
                } else
                {
                    
                    strIsDownload = lineIsDownload.substr(pos + 12 +1, 6);
                    if( strIsDownload.compare("true") == 0 )
                    {
                        layout_info->bIsDownload = true;
                    } else
                    {
                        layout_info->bIsDownload = false;
                    }
                }
                // --------

                // type
                std::getline(infile, lineType);
                pos = lineType.find("type:");
                if( pos == std::string::npos )
                {
                } else
                {
                    
                    strType = lineType.substr(pos + 5 +1, 20);
                    layout_info->strType = AnsiString(strType.c_str());
                }
                // -------
                

                // linear_start_addr
                std::getline(infile, lineLinearStartAddr);
                pos = lineLinearStartAddr.find("linear_start_addr:");

                if( pos == std::string::npos )
                {
                } else
                {
                    
                    std::string x = lineLinearStartAddr.substr(pos + 18 + 1, 16);

                    ulLinearStartAddr = (unsigned __int64) StrToInt64(AnsiString(x.c_str()));
                    layout_info->ulLinearStartAddr = ulLinearStartAddr;
                }

                // -------


                // physical_start_addr
                std::getline(infile, linePhyAddr);
                pos = linePhyAddr.find("physical_start_addr:");

                if( pos == std::string::npos )
                {
                } else
                {
                    
                    std::string x = linePhyAddr.substr(pos + 20 + 1, 16);

                    ulPhysicalStartAddr = (unsigned __int64) StrToInt64(AnsiString(x.c_str()));
                    layout_info->ulPhysicalStartAddr = ulPhysicalStartAddr;
                }

                // ------

                // partition_size
                std::getline(infile, linePartSize);
                pos = linePartSize.find("partition_size:");

                if( pos == std::string::npos )
                {
                } else
                {
                    
                    std::string x = linePartSize.substr(pos + 15 + 1, 16);

                    ulPartitionSize = (unsigned __int64) StrToInt64(AnsiString(x.c_str()));
                    layout_info->ulPartitionSize = ulPartitionSize;
                }

                // ------------                

                // region
                std::getline(infile, lineRegion);
                pos = lineRegion.find("region:");
                if( pos == std::string::npos )
                {
                } else
                {
                    strRegion = lineRegion.substr(pos + 7 +1, 18);
                    layout_info->strRegion = AnsiString(strRegion.c_str());
                }
                // ----------

                // storage **** parition storage
                std::getline(infile, lineStorage);
                pos = lineStorage.find("storage:");
                if( pos == std::string::npos )
                {
                } else
                {
                    strPartStorage = lineStorage.substr(pos + 8 +1, 20);
                    layout_info->strStorage = AnsiString(strPartStorage.c_str());
                }
                // ------------

                // boundary_check
                std::getline(infile, lineBoundCheck);
                pos = lineBoundCheck.find("boundary_check:");
                if( pos == std::string::npos )
                {
                } else
                {
                    strBoundaryCheck = lineBoundCheck.substr(pos + 15 +1, 6);
                    if( strBoundaryCheck.compare("true") == 0 )
                    {
                        layout_info->bBoundaryCheck = true;
                    } else
                    {
                        layout_info->bBoundaryCheck = false;
                    }
                }
                // --------------

                // is_reserved
                std::getline(infile, lineIsRes);
                pos = lineIsRes.find("is_reserved:");
                if( pos == std::string::npos )
                {
                } else
                {
                    strIsReserved = lineIsRes.substr(pos + 12 +1, 6);
                    if( strIsReserved.compare("true") == 0 )
                    {
                        layout_info->bIsReserved = true;
                    } else
                    {
                        layout_info->bIsReserved = false;
                    }
                }
                // -------------

                // operation_type
                std::getline(infile, lineOptType);
                pos = lineOptType.find("operation_type:");
                if( pos == std::string::npos )
                {
                } else
                {
                    strOperationType = lineOptType.substr(pos + 15 +1, 15);
                    layout_info->strOperationType = AnsiString(strOperationType.c_str());
                }
                // -------
                // *************************
                // for MT6797 only -- is_upgradable, empty_boot_needed
                // *************************
                if(this->general_info->strPlatform.AnsiCompareIC("MT6797") == 0)
                {
                    // is_upgradable
                    std::getline(infile, lineIsUpgrade);
                    pos = lineIsUpgrade.find("is_upgradable:");
                    if( pos == std::string::npos )
                    {
                    } else
                    {
                        strIsUpgradable = lineIsUpgrade.substr(pos + 14 +1, 6);
                        if( strIsUpgradable.compare("true") == 0 )
                        {
                            layout_info->bIsUpgradable = true;
                        } else
                        {
                            layout_info->bIsUpgradable = false;
                        }
                    }
                    // ------
                    // empty_boot_needed

                    std::getline(infile, lineEmptyBoot);
                    pos = lineEmptyBoot.find("empty_boot_needed:");
                    if( pos == std::string::npos )
                    {
                    } else
                    {
                        strEmptyBootNeeded = lineEmptyBoot.substr(pos + 18 +1, 6);
                        if( strEmptyBootNeeded.compare("true") == 0 )
                        {
                            layout_info->bEmptyBootNeeded = true;
                        } else
                        {
                            layout_info->bEmptyBootNeeded = false;
                        }
                    }
                }
                // -------

                // reserve
                std::getline(infile, lineReserve);
                pos = lineReserve.find("reserve:");

                if( pos == std::string::npos )
                {
                } else
                {
                    std::string x = lineReserve.substr(pos + 8 + 1, 16);

                    ulReserve = (unsigned __int64) StrToInt64(AnsiString(x.c_str()));
                    layout_info->ulReserve = ulReserve;

                    //this->m_list_partitions->Add(layout_info);
                    this->m_list_partitions->Insert(layout_info->nPartitionIndex, layout_info);
                    layout_info = new LayoutInfo;
                }
            }
        }


    }

    infile.close();
    return 0;
}

/*

    
        // starts parse Layout Setting

        // partition_index
        pos = line.find("partition_index:");
        if( pos == std::string::npos )
        {
        } else
        {
            //std::string sys = line.substr(pos + 16 + 1, 4);
            unsigned int nSysPos = line.find("SYS");
            if ( nSysPos != std::string::npos )
            {
                std::string strNum = line.substr(nSysPos + 2, 3);
                nScatterPartitionIndex = atoi(strNum.c_str());
                layout_info->nPartitionIndex = nScatterPartitionIndex;

            }
        }

        // partition_name
        pos = line.find("partition_name:");
        if( pos == std::string::npos )
        {
        } else
        {
            strPartitionName = line.substr(pos + 15 +1, 40);
            layout_info->strPartitionName = AnsiString(strPartitionName.c_str());
        }

        // file_name
        pos = line.find("file_name:");
        if( pos == std::string::npos )
        {
        } else
        {
            strFileName = line.substr(pos + 10 +1, 40);
            layout_info->strFileName = AnsiString(strFileName.c_str());
        }

        // is_download
        pos = line.find("is_download:");
        if( pos == std::string::npos )
        {
        } else
        {
            strIsDownload = line.substr(pos + 12 +1, 6);
            if( strIsDownload.compare("true") == 0 )
            {
                layout_info->bIsDownload = true;
            } else
            {
                layout_info->bIsDownload = false;
            }
        }

        // type
        pos = line.find("type:");
        if( pos == std::string::npos )
        {
        } else
        {
            strType = line.substr(pos + 5 +1, 20);
            layout_info->strType = AnsiString(strType.c_str());
        }

        // linear_start_addr
        pos = line.find("linear_start_addr:");

        if( pos == std::string::npos )
        {
        } else
        {
            std::string x = line.substr(pos + 18 + 1, 16);
            //unsigned long ul = strtoul( x.c_str(), NULL, 16);
            ulLinearStartAddr = (unsigned __int64) StrToInt64(AnsiString(x.c_str()));
            layout_info->ulLinearStartAddr = ulLinearStartAddr;
        }

        // physical_start_addr
        pos = line.find("physical_start_addr:");

        if( pos == std::string::npos )
        {
        } else
        {
            std::string x = line.substr(pos + 20 + 1, 16);
            //unsigned long ul = strtoul( x.c_str(), NULL, 16);
            ulPhysicalStartAddr = (unsigned __int64) StrToInt64(AnsiString(x.c_str()));
            layout_info->ulPhysicalStartAddr = ulPhysicalStartAddr;
        }

        // partition_size
        pos = line.find("partition_size:");

        if( pos == std::string::npos )
        {
        } else
        {
            std::string x = line.substr(pos + 15 + 1, 16);
            //unsigned long ul = strtoul( x.c_str(), NULL, 16);
            ulPartitionSize = (unsigned __int64) StrToInt64(AnsiString(x.c_str()));
            layout_info->ulPartitionSize = ulPartitionSize;
        }

        // region
        pos = line.find("region:");
        if( pos == std::string::npos )
        {
        } else
        {
            strRegion = line.substr(pos + 6 +1, 15);
            layout_info->strRegion = AnsiString(strRegion.c_str());
        }

        // storage **** parition storage
        pos = line.find("storage:");
        if( pos == std::string::npos || bGeneralInfoStorageAdded )
        {
        } else
        {
            strPartStorage = line.substr(pos + 7 +1, 15);
            layout_info->strStorage = AnsiString(strPartStorage.c_str());
        }

        // boundary_check
        pos = line.find("boundary_check:");
        if( pos == std::string::npos )
        {
        } else
        {
            strBoundaryCheck = line.substr(pos + 15 +1, 6);
            if( strBoundaryCheck.compare("true") == 0 )
            {
                layout_info->bBoundaryCheck = true;
            } else
            {
                layout_info->bBoundaryCheck = false;
            }
        }

        // is_reserved
        pos = line.find("is_reserved:");
        if( pos == std::string::npos )
        {
        } else
        {
            strIsReserved = line.substr(pos + 12 +1, 6);
            if( strIsReserved.compare("true") == 0 )
            {
                layout_info->bIsReserved = true;
            } else
            {
                layout_info->bIsReserved = false;
            }
        }

        // operation_type
        pos = line.find("operation_type:");
        if( pos == std::string::npos )
        {
        } else
        {
            strOperationType = line.substr(pos + 15 +1, 15);
            layout_info->strOperationType = AnsiString(strOperationType.c_str());
        }

        // reserve
        pos = line.find( "reserve:");

        if( pos == std::string::npos )
        {
        } else
        {
            std::string x = line.substr(pos + 8 + 1, 16);
            //unsigned long ul = strtoul( x.c_str(), NULL, 16);
            ulReserve = (unsigned __int64) StrToInt64(AnsiString(x.c_str()));
            layout_info->ulReserve = ulReserve;

            // think its end :3

            this->m_list_partitions->Add(layout_info);
            
        }

 */
