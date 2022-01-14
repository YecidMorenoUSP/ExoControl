#ifndef BLOCKS_H
    #include "BLOCKS.h"   
#endif

#include <rehamovelib.c>

#define name_of_class  PPCAT(Block, name_of_object)
#define name_of_type   PPCAT(BLKType_, name_of_object)
#define name_of_block  STRINGIZE(name_of_object)
#define name_of_init   PPCAT(name_of_class,_INIT)


namespace BLOCKS{

 class name_of_class : public BLOCK {
        public:
            static int count;
            RehamoveDevice * FES;
             struct Properties{
                std::string nameCOM = "COM3";
                int Freq = 30; 
            }Properties;


            class foo
            {
                public:
               
                RehamoveDevice * FES;
                std::atomic<bool>  running_mutex;
                std::mutex mtx;
                std::string nameCOM = "COM3";
                float min = 10;
                float max = 60;
                float mA = 0;
                float onExecmA=0;

                int Freq = 30;

                float mA_export = 0;

                void runTest(int x){
                    FES = open_port(nameCOM.c_str()); 
                    if(FES == NULL) {
                        close_port(FES);
                        return;
                    }
                    for( mA = min ; mA < max; mA+=5){                      

                        mtx.lock();
                            mA_export = mA;
                        mtx.unlock();

                        
                        for(int i = 0 ; i < 60; i++){
                            std::this_thread::yield();
                            if (running_mutex.load()) break;
                            pulse(FES,Smpt_Channel::Smpt_Channel_Blue,mA,Freq); 
                        }

                        std::this_thread::yield();
                        if (running_mutex.load()) break;
                            
                    }
                        
                    close_port(FES);
                    running_mutex.store(true);
                }
                void bar()
                {
                   runTest(0);
                }

                void test_k(){
                    FES = open_port(nameCOM.c_str()); 
                    if(FES == NULL) {
                        close_port(FES);
                        return;
                    }
                  
                    
                    for(int i = 0 ; i < 60*4; i++){
                        std::this_thread::yield();
                        if (running_mutex.load()) break;
                        pulse(FES,Smpt_Channel::Smpt_Channel_Blue,mA,Freq); 
                    }
                
                        
                    close_port(FES);
                    running_mutex.store(true);
                }

                void onExec(){
                    FES = open_port(nameCOM.c_str()); 
                    if(FES == NULL) {
                        close_port(FES);
                        return;
                    }
                  
                    while(!running_mutex.load()){
                        pulse(FES,Smpt_Channel::Smpt_Channel_Blue,onExecmA,Freq); 
                    }
                
                        
                    close_port(FES);
                    running_mutex.store(true);
                }
                
                
            };

            struct VARS{
                ImVec4 colors[4] = {ImVec4(0.06f, 0.59f, 0.87f, 1.00f),
                                    ImVec4(1.00f, 0.46f, 0.00f, 1.00f),
                                    ImVec4(0.31f, 0.94f, 0.11f, 1.00f),      
                                    ImVec4(0.62f, 0.10f, 1.00f, 1.00f)};
                std::thread TestThread_;
                foo f;
            }VARS;

           

            struct{
                bool CALIBRATING = false;
                float min = 10;
                float max = 60;

                float mA_K = 20;
                
            }TEST;
            std::vector<std::thread> threads;
            

             
            

            virtual void showProperties(){
                ImGui::Begin("Properties",&GUI::EVENTS::showProperties,0); 
                ImGui::InputText(("COM Port"), (char*)Properties.nameCOM.c_str() , size_t(Properties.nameCOM.c_str()));
                if(ImGui::InputInt( "Freq", &(VARS.f.Freq))){
                    
                }
                if(ImGui::InputFloat( "Min_mA", &(TEST.min), 0.0f, 50.0f, "%.3f")){
                    if(TEST.min>TEST.max) TEST.min = 0;
                }
                if(ImGui::InputFloat( "Max_mA", &(TEST.max), 0.0f, 200.0f, "%.3f")){
                    if(TEST.max<TEST.min){
                        TEST.min = 0;
                        TEST.max = 40;
                    }
                }
                if(ImGui::Button("Calibrate")){
                    if(VARS.f.running_mutex.load()){
                        
                        if(VARS.TestThread_.joinable())VARS.TestThread_.join();

                        VARS.f.running_mutex.store(false);
                        VARS.f.min = TEST.min;
                        VARS.f.max = TEST.max;
                        
                        
                        VARS.TestThread_ =  std::thread(&foo::bar, &VARS.f);
                        // threads.push_back(std::thread(runTest,0));
                    }else{
                        
                        VARS.f.running_mutex.store(true);
                        if(VARS.TestThread_.joinable())VARS.TestThread_.join();
                    }                    
                    
                }
                ImGui::SameLine();
                ImGui::LabelText("#info","mA: %f",VARS.f.mA);

                if(ImGui::InputFloat( "mA_K", &(VARS.f.mA), 0.0f, 200.0f, "%.3f")){}

                if(ImGui::Button("Test_K")){
                    if(VARS.f.running_mutex.load()){
                        
                        if(VARS.TestThread_.joinable())VARS.TestThread_.join();

                        VARS.f.running_mutex.store(false);
                        // VARS.f.mA = TEST.mA_K;                     
                        
                        VARS.TestThread_ =  std::thread(&foo::test_k, &VARS.f);

                    }else{
                        
                        VARS.f.running_mutex.store(true);
                        if(VARS.TestThread_.joinable())VARS.TestThread_.join();
                    }                    
                    
                }
         

                ShowDemoWindowWidgets();
                ImGui::End();
            }

        // public:
        
            name_of_class(){
                VARS.f.running_mutex.store(true);
                name = name_of_block;
                TYPE = name_of_type;

                N_IN  = 4;
                N_OUT = 0;
                
                sizeBlock = ImVec2(90,60);

                N_IN_size  = sizeBlock.y/(float)(N_IN+1.0f);
                N_OUT_size = sizeBlock.y/(float)(N_OUT+1.0f);

                posIn.insert(posIn.begin(),N_IN+1,ImVec2(0,0));
                posOut.insert(posOut.begin(),N_OUT+1,ImVec2(0,0)); 

                arma::fmat auxOut ;
                auxOut << 0.0f;
                
                OUT_ARMA.insert(OUT_ARMA.begin(),N_OUT+1,auxOut); 
                IN_ARMA.insert(IN_ARMA.begin(),N_IN+1,new arma::fmat);            
            
            }

            virtual void Exec() override{
                // if(SIM::EVENTS::time_index == FIRST_LAP){
                //     FES = open_port(Properties.nameCOM.c_str());
                //     if(FES == NULL) {
                //         LOCAL.double_clicked_count = 50;
                //         close_port(FES);
                //         GUI::MODAL_WARNING::setModal("SIMULATION FAILED","RehaMove : "+Properties.nameCOM+" with Error","");
                //         SIM::EVENTS::SimulationTaskMutex_end.store(true); 
                        
                //     }
                //     return;
                //  }
                //  if(SIM::EVENTS::time_index == LAST_LAP){
                //      close_port(FES);
                //     return;
                //  }
                // pulse(FES,Smpt_Channel::Smpt_Channel_Blue,(*IN_ARMA[1])[0],30); 

                if(SIM::EVENTS::time_index == FIRST_LAP){
                    if(VARS.TestThread_.joinable())VARS.TestThread_.join();
                    VARS.f.running_mutex.store(false);    
                    VARS.f.onExecmA = 0;
                    VARS.TestThread_ =  std::thread(&foo::onExec, &VARS.f);
                    return;
                }

                if(SIM::EVENTS::time_index == LAST_LAP){
                    VARS.f.running_mutex.store(true);
                    if(VARS.TestThread_.joinable())VARS.TestThread_.join();
                    return;
                }

                VARS.f.onExecmA = (*IN_ARMA[1])[0];

            }
            
            virtual BLOCK * Create(){
                return new name_of_class();
            }
            
            virtual void DrawADD(){
                ImDrawList* draw_list = ImGui::GetWindowDrawList();
                for(int i  = 1 ; i <= N_IN ; i++)
                    draw_list->AddCircleFilled(posIn[i],5,ImGui::GetColorU32(VARS.colors[i-1]));
                
            }    
            
    };

    void name_of_init(){
        ALL_BLOCKS_GUI[name_of_type] = new name_of_class();
        GUI::LOG_MSG =GUI::LOG_MSG + "\n   " + STRINGIZE(name_of_class)   + ": Cargado " ;
    }
 
 

};
