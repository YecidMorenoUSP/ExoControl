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
                N_OUT = 3;
                
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
            BlockCAN_CFG * BlockCAN;
            

            virtual void Exec() override{
                //static __T1__
                //static __T2__
                
                
                if(SIM::EVENTS::time_index == FIRST_LAP){
                    // cout<<"Cargando  "<<GUI::BLOCK_findByName("CAN_CFG(1)")->name;
                    CAN =  ((BlockCAN_CFG*)(GUI::BLOCK_findByName("CAN_CFG(1)")))->CAN;
                    BlockCAN = ((BlockCAN_CFG*)(GUI::BLOCK_findByName("CAN_CFG(1)")));                    
                    
                    CAN->configure(Properties.nodeId);
                    CAN->setState(Properties.nodeId,ST_ENABLED);
                    CAN->configureInputs(Properties.nodeId);

                    BlockCAN->VARS.f.mtx.lock();
                    BlockCAN->VARS.f.writeEpos [Properties.nodeId] = (int)(*IN_ARMA[1])[0];
                    BlockCAN->VARS.f.readPosition [Properties.nodeId] = (float*)OUT_ARMA[1].memptr();
                    BlockCAN->VARS.f.readAnalog   [Properties.nodeId*1000 + 1] = (float*)OUT_ARMA[2].memptr();
                    BlockCAN->VARS.f.readAnalog   [Properties.nodeId*1000 + 2] = (float*)OUT_ARMA[3].memptr();
                    SIM::EVENTS::pauseSimulation.store(true);
                    BlockCAN->VARS.f.mtx.unlock();
                    

                    // CAN->setVelocity(100);
                    
                    cout<<"Cargado";
                    return;
                 }
                
                 if(SIM::EVENTS::time_index == LAST_LAP){
                    
                    CAN->setVelocity(Properties.nodeId,0);
                    CAN->setState(Properties.nodeId,ST_DISABLED);
                    return;
                }
                //__TIC__


                if((*IN_ARMA[1]).size()>=1){
                    BlockCAN->VARS.f.mtx.lock();
                    BlockCAN->VARS.f.writeEpos [Properties.nodeId] = (int)(*IN_ARMA[1])[0];
                    BlockCAN->VARS.f.mtx.unlock();
                }
                if (N_OUT >= 1 && true){
                    BlockCAN->VARS.f.mtx.lock();
                    BlockCAN->VARS.f.readPosition [Properties.nodeId] = (float*)OUT_ARMA[1].memptr();
                    BlockCAN->VARS.f.readAnalog   [Properties.nodeId*1000 + 1] = (float*)OUT_ARMA[2].memptr();
                    BlockCAN->VARS.f.readAnalog   [Properties.nodeId*1000 + 2] = (float*)OUT_ARMA[3].memptr();
                    BlockCAN->VARS.f.mtx.unlock();
                }
                


                            
                //__TOC__
                //std::cout<<"Epos: "<<name;
                //__SHOWTL__
              
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
