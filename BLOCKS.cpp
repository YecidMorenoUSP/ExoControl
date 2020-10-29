#ifndef BLOCKS_H
    #include "BLOCKS.h"   
#endif

namespace BLOCKS{
    
    void Init(){
        
        

        BLOCKS::BlockSUM * auxSum1 = new BLOCKS::BlockSUM();
        BLOCKS::BlockPOW * auxPow1 = new BLOCKS::BlockPOW();

        BLOCKS::BlockSUM * auxSum2 = new BLOCKS::BlockSUM();
        BLOCKS::BlockPOW * auxPow2 = new BLOCKS::BlockPOW();

        auxSum1->props.val = 1;
        auxSum2->props.val = 2;

        auxPow1->props.y = 10;
        auxPow2->props.y = 20;

         auxSum1->Exec(); cout<<sizeof(auxSum1);
         auxSum2->Exec(); cout<<sizeof(auxSum2);
         auxPow1->Exec(); cout<<sizeof(auxPow1);
         auxPow2->Exec(); cout<<sizeof(auxPow2);

        int * Bloques[] = {(int*)auxSum1,(int*)auxPow1,(int*)auxSum2,(int*)auxPow2};

        BLOCKS::BLOCK * auxSum11 =(BLOCKS::BLOCK *)Bloques[1];
        
        cout<<auxSum11->TYPE;

        ALL_BLOCKS[BLKType_Sum] = ALL_BLOCKS[BLKType_Default];
        ALL_BLOCKS[BLKType_Sum].name = "ADD";       

        ALL_BLOCKS[BLKType_Pow] = ALL_BLOCKS[BLKType_Default];
        ALL_BLOCKS[BLKType_Pow].name = "POW"; 

      
    }

    void BLOCK::Draw(){
                
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
        
            
        for(int i = BLKType_COUNT ; i < MAX_NUM_BLOCKS ; i++){
            if(!BLOCKS::ALL_BLOCKS[i].ACTIVE){
                
                BLOCKS::ALL_BLOCKS[TypeBlock].indexType += 1;
                int index = BLOCKS::ALL_BLOCKS[TypeBlock].indexType;

                ImGuiWindow* window = ImGui::GetCurrentWindow();
                std::string name = BLOCKS::ALL_BLOCKS[TypeBlock].name + "(" + std::to_string(index) + ")";

                BLOCKS::ALL_BLOCKS[i] = BLOCKS::ALL_BLOCKS[TypeBlock];

                BLOCKS::ALL_BLOCKS[i].ID = window->GetID(name.c_str());
                BLOCKS::ALL_BLOCKS[i].TYPE = TypeBlock;
                BLOCKS::ALL_BLOCKS[i].indexType = index;
                BLOCKS::ALL_BLOCKS[i].ENABLED = true;  
                BLOCKS::ALL_BLOCKS[i].ACTIVE = true;
                BLOCKS::ALL_BLOCKS[i].name = name;
                
                return;
            }
            
        }
            
    }

    void DROOPBLOCK(ImGuiID ID){
            
            //Falta limitarlo hasta que encuentre algun objeto incativo
            bool found = false;
            for(int i = BLKType_COUNT ; i < (MAX_NUM_BLOCKS-1) ; i++){
                if(BLOCKS::ALL_BLOCKS[i].ID == ID)found = true;
                if(found){
                    BLOCKS::ALL_BLOCKS[i] = BLOCKS::ALL_BLOCKS[i+1];
                }
            }
            if(found) BLOCKS::ALL_BLOCKS[MAX_NUM_BLOCKS-1] = BLOCKS::ALL_BLOCKS[BLKType_Default];
                
        }

    
}