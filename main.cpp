#include <windows.h>
#include <string.h>
#include <iostream>

std::string savefilename(char *filter = "All Files (*.blkReabRob)\0*.blkReabRob\0", HWND owner = NULL) {
  OPENFILENAME ofn;
  char fileName[MAX_PATH] = "";
  ZeroMemory(&ofn, sizeof(ofn));

  ofn.lStructSize = sizeof(OPENFILENAME);
  ofn.hwndOwner = owner;
  ofn.lpstrFilter = filter;
  ofn.lpstrFile = fileName;
  ofn.nMaxFile = MAX_PATH;
  ofn.Flags = 0x00080000 | 0x00001000 | 0x00000004;
  ofn.lpstrDefExt = "";

  std::string fileNameStr;

  if ( GetSaveFileName(&ofn) )
    fileNameStr = fileName;

  return fileNameStr;
}

std::string openfilename(char *filter = "All Files (*.blkReabRob)\0*.blkReabRob\0", HWND owner = NULL) {
  OPENFILENAME ofn;
  char fileName[MAX_PATH] = "";
  ZeroMemory(&ofn, sizeof(ofn));

  ofn.lStructSize = sizeof(OPENFILENAME);
  ofn.hwndOwner = owner;
  ofn.lpstrFilter = filter;
  ofn.lpstrFile = fileName;
  ofn.nMaxFile = MAX_PATH;
  ofn.Flags = 0x00080000 | 0x00001000 | 0x00000004;
  ofn.lpstrDefExt = "";

  std::string fileNameStr;

  if ( GetOpenFileName(&ofn) )
    fileNameStr = fileName;

  return fileNameStr;
}

#include "libs.cpp"

int __NUM_TEST__ = 0;
int __TYPE_TEST__ = 0;
char __NAME__P1__ [40] = "Yecid";
char __NAME__P2__ [40] = "Mauricio";

int __FREQ_FES__ = 30;
int __FREQ_FES__2 = 30;

arma::fvec __FES__Values = {1,  30, 50};
arma::fvec __KV__Values  = {0,  20, 40};
arma::fvec __BV__Values  = {0,   4,  8};

arma::umat TestGM_Values_ = {{0,0,0},
                             {0,1,0},
                             {0,2,0},
                             {1,2,1},
                             {1,1,1},
                             {1,0,1},
                             {0,0,0},
                             {0,1,0},
                             {0,2,0},
                             {2,2,2},
                             {2,1,2},
                             {2,0,2},
                             {0,0,0}};



void ADD_LINE_BI_PI_BO_PO( int b0, int p0, int b1, int p1){                   
    LINES::ALL_LINES_GUI.push_back( new LINES::LINE() );
    LINES::ALL_LINES_GUI.back()->posIn = p1;
    LINES::ALL_LINES_GUI.back()->posOut = p0;
    LINES::ALL_LINES_GUI.back()->blockOut = BLOCKS::ALL_BLOCKS_GUI[BLKType_COUNT + b0];
    LINES::ALL_LINES_GUI.back()->blockIn = BLOCKS::ALL_BLOCKS_GUI[BLKType_COUNT + b1];
    LINES::ALL_LINES_GUI.back()->blockIn->IN_ARMA[LINES::ALL_LINES_GUI.back()->posIn] = &(LINES::ALL_LINES_GUI.back()->blockOut->OUT_ARMA[LINES::ALL_LINES_GUI.back()->posOut]);
}

void V_ADD_LINE_BI_PI_BO_PO( int b0, int p0, int b1, int p1){                   
    LINES::LINE * l =  new LINES::LINE() ;

    l->posIn = p1;
    l->posOut = p0;
    l->blockOut = BLOCKS::ALL_BLOCKS_GUI[BLKType_COUNT + b0];
    l->blockIn = BLOCKS::ALL_BLOCKS_GUI[BLKType_COUNT + b1];
    l->blockIn->IN_ARMA[l->posIn] = &(l->blockOut->OUT_ARMA[l->posOut]);
}

void ADD_ANKLEBOT(int XX, int YY){
        
        int OB = BLOCKS::ALL_BLOCKS_GUI.size()-BLKType_COUNT-1;

        BLOCKS::AddBLOCK((TypeBlock_)BLKType_ENCODE_TCP);
        BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(XX+0,YY+0);
        ((BLOCKS::BlockENCODE_TCP*) BLOCKS::ALL_BLOCKS_GUI.back())->N_IN  = 4;
        ((BLOCKS::BlockENCODE_TCP*) BLOCKS::ALL_BLOCKS_GUI.back())->UpadateIO();
        
        BLOCKS::AddBLOCK((TypeBlock_)BLKType_CLIENT_TCP);
        BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(XX+120,YY+50);
        sprintf(((BLOCKS::BlockCLIENT_TCP*) BLOCKS::ALL_BLOCKS_GUI.back())->VARS.address,"192.168.0.66",sizeof("192.168.0.66"));
   
        BLOCKS::AddBLOCK((TypeBlock_)BLKType_DECODE_TCP);
        BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(XX+240,YY+12);
        ((BLOCKS::BlockDECODE_TCP*) BLOCKS::ALL_BLOCKS_GUI.back())->N_OUT  = 3;
        ((BLOCKS::BlockDECODE_TCP*) BLOCKS::ALL_BLOCKS_GUI.back())->UpdateOut();

        ADD_LINE_BI_PI_BO_PO(  OB+1,1,  OB+2,1  );
        ADD_LINE_BI_PI_BO_PO(  OB+2,1,  OB+3,1  );
}

void ADD_SPAR(int XX, int YY){

    int OB = BLOCKS::ALL_BLOCKS_GUI.size()-BLKType_COUNT-1;

    BLOCKS::AddBLOCK((TypeBlock_)BLKType_CAN_CFG);
    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(XX+163,YY+200);

    BLOCKS::AddBLOCK((TypeBlock_)BLKType_SPAR);
    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(XX+150,YY+0);

    BLOCKS::AddBLOCK((TypeBlock_)BLKType_EPOS);
    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(XX+0,YY+80);
    ((BLOCKS::BlockEPOS*) BLOCKS::ALL_BLOCKS_GUI.back())->Properties.nodeId=3;

    BLOCKS::AddBLOCK((TypeBlock_)BLKType_EPOS);
    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(XX+0,YY+132);
    ((BLOCKS::BlockEPOS*) BLOCKS::ALL_BLOCKS_GUI.back())->Properties.nodeId=32;

    ADD_LINE_BI_PI_BO_PO(  OB+3,1,  OB+2,4  );
    ADD_LINE_BI_PI_BO_PO(  OB+3,2,  OB+2,5  );
    ADD_LINE_BI_PI_BO_PO(  OB+3,3,  OB+2,6  );
    ADD_LINE_BI_PI_BO_PO(  OB+4,1,  OB+2,7  );
    ADD_LINE_BI_PI_BO_PO(  OB+2,1,  OB+3,1  );
    
    
}

void ADD_GAME_MARCIAN(int XX, int YY){
        
        int OB = BLOCKS::ALL_BLOCKS_GUI.size()-BLKType_COUNT-1;

        // BlOCK 1
        BLOCKS::AddBLOCK((TypeBlock_)BLKType_ENCODE_TCP);
        BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(XX+0,YY+0);
        ((BLOCKS::BlockENCODE_TCP*) BLOCKS::ALL_BLOCKS_GUI.back())->N_IN  = 2;
        ((BLOCKS::BlockENCODE_TCP*) BLOCKS::ALL_BLOCKS_GUI.back())->UpadateIO();
        
        // BlOCK 2
        BLOCKS::AddBLOCK((TypeBlock_)BLKType_SERVER_TCP);
        BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(XX+120,YY+25);
        sprintf(((BLOCKS::BlockSERVER_TCP*) BLOCKS::ALL_BLOCKS_GUI.back())->VARS.port,"2121",sizeof("2121"));
        
        // BlOCK 3
        BLOCKS::AddBLOCK((TypeBlock_)BLKType_DECODE_TCP);
        BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(XX+240,YY+0);
        ((BLOCKS::BlockDECODE_TCP*) BLOCKS::ALL_BLOCKS_GUI.back())->N_OUT  = 2;
        ((BLOCKS::BlockDECODE_TCP*) BLOCKS::ALL_BLOCKS_GUI.back())->UpdateOut(); //Ysize = 50.0f + (N_OUT)*25

        ADD_LINE_BI_PI_BO_PO(  OB+1,1,  OB+2,1  );
        ADD_LINE_BI_PI_BO_PO(  OB+2,1,  OB+3,1  );
}

void ADD_GAME_AIRHOCHEY(int XX, int YY){
        
        int OB = BLOCKS::ALL_BLOCKS_GUI.size()-BLKType_COUNT;

        // BlOCK 0
        BLOCKS::AddBLOCK((TypeBlock_)BLKType_ENCODE_TCP);
        BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(XX+0,YY+50);
        ((BLOCKS::BlockENCODE_TCP*) BLOCKS::ALL_BLOCKS_GUI.back())->N_IN  = 2;
        ((BLOCKS::BlockENCODE_TCP*) BLOCKS::ALL_BLOCKS_GUI.back())->UpadateIO();
        
        // BlOCK 1
        BLOCKS::AddBLOCK((TypeBlock_)BLKType_SERVER_TCP);
        BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(XX+120,YY+75);
        sprintf(((BLOCKS::BlockSERVER_TCP*) BLOCKS::ALL_BLOCKS_GUI.back())->VARS.port,"2121",sizeof("2121"));
        
        // BlOCK 2
        BLOCKS::AddBLOCK((TypeBlock_)BLKType_DECODE_TCP);
        BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(XX+240,YY+0);
        ((BLOCKS::BlockDECODE_TCP*) BLOCKS::ALL_BLOCKS_GUI.back())->N_OUT  = 6;
        ((BLOCKS::BlockDECODE_TCP*) BLOCKS::ALL_BLOCKS_GUI.back())->UpdateOut(); //Ysize = 50.0f + (N_OUT)*25

        ADD_LINE_BI_PI_BO_PO(  OB+0,1,  OB+1,1  );
        ADD_LINE_BI_PI_BO_PO(  OB+1,1,  OB+2,1  );
}

void TestGM_RA_FES_KV_BV(float __FES__ , float __Kv__ , float __Bv__){
    int OB1 = BLOCKS::ALL_BLOCKS_GUI.size()-BLKType_COUNT-1;
    ADD_ANKLEBOT(100,100);
    // 177 224
    
    BLOCKS::AddBLOCK((TypeBlock_)BLKType_NUMK);
    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(0,100);
    ((BLOCKS::BlockNUMK*) BLOCKS::ALL_BLOCKS_GUI.back())->Properties.K = __Kv__;

    BLOCKS::AddBLOCK((TypeBlock_)BLKType_NUMK);
    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(0,146);
    ((BLOCKS::BlockNUMK*) BLOCKS::ALL_BLOCKS_GUI.back())->Properties.K = __Bv__;


    int OB2 = BLOCKS::ALL_BLOCKS_GUI.size()-BLKType_COUNT-1;
    ADD_GAME_MARCIAN(400,245);

    int OB3 = BLOCKS::ALL_BLOCKS_GUI.size()-BLKType_COUNT-1;
    BLOCKS::AddBLOCK((TypeBlock_)BLKType_PULSE);
    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(780,254);
    ((BLOCKS::BlockPULSE*) BLOCKS::ALL_BLOCKS_GUI.back())->Properties.item_current  = 2;
    ((BLOCKS::BlockPULSE*) BLOCKS::ALL_BLOCKS_GUI.back())->Properties.Amplitude1  = __FES__; //FES[N]
    
    BLOCKS::AddBLOCK((TypeBlock_)BLKType_REHAMOVE);
    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(920,258);
    ((BLOCKS::BlockREHAMOVE*) BLOCKS::ALL_BLOCKS_GUI.back())->VARS.f.Freq  = __FREQ_FES__;

    ADD_LINE_BI_PI_BO_PO(OB1+4,1,  OB1+1, 1);
    ADD_LINE_BI_PI_BO_PO(OB1+5,1,  OB1+1, 2);

    ADD_LINE_BI_PI_BO_PO(OB1+3,1,  OB2+1, 1);

    ADD_LINE_BI_PI_BO_PO(OB3+0,1,  OB3+1, 1);
    ADD_LINE_BI_PI_BO_PO(OB3+1,1,  OB3+2, 1);

    ADD_LINE_BI_PI_BO_PO(OB2+3,1,  OB1+1, 3);

    int OB4 = BLOCKS::ALL_BLOCKS_GUI.size()-BLKType_COUNT-1;

    BLOCKS::AddBLOCK((TypeBlock_)BLKType_SAVE);
    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(336,50);
    sprintf(((BLOCKS::BlockSAVE*) BLOCKS::ALL_BLOCKS_GUI.back())->Properties.fileName,
            "%s_Test_%d_Type_%d_Log_%s",__NAME__P1__,__NUM_TEST__,__TYPE_TEST__,"R");

    BLOCKS::AddBLOCK((TypeBlock_)BLKType_ENCODE_TCP);
    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(913,329);
    ((BLOCKS::BlockENCODE_TCP*) BLOCKS::ALL_BLOCKS_GUI.back())->N_IN  = 3;
    ((BLOCKS::BlockENCODE_TCP*) BLOCKS::ALL_BLOCKS_GUI.back())->UpadateIO();

    BLOCKS::AddBLOCK((TypeBlock_)BLKType_SAVE);
    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(1040,367);
    sprintf(((BLOCKS::BlockSAVE*) BLOCKS::ALL_BLOCKS_GUI.back())->Properties.fileName,
            "%s_Test_%d_Type_%d_Log_%s",__NAME__P1__,__NUM_TEST__,__TYPE_TEST__,"L");

    ADD_LINE_BI_PI_BO_PO(OB1+2,1,  OB4+1, 1);
    
    ADD_LINE_BI_PI_BO_PO(OB3+1,1,  OB4+2, 1);
    ADD_LINE_BI_PI_BO_PO(OB3+1,2,  OB4+2, 2);
    ADD_LINE_BI_PI_BO_PO(OB2+3,1,  OB4+2, 3);
    ADD_LINE_BI_PI_BO_PO(OB4+2,1,  OB4+3, 1);

}

void TestGM_RS_FES_KV_BV(float __FES__ , float __Kv__ , float __Bv__){
    int OB1 = BLOCKS::ALL_BLOCKS_GUI.size()-BLKType_COUNT-1;
    ADD_SPAR(100,100);
    // 177 224
    ((BLOCKS::BlockSPAR*) BLOCKS::ALL_BLOCKS_GUI[BLKType_COUNT + OB1+2])->VARS.Kv  = __Kv__; //Kv[N]
    ((BLOCKS::BlockSPAR*) BLOCKS::ALL_BLOCKS_GUI[BLKType_COUNT + OB1+2])->VARS.Bv  = __Bv__;  //Bv[N]
    
    int OB2 = BLOCKS::ALL_BLOCKS_GUI.size()-BLKType_COUNT-1;
    ADD_GAME_MARCIAN(400,245+135);

    int OB3 = BLOCKS::ALL_BLOCKS_GUI.size()-BLKType_COUNT-1;
    BLOCKS::AddBLOCK((TypeBlock_)BLKType_PULSE);
    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(780,254+135);
    ((BLOCKS::BlockPULSE*) BLOCKS::ALL_BLOCKS_GUI.back())->Properties.item_current  = 2;
    ((BLOCKS::BlockPULSE*) BLOCKS::ALL_BLOCKS_GUI.back())->Properties.Amplitude1  = __FES__; //FES[N]
    
    BLOCKS::AddBLOCK((TypeBlock_)BLKType_REHAMOVE);
    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(920,258+135);
    ((BLOCKS::BlockREHAMOVE*) BLOCKS::ALL_BLOCKS_GUI.back())->VARS.f.Freq  = __FREQ_FES__;

    ADD_LINE_BI_PI_BO_PO(OB1+2,6,  OB2+1, 1);

    ADD_LINE_BI_PI_BO_PO(OB3+0,1,  OB3+1, 1);
    ADD_LINE_BI_PI_BO_PO(OB3+1,1,  OB3+2, 1);

    ADD_LINE_BI_PI_BO_PO(OB3+1,1,  OB3+2, 1);

    ADD_LINE_BI_PI_BO_PO(OB2+3,1,  OB1+2, 3);

    int OB4 = BLOCKS::ALL_BLOCKS_GUI.size()-BLKType_COUNT-1;

    BLOCKS::AddBLOCK((TypeBlock_)BLKType_ENCODE_TCP);
    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(915,40);
    ((BLOCKS::BlockENCODE_TCP*) BLOCKS::ALL_BLOCKS_GUI.back())->N_IN  = 10;
    ((BLOCKS::BlockENCODE_TCP*) BLOCKS::ALL_BLOCKS_GUI.back())->UpadateIO();

    BLOCKS::AddBLOCK((TypeBlock_)BLKType_SAVE);
    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(1047,160);
    sprintf(((BLOCKS::BlockSAVE*) BLOCKS::ALL_BLOCKS_GUI.back())->Properties.fileName,
            "%s_Test_%d_Type_%d_Log_%s",__NAME__P1__,__NUM_TEST__,__TYPE_TEST__,"L");

    ADD_LINE_BI_PI_BO_PO(OB1+2,1,  OB4+1,  1);
    ADD_LINE_BI_PI_BO_PO(OB1+2,2,  OB4+1,  2);
    ADD_LINE_BI_PI_BO_PO(OB1+2,3,  OB4+1,  3);
    ADD_LINE_BI_PI_BO_PO(OB1+2,4,  OB4+1,  4);
    ADD_LINE_BI_PI_BO_PO(OB1+2,5,  OB4+1,  5);
    ADD_LINE_BI_PI_BO_PO(OB1+2,6,  OB4+1,  6);
    ADD_LINE_BI_PI_BO_PO(OB1+2,7,  OB4+1,  7);
    ADD_LINE_BI_PI_BO_PO(OB1+2,8,  OB4+1,  8);
    ADD_LINE_BI_PI_BO_PO(OB2+3,1,  OB4+1,  9);
    ADD_LINE_BI_PI_BO_PO(OB3+1,1,  OB4+1, 10);

    ADD_LINE_BI_PI_BO_PO(OB4+1,1,  OB4+2, 1);

}

void TestGA_RAS_FES(float __FES__){
    
    int OB1 = BLOCKS::ALL_BLOCKS_GUI.size()-BLKType_COUNT-1;
    ADD_ANKLEBOT(100,100);
    
    int OB2 = BLOCKS::ALL_BLOCKS_GUI.size()-BLKType_COUNT-1;
    ADD_SPAR(100+90,250+18);

    int OB3 = BLOCKS::ALL_BLOCKS_GUI.size()-BLKType_COUNT-1;
    ADD_GAME_AIRHOCHEY(480,150);

    int OB4 = BLOCKS::ALL_BLOCKS_GUI.size()-BLKType_COUNT-1;
    BLOCKS::AddBLOCK((TypeBlock_)BLKType_PULSE);
    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(500,50);
    ((BLOCKS::BlockPULSE*) BLOCKS::ALL_BLOCKS_GUI.back())->Properties.item_current  = 2;
    ((BLOCKS::BlockPULSE*) BLOCKS::ALL_BLOCKS_GUI.back())->Properties.Amplitude1  = __FES__; //FES[N]
    
    BLOCKS::AddBLOCK((TypeBlock_)BLKType_REHAMOVE);
    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(640,50);
    ((BLOCKS::BlockREHAMOVE*) BLOCKS::ALL_BLOCKS_GUI.back())->VARS.f.Freq  = __FREQ_FES__;

    int OB5 = BLOCKS::ALL_BLOCKS_GUI.size()-BLKType_COUNT-1;
    BLOCKS::AddBLOCK((TypeBlock_)BLKType_PULSE);
    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(500,540);
    ((BLOCKS::BlockPULSE*) BLOCKS::ALL_BLOCKS_GUI.back())->Properties.item_current  = 2;
    ((BLOCKS::BlockPULSE*) BLOCKS::ALL_BLOCKS_GUI.back())->Properties.Amplitude1  = __FES__; //FES[N]
    
    BLOCKS::AddBLOCK((TypeBlock_)BLKType_REHAMOVE);
    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(640,540);
    ((BLOCKS::BlockREHAMOVE*) BLOCKS::ALL_BLOCKS_GUI.back())->VARS.f.Freq  = __FREQ_FES__2;


    ADD_LINE_BI_PI_BO_PO(OB1+3,1,  OB3+1, 1);
    ADD_LINE_BI_PI_BO_PO(OB2+2,8,  OB3+1, 2);

    // ADD_LINE_BI_PI_BO_PO(OB3+3,1,  OB1+1, 1);
    // ADD_LINE_BI_PI_BO_PO(OB3+3,2,  OB1+1, 2);

    // ADD_LINE_BI_PI_BO_PO(OB3+3,4,  OB2+2, 8);
    // ADD_LINE_BI_PI_BO_PO(OB3+3,5,  OB2+2, 9);

    V_ADD_LINE_BI_PI_BO_PO(OB3+3,1,  OB1+1, 1);
    V_ADD_LINE_BI_PI_BO_PO(OB3+3,2,  OB1+1, 2);
    V_ADD_LINE_BI_PI_BO_PO(OB3+3,4,  OB2+2, 8);
    V_ADD_LINE_BI_PI_BO_PO(OB3+3,5,  OB2+2, 9);

    

    ADD_LINE_BI_PI_BO_PO(OB4+1,1,  OB4+2, 1);
    ADD_LINE_BI_PI_BO_PO(OB1+3,1,  OB4+1, 1);
    
    ADD_LINE_BI_PI_BO_PO(OB5+1,1,  OB5+2, 1);
    ADD_LINE_BI_PI_BO_PO(OB2+2,8,  OB5+1, 1);


    int OB6 = BLOCKS::ALL_BLOCKS_GUI.size()-BLKType_COUNT-1;
    
    BLOCKS::AddBLOCK((TypeBlock_)BLKType_ENCODE_TCP);
    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(842,36);
    ((BLOCKS::BlockENCODE_TCP*) BLOCKS::ALL_BLOCKS_GUI.back())->N_IN  = 4;
    ((BLOCKS::BlockENCODE_TCP*) BLOCKS::ALL_BLOCKS_GUI.back())->UpadateIO();

    BLOCKS::AddBLOCK((TypeBlock_)BLKType_SAVE);
    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(993,88);
    sprintf(((BLOCKS::BlockSAVE*) BLOCKS::ALL_BLOCKS_GUI.back())->Properties.fileName,
    "GH_Test_%d_Type_%d_Log_%s",__NUM_TEST__,__TYPE_TEST__,__NAME__P1__);


    int OB7 = BLOCKS::ALL_BLOCKS_GUI.size()-BLKType_COUNT-1;

    BLOCKS::AddBLOCK((TypeBlock_)BLKType_ENCODE_TCP);
    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(852,382);
    ((BLOCKS::BlockENCODE_TCP*) BLOCKS::ALL_BLOCKS_GUI.back())->N_IN  = 9;
    ((BLOCKS::BlockENCODE_TCP*) BLOCKS::ALL_BLOCKS_GUI.back())->UpadateIO();

    BLOCKS::AddBLOCK((TypeBlock_)BLKType_SAVE);
    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(998,494);
    sprintf(((BLOCKS::BlockSAVE*) BLOCKS::ALL_BLOCKS_GUI.back())->Properties.fileName,
    "GH_Test_%d_Type_%d_Log_%s",__NUM_TEST__,__TYPE_TEST__,__NAME__P2__);

    int OB8 = BLOCKS::ALL_BLOCKS_GUI.size()-BLKType_COUNT-1;
    BLOCKS::AddBLOCK((TypeBlock_)BLKType_SAVE);
    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(842,225);
    sprintf(((BLOCKS::BlockSAVE*) BLOCKS::ALL_BLOCKS_GUI.back())->Properties.fileName,
    "GH_Test_%d_Type_%d_Log_%s",__NUM_TEST__,__TYPE_TEST__,"KvBv");


    ADD_LINE_BI_PI_BO_PO(OB6+1,1,  OB6+2, 1);
    ADD_LINE_BI_PI_BO_PO(OB1+3,1,  OB6+1, 1);
    ADD_LINE_BI_PI_BO_PO(OB1+3,2,  OB6+1, 2);
    ADD_LINE_BI_PI_BO_PO(OB1+3,3,  OB6+1, 3);
    ADD_LINE_BI_PI_BO_PO(OB4+1,1,  OB6+1, 4);

    ADD_LINE_BI_PI_BO_PO(OB7+1,1,  OB7+2, 1);
    ADD_LINE_BI_PI_BO_PO(OB2+2,1,  OB7+1, 1);
    ADD_LINE_BI_PI_BO_PO(OB2+2,2,  OB7+1, 2);
    ADD_LINE_BI_PI_BO_PO(OB2+2,3,  OB7+1, 3);
    ADD_LINE_BI_PI_BO_PO(OB2+2,4,  OB7+1, 4);
    ADD_LINE_BI_PI_BO_PO(OB2+2,5,  OB7+1, 5);
    ADD_LINE_BI_PI_BO_PO(OB2+2,6,  OB7+1, 6);
    ADD_LINE_BI_PI_BO_PO(OB2+2,7,  OB7+1, 7);
    ADD_LINE_BI_PI_BO_PO(OB2+2,8,  OB7+1, 8);
    ADD_LINE_BI_PI_BO_PO(OB5+1,1,  OB7+1, 9);

    ADD_LINE_BI_PI_BO_PO(OB3+2,1,  OB8+1, 1);


}

void ADDMenuBar();

void Menu_GM_RA();
void Menu_GM_RS();
void Menu_GA_RAS();

#define IO_BEGIN_FILE "[BEGIN]\0"
#define IO_BLOCK_FILE "\n[BLOCK]\0"
#define IO_LINE_FILE  "\n[LINE]\0"
#define IO_END_FILE   "\n[END]\0"




int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1; 
    }              

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | 0 );
    //window_flags |= ((SDL_WindowFlags)SDL_WINDOW_FULLSCREEN_DESKTOP);
    //window_flags |= (SDL_WindowFlags)SDL_WINDOW_FULLSCREEN;

    SDL_Window* window = SDL_CreateWindow("AppExo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync
    
    
     
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    io.ConfigFlags |= ImGuiWindowFlags_NoBackground;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

 
    GUI::StyleApp();
    //ImGui::StyleColorsLight();
    
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 1.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
 

    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL2_Init();

    {// Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);    
    }

    GUI::init();
    BLOCKS::Init();
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.00f);

    
    while (!GUI::EVENTS::DONE)
    {
       

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                GUI::EVENTS::DONE = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                GUI::EVENTS::DONE = true;
        }


        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        GUI::createControls();
        
        ADDMenuBar();
             

        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());


        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
            SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
        }

        
        SDL_GL_SwapWindow(window);
        
        Sleep(50);
    }

    // Cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


void ADDMenuBar(){
    ImGui::Begin("MainWindow");
        if (ImGui::BeginMenuBar()){

            if (ImGui::BeginMenu("Examples")){
                
                if(ImGui::MenuItem("LOAD"        , NULL, false)){
                    
                    std::string FileNameSTR = openfilename();
                    if(FileNameSTR.length()>0){

                        FILE *fptr;
                        if ((fptr = fopen(FileNameSTR.c_str(),"rb")) == NULL){
                            printf("Error! opening file");
                            return;
                        }

                        char info[100]  = "";
                        fread(&info, sizeof(info), 1, fptr); 

                        if(strcmp(info,IO_BEGIN_FILE) == 0){
                            while(true){
                                
                                fread(&info, sizeof(info), 1, fptr); 

                                    if(strcmp(info,IO_BEGIN_FILE) == 0){}
                                else if(strcmp(info,IO_END_FILE  ) == 0){break;}
                                else if(strcmp(info,IO_BLOCK_FILE) == 0){
                                    BLOCKS::BLOCK * blk = new BLOCKS::BLOCK();
                                    blk->load(fptr);

                                    BLOCKS::AddBLOCK((TypeBlock_)blk->dataBlock.type);
                                    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(blk->dataBlock.posX,blk->dataBlock.posY);
                                    BLOCKS::ALL_BLOCKS_GUI.back()->sizeBlock = ImVec2(blk->dataBlock.sizeX,blk->dataBlock.sizeY);
                                    BLOCKS::ALL_BLOCKS_GUI.back()->N_IN  = blk->dataBlock.N_IN;
                                    BLOCKS::ALL_BLOCKS_GUI.back()->N_OUT = blk->dataBlock.N_OUT;
                                    BLOCKS::ALL_BLOCKS_GUI.back()->UpadateIO();
                                }
                                else if(strcmp(info,IO_LINE_FILE) == 0){
                                    LINES::LINE * ln = new LINES::LINE();
                                    ln->load(fptr);

                                    LINES::ALL_LINES_GUI.push_back( new LINES::LINE() );
                                    LINES::ALL_LINES_GUI.back()->posIn = ln->dataLine.posIn;
                                    LINES::ALL_LINES_GUI.back()->posOut = ln->dataLine.posOut;
                                    LINES::ALL_LINES_GUI.back()->blockOut = BLOCKS::ALL_BLOCKS_GUI[ln->dataLine.idxOut+BLKType_COUNT];
                                    LINES::ALL_LINES_GUI.back()->blockIn = BLOCKS::ALL_BLOCKS_GUI[ln->dataLine.idxIn+BLKType_COUNT];
                                    LINES::ALL_LINES_GUI.back()->blockIn->IN_ARMA[LINES::ALL_LINES_GUI.back()->posIn] = &(LINES::ALL_LINES_GUI.back()->blockOut->OUT_ARMA[LINES::ALL_LINES_GUI.back()->posOut]);
                                }
                                else break;

                            }
                        }else{
                            printf("ERROR con el archivo");
                        }

                        fclose(fptr);    
                    }

                }

                if(ImGui::MenuItem("SAVE"        , NULL, false)){
                    std::string FileNameSTR = savefilename();
                    if(FileNameSTR.length()>0){
                        FILE *fptr;

                        if ((fptr = fopen(FileNameSTR.c_str(),"wb")) == NULL){
                            printf("Error! opening file");
                            return;
                        }

                        char info[100];

                        sprintf(info,IO_BEGIN_FILE);
                        fwrite(&info, sizeof(info), 1, fptr); 


                        iterateBLOCKS_GUI{
                            sprintf(info,IO_BLOCK_FILE);
                            fwrite(&info, sizeof(info), 1, fptr); 
                            (*it)->save(fptr);
                        }

                        iterateLINES_GUI{
                            sprintf(info,IO_LINE_FILE);
                            fwrite(&info, sizeof(info), 1, fptr); 
                            (*it)->save(fptr);
                        }

                        sprintf(info,IO_END_FILE);
                        fwrite(&info, sizeof(info), 1, fptr); 

                        fclose(fptr);     
                    }
                    // iterateBLOCKS_GUI{
                    //     printf("\n");
                    //     printf("\nBLOCKS::AddBLOCK((TypeBlock_)%d);",(*it)->TYPE);
                    //     printf("\nBLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(%ff,%ff);",(*it)->posBlock.x,(*it)->posBlock.y);
                    //     printf("\nBLOCKS::ALL_BLOCKS_GUI.back()->sizeBlock = ImVec2(%ff,%ff);",(*it)->sizeBlock.x,(*it)->sizeBlock.y);
                    //     printf("\nBLOCKS::ALL_BLOCKS_GUI.back()->N_IN  = %d;",(*it)->N_IN );
                    //     printf("\nBLOCKS::ALL_BLOCKS_GUI.back()->N_OUT = %d;",(*it)->N_OUT);
                    //     printf("\nBLOCKS::ALL_BLOCKS_GUI.back()->UpadateIO();");
                    // }

                    // iterateLINES_GUI{
                    //     printf("\n");
                    //     printf("\nLINES::ALL_LINES_GUI.push_back( new LINES::LINE() );");
                    //     printf("\nLINES::ALL_LINES_GUI.back()->posIn = %d;",(*it)->posIn);
                    //     printf("\nLINES::ALL_LINES_GUI.back()->posOut = %d;",(*it)->posOut);
                    //     printf("\nLINES::ALL_LINES_GUI.back()->blockOut = BLOCKS::ALL_BLOCKS_GUI[%d+BLKType_COUNT];",(*it)->blockOut->indexBLOCKS);
                    //     printf("\nLINES::ALL_LINES_GUI.back()->blockIn = BLOCKS::ALL_BLOCKS_GUI[%d+BLKType_COUNT];",(*it)->blockIn->indexBLOCKS);
                    //     printf("\nLINES::ALL_LINES_GUI.back()->blockIn->IN_ARMA[LINES::ALL_LINES_GUI.back()->posIn] = &(LINES::ALL_LINES_GUI.back()->blockOut->OUT_ARMA[LINES::ALL_LINES_GUI.back()->posOut]);");
                    // }

                    // BLOCKS::AddBLOCK((TypeBlock_)BLKType_CAN_CFG);
                    // BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(100,100);
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Assets")){
                if(ImGui::MenuItem("SPAR"        , NULL, false))    ADD_SPAR(100,100);
                if(ImGui::MenuItem("ANKLEBOT"        , NULL, false))    ADD_ANKLEBOT(100,100);
                if(ImGui::MenuItem("GAME_MARCIAN"        , NULL, false))    ADD_GAME_MARCIAN(400,100);
                if(ImGui::MenuItem("GAME_AIRHOCKEY"        , NULL, false))    ADD_GAME_AIRHOCHEY(400,100);
                ImGui::EndMenu();
            }

            Menu_GM_RA();
            Menu_GM_RS();

            Menu_GA_RAS();

            ImGui::EndMenuBar();
        }
        ImGui::End();
}

void Menu_GM_RA(){
    
            if (ImGui::BeginMenu("Test GM & RA")){
                char nameOfMenu[50] = "Test";
                for(int nTest = 0 ; nTest < TestGM_Values_.n_rows ; nTest ++ ){
                    sprintf(nameOfMenu,"T%d",nTest+1);
                    if(ImGui::MenuItem(nameOfMenu        , NULL, false)){
                        __NUM_TEST__ = nTest+1;
                        __TYPE_TEST__ = 1;
                        TestGM_RA_FES_KV_BV(__FES__Values((int)TestGM_Values_(nTest,0)),
                                            __KV__Values((int)TestGM_Values_(nTest,1)),
                                            __BV__Values((int)TestGM_Values_(nTest,2)));
                    }
                }
                ImGui::EndMenu();
            }
}

void Menu_GM_RS(){
    
            if (ImGui::BeginMenu("Test GM & RS")){
                char nameOfMenu[50] = "Test";
                for(int nTest = 0 ; nTest < TestGM_Values_.n_rows ; nTest ++ ){
                    sprintf(nameOfMenu,"T%d",nTest+1);
                    if(ImGui::MenuItem(nameOfMenu        , NULL, false)){
                        __NUM_TEST__ = nTest+1;
                        __TYPE_TEST__ = 2;
                        TestGM_RS_FES_KV_BV(__FES__Values((int)TestGM_Values_(nTest,0)),
                                            __KV__Values((int)TestGM_Values_(nTest,1)),
                                            __BV__Values((int)TestGM_Values_(nTest,2)));
                    }
                }
                
                ImGui::EndMenu();
            }

}

void Menu_GA_RAS(){
    if (ImGui::BeginMenu("Test GA & RA & RS")){
                char nameOfMenu[50] = "Test";
                for(int nTest = 0 ; nTest < __FES__Values.n_rows ; nTest ++ ){
                    sprintf(nameOfMenu,"T%d",nTest+1);
                    if(ImGui::MenuItem(nameOfMenu        , NULL, false)){
                        __NUM_TEST__ = nTest+1;
                        __TYPE_TEST__ = 3;
                        TestGA_RAS_FES(__FES__Values((int)TestGM_Values_(nTest,0)));
                    }
                }
                
                ImGui::EndMenu();
    }
}