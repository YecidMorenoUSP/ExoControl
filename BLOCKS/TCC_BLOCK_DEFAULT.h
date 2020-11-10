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
                /*Variaveis do bloco, são so de uso interno. 
                    Resultado de operações, Cores, constantes */
            }VARS;
 
            struct Properties{
                /*Propiedades do bloco, vão ser apresentadas na janela PROPERTIES*/
            }Properties;
 
            virtual void showProperties(){
                ImGui::Begin("Properties",&GUI::EVENTS::showProperties,0);            
                    ShowDemoWindowWidgets(); //Demo da GUI em properties
                /*Todo o que estiver aquí vai ser apresentado na janela PROPERTIES.
                    Desenho de botão, slider, checkBox com ImGui.
                    Pode olhar a função ShowDemoWindowWidgets(); para mais ajuda*/
                ImGui::End();
            }
 
        public:
            name_of_class(){
                name = name_of_block;
                TYPE = name_of_type;
 
                N_IN  = 1; //Numero de entradas
                N_OUT = 1; //Numero de saidas
                
                arma::fmat auxOut = {0.0f};
                
                OUT_ARMA.insert(OUT_ARMA.begin(),N_OUT+1,auxOut); 
                IN_ARMA.insert(IN_ARMA.begin(),N_IN+1,new arma::fmat);            
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
            }
            
            
            virtual void DrawADD(){ 
                //Mudar o estilo visual do bloco
            }    
            
    };
 
};
