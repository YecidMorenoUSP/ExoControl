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

            static int count;
    
            struct VARS{
                arma::fmat::fixed<10,1> pos_v10;
                float meadia_n_1;
                int index;
                int index_activate;
                double faixa;
                double pos_d_1;
            }VARS;


            struct Properties{     
                float Amp_FES;
                int Time_FES;
            }Properties ;

            virtual void showProperties(){
                ImGui::Begin("Properties",&GUI::EVENTS::showProperties,0);                               
                    // ShowDemoWindowWidgets();
                    ImGui::InputFloat( "Amp_FES", &(Properties.Amp_FES), 0, 100.0f, "%.3f");
                    ImGui::InputInt( "Time_FES", &(Properties.Time_FES), 1, 10);
                ImGui::End();
            }

        public:
    

            name_of_class(){

                name = name_of_block;
                TYPE = name_of_type;

                // priority = 7;

                N_IN  = 4;
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
           
                Properties.Amp_FES = 22.0f;
                Properties.Time_FES = 100.0f;
                return;

            }

            virtual void Exec() override{
   
                if(SIM::EVENTS::time_index == FIRST_LAP){
                    // Inicialiçar os DATA_LOG
                    VARS.index = 0;
                    VARS.index_activate = 0;
                    VARS.meadia_n_1 = 0;
                    VARS.faixa = 0.15f;
                    VARS.pos_d_1 = 0;
                    return;   
                }
                if(SIM::EVENTS::time_index == LAST_LAP){
                    return;
                }

                /*VARS.pos_v10[VARS.index%10] = arma::as_scalar((*IN_ARMA[1]));
                
                if(VARS.index%10 == 9){
                    float media_cur = arma::mean(VARS.pos_v10);
                    if(VARS.meadia_n_1 > 0 && media_cur < 0){
                        //ATIVAR AS FES depois de T segundos
                        VARS.index_activate = 200;
                        OUT_ARMA[1] = Properties.Amp_FES;
                    }
                    VARS.meadia_n_1 = media_cur;
                }

                // MEdia de 10 amostras > 0 e ativar as FES

                // Salvar os dados

                VARS.index += 1;
                if(VARS.index_activate>0) {
                    OUT_ARMA[1] = Properties.Amp_FES;
                    VARS.index_activate--;
                    printf("\n\n Estimulando");
                }else{
                    OUT_ARMA[1] = 0.0f;
                }*/
                
                double pos_dp = arma::as_scalar((*IN_ARMA[1]));
                double pos_d  = arma::as_scalar((*IN_ARMA[2]));
                double vel_dp = arma::as_scalar((*IN_ARMA[3]));

                double vel_d = pos_d - VARS.pos_d_1; // / Ts
                
                

                if(pos_dp > (-VARS.faixa) &&  pos_dp < VARS.faixa ){
                    if(vel_d > 0.05 && vel_dp > 0.05 ){
                        VARS.index_activate = Properties.Time_FES;
                    }
                }

                if(VARS.index_activate >= 0 ){
                    OUT_ARMA[1] = Properties.Amp_FES;
                    VARS.index_activate--;
                }else{
                    OUT_ARMA[1] = 0.0f;
                }

                VARS.pos_d_1 = vel_d;

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
