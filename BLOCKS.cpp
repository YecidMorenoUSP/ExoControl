#ifndef BLOCKS_H
    #include "BLOCKS.h"   
#endif

#include "BLOCKS/BLOCK_SUM.h" 
#include "BLOCKS/BLOCK_POW.h"

namespace BLOCKS{
    
    void Init(){
               
        cout << "\n>> Cargando Bloques : ";
        BlockSUM_INIT();
        BlockPOW_INIT();
       
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