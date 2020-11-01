#ifndef BLOCKS_H
    #include "BLOCKS.h"   
#endif

#define DefineBLOCKS BlockSUM_INIT();       \
                     BlockPOW_INIT();       \
                     BlockFUNGEN_INIT();    \
                     BlockSCOPE_INIT();     \
                     
                    
#define name_of_object SUM
#include "BLOCKS/BLOCK_SUM.h"

#define name_of_object POW
#include "BLOCKS/BLOCK_POW.h"

#define name_of_object FUNGEN
#include "BLOCKS/BLOCK_FUNGEN.h"

#define name_of_object SCOPE
#include "BLOCKS/BLOCK_SCOPE.h"

namespace BLOCKS{
    
    void Init(){
               
        cout << "\n>> Cargando Bloques : ";
        
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

    
}