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
        private:          

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

            virtual void showProperties(){
                ImGui::Begin("Properties",&GUI::EVENTS::showProperties,0);           
                    
                    if(ImGui::Combo("TypeFrame", &Properties.item_current, Properties.items, IM_ARRAYSIZE(Properties.items))){
                        switch (Properties.item_current)
                        {
                            case  0: N_OUT = 0; break;
                            case  1: N_OUT = 2; break;
                            default: N_OUT = 0; break;
                        }

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
                    
                    ShowDemoWindowWidgets();
                ImGui::End();
            }

        public:
    

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

                switch (Properties.item_current){
                    
                    case 0: //  - - - 
                         (*IN_ARMA[1]).print("IN : ");
                         break;
                    case 1: //  - - - 
                        OUT_ARMA[1] = (*IN_ARMA[1])[1];
                        OUT_ARMA[2] = (*IN_ARMA[1])[2];
                         break;
                     
                     default:
                         break;
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
