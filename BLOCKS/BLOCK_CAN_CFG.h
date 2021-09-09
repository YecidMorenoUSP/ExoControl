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
            // Esta variable esuna instancia del nodo central, "EPOS1   "
            CAN_Network * CAN;

            name_of_class(){
                name = name_of_block;
                TYPE = name_of_type;

                N_IN  = 0;
                N_OUT = 0;

                priority = 8;
                VARS.running_mutex.store(true);
            }

            
            
            class foo
            {
            public:
                void bar()
                {   //std::unordered_map<int, int>::iterator itr;
                    //std::unordered_map<int, int>::iterator itr2;
                    int n = 0;
                    while (true)
                    {   
                        std::this_thread::yield();
                        if (running_mutex.load()) break;

                        mtx.lock();
                        std::this_thread::yield();
                        std::unordered_map<int, int> aux;
                        aux.swap(writeEpos);
                        std::unordered_map<int, float*> aux2;
                        aux2.swap(readPosition);
                        std::unordered_map<int, float*> aux3;
                        aux3.swap(readAnalog);
                        mtx.unlock();
                      
                        for (auto x : aux){
                            CAN->setVelocity(x.first,x.second); 
                            std::this_thread::yield();
                        }
                        std::unordered_map<int, float*>::iterator it = aux2.begin();
                        while(it != aux2.end()){
                            std::this_thread::yield();
                            (*it->second) = CAN->positionRead(it->first);
                            it++;
                        }

                        std::unordered_map<int, float*>::iterator it2 = aux3.begin();
                        while(it2 != aux3.end()){
                            std::this_thread::yield();
                            (*it2->second) = CAN->analogRead(it2->first/1000,it2->first%1000);
                            it2++;
                        }
                        if(SIM::EVENTS::pauseSimulation.load()) n++;

                        if(n>=2){
                            n = 0;
                            SIM::EVENTS::pauseSimulation.store(false);
                        }

                        
                    
                    }
                }
                int n = 0;
                std::atomic<bool>  running_mutex;
                
                std::mutex mtx;
                
                std::unordered_map<int, int> writeEpos;
                std::unordered_map<int, float*> readPosition;
                std::unordered_map<int, float*> readAnalog;
                
                CAN_Network * CAN;
            };

            struct VARS{
                std::atomic<bool> running_mutex;
                std::thread EposThread_;
                foo f;
            }VARS;

            virtual void Exec() override{
        
                

                if(SIM::EVENTS::time_index == FIRST_LAP){
                  
                    CAN = new CAN_Network((char*)Properties.deviceName.c_str(),
                                                    (char*)Properties.protocolStackName.c_str(),
                                                    (char*)Properties.interfaceName.c_str(),
                                                    (char*)Properties.portName.c_str());
                    CAN->connect();
                     
                 }
                 if(SIM::EVENTS::time_index == LAST_LAP){
                     iterateBLOCKS_GUI{
                         if((*it)->TYPE == BLKType_EPOS){
                             (*it)->Exec();
                             std::cout<<(*it)->name<<" + ";
                         }
                     }
                     CAN->close();
                     
                 }

                 if(SIM::EVENTS::time_index == FIRST_LAP){
                    // SIM::EVENTS::pauseSimulation.store(true);
                    VARS.f.CAN = CAN;
                    if(VARS.EposThread_.joinable())VARS.EposThread_.join();
                    VARS.running_mutex.store(false);  
                    VARS.f.running_mutex.store(false);
                    
                    VARS.EposThread_ =  std::thread(&foo::bar, &VARS.f);
                 }

                 
                if(SIM::EVENTS::time_index == LAST_LAP){
                    VARS.running_mutex.store(true); 
                    VARS.f.running_mutex.store(true);
                    if(VARS.EposThread_.joinable())VARS.EposThread_.join();
                    std::cout<<"N thread: "<<VARS.f.n;
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
