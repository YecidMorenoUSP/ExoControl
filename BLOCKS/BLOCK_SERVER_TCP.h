#ifndef BLOCKS_H
    #include "BLOCKS.h"   
#endif

#define name_of_class  PPCAT(Block, name_of_object)
#define name_of_type   PPCAT(BLKType_, name_of_object)
#define name_of_block  STRINGIZE(name_of_object)
#define name_of_init   PPCAT(name_of_class,_INIT)
#define name_of_path   (std::string(name_of_block) + "/").c_str()

#define SERVER_TCP_SEND_FIRST
// #define DEBUG_SERVER_TCP
#define DEFAULT_BUFLEN 512

#include <ServerTCP.h>


namespace BLOCKS{

 class name_of_class : public BLOCK {
        public:          

            static int count;
    
            struct VARS{
                ServerTCP * server;
                SharedBuffer app; 
                char port[10];         
                bool SERVER_TCP_SEND_FIRST_CH;     

            }VARS;


            struct Properties{
                
            }Properties;

            virtual void showProperties(){
                ImGui::Begin("Properties",&GUI::EVENTS::showProperties,0);           
                    if(ImGui::InputText("Port",VARS.port,sizeof(VARS.port))){
                        
                    }
                    // if(ImGui::Checkbox("SERVER_TCP_SEND_FIRST",&VARS.SERVER_TCP_SEND_FIRST_CH)){
                    //     #define SERVER_TCP_SEND_FIRST
                    // }else{
                    //     #undef SERVER_TCP_SEND_FIRST
                    // }
                    ShowDemoWindowWidgets();
                ImGui::End();
            }

        // public:
    

            name_of_class(){

                sprintf(VARS.port,"27015",sizeof("27015"));

                name = name_of_block;
                TYPE = name_of_type;

                priority = 8;

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

                // OUT_ARMA[1] = fmat::fixed<1, 3>();
                OUT_ARMA[1] = fmat::fixed<1, (int)(DEFAULT_BUFLEN/4)>();
                OUT_ARMA[1].fill(0);

            
                return;

            }

            virtual void Exec() override{
                
                if(SIM::EVENTS::time_index == FIRST_LAP){
                     VARS.app.updateSendBuffer("S: HOLA\n\0",sizeof("S: HOLA\n\0"));
                    //  VARS.app.updateRecBuffer(0,1);
                     ZeroMemory(VARS.app.recBuffer,DEFAULT_BUFLEN);

                     VARS.server = new ServerTCP((PCSTR)VARS.port,&VARS.app);
                     if(VARS.server->initServer()){
                        LOCAL.double_clicked_count = 50;
                        GUI::MODAL_WARNING::setModal("No es posible iniciar el servidor","");
                        SIM::EVENTS::SimulationTaskMutex_end.store(true); 
                     }
                     LOCAL.double_clicked_count = 10;
                     if(VARS.server->acceptClient()){
                        LOCAL.double_clicked_count = 50;
                        GUI::MODAL_WARNING::setModal("El cliente no es compatible","");
                        SIM::EVENTS::SimulationTaskMutex_end.store(true); 
                     }
                    
                      VARS.server->runLoop();

                     return;
                }
                if(SIM::EVENTS::time_index == LAST_LAP){
                    if(VARS.server->closeServer()){
                        LOCAL.double_clicked_count = 20;
                        GUI::MODAL_WARNING::setModal("No es posible detener el servidor","");
                        SIM::EVENTS::SimulationTaskMutex_end.store(true); 
                    }
                    VARS.server->waitJoin();      
                    return;
                }

                // VARS.app.updateSendBuffer("S: HOLA\n\0",sizeof("S: HOLA\n\0"));
                if((*IN_ARMA[1]).size()>=1){
                    VARS.app.updateSendBuffer((char *)(*IN_ARMA[1]).memptr(),((*IN_ARMA[1])[0]+1)*sizeof(float)) ;
                }

                int x = 0;
                VARS.app.readRecBuffer((char *) (OUT_ARMA[1].memptr()),&x);
                // OUT_ARMA[1][0] = x;
                // OUT_ARMA[1].print("OUT_ARMA : ");
                
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
