#ifndef BLOCKS_H
    #include "BLOCKS.h"   
#endif

namespace BLOCKS{

 class BlockSUM : public BLOCK {
        private:
            static int count;
            struct LOCAL{
                int double_clicked_count = 0;
                bool double_clicked = false;
                bool clicked = false;
                bool inDrag = false;
                bool hovered = false;
                ImVec2 posBlock_aux ;
            }LOCAL;
            struct Properties{
                    float val;
            }Properties;
            void showProperties(){
                ImGui::Begin("Properties",&GUI::EVENTS::showProperties,0);  
                    char str[100];
                    sprintf(str,"Val : %f",Properties.val);
                    ImGui::Text(str);
                    ImGui::SliderFloat("##Val",&Properties.val,-100,100,"%f U");
                ImGui::End();
            }

        public:
        
            
            BlockSUM(){
                name = "SUM";
                TYPE = BLKType_Sum;
                N_IN  = 2;
                N_OUT = 1;
                
                N_IN_size  = sizeBlock.y/(float)(N_IN+1.0f);
                N_OUT_size = sizeBlock.y/(float)(N_OUT+1.0f);

            
            }

            virtual void Exec() override{
                cout<<"\n"<<name;
            }
            
            virtual BLOCK * Create(){
                return new BlockSUM();
            }
            
            virtual  void Draw(){
                
                ImGuiWindow* window = ImGui::GetCurrentWindow();
                ImGuiContext& g = *GImGui;
                
                const  ImGuiID id = window->GetID(name.c_str());

                ImDrawList* draw_list = ImGui::GetWindowDrawList();
                ImVec2 pos = ImGui::GetWindowPos();          


                if(LOCAL.clicked && ImGui::IsMouseReleased(0)) LOCAL.clicked = false;
                if(LOCAL.double_clicked && ImGui::IsMouseReleased(0)) LOCAL.double_clicked = false;
                
                
                if(LOCAL.hovered && ImGui::IsMouseDragging(0) && LOCAL.clicked){
                    posBlock =  LOCAL.posBlock_aux + ImGui::GetMouseDragDelta();
                }                      
               
                ImRect posBlock_Cursor = ImRect(window->DC.CursorPos,window->DC.CursorPos+posBlock+sizeBlock);
                ImRect posBlock_Global(pos+posBlock,pos+posBlock+sizeBlock);


                for(int i  = 1 ; i <= N_OUT ; i++){
                    ImRect  OUTRec(posBlock_Global.Min + ImVec2(-5 + sizeBlock.x ,i*N_OUT_size-5),
                                   posBlock_Global.Min + ImVec2( 5 + sizeBlock.x ,i*N_OUT_size+5));
                    cout<<ImGui::ItemHoverable(OUTRec, id);    
                    //EVENTS::LinePoints[0] = this;
                }

                if (!ImGui::ItemAdd(posBlock_Cursor, id)) return;

                LOCAL.hovered = ImGui::ItemHoverable(posBlock_Global, id);
                const bool double_clicked = (LOCAL.hovered && g.IO.MouseDoubleClicked[0]);
                const bool clicked = (LOCAL.hovered && g.IO.MouseClicked[0]);
                                               
                if(clicked){
                    LOCAL.inDrag = true;
                    LOCAL.posBlock_aux = posBlock;
                    LOCAL.clicked = clicked;
                }

                if(double_clicked) {
                    BLOCKS::EVENTS::ActiveBlock = id;
                    LOCAL.double_clicked_count = 10;
                    LOCAL.double_clicked = double_clicked;
                    GUI::EVENTS::showProperties = true;     
                }

                if(LOCAL.double_clicked_count>=0){
                    draw_list->AddRect(posBlock_Global.Min-ImVec2(LOCAL.double_clicked_count,LOCAL.double_clicked_count),
                                        posBlock_Global.Max+ImVec2(LOCAL.double_clicked_count,LOCAL.double_clicked_count),GUI::getColorU32(GUICol_BlockFill),0.0f);
                    LOCAL.double_clicked_count--;
                }
                    
                if(GUI::EVENTS::showProperties && BLOCKS::EVENTS::ActiveBlock == id)showProperties();           
                
                draw_list->AddRectFilled(posBlock_Global.Min,posBlock_Global.Max,GUI::getColorU32(GUICol_BlockFill),0.0f);
                draw_list->AddRect(posBlock_Global.Min,posBlock_Global.Max,GUI::getColorU32(GUICol_BlockBorder),0.0f);
                draw_list->AddText(pos+posBlock- ImGui::CalcTextSize(this->name.c_str())*.5f + sizeBlock*.5f ,GUI::getColorU32(GUICol_BlockText),this->name.c_str());          
                
                if(BLOCKS::EVENTS::ActiveBlock == id){
                    draw_list->AddRect(posBlock_Global.Min,posBlock_Global.Max,GUI::getColorU32(GUICol_BlockBorderActive),0.0f);
                }

                for(int i  = 1 ; i <= N_IN ; i++)
                    draw_list->AddCircleFilled(posBlock_Global.Min + ImVec2(0,i*N_IN_size),5,GUI::getColorU32(GUICol_BlockIN));
                for(int i  = 1 ; i <= N_OUT ; i++)
                    draw_list->AddCircleFilled(posBlock_Global.Min  + ImVec2(sizeBlock.x,i*N_OUT_size),5,GUI::getColorU32(GUICol_BlockIN));
            }

            


            
            
    };

    void BlockSUM_INIT(){
        ALL_BLOCKS_GUI[BLKType_Sum] = new BlockSUM();
        cout << "\n   "<< name_of(BLKType_Sum)  <<": Cargado ";
    }
 
 

}