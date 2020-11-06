#define LINES_H

namespace LINES{


    class LINE{
        public :
            int posIn;
            int posOut;
            BLOCKS::BLOCK * blockIn;
            BLOCKS::BLOCK * blockOut;

            bool usedGrafo = false;
                        
            void Draw(bool * eraseItem){
                ImVec2 lineCenter = (blockOut->posOut[posOut]+blockIn->posIn[posIn])/2.0f;
                ImRect centerArea(lineCenter-ImVec2(4,4),lineCenter+ImVec2(4,4));
                ImDrawList* draw_list = ImGui::GetWindowDrawList();
                 //if(usedGrafo)draw_list->AddLine(blockOut->posOut[posOut],blockIn->posIn[posIn],GUI::getColorU32(GUICol_Black),2);
                 //else 
                draw_list->AddLine(blockOut->posOut[posOut],blockIn->posIn[posIn],GUI::getColorU32(GUICol_Amarillo),2);
                if(ImGui::ItemHoverable(centerArea, 0)){
                    draw_list->AddCircleFilled(lineCenter,4,GUI::getColorU32(GUICol_Black));                    
                    draw_list->AddCircleFilled(lineCenter,2,GUI::getColorU32(GUICol_White));                    
                    if(ImGui::IsMouseReleased(0)) (*eraseItem) = true;
                }else
               
                draw_list->AddCircleFilled(lineCenter,2,GUI::getColorU32(GUICol_Black));                    
            }
            
    };

    std::vector<LINE*>  ALL_LINES_GUI;
    
};