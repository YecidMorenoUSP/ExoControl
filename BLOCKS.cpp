#ifndef BLOCKS_H
    #include "BLOCKS.h"   
#endif

#include "BLOCKS/BLOCK_SUM.h"
#include "BLOCKS/BLOCK_POW.h"

namespace BLOCKS{
    
    void Init(){
               
               
        BlockSUM_INIT();
        BlockPOW_INIT();
   
       
    }

    void BLOCK::Draw2(){
                
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        ImGuiContext& g = *GImGui;
        
        const  ImGuiID id = this->ID;
        static ImVec2 posBlock  = ImVec2(250,250);
        static ImVec2 sizeBlock = ImVec2(100,50);
 
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImVec2 pos = ImGui::GetWindowPos();          

        ImRect posBlock_Cursor = ImRect(window->DC.CursorPos,window->DC.CursorPos+posBlock+sizeBlock);
        ImRect posBlock_Global(pos+posBlock,pos+posBlock+sizeBlock);

        if (!ImGui::ItemAdd(posBlock_Cursor, id)) return;

        const bool hovered = ImGui::ItemHoverable(posBlock_Global, id);

        const bool double_clicked = (hovered && g.IO.MouseDoubleClicked[0]);

        static int double_clicked_count = 0;

        if(double_clicked) {
            BLOCKS::EVENTS::ActiveBlock = id;
            double_clicked_count = 10;
            GUI::EVENTS::showProperties = true;
            
        }

        if(double_clicked_count>=0){
            draw_list->AddRect(posBlock_Global.Min-ImVec2(double_clicked_count,double_clicked_count),
                                posBlock_Global.Max+ImVec2(double_clicked_count,double_clicked_count),GUI::getColorU32(GUICol_BlockFill),0.0f);
            double_clicked_count--;
        }
            
        if(GUI::EVENTS::showProperties && BLOCKS::EVENTS::ActiveBlock == id){
            ImGui::Begin("Properties",&GUI::EVENTS::showProperties,0);  
            ImGui::Text("Hola 1");
            ImGui::Text("Hola 2");
            ImGui::Text("Hola 3");
            ImGui::Text("Hola 4");
            ImGui::End();
        }                       
        
        draw_list->AddRectFilled(posBlock_Global.Min,posBlock_Global.Max,GUI::getColorU32(GUICol_BlockFill),0.0f);
        draw_list->AddText(pos+posBlock- ImGui::CalcTextSize("Test Block")*.5f + sizeBlock*.5f ,GUI::getColorU32(GUICol_BlockText),"Test Block");          
                
    }



    void AddBLOCK(TypeBlock_ TypeBlock){
        
        
        BLOCK * aux = ALL_BLOCKS_GUI[TypeBlock]->Create();
        aux->indexType = ++ALL_BLOCKS_GUI[TypeBlock]->indexType;
        std::string name = BLOCKS::ALL_BLOCKS_GUI[TypeBlock]->name + "(" + std::to_string(aux->indexType) + ")";
        aux->ID = BLOCKS::getIDBLOCK(name.c_str());
        aux->name = name;   
        aux->ENABLED = true;
        aux->ACTIVE = true;

        ALL_BLOCKS_GUI.push_back(aux);
        GUI::showAllConsole();
    }

    void DROOPBLOCK(ImGuiID ID){
            
            for (std::vector<BLOCK*>::iterator it = ALL_BLOCKS_GUI.begin() + BLKType_COUNT ; it != ALL_BLOCKS_GUI.end(); it++){
                if((*it)->ID == ID) {
                    ALL_BLOCKS_GUI.erase(it);
                    break;
                }
            }

            GUI::showAllConsole();
                
    }

    
}