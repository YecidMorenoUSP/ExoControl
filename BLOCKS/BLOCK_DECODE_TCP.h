#ifndef BLOCKS_H
    #include "BLOCKS.h"   
#endif

#define name_of_class  PPCAT(Block, name_of_object)
#define name_of_type   PPCAT(BLKType_, name_of_object)
#define name_of_block  STRINGIZE(name_of_object)
#define name_of_init   PPCAT(name_of_class,_INIT)
#define name_of_path   (std::string(name_of_block) + "/").c_str()


namespace BLOCKS{

 class name_of_class : public BLOCK {
        // private: 
        public:         

            typedef struct{
                float size = 9.0;
                struct frame{
                    float state;
                    float other;
                };
            }AnkleFrame;

            static int count;
    
            struct VARS{
                void * toParse;
            }VARS;


            struct Properties{     
                char* items[2];
                int item_current;
            }Properties = { 
                            .items = {"- - -","AnkleFrame"},
                            .item_current = 1
                          };

            void UpdateOut(){
                        sizeBlock.y = 50.0f + (N_OUT)*25;

                        N_OUT_size = sizeBlock.y/(float)(N_OUT+1.0f);
                        N_IN_size  = sizeBlock.y/(float)(N_IN+1.0f);

                        posOut.clear();
                        posOut.insert(posOut.begin(),N_OUT+1,ImVec2(0,0)); 

                        arma::fmat auxOut ;
                        auxOut << 0.0f;
                        OUT_ARMA.clear();
                        OUT_ARMA.insert(OUT_ARMA.begin(),N_OUT+1,auxOut); 
            }

            virtual void showProperties(){
                ImGui::Begin("Properties",&GUI::EVENTS::showProperties,0);           
                    
                    bool changed = false;
                    ImGui::PushButtonRepeat(true);
                    if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { 
                        N_OUT--;
                        changed = true;
                        if(N_OUT<=0) N_OUT = 0;}
                    ImGui::SameLine();
                    ImGui::Text("  %d  ", N_OUT);
                    ImGui::SameLine();
                    if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { N_OUT++;changed = true;}
                    ImGui::PopButtonRepeat();
                    
                    if(changed){
                        UpdateOut();
                    }
                    
                    ShowDemoWindowWidgets();
                ImGui::End();
            }

        // public:
    

            name_of_class(){

                name = name_of_block;
                TYPE = name_of_type;

                // priority = 7;

                N_IN  = 1;
                
                N_OUT = 0;

                sizeBlock = ImVec2(100,50);
                
                N_IN_size  = sizeBlock.y/(float)(N_IN+1.0f);
                N_OUT_size = sizeBlock.y/(float)(N_OUT+1.0f);

                posIn.insert(posIn.begin(),N_IN+1,ImVec2(0,0));
                posOut.insert(posOut.begin(),N_OUT+1,ImVec2(0,0)); 

                arma::fmat auxOut ;
                auxOut << 0.0f;
            
                
                OUT_ARMA.insert(OUT_ARMA.begin(),N_OUT+1,auxOut); 
                IN_ARMA.insert(IN_ARMA.begin(),N_IN+1,new arma::fmat);  
           
                return;

            }

            virtual void Exec() override{
                
                if(SIM::EVENTS::time_index == FIRST_LAP){
                    
                     return;
                }
                if(SIM::EVENTS::time_index == LAST_LAP){
                    return;
                }

                if(N_OUT == 0) (*IN_ARMA[1]).print("IN: "); else
                for(int i = 1 ; i <= N_OUT ; i++){
                    OUT_ARMA[i] = (*IN_ARMA[1])[i];
                }
                
            }
            
            virtual BLOCK * Create(){
                return new name_of_class();
            }
            
            virtual void DrawADD(){
            
            }    
            
    };

    void name_of_init(){
        ALL_BLOCKS_GUI[name_of_type] = new name_of_class();
        GUI::LOG_MSG =GUI::LOG_MSG + "\n   " + STRINGIZE(name_of_class)   + ": Cargado " ;
    }
 
 

};
