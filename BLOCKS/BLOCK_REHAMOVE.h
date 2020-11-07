#ifndef BLOCKS_H
    #include "BLOCKS.h"   
#endif

#include <rehamovelib.c>

#define name_of_class  PPCAT(Block, name_of_object)
#define name_of_type   PPCAT(BLKType_, name_of_object)
#define name_of_block  STRINGIZE(name_of_object)
#define name_of_init   PPCAT(name_of_class,_INIT)


namespace BLOCKS{

 class name_of_class : public BLOCK {
        private:
            static int count;
            RehamoveDevice * FES;
            struct VARS{
                ImVec4 colors[4] = {ImVec4(0.06f, 0.59f, 0.87f, 1.00f),
                                    ImVec4(1.00f, 0.46f, 0.00f, 1.00f),
                                    ImVec4(0.31f, 0.94f, 0.11f, 1.00f),      
                                    ImVec4(0.62f, 0.10f, 1.00f, 1.00f)};
            }VARS;

            struct Properties{
                std::string nameCOM = "COM3";
            }Properties;

            virtual void showProperties(){
                ImGui::Begin("Properties",&GUI::EVENTS::showProperties,0); 
                ImGui::InputText(("COM Port"), (char*)Properties.nameCOM.c_str() , size_t(Properties.nameCOM.c_str()));
                    ShowDemoWindowWidgets();
                ImGui::End();
            }

        public:
        
            name_of_class(){
                name = name_of_block;
                TYPE = name_of_type;

                N_IN  = 4;
                N_OUT = 0;
                
                sizeBlock = ImVec2(90,60);

                N_IN_size  = sizeBlock.y/(float)(N_IN+1.0f);
                N_OUT_size = sizeBlock.y/(float)(N_OUT+1.0f);

                posIn.insert(posIn.begin(),N_IN+1,ImVec2(0,0));
                posOut.insert(posOut.begin(),N_OUT+1,ImVec2(0,0)); 

                arma::fmat auxOut ;
                auxOut << 0.0f;
                
                OUT_ARMA.insert(OUT_ARMA.begin(),N_OUT+1,auxOut); 
                IN_ARMA.insert(IN_ARMA.begin(),N_IN+1,new arma::fmat);            
            
            }

            virtual void Exec() override{
                if(SIM::EVENTS::time_index == FIRST_LAP){
                    FES = open_port(Properties.nameCOM.c_str());
                    if(FES == NULL) {
                        LOCAL.double_clicked_count = 50;
                        close_port(FES);
                        GUI::MODAL_WARNING::setModal("SIMULATION FAILED","RehaMove : "+Properties.nameCOM+" with Error","");
                        SIM::EVENTS::SimulationTaskMutex_end.store(true); 
                        
                    }
                    return;
                 }
                 if(SIM::EVENTS::time_index == LAST_LAP){
                     close_port(FES);
                    return;
                 }
                pulse(FES,Smpt_Channel::Smpt_Channel_Blue,(*IN_ARMA[1])[0],100); 
            }
            
            virtual BLOCK * Create(){
                return new name_of_class();
            }
            
            virtual void DrawADD(){
                ImDrawList* draw_list = ImGui::GetWindowDrawList();
                for(int i  = 1 ; i <= N_IN ; i++)
                    draw_list->AddCircleFilled(posIn[i],5,ImGui::GetColorU32(VARS.colors[i-1]));
                
            }    
            
    };

    void name_of_init(){
        ALL_BLOCKS_GUI[name_of_type] = new name_of_class();
        cout << "\n   "<< STRINGIZE(name_of_class)  <<": Cargado ";
    }
 
 

};
