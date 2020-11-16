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
                arma::fmat wave = {0.0f}; 
            }VARS;

            struct Properties{
                    const char * itemsComboType [3] = {"SIN","SQUARE","SAWTOOTH"};        
                    int TypeSelected = 0;

                    int   Rad_or_Hz = 1;
                    float FrequencyGUI = 1.0f;
                    float FrequencyW = 1.0f;

                    float PhaseGUI = 0;
                    float PhaseW = 0;
                    
                    float Amplitude = 1;

                    float Offset = 0;
                    

                    char strBuffer[100];                
                    
            }Properties;

            virtual void showProperties(){
                ImGui::Begin("Properties",&GUI::EVENTS::showProperties,0);  
                  
      
                        ImGui::Combo("Type", &Properties.TypeSelected, Properties.itemsComboType, IM_ARRAYSIZE(Properties.itemsComboType));
                                        
                        ImGui::RadioButton("Radians  ", &Properties.Rad_or_Hz, 0); ImGui::SameLine();
                        ImGui::RadioButton("Hertz ", &Properties.Rad_or_Hz, 1); 
                        
                        ImGui::InputFloat("Phase" , &Properties.PhaseGUI, -10.0f, 10.0f, "%.3f");
                        ImGui::InputFloat("Offset", &Properties.Offset  , -10.0f, 10.0f, "%.3f");
                        ImGui::InputFloat( Properties.Rad_or_Hz == 1? "Hz" : "rad/s", &Properties.FrequencyGUI, 0.1f, 10.0f, "%.3f");

                        ImGui::InputFloat("U", &Properties.Amplitude, -5.0f, 5.0f, "%.3f");

                        Properties.FrequencyW = Properties.Rad_or_Hz == 1 ? Properties.FrequencyGUI*2.0f*datum::pi : Properties.FrequencyGUI ;
                        Properties.PhaseW = Properties.Rad_or_Hz == 1 ? Properties.PhaseGUI*2.0f*datum::pi : Properties.PhaseW ;
                        ShowDemoWindowWidgets();

                 
                 
                ImGui::End();
            }

        public:
        
            name_of_class(){
                name = name_of_block;
                TYPE = name_of_type;

                N_IN  = 0;
                N_OUT = 1;
                
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
                 if(SIM::EVENTS::time_index == -1)return;
                
                arma::fmat time = {SIM::GET_NANOS()};
                arma::fmat sineWave =    Properties.Amplitude * arma::sin(time*Properties.FrequencyW + Properties.PhaseW);
                
                switch (Properties.TypeSelected)
                {
                    case 0:
                        VARS.wave = Properties.Offset + sineWave;
                        break;
                    case 1:
                        VARS.wave = Properties.Offset + arma::sign(sineWave) * Properties.Amplitude;
                        break;
                
                    default:
                        //VARS.wave += (sineWave.at(0) >= 0) ? SIM::EVENTS::Ts : -SIM::EVENTS::Ts;
                        VARS.wave = Properties.Offset + asin(sineWave)*2.0f/datum::pi *  Properties.Amplitude;
                        
                        break;
                }
                
                OUT_ARMA[1] =  VARS.wave;

            }
            
            virtual BLOCK * Create(){
                return new name_of_class();
            }
            
            virtual void DrawADD(){
                //ImDrawList* draw_list = ImGui::GetWindowDrawList();
                //draw_list->AddCircleFilled(LOCAL.posBlock_Global.Min,5,GUI::getColorU32(GUICol_Amarillo));
            }    
            
    };

    void name_of_init(){
        ALL_BLOCKS_GUI[name_of_type] = new name_of_class();
        cout << "\n   "<< STRINGIZE(name_of_class)  <<": Cargado ";
    }
 
 

};
