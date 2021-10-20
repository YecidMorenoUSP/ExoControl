#ifndef BLOCKS_H
    #include "BLOCKS.h"   
#endif

#define name_of_class  PPCAT(Block, name_of_object)
#define name_of_type   PPCAT(BLKType_, name_of_object)
#define name_of_block  STRINGIZE(name_of_object)
#define name_of_init   PPCAT(name_of_class,_INIT)
#define name_of_path   (std::string(name_of_block) + "/").c_str()

#define DEBUG_CLIENT_TCP
#define DEFAULT_BUFLEN 512

#include <utilsTCP.h>
#include <ClientTCP.h>


namespace BLOCKS{

 class name_of_class : public BLOCK {
        private:          

            static int count;
    
            struct VARS{
                ClientTCP * client;
                SharedBuffer app; 
                char address[20];         
                char port[10];    
            }VARS;


            struct Properties{
                
            }Properties;

            virtual void showProperties(){
                ImGui::Begin("Properties",&GUI::EVENTS::showProperties,0);           
                    if(ImGui::InputText("Address",VARS.address,sizeof(VARS.address))){
                        
                    }
                    if(ImGui::InputText("Port",VARS.port,sizeof(VARS.port))){
                        
                    }
                    if(ImGui::Button("ANKLEBOT")){
                        sprintf(VARS.address,"192.168.0.66",sizeof("192.168.0.66"));
                        sprintf(VARS.port,"8000",sizeof("8000"));
                    }
                    
                    ShowDemoWindowWidgets();
                ImGui::End();
            }

        public:
    

            name_of_class(){

                sprintf(VARS.address,"127.0.0.1",sizeof("127.0.0.1"));
                sprintf(VARS.port,"27015",sizeof("27015"));

                name = name_of_block;
                TYPE = name_of_type;

                priority = 7;

                N_IN  = 1;
                
                N_OUT = 1;

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
                     VARS.app.updateSendBuffer("C: HOLA\n\0",sizeof("C: HOLA\n\0"));
                     
                     VARS.client = new ClientTCP((PCSTR)VARS.address,(PCSTR)VARS.port,&VARS.app);
                     if(VARS.client->initClient()){
                        LOCAL.double_clicked_count = 50;
                        GUI::MODAL_WARNING::setModal("No es posible iniciar el cliente","");
                        SIM::EVENTS::SimulationTaskMutex_end.store(true); 
                     }
                     LOCAL.double_clicked_count = 10;
                     if(VARS.client->tryConnect()){
                        LOCAL.double_clicked_count = 50;
                        GUI::MODAL_WARNING::setModal("El cliente no se pudo conectar","");
                        SIM::EVENTS::SimulationTaskMutex_end.store(true); 
                     }
                    
                     VARS.client->runLoop();

                     return;
                }
                if(SIM::EVENTS::time_index == LAST_LAP){
                    if(VARS.client->closeClient()){
                        LOCAL.double_clicked_count = 20;
                        GUI::MODAL_WARNING::setModal("No es posible detener el cliente","");
                        SIM::EVENTS::SimulationTaskMutex_end.store(true); 
                    }
                    VARS.client->waitJoin();      
                    return;
                }

                if((*IN_ARMA[1]).size()>=1){
                    VARS.app.updateSendBuffer((char *)(*IN_ARMA[1]).memptr(),((*IN_ARMA[1])[0]+1)*sizeof(float)) ;
                }

                int x = 0;
                VARS.app.readRecBuffer((char *) (OUT_ARMA[1].memptr()),&x);
                
                
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
