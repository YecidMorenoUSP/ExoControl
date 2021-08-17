#ifndef BLOCKS_H
    #include "BLOCKS.h"   
#endif


#define name_of_class  PPCAT(Block, name_of_object)
#define name_of_type   PPCAT(BLKType_, name_of_object)
#define name_of_block  STRINGIZE(name_of_object)
#define name_of_init   PPCAT(name_of_class,_INIT)

#include<ReabRob_EPOS.h>

namespace BLOCKS{   

 class name_of_class : public BLOCK {
        private:
            static int count;

            struct VARS{
                
            }VARS;

            struct Properties{
                std::string deviceName = "EPOS2";
                std::string protocolStackName = "MAXON SERIAL V2";
                std::string interfaceName = "USB";
                std::string portName = "USB0";
            }Properties;

            virtual void showProperties(){
                ImGui::Begin("Properties",&GUI::EVENTS::showProperties,0);            
                    ImGui::InputText("Device Name##1", (char*)Properties.deviceName.c_str() , size_t(Properties.deviceName.c_str()));
                    ImGui::InputText("Protocol##1", (char*)Properties.protocolStackName.c_str() , size_t(Properties.protocolStackName.c_str()));
                    ImGui::InputText("Interface Name##1", (char*)Properties.interfaceName.c_str() , size_t(Properties.interfaceName.c_str()));
                    ImGui::InputText("Port Name Name##1", (char*)Properties.portName.c_str() , size_t(Properties.portName.c_str()));
                    if(ImGui::Button("Test . . .")){
                        GUI::showLOG("\n>> Test CAN Network ");
                        if(!this->test())GUI::showLOG(" [ FAIL ]\n");
                        else GUI::showLOG(" [ OK ]\n");
                        
                    };
                ImGui::End();
            }

        public:
        
            CAN_Network * CAN;

            name_of_class(){
                name = name_of_block;
                TYPE = name_of_type;

                N_IN  = 0;
                N_OUT = 0;

                priority = 8;
                
            }

            virtual void Exec() override{
                if(SIM::EVENTS::time_index == FIRST_LAP){
                  

                    CAN = new CAN_Network((char*)Properties.deviceName.c_str(),
                                                    (char*)Properties.protocolStackName.c_str(),
                                                    (char*)Properties.interfaceName.c_str(),
                                                    (char*)Properties.portName.c_str());
                    CAN->connect();
                     return;
                 }
                 if(SIM::EVENTS::time_index == LAST_LAP){
                     
                     CAN->close();
                     return;
                 }
            }
            
            virtual BLOCK * Create(){
                return new name_of_class();
            }
            
            virtual void DrawADD(){
                //ImDrawList* draw_list = ImGui::GetWindowDrawList();
                //draw_list->AddCircleFilled(LOCAL.posBlock_Global.Min,5,GUI::getColorU32(GUICol_Amarillo));
            }    

            

            bool test(){
                CAN_Network * CAN1 = new CAN_Network((char*)Properties.deviceName.c_str(),
                                                    (char*)Properties.protocolStackName.c_str(),
                                                    (char*)Properties.interfaceName.c_str(),
                                                    (char*)Properties.portName.c_str());
                if(!CAN1->connect()) return false;
                else{                    
                    CAN1->close();
                    return true;
                }
            }
            
    };

    void name_of_init(){
        ALL_BLOCKS_GUI[name_of_type] = new name_of_class();
        GUI::LOG_MSG = GUI::LOG_MSG + "\n   " + STRINGIZE(name_of_class)   + ": Cargado " ;
    }
 
 

};
