#ifndef BLOCKS_H
    #include "BLOCKS.h"   
#endif

#define DefineBLOCKS BlockSUM_INIT();       \
                     BlockPOW_INIT();       \
                     BlockABS_INIT();       \
                     BlockMULTI_INIT();     \
                     BlockNUMK_INIT();      \
                     BlockFUNGEN_INIT();    \
                     BlockSCOPE_INIT();     \
                     BlockDELSYS_INIT();    \
                     BlockREHAMOVE_INIT();  \
                     BlockCAN_CFG_INIT();   \
                     BlockEPOS_INIT();      \
                     BlockSPAR_INIT();      \
                     BlockSERVER_TCP_INIT();      \
                     BlockCLIENT_TCP_INIT();      \
                     BlockDECODE_TCP_INIT();      \
                     BlockENCODE_TCP_INIT();      \
                     BlockESP32_INIT();		  \
					 BlockGIOVANNA_TCC_INIT();		  \
					 BlockSAVE_INIT();		  \
					 BlockPULSE_INIT();		  \
					 //<ADD_BLOCK_INIT>


#define name_of_object SUM
#include "BLOCKS/BLOCK_SUM.h"

#define name_of_object POW
#include "BLOCKS/BLOCK_POW.h"

#define name_of_object MULTI
#include "BLOCKS/BLOCK_MULTI.h"

#define name_of_object FUNGEN
#include "BLOCKS/BLOCK_FUNGEN.h"

#define name_of_object SCOPE
#include "BLOCKS/BLOCK_SCOPE.h"

#define name_of_object DELSYS
#include "BLOCKS/BLOCK_DELSYS.h"

#define name_of_object REHAMOVE
#include "BLOCKS/BLOCK_REHAMOVE.h"

#define name_of_object NUMK
#include "BLOCKS/BLOCK_NUMK.h"

#define name_of_object ABS
#include "BLOCKS/BLOCK_ABS.h"

#define name_of_object CAN_CFG
#include "BLOCKS/BLOCK_CAN_CFG.h"

#define name_of_object EPOS
#include "BLOCKS/BLOCK_EPOS.h"

#define name_of_object SPAR
#include "BLOCKS/BLOCK_SPAR.h"

#define name_of_object SERVER_TCP
#include "BLOCKS/BLOCK_SERVER_TCP.h"

#define name_of_object CLIENT_TCP
#include "BLOCKS/BLOCK_CLIENT_TCP.h"

#define name_of_object DECODE_TCP
#include "BLOCKS/BLOCK_DECODE_TCP.h"

#define name_of_object ENCODE_TCP
#include "BLOCKS/BLOCK_ENCODE_TCP.h"

#define name_of_object ESP32
#include "BLOCKS/BLOCK_ESP32.h"

#define name_of_object GIOVANNA_TCC
#include "BLOCKS/BLOCK_GIOVANNA_TCC.h"

#define name_of_object SAVE
#include "BLOCKS/BLOCK_SAVE.h"

#define name_of_object PULSE
#include "BLOCKS/BLOCK_PULSE.h"

//<ADD_BLOCK_DEFINE_NAME_AND_INCLUDE_H>

namespace BLOCKS{
    
    void Init(){
               
        GUI::LOG_MSG += "\n>> Cargando Bloques : ";
        
        DefineBLOCKS;   
               
    }
   
    void AddBLOCK(TypeBlock_ TypeBlock){
            
        
        BLOCK * aux = ALL_BLOCKS_GUI[TypeBlock]->Create();
        aux->indexType = ++ALL_BLOCKS_GUI[TypeBlock]->indexType;
        std::string name = BLOCKS::ALL_BLOCKS_GUI[TypeBlock]->name + "(" + std::to_string(aux->indexType) + ")";
        aux->ID = BLOCKS::getIDBLOCK(name.c_str());
        aux->name = name;   
        aux->ENABLED = true;
        aux->ACTIVE = true;
        aux->posBlock = aux->posBlock + ImVec2(30,20)*aux->indexType;
        aux->indexBLOCKS =  ALL_BLOCKS_GUI.size()-BLKType_COUNT;

        ALL_BLOCKS_GUI.push_back(aux);
        
        //GUI::showAllConsole();
    }

    void DROOPBLOCK(ImGuiID ID){
            
            for (std::vector<BLOCK*>::iterator it = ALL_BLOCKS_GUI.begin() + BLKType_COUNT ; it != ALL_BLOCKS_GUI.end(); it++){
                if((*it)->ID == ID) {
                    ALL_BLOCKS_GUI.erase(it);
                    break;
                }
            }

            //GUI::showAllConsole();
                
    }

    void DROOPBLOCK(BLOCK * blk){
            
            
        blk->ACTIVE = false;
        while(true){
            bool eraseItem = false;
            iterateLINES_GUI{ 
                if((*it)->blockIn->ACTIVE == false || (*it)->blockOut->ACTIVE == false ){
                    (*it)->blockIn->IN_ARMA.clear();
                    (*it)->blockIn->IN_ARMA.insert((*it)->blockIn->IN_ARMA.begin(),(*it)->blockIn->N_IN+1,new arma::fmat);  
                    LINES::ALL_LINES_GUI.erase(it);
                    eraseItem = true;
                    break;
                }
            }
            if(!eraseItem) break;
        }
        
                
    }

    

    
}