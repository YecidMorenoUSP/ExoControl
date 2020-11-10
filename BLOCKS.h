#define BLOCKS_H


enum TypeBlock_{
    BLKType_Default,
    BLKType_SUM,
    BLKType_MULTI,
    BLKType_POW,
    BLKType_NUMK,
    BLKType_FUNGEN,
    BLKType_SCOPE,
    BLKType_DELSYS,
    BLKType_REHAMOVE,
    BLKType_ABS,
    BLKType_COUNT
};

namespace BLOCKS{

    ImGuiID getIDBLOCK(const char * str){
        ImGuiID id = ImHashStr(str);
        return id;
    }

    template <typename T>
    void runBlock(T arg){
        arg->Exec();
    }

    void Init();


    class BLOCK {
        public:

            struct LOCAL{
                int double_clicked_count = 0;
                bool double_clicked = false;
                bool clicked = false;
                bool inDrag = false;
                bool hovered = false;
                
                bool firsTime = true;

                ImRect posBlock_Global;

                ImVec2 posBlock_aux ;                

            }LOCAL;

            ImGuiID ID;
            TypeBlock_ TYPE;
            int indexType = 0;

            std::string name = "DefaultBlock";
            std::string helpText;

            bool ENABLED = false;
            bool ACTIVE  = false;

            ImVec2 posBlock  = ImVec2(10,10);
            ImVec2 sizeBlock = ImVec2(80,40);
            
            struct Properties;

            int N_IN;
            int N_OUT;

            float N_IN_size ;
            float N_OUT_size;

            std::vector<arma::fmat * > IN_ARMA;
            std::vector<arma::fmat> OUT_ARMA;

            std::vector<ImVec2> posIn;
            std::vector<ImVec2> posOut;

        virtual void showProperties(){};
        virtual void Draw();
        virtual void DrawADD(){};
        virtual void Exec(){};
        virtual BLOCK * Create(){return NULL;};
    
    };

    namespace EVENTS{
        ImGuiID ActiveBlock;
        BLOCK * LinePoints[2] = {NULL,NULL};

        int creatingLine = 0;

        ImVec2 newLinePosOUT;
        ImVec2 newLinePosIN;

        int posInLineIndex;
        int posOutLineIndex;


        BLOCKS::BLOCK * blockInLine;
        BLOCKS::BLOCK * blockOutLine;
    }
    std::vector<BLOCK*> ALL_BLOCKS_GUI(BLKType_COUNT,NULL);

   
    void AddBLOCK(TypeBlock_ TypeBlock);
    void DROOPBLOCK(ImGuiID ID);

    void BLOCK::Draw(){
                
                if(!ImGui::GetCurrentWindow()->DockTabIsVisible){
                    this->DrawADD();
                    if(LOCAL.firsTime){
                        LOCAL.firsTime = false;
                    }
                    return;
                }

                ImGuiWindow* window = ImGui::GetCurrentWindow();
                ImGuiContext& g = *GImGui;
                            
                
                const  ImGuiID id = window->GetID(name.c_str());

                ImDrawList* draw_list = ImGui::GetWindowDrawList();
                ImVec2 pos = ImGui::GetWindowPos();          


                if(LOCAL.clicked && ImGui::IsMouseReleased(0)) LOCAL.clicked = false;
                if(LOCAL.double_clicked && ImGui::IsMouseReleased(0)) LOCAL.double_clicked = false;
                              

                if(LOCAL.hovered && ImGui::IsMouseDragging(0) && LOCAL.clicked){
                    posBlock =  LOCAL.posBlock_aux + ImGui::GetMouseDragDelta();
                    for(int i  = 1 ; i <= N_OUT ; i++)
                        posOut[i] = pos+posBlock  + ImVec2(sizeBlock.x,i*N_OUT_size);
                    for(int i  = 1 ; i <= N_IN ; i++)
                        posIn[i] = pos+posBlock + ImVec2(0,i*N_IN_size);
                }                      
               
                ImRect posBlock_Cursor = ImRect(window->DC.CursorPos,window->DC.CursorPos+posBlock+sizeBlock);
                ImRect posBlock_Global(pos+posBlock,pos+posBlock+sizeBlock);             
                LOCAL.posBlock_Global = posBlock_Global;
                LOCAL.hovered = ImGui::ItemHoverable(posBlock_Global, id);

                for(int i  = 1 ; i <= N_OUT ; i++)
                        posOut[i] = pos+posBlock  + ImVec2(sizeBlock.x,i*N_OUT_size);
                for(int i  = 1 ; i <= N_IN ; i++)
                        posIn[i] = pos+posBlock + ImVec2(0,i*N_IN_size);

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

                if(clicked && GUI::EVENTS::showProperties) {
                    BLOCKS::EVENTS::ActiveBlock = id;
                    LOCAL.double_clicked_count = 10; 
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

                this->DrawADD();
                
                if(LOCAL.firsTime){
                    LOCAL.firsTime = false;
                }
                
            }    
            

}

