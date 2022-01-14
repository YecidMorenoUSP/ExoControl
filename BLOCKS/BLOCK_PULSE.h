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
        public:          

            static int count;

            arma::fvec points = zeros<fvec>(6);
            arma::fvec coff =  {-137.0f/60.0f,5.0f,-5.0f,10.0f/3.0f,-5.0f/4.0f,1.0f/5.0f};
            arma::fvec Dxs = zeros<fvec>(20);
            struct VARS{
                float Dx = 0.0f;
                int Ticks1 = 0;
                int Ticks2 = 0;
                int count = 0;
                
            }VARS;


            struct Properties{ 
                float th = 0.5;
                float Amplitude1 = 1;
                float Amplitude2 = 0;
                float T1 = .5;                
                float T2 = .5;       

                
                int item_current = 0;
                

            }Properties ;

            virtual void showProperties(){
                ImGui::Begin("Properties",&GUI::EVENTS::showProperties,0);        
                
                    const char* items[] = { "Dx > 0", "Dx < 0", "Dx > 0 & MOC ", "Dx < 0 & MOC" };
                    ImGui::Combo("Type Pulse", &Properties.item_current, items, IM_ARRAYSIZE(items));
                    ImGui::SliderFloat("< Dx >", &Properties.th, -10.0f, 10.0f, "%.3f");
                    ImGui::SameLine();
                    ImGui::LabelText("#info","Dx: %f",VARS.Dx);

                    ImGui::SliderFloat("Amplitude_On", &Properties.Amplitude1, -100.0f, 200.0f, "%.3f");
                    ImGui::SliderFloat("Amplitude_Off", &Properties.Amplitude2, -100.0f, 200.0f, "%.3f");
                    ImGui::InputFloat("Time_On", &Properties.T1, 0.1f, 10.0f, "%.3f");
                    ImGui::InputFloat("Time_Off", &Properties.T2, 0.1f, 10.0f, "%.3f");
                    ShowDemoWindowWidgets();
                ImGui::End();
            }

        // public:
    

            name_of_class(){

                coff = -arma::reverse(coff);

                name = name_of_block;
                TYPE = name_of_type;

                // priority = 7;

                N_IN  = 1;
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
           
                return;

            }

            void fvec_push(arma::fvec & v, float value) {
                arma::fvec av(1);
                av.at(0) = value;
                v.insert_rows(v.n_rows, av.row(0));
            }

            void fvec_pop0(arma::fvec & v, unsigned int idx) {
                v.shed_row(idx);
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

                if(SIM::EVENTS::time_index == FIRST_LAP)return;
                if(SIM::EVENTS::time_index == LAST_LAP)return;

                fvec_push(points,(*IN_ARMA[1])[0]);
                fvec_pop0(points,0);
            
                VARS.Dx = as_scalar(arma::sum((coff)%points)) / (6.0f*SIM::EVENTS::Ts);
                
                fvec_push(Dxs, VARS.Dx );
                fvec_pop0(Dxs,0);

                OUT_ARMA[2] = as_scalar(arma::mean(Dxs));

                if(VARS.Ticks1 <= 0 && VARS.Ticks2 <= 0)

                switch (Properties.item_current)
                {
                case 0:
                        if( as_scalar(arma::mean(Dxs)) >=Properties.th){
                            VARS.Ticks1 = (int)(Properties.T1 / SIM::EVENTS::Ts);
                            VARS.Ticks2 = (int)(Properties.T2 / SIM::EVENTS::Ts);
                        }
                    break;
                case 2:
                        if( as_scalar(arma::mean(Dxs)) >=Properties.th && arma::mean(points) > 0.0f){
                            VARS.Ticks1 = (int)(Properties.T1 / SIM::EVENTS::Ts);
                            VARS.Ticks2 = (int)(Properties.T2 / SIM::EVENTS::Ts);
                        }
                    break;
                
                default:
                    break;
                }

                if(VARS.Ticks1>0){
                    VARS.Ticks1--;
                    OUT_ARMA[1] = Properties.Amplitude1;
                }else if(VARS.Ticks2>0){
                    VARS.Ticks2--;
                    OUT_ARMA[1] = Properties.Amplitude2;
                }else{
                    OUT_ARMA[1] = Properties.Amplitude2;
                }
                

                

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
