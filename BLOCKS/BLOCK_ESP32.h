#ifndef BLOCKS_H
    #include "BLOCKS.h"   
#endif

#define name_of_class  PPCAT(Block, name_of_object)
#define name_of_type   PPCAT(BLKType_, name_of_object)
#define name_of_block  STRINGIZE(name_of_object)
#define name_of_init   PPCAT(name_of_class,_INIT)
#define name_of_path   (std::string(name_of_block) + "/").c_str()

#include <Utils_COM.h>

namespace BLOCKS{

 class name_of_class : public BLOCK {
        private:       
        
            typedef struct {
                float S1;
                float S2;
            } ToRec;
            
            typedef struct {
                char Type [8];
            } ToSend;   

            static int count;
    
            struct VARS{
                ToSend * toSend;
                ToRec  * toRec;
                COM * esp32;
            }VARS;


            struct Properties{     
                
            }Properties ;

            virtual void showProperties(){
                ImGui::Begin("Properties",&GUI::EVENTS::showProperties,0);                               
                    ShowDemoWindowWidgets();
                ImGui::End();
            }

        public:
    

            name_of_class(){

                name = name_of_block;
                TYPE = name_of_type;

                // priority = 7;

                N_IN  = 0;
                N_OUT = 2;

                sizeBlock = ImVec2(100,50);
                
                N_IN_size  = sizeBlock.y/(float)(N_IN+1.0f);
                N_OUT_size = sizeBlock.y/(float)(N_OUT+1.0f);

                posIn.insert(posIn.begin(),N_IN+1,ImVec2(0,0));
                posOut.insert(posOut.begin(),N_OUT+1,ImVec2(0,0)); 

                arma::fmat auxOut ;
                auxOut << 0.0f;
                
                OUT_ARMA.insert(OUT_ARMA.begin(),N_OUT+1,auxOut); 
                IN_ARMA.insert(IN_ARMA.begin(),N_IN+1,new arma::fmat);  
           
                VARS.esp32 = new COM();
                VARS.esp32->LOCAL.buffRec_SIZE  = sizeof(ToRec);
                VARS.esp32->LOCAL.buffSend_SIZE = sizeof(ToSend);
                VARS.esp32->LOCAL.Parameter.BaudRate = 1000000;
                VARS.esp32->LOCAL.Parameter.ByteSize = 8;
                VARS.esp32->LOCAL.Parameter.StopBits = ONESTOPBIT;
                VARS.esp32->LOCAL.Parameter.Parity = NOPARITY;
                VARS.esp32->LOCAL.Parameter.fDtrControl = DTR_CONTROL_ENABLE;

                sprintf(VARS.esp32->LOCAL.portName,"\\\\.\\COM15");


                VARS.toSend = (ToSend *) VARS.esp32->LOCAL.buffSend;
                VARS.toRec  = (ToRec  *) VARS.esp32->LOCAL.buffRec;
                return;

            }

            virtual void Exec() override{
            /*Esta função será executada com cada um das repetições da simulação

                FIRST_LAP     -> Se estabelece a conexão com o hardware 
                                 e as primeroras configurações se precisa

                LAST_LAP      -> É a ultima volta da simulação, 
                                 aquí se fecham conexões e salva os dados

                n             -> Numero da entrada ou saida
                
                (*IN_ARMA)[n] -> Valor da entrada n

                OUT_ARMA[n]   -> Valor da saida n*/

                if(SIM::EVENTS::time_index == FIRST_LAP){
                    VARS.esp32->openCOM();

                    sprintf(VARS.toSend->Type,COM_BEGIN_TX);
                    VARS.esp32->sendCOM();
                    
                    VARS.esp32->recvCOM();

                    VARS.esp32->runLoop();
                    return;
                };
                if(SIM::EVENTS::time_index == LAST_LAP){
                    sprintf(VARS.toSend->Type,COM_END_TX);
                    VARS.esp32->sendCOM();   

                    VARS.esp32->closeCOM();
                    return;
                };

                OUT_ARMA[1] = VARS.toRec->S1;
                OUT_ARMA[2] = VARS.toRec->S2;


                

            }
            
            
            virtual void DrawADD(){ 
                //Mudar o estilo visual do bloco
            }    
            
            virtual BLOCK * Create(){
                return new name_of_class();
            }
            
            
    };

    void name_of_init(){
        ALL_BLOCKS_GUI[name_of_type] = new name_of_class();
        GUI::LOG_MSG =GUI::LOG_MSG + "\n   " + STRINGIZE(name_of_class)   + ": Cargado " ;
    }
 
 

};
