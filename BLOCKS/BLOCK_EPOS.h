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
                
            }VARS;

            struct Properties{
                int nodeId = 1;
            }Properties;

            virtual void showProperties(){
                ImGui::Begin("Properties",&GUI::EVENTS::showProperties,0);            
                    ImGui::InputInt("input int", &Properties.nodeId);
                ImGui::End();
            }

        public:
        
            name_of_class(){
                name = name_of_block;
                TYPE = name_of_type;

                N_IN  = 1;
                N_OUT = 2;
                
                N_IN_size  = sizeBlock.y/(float)(N_IN+1.0f);
                N_OUT_size = sizeBlock.y/(float)(N_OUT+1.0f);

                posIn.insert(posIn.begin(),N_IN+1,ImVec2(0,0));
                posOut.insert(posOut.begin(),N_OUT+1,ImVec2(0,0)); 

                arma::fmat auxOut ;
                auxOut << 0.0f;
                
                OUT_ARMA.insert(OUT_ARMA.begin(),N_OUT+1,auxOut); 
                IN_ARMA.insert(IN_ARMA.begin(),N_IN+1,new arma::fmat);            
                
            }

            CAN_Network * CAN;

            virtual void Exec() override{
                if(SIM::EVENTS::time_index == FIRST_LAP){
                    // cout<<"Cargando  "<<GUI::BLOCK_findByName("CAN_CFG(1)")->name;
                    CAN =  ((BlockCAN_CFG*)(GUI::BLOCK_findByName("CAN_CFG(1)")))->CAN;
                    CAN->nodeId = Properties.nodeId;
                    CAN->configure();
                    CAN->setState(ST_ENABLED);
                    // CAN->setVelocity(100);

                    cout<<"Cargado";
                    return;
                 }
                CAN->nodeId = Properties.nodeId;
                CAN->setVelocity((int)(*IN_ARMA[1])[0]);
                OUT_ARMA[1] = CAN->positionRead();
                OUT_ARMA[2] = CAN->analogRead(1);
                
                 if(SIM::EVENTS::time_index == LAST_LAP){
                    CAN->setState(ST_DISABLED);
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
            
    };

    void name_of_init(){
        ALL_BLOCKS_GUI[name_of_type] = new name_of_class();
        GUI::LOG_MSG =GUI::LOG_MSG + "\n   " + STRINGIZE(name_of_class)   + ": Cargado " ;
    }
 
 

};
