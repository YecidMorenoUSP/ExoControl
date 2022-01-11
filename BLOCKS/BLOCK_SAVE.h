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
                 arma::vec  tosave;
                 int index;
            }VARS;


            struct Properties{     
                
            }Properties ;

            virtual void showProperties(){
                ImGui::Begin("Properties",&GUI::EVENTS::showProperties,0);                               
                    ShowDemoWindowWidgets();
                ImGui::End();
            }

        public:
    
            void uvec_push(arma::vec  & v, float value) {
                arma::vec av(1);
                av.at(0) = value;
                v.insert_cols(v.n_cols, av.col(0));
            }

            name_of_class(){

                name = name_of_block;
                TYPE = name_of_type;

                // priority = 7;

                N_IN  = 1;
                N_OUT = 0;

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
            /*Esta função será executada com cada um das repetições da simulação

                FIRST_LAP     -> Se estabelece a conexão com o hardware 
                                 e as primeroras configurações se precisa

                LAST_LAP      -> É a ultima volta da simulação, 
                                 aquí se fecham conexões e salva os dados

                n             -> Numero da entrada ou saida
                
                (*IN_ARMA)[n] -> Valor da entrada n  (*IN_ARMA[1])

                OUT_ARMA[n]   -> Valor da saida n*/

                if(SIM::EVENTS::time_index == FIRST_LAP){
                    VARS.tosave.clear();
                    VARS.index = 0;
                    return;
                }
                if(SIM::EVENTS::time_index == LAST_LAP){
                    VARS.tosave.save("out.dat", raw_ascii);
                    return;
                }
                // VARS.tosave[VARS.index] =  as_scalar(*IN_ARMA[1]);
                // uvec_push(VARS.tosave,as_scalar(*IN_ARMA[1]));
                int sz = VARS.tosave.size();
                VARS.tosave.resize(sz+1);
                VARS.tosave(sz) = as_scalar(*IN_ARMA[1]);
                VARS.index ++;
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
