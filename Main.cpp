//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "MTKScatter.h"
#include "LayoutInfo.h"
#include "frmEditBlock.h"
#include "AboutDlg.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "sSkinManager"
#pragma link "sSkinProvider"
#pragma resource "*.dfm"

TfrmMain *frmMain;
extern TfrmEdit *frmEdit;
extern TfrmAbout* frmAbout;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
    : TForm(Owner)
{
   m_is_edited = false; 
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormResize(TObject *Sender)
{
    this->Panel1->Width = this->Width;


}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::menuExitClick(TObject *Sender)
{
    this->Close();    
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::menuOpenClick(TObject *Sender)
{
    if( this->OpenScatter->Execute() )
    {
        this->m_mtk_scatter = new MTKScatter(OpenScatter->FileName.c_str());

        int result = this->m_mtk_scatter->StartRead();

        // if error occured
        if( result == 1 )
            return;

        // set member var as unedited
        this->m_is_edited = false;
                 
        // clear first
        this->lstLayoutSetting->Clear();

        if( m_mtk_scatter->m_list_partitions != NULL )
        {
            // loaded

            // change Window Title
            this->Caption = AnsiString("MTK Scatter Studio - ") + OpenScatter->FileName;


            int nPartCount = m_mtk_scatter->m_list_partitions->Count;

            // general infos
            this->edt_General->Text = m_mtk_scatter->general_info->strGeneralName;
            this->edt_BootChannel->Text = m_mtk_scatter->general_info->strBootChannel;
            this->edt_ConfigVer->Text = m_mtk_scatter->general_info->strConfigVersion;
            this->edt_Platform->Text = m_mtk_scatter->general_info->strPlatform;
            this->edt_Storage->Text = m_mtk_scatter->general_info->strStorage;
            this->edt_BlockSize->Text = AnsiString("0x") + IntToHex( (__int64)m_mtk_scatter->general_info->ulBlockSize, 8);
            this->edt_Project->Text = m_mtk_scatter->general_info->strProject;

            // set infos to status bar
            this->StatusBar->Panels->Items[0]->Text = AnsiString("Platform: ") + m_mtk_scatter->general_info->strPlatform;
            this->StatusBar->Panels->Items[1]->Text = AnsiString("Storage: ") + m_mtk_scatter->general_info->strStorage;
            this->StatusBar->Panels->Items[2]->Text = AnsiString("Config Version: ") + m_mtk_scatter->general_info->strConfigVersion;
            this->StatusBar->Panels->Items[3]->Text = AnsiString("TotalPartitions: ") + AnsiString(m_mtk_scatter->m_total_partitions);

            for( int i=0; i < nPartCount; i++)
            {
                TListItem* item;
                LayoutInfo* layoutInfo = reinterpret_cast<LayoutInfo*>(m_mtk_scatter->m_list_partitions->Items[i]);

                // new item
                
                item = this->lstLayoutSetting->Items->Add();
                // index
                item->Caption = IntToStr(layoutInfo->nPartitionIndex);
                item->SubItems->Add( layoutInfo->strPartitionName );
                item->SubItems->Add( layoutInfo->strFileName );
                int nIsDownload = (int)layoutInfo->bIsDownload;
                AnsiString strIsDownload;

                if( nIsDownload == 0 )
                    strIsDownload = "false";
                else
                    strIsDownload = "true";


                item->SubItems->Add( strIsDownload );
                item->SubItems->Add( layoutInfo->strType );
                item->SubItems->Add( AnsiString("0x") + IntToHex( (__int64)layoutInfo->ulLinearStartAddr, 8 ) );
                item->SubItems->Add( AnsiString("0x") + IntToHex( (__int64)layoutInfo->ulPhysicalStartAddr, 8 ) );
                item->SubItems->Add( AnsiString("0x") + IntToHex((__int64)layoutInfo->ulPartitionSize, 8 ));
                item->SubItems->Add( layoutInfo->strRegion );
                item->SubItems->Add( layoutInfo->strStorage );

                int nBoundCheck = (int)layoutInfo->bBoundaryCheck;
                AnsiString strBoundCheck;

                if( nBoundCheck == 0 )
                    strBoundCheck = "false";
                else
                    strBoundCheck = "true";

                item->SubItems->Add( strBoundCheck );

                int nIsReserved = (int)layoutInfo->bIsReserved;
                AnsiString strIsReserved;
                if( nIsReserved == 0 )
                    strIsReserved = "false";
                else
                    strIsReserved = "true";

                item->SubItems->Add( strIsReserved );
                item->SubItems->Add( layoutInfo->strOperationType );

                // for MT6797
                if( m_mtk_scatter->general_info->strPlatform.AnsiCompareIC("MT6797") == 0)
                {
                    int nIsUpgradable = (int)layoutInfo->bIsUpgradable;
                    AnsiString strIsUpgradable;
                    if( nIsUpgradable == 0 )
                        strIsUpgradable = "false";
                    else
                        strIsUpgradable = "true";

                    item->SubItems->Add( strIsUpgradable );

                    int nEmptyBoot = (int)layoutInfo->bEmptyBootNeeded;
                    AnsiString strEmptyBoot;
                    if( nEmptyBoot == 0 )
                        strEmptyBoot = "false";
                    else
                        strEmptyBoot = "true";

                    item->SubItems->Add( strEmptyBoot );
                } else
                {
                    item->SubItems->Add ( "" );
                    item->SubItems->Add ( "" );

                } // if --  MT6797

                item->SubItems->Add( AnsiString("0x") + IntToHex((__int64) layoutInfo->ulReserve, 8));


            }

        }
    }    
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::lstLayoutSettingDblClick(TObject *Sender)
{
    TListItem * item = this->lstLayoutSetting->Selected; //(TListItem*) Sender;

    frmEdit = new TfrmEdit(this);

    frmEdit->m_partition_index = item->Caption; // index
    frmEdit->m_partition_name = item->SubItems->operator [](0); // name
    frmEdit->m_file_name = item->SubItems->operator [](1); // filename
    frmEdit->m_is_downloadable = item->SubItems->operator [](2);
    frmEdit->m_type = item->SubItems->operator [](3);
    frmEdit->m_linear_start = item->SubItems->operator [](4);
    frmEdit->m_physical_start = item->SubItems->operator [](5);
    frmEdit->m_partition_size = item->SubItems->operator [](6);
    frmEdit->m_region = item->SubItems->operator [](7);
    frmEdit->m_storage = item->SubItems->operator [](8);
    frmEdit->m_boundary_check = item->SubItems->operator [](9);
    frmEdit->m_is_reserved = item->SubItems->operator [](10);
    frmEdit->m_operation_type = item->SubItems->operator [](11);
    frmEdit->m_is_upgradable = item->SubItems->operator [](12);
    frmEdit->m_empty_boot_needed = item->SubItems->operator [](13);
    frmEdit->m_reserve = item->SubItems->operator [](14);

    frmEdit->ShowModal();
        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::menuSaveClick(TObject *Sender)
{
    /// if not opened a file
    if( this->m_mtk_scatter == NULL )
    {
        MessageDlg( "There is no file to save", mtError, TMsgDlgButtons() << mbOK, 0);
        return;
    }
    
    std::ifstream streamIn(OpenScatter->FileName.c_str(), std::ifstream::binary);

    // get size of original file
    streamIn.seekg(0, std::ios::end);
    long size = streamIn.tellg();
    streamIn.seekg(0);

    AnsiString buffer;

    // for header
    buffer.sprintf("\
############################################################################################################\n\
#\n\
#  General Setting\n\
#\n\
# Generated by MTK Scatter Studio.\n\
############################################################################################################\n\
- general: %s\n\
  info:\n\
    - config_version: %s\n\
      platform: %s\n\
      project: %s\n\
      storage: %s\n\
      boot_channel: %s\n\
      block_size: %s\n\
############################################################################################################\n\
#\n\
#  Layout Setting\n\
#\n\
############################################################################################################\n\
"
, this->edt_General->Text.c_str(),
  this->edt_ConfigVer->Text.c_str(),
  this->edt_Platform->Text.c_str(),
  this->edt_Project->Text.c_str(),
  this->edt_Storage->Text.c_str(),
  this->edt_BootChannel->Text.c_str(),
  this->edt_BlockSize->Text.c_str()
  );

    // start parse and replace changes

    // start parsing blocks
    for ( int x=0; x < m_mtk_scatter->m_total_partitions; x++)
    {
        //LayoutInfo* layoutInfo = reinterpret_cast<LayoutInfo*>(m_mtk_scatter->m_list_partitions->Items[x]);

        TListItem * item = this->lstLayoutSetting->Items->operator [](x);

        AnsiString strBlocks;

        // for MT6797 scatter
        if( m_mtk_scatter->general_info->strPlatform.AnsiCompareIC("MT6797") == 0 )
        {
            strBlocks.sprintf(
  "\
- partition_index: SYS%d\n\
  partition_name: %s\n\
  file_name: %s\n\
  is_download: %s\n\
  type: %s\n\
  linear_start_addr: %s\n\
  physical_start_addr: %s\n\
  partition_size: %s\n\
  region: %s\n\
  storage: %s\n\
  boundary_check: %s\n\
  is_reserved: %s\n\
  operation_type: %s\n\
  is_upgradable: %s\n\
  empty_boot_needed: %s\n\
  reserve: %s\n\n"
            , atoi(item->Caption.c_str()) // index
            , item->SubItems->operator [](0).c_str() // name
            , item->SubItems->operator [](1).c_str() // filename
            , item->SubItems->operator [](2).c_str() // isdownload
            , item->SubItems->operator [](3).c_str() // type
            , item->SubItems->operator [](4).c_str() // linear_start
            , item->SubItems->operator [](5).c_str() // phystart
            , item->SubItems->operator [](6).c_str() // partsize
            , item->SubItems->operator [](7).c_str() // region
            , item->SubItems->operator [](8).c_str() // storage
            , item->SubItems->operator [](9).c_str() // boundcheck
            , item->SubItems->operator [](10).c_str()// isreserved
            , item->SubItems->operator [](11).c_str()// opttype

            , item->SubItems->operator [](12).c_str()// isupgrade
            , item->SubItems->operator [](13).c_str()// emptyboot
            , item->SubItems->operator [](14).c_str()// reserve

            );

            buffer += strBlocks;
        } else // -- not MT6797
        {
            strBlocks.sprintf(
  "\
- partition_index: SYS%d\n\
  partition_name: %s\n\
  file_name: %s\n\
  is_download: %s\n\
  type: %s\n\
  linear_start_addr: %s\n\
  physical_start_addr: %s\n\
  partition_size: %s\n\
  region: %s\n\
  storage: %s\n\
  boundary_check: %s\n\
  is_reserved: %s\n\
  operation_type: %s\n\
  reserve: %s\n\n"
            , atoi(item->Caption.c_str()) // index
            , item->SubItems->operator [](0).c_str() // name
            , item->SubItems->operator [](1).c_str() // filename
            , item->SubItems->operator [](2).c_str() // isdownload
            , item->SubItems->operator [](3).c_str() // type
            , item->SubItems->operator [](4).c_str() // linear_start
            , item->SubItems->operator [](5).c_str() // phystart
            , item->SubItems->operator [](6).c_str() // partsize
            , item->SubItems->operator [](7).c_str() // region
            , item->SubItems->operator [](8).c_str() // storage
            , item->SubItems->operator [](9).c_str() // boundcheck
            , item->SubItems->operator [](10).c_str()// isreserved
            , item->SubItems->operator [](11).c_str()// opttype
            , item->SubItems->operator [](14).c_str()// reserve

            );

            buffer += strBlocks;        
        } // -- if - else
    } // for --

        
    // ------------
    // write it

    //if( this->SaveDialog->Execute() )
    //{
        //if( !this->OpenScatter->FileName.IsEmpty() )
        //    this->SaveDialog->FileName = this->OpenScatter->FileName;
        
        std::ofstream streamOut(this->OpenScatter->FileName.c_str(), std::ofstream::binary);

        streamOut.write( buffer.c_str(), buffer.Length());


        streamOut.close();
        streamIn.close();
    //}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::edt_GeneralChange(TObject *Sender)
{
    this->m_is_edited = true;    
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::edt_ConfigVerChange(TObject *Sender)
{
    this->m_is_edited = true;
        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::edt_BootChannelChange(TObject *Sender)
{
    this->m_is_edited = true;    
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::edt_StorageChange(TObject *Sender)
{
    this->m_is_edited = true;     
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::edt_PlatformChange(TObject *Sender)
{
    this->m_is_edited = true;     
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::edt_BlockSizeChange(TObject *Sender)
{
    this->m_is_edited = true;     
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::menuAboutClick(TObject *Sender)
{
    frmAbout = new TfrmAbout(this);
    frmAbout->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::menuSaveasClick(TObject *Sender)
{
    /// save as
    /// if not opened a file
    if( this->m_mtk_scatter == NULL )
    {
        MessageDlg( "There is no file to save", mtError, TMsgDlgButtons() << mbOK, 0);
        return;
    }
    
    std::ifstream streamIn(OpenScatter->FileName.c_str(), std::ifstream::binary);

    // get size of original file
    streamIn.seekg(0, std::ios::end);
    long size = streamIn.tellg();
    streamIn.seekg(0);

    AnsiString buffer;

    // for header
    buffer.sprintf("\
############################################################################################################\n\
#\n\
#  General Setting\n\
#\n\
# Generated by MTK Scatter Studio.\n\
############################################################################################################\n\
- general: %s\n\
  info:\n\
    - config_version: %s\n\
      platform: %s\n\
      project: %s\n\
      storage: %s\n\
      boot_channel: %s\n\
      block_size: %s\n\
############################################################################################################\n\
#\n\
#  Layout Setting\n\
#\n\
############################################################################################################\n\
"
, this->edt_General->Text.c_str(),
  this->edt_ConfigVer->Text.c_str(),
  this->edt_Platform->Text.c_str(),
  this->edt_Project->Text.c_str(),
  this->edt_Storage->Text.c_str(),
  this->edt_BootChannel->Text.c_str(),
  this->edt_BlockSize->Text.c_str()
  );

    // start parse and replace changes

    // start parsing blocks
    for ( int x=0; x < m_mtk_scatter->m_total_partitions; x++)
    {
        //LayoutInfo* layoutInfo = reinterpret_cast<LayoutInfo*>(m_mtk_scatter->m_list_partitions->Items[x]);

        TListItem * item = this->lstLayoutSetting->Items->operator [](x);

        AnsiString strBlocks;

        // for MT6797 scatter
        if( m_mtk_scatter->general_info->strPlatform.AnsiCompareIC("MT6797") == 0 )
        {
            strBlocks.sprintf(
  "\
- partition_index: SYS%d\n\
  partition_name: %s\n\
  file_name: %s\n\
  is_download: %s\n\
  type: %s\n\
  linear_start_addr: %s\n\
  physical_start_addr: %s\n\
  partition_size: %s\n\
  region: %s\n\
  storage: %s\n\
  boundary_check: %s\n\
  is_reserved: %s\n\
  operation_type: %s\n\
  is_upgradable: %s\n\
  empty_boot_needed: %s\n\
  reserve: %s\n\n"
            , atoi(item->Caption.c_str()) // index
            , item->SubItems->operator [](0).c_str() // name
            , item->SubItems->operator [](1).c_str() // filename
            , item->SubItems->operator [](2).c_str() // isdownload
            , item->SubItems->operator [](3).c_str() // type
            , item->SubItems->operator [](4).c_str() // linear_start
            , item->SubItems->operator [](5).c_str() // phystart
            , item->SubItems->operator [](6).c_str() // partsize
            , item->SubItems->operator [](7).c_str() // region
            , item->SubItems->operator [](8).c_str() // storage
            , item->SubItems->operator [](9).c_str() // boundcheck
            , item->SubItems->operator [](10).c_str()// isreserved
            , item->SubItems->operator [](11).c_str()// opttype

            , item->SubItems->operator [](12).c_str()// isupgrade
            , item->SubItems->operator [](13).c_str()// emptyboot
            , item->SubItems->operator [](14).c_str()// reserve

            );

            buffer += strBlocks;
        } else // -- not MT6797
        {
            strBlocks.sprintf(
  "\
- partition_index: SYS%d\n\
  partition_name: %s\n\
  file_name: %s\n\
  is_download: %s\n\
  type: %s\n\
  linear_start_addr: %s\n\
  physical_start_addr: %s\n\
  partition_size: %s\n\
  region: %s\n\
  storage: %s\n\
  boundary_check: %s\n\
  is_reserved: %s\n\
  operation_type: %s\n\
  reserve: %s\n\n"
            , atoi(item->Caption.c_str()) // index
            , item->SubItems->operator [](0).c_str() // name
            , item->SubItems->operator [](1).c_str() // filename
            , item->SubItems->operator [](2).c_str() // isdownload
            , item->SubItems->operator [](3).c_str() // type
            , item->SubItems->operator [](4).c_str() // linear_start
            , item->SubItems->operator [](5).c_str() // phystart
            , item->SubItems->operator [](6).c_str() // partsize
            , item->SubItems->operator [](7).c_str() // region
            , item->SubItems->operator [](8).c_str() // storage
            , item->SubItems->operator [](9).c_str() // boundcheck
            , item->SubItems->operator [](10).c_str()// isreserved
            , item->SubItems->operator [](11).c_str()// opttype
            , item->SubItems->operator [](14).c_str()// reserve

            );

            buffer += strBlocks;        
        } // -- if - else
    } // for --

        
    // ------------
    // write it

    if( this->SaveDialog->Execute() )
    {
        std::ofstream streamOut(this->SaveDialog->FileName.c_str(), std::ofstream::binary);

        streamOut.write( buffer.c_str(), buffer.Length());


        streamOut.close();
        streamIn.close();
    }
}
//---------------------------------------------------------------------------

