#ifndef BLOCKS_H
    #include "BLOCKS.h"   
#endif
/*
    
    name_of_class    ->   
    name_of_type     ->    to enum TypeBlock_ in BLOCKS.h
    name_of_block    ->  
    
    name_of_class_INIT(); -> to BLOCOS.cpp/void INIT(); 

    #include "BLOCKS/name_of_class.h" -> to BLOCOS.cpp
    
    struct Properties             ->   propiedades do bloco, para apresentar na janela Properties
    showProperties()              ->   distribuição das propiedades na janela

    virtual void Exec()           ->   função para executar na simulação
*/
//#ifdef name_of_class
//    #undef name_of_class
//#endif
//#ifdef name_of_type
//    #undef name_of_type
//#endif
//#ifdef name_of_block
//    #undef name_of_block
//#endif
//#ifdef name_of_init
//    #undef name_of_init
//#endif



#define name_of_class  PPCAT(Block, name_of_object)
#define name_of_type   PPCAT(BLKType_, name_of_object)
#define name_of_block  STRINGIZE(name_of_object)
#define name_of_init   PPCAT(name_of_class,_INIT)

//#define name_of_class  BlockFUNGEN
//#define name_of_type   BLKType_FUNGEN
//#define name_of_block  "FUNGEN"
//#define name_of_init   PPCAT(name_of_class,_INIT)








namespace BLOCKS{

 class name_of_class : public BLOCK {
        private:
            static int count;
            struct LOCAL{
                int double_clicked_count = 0;
                bool double_clicked = false;
                bool clicked = false;
                bool inDrag = false;
                bool hovered = false;
                
                bool firsTime = true;

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
                    ShowDemoWindowWidgets();
                ImGui::End();
            }

        public:
        
            
            name_of_class(){
                name = name_of_block;
                TYPE = name_of_type;

                N_IN  = 2;
                N_OUT = 1;
                
                N_IN_size  = sizeBlock.y/(float)(N_IN+1.0f);
                N_OUT_size = sizeBlock.y/(float)(N_OUT+1.0f);

                posIn.insert(posIn.begin(),N_IN+1,ImVec2(0,0));
                posOut.insert(posOut.begin(),N_OUT+1,ImVec2(0,0)); 

                arma::mat auxOut ;
                auxOut << 0.0f;
                
                OUT_ARMA.insert(OUT_ARMA.begin(),N_OUT+1,auxOut); 
                IN_ARMA.insert(IN_ARMA.begin(),N_IN+1,new arma::mat);            
            
            }

            virtual void Exec() override{
                
            }
            
            virtual BLOCK * Create(){
                return new name_of_class();
            }
            
            virtual  void Draw(){
                
                ImGuiWindow* window = ImGui::GetCurrentWindow();
                ImGuiContext& g = *GImGui;
                
                const  ImGuiID id = window->GetID(name.c_str());

                ImDrawList* draw_list = ImGui::GetWindowDrawList();
                ImVec2 pos = ImGui::GetWindowPos();          


                if(LOCAL.clicked && ImGui::IsMouseReleased(0)) LOCAL.clicked = false;
                if(LOCAL.double_clicked && ImGui::IsMouseReleased(0)) LOCAL.double_clicked = false;
                
                if(LOCAL.firsTime){
                    for(int i  = 1 ; i <= N_OUT ; i++)
                        posOut[i] = pos+posBlock  + ImVec2(sizeBlock.x,i*N_OUT_size);
                    for(int i  = 1 ; i <= N_IN ; i++)
                        posIn[i] = pos+posBlock + ImVec2(0,i*N_IN_size);
                    
                    LOCAL.firsTime = false;
                }
                
                if(LOCAL.hovered && ImGui::IsMouseDragging(0) && LOCAL.clicked){
                    posBlock =  LOCAL.posBlock_aux + ImGui::GetMouseDragDelta();
                    for(int i  = 1 ; i <= N_OUT ; i++)
                        posOut[i] = pos+posBlock  + ImVec2(sizeBlock.x,i*N_OUT_size);
                    for(int i  = 1 ; i <= N_IN ; i++)
                        posIn[i] = pos+posBlock + ImVec2(0,i*N_IN_size);
                }                      
               
                ImRect posBlock_Cursor = ImRect(window->DC.CursorPos,window->DC.CursorPos+posBlock+sizeBlock);
                ImRect posBlock_Global(pos+posBlock,pos+posBlock+sizeBlock);             

                LOCAL.hovered = ImGui::ItemHoverable(posBlock_Global, id);

                if(EVENTS::creatingLine == 0){
                    for(int i  = 1 ; i <= N_OUT ; i++){
                        ImRect  OUTRec(posBlock_Global.Min + ImVec2(-6 + sizeBlock.x ,i*N_OUT_size-6),
                                       posBlock_Global.Min + ImVec2( 6 + sizeBlock.x ,i*N_OUT_size+6));
                        if(ImGui::ItemHoverable(OUTRec, id)){
                            draw_list->AddCircleFilled(posOut[i],8,GUI::getColorU32(GUICol_BlockOUTHover));
                            if(g.IO.KeyCtrl)
                                OUT_ARMA[i].print("OUT : ");
                                
                        }
                        if(ImGui::ItemHoverable(OUTRec, id)&&ImGui::IsMouseClicked(0)){
                            EVENTS::blockOutLine = this;
                            EVENTS::posOutLineIndex = i;
                            EVENTS::creatingLine = 1;
                            EVENTS::newLinePosOUT= ImVec2(posBlock_Global.Min.x + sizeBlock.x ,
                                                          posBlock_Global.Min.y + i*N_OUT_size);
                        }
                    }
                }

                if(EVENTS::creatingLine == 1 ){
                    for(int i  = 1 ; i <= N_IN ; i++){
                        ImRect  OUTRec(posBlock_Global.Min + ImVec2(-6  ,i*N_IN_size-6),
                                       posBlock_Global.Min + ImVec2( 6  ,i*N_IN_size+6));
                        
                        if(ImGui::ItemHoverable(OUTRec, id)){
                            draw_list->AddCircleFilled(posIn[i],8,GUI::getColorU32(GUICol_BlockOUTHover));
                        }
                        if(ImGui::ItemHoverable(OUTRec, id)&&(ImGui::IsMouseReleased(0))){
                            EVENTS::blockInLine = this;
                            EVENTS::posInLineIndex = i;
                            EVENTS::creatingLine = 2;
                            EVENTS::newLinePosIN= ImVec2(posBlock_Global.Min.x  ,
                                                          posBlock_Global.Min.y + i*N_IN_size);
                        }
                    }
                }


                if (!ImGui::ItemAdd(posBlock_Cursor, id)) return;

                
                const bool double_clicked = (LOCAL.hovered && g.IO.MouseDoubleClicked[0]);
                const bool clicked = (LOCAL.hovered && g.IO.MouseClicked[0]);
                                               
                if(clicked && EVENTS::creatingLine == 0){
                    LOCAL.inDrag = true;
                    LOCAL.posBlock_aux = posBlock;
                    LOCAL.clicked = clicked;
                }

                if(double_clicked && EVENTS::creatingLine == 0) {
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
                    draw_list->AddCircleFilled(posIn[i],5,GUI::getColorU32(GUICol_BlockIN));
                for(int i  = 1 ; i <= N_OUT ; i++)
                    draw_list->AddCircleFilled(posOut[i],5,GUI::getColorU32(GUICol_BlockIN));
            }    
          
            
    };

    void name_of_init(){
        //STRINGIZE(PPCAT(name_of_class, _INIT()))
        ALL_BLOCKS_GUI[name_of_type] = new name_of_class();
        cout << "\n   "<< STRINGIZE(name_of_class)  <<": Cargado ";
        //cout<<"\n resultDefine    : "<<STRINGIZE(resultDefine);
        //cout<<"\n resultDefineAux : "<<STRINGIZE(resultDefineAux);
    }
 
 

};
