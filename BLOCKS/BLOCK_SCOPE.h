#ifndef BLOCKS_H
    #include "BLOCKS.h"   
#endif



#define name_of_class  PPCAT(Block, name_of_object)
#define name_of_type   PPCAT(BLKType_, name_of_object)
#define name_of_block  STRINGIZE(name_of_object)
#define name_of_init   PPCAT(name_of_class,_INIT)


namespace BLOCKS{

 class name_of_class : public BLOCK {
        private:
            static int count;

      
            struct VARS{
                bool firstTime = true;
                arma::fmat vals ;
                arma::fmat time ;

                ImGui::PlotInterface SCOPE;
                std::vector<ImGui::PlotItem> items; 
 
             }VARS;
        

            struct Properties{
                const char * labels [4] = {"Curve 0","Curve 1","Curve 2","Curve 3"}; 
                
                ImVec4 colors[4] = {ImVec4(0.06f, 0.59f, 0.87f, 1.00f),
                                    ImVec4(1.00f, 0.46f, 0.00f, 1.00f),
                                    ImVec4(0.31f, 0.94f, 0.11f, 1.00f),      
                                    ImVec4(0.62f, 0.10f, 1.00f, 1.00f)};
                
                int typeLine[4] = {ImGui::PlotItem::Line,ImGui::PlotItem::Line,ImGui::PlotItem::Line,ImGui::PlotItem::Line};
                
                int sizeLine[4] = {20,20,20,20};

                std::string windowName = "Graphs";

                bool maximized = true;

            }Properties;

            void updateN_IN(){
                N_IN_size  = sizeBlock.y/(float)(N_IN+1.0f);
                N_OUT_size = sizeBlock.y/(float)(N_OUT+1.0f);

                posIn.clear();
                posOut.clear();
                IN_ARMA.clear();
                VARS.items.clear();
                
                posIn.insert(posIn.begin(),N_IN+1,ImVec2(0,0));
                
                arma::fmat auxOut ;
                auxOut << 0.0f;
                    
                IN_ARMA.insert(IN_ARMA.begin(),N_IN+1,new arma::fmat);        


                for(int i = 0 ; i < (N_IN) ; i++){
                    ImGui::PlotItem A;
                    A.label = Properties.labels[i];
                    A.type = (ImGui::PlotItem::Type) Properties.typeLine[i]; 
                    A.color = Properties.colors[i];
                    A.size = 1;
                    VARS.items.push_back(A);
                }
            }

            virtual void showProperties(){
                ImGui::Begin("Properties",&GUI::EVENTS::showProperties,0);  
                    
                    int aux_N_IN = 0;
                    float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
                    ImGui::PushButtonRepeat(true);
                    if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { aux_N_IN--; }
                    ImGui::SameLine(0.0f, spacing);
                    if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { aux_N_IN++; }
                    ImGui::PopButtonRepeat();
                    ImGui::SameLine();
                    if(aux_N_IN!=0 && (N_IN+aux_N_IN)>=1 && (N_IN+aux_N_IN)<= 4 ){
                        N_IN += aux_N_IN;
                        updateN_IN();
                    }
                    ImGui::Text("%d", N_IN);

                    ImGui::InputText(("Window"), (char*)Properties.windowName.c_str() , size_t(Properties.windowName.c_str()));
                    ImGui::Checkbox("Maximized",&Properties.maximized);

                    for(int i = 0 ; i < N_IN ; i++){
                        if(ImGui::TreeNode(("Curve "+std::to_string(i)).c_str())){

                            ImGui::InputText(("Name##"+std::to_string(i+1)).c_str(), (char*)VARS.items[i].label.c_str() , size_t(VARS.items[i].label.c_str()));

                            ImGui::RadioButton(("Scatter##"+std::to_string(i+1)).c_str(), &Properties.typeLine[i], ImGui::PlotItem::Scatter); ImGui::SameLine();
                            ImGui::RadioButton(("Line##"+std::to_string(i+1)).c_str(),&Properties.typeLine[i], ImGui::PlotItem::Line); 
                            ImGui::ColorPicker4(("Color##"+std::to_string(i+1)).c_str(), (float*)&Properties.colors[i], ImGuiColorEditFlags_Float );
                            ImGui::SliderInt(("Size##"+std::to_string(i+1)).c_str(),  &Properties.sizeLine[i] , 1, 100);

                            VARS.items[i].type  = (ImGui::PlotItem::Type) Properties.typeLine[i]; 
                            VARS.items[i].color = Properties.colors[i];
                            VARS.items[i].size  = 10.0f * Properties.sizeLine[i]/100.0f;

                            ImGui::TreePop();
                        }
                    }
                    ShowDemoWindowWidgets();
                ImGui::End();
            }

        public:
        
            name_of_class(){
                name = name_of_block;
                TYPE = name_of_type;

                N_IN  = 1;
                N_OUT = 0;
                
                updateN_IN();
                         
            }

            virtual void Exec() override{
                
                if(SIM::EVENTS::time_index == -1){
                    for(int i = 1 ; i <= N_IN ; i++)
                        VARS.items[i-1].data.clear();
                    return;
                }

                try{
                    for(int i = 1 ; i <= N_IN ; i++)
                    VARS.items[i-1].data.push_back( ImVec2(SIM::GET_NANOS() , (*IN_ARMA[i])[0] ) );
                }catch(...){
                    LOCAL.double_clicked_count = 20;
                    cout<<"\nERROR IN SCOPE\n";
                }        
                     

            }
            
            virtual BLOCK * Create(){
                return new name_of_class();
            }
            
            virtual void DrawADD(){
                
                if(VARS.firstTime){
                    Properties.windowName = name;
                    VARS.firstTime = false;
                }

                ImDrawList* draw_list = ImGui::GetWindowDrawList();
                
                for(int i  = 1 ; i <= N_IN ; i++)
                    draw_list->AddCircleFilled(posIn[i],5,ImGui::GetColorU32(Properties.colors[i-1]));

                ImGui::End();
                ImGui::Begin((" "+Properties.windowName).c_str(),&GUI::EVENTS::showBlocks,0);                

                if(Properties.maximized)
                    ImGui::Plot(name.c_str(), VARS.SCOPE, VARS.items); 
                else
                    ImGui::Plot(name.c_str(), VARS.SCOPE, VARS.items,ImVec2(ImGui::GetCurrentWindow()->Size.x - 20 , 200)); 
                
                ImGui::End();
                ImGui::Begin("Block logic",&GUI::EVENTS::showBlocks,0);       
            }    
            
    };

    void name_of_init(){
        ALL_BLOCKS_GUI[name_of_type] = new name_of_class();
        cout << "\n   "<< STRINGIZE(name_of_class)  <<": Cargado ";
    }
 
 

};
