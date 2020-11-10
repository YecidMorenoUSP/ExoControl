#define SIMULATION_H

#define FIRST_LAP -1
#define LAST_LAP  -2

namespace SIM{
    
    namespace EVENTS{
        //float Ts = 1.0f/2000.0f;
        float Ts = 1.0f/200.0f;
        
        std::atomic<bool> SimulationTaskMutex_end(true);

        std::thread SimulationThread_;

        std::chrono::steady_clock::time_point time_begin;
        std::chrono::steady_clock::time_point time_cur;

        long time_index;

    };

    float GET_NANOS(){
        return std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::steady_clock::now() - EVENTS::time_begin).count()/1000000000.f;
    }

    int getActivesGrafo(std::string name){
        int count = 0;
        iterateLINES_GUI{
            if((*it)->usedGrafo == true) continue;
            if((*it)->blockIn->name.compare(name) == 0) count ++;
        }
        return count;
    }

    void RUN(){

        std::vector<BLOCKS::BLOCK*> BLOCK_QUEUE;
        std::vector<BLOCKS::BLOCK*> BLOCK_ORDER;

        iterateLINES_GUI{
            (*it)->usedGrafo = false;
        }
    
        iterateBLOCKS_GUI{
            if((*it)->N_IN == 0) BLOCK_QUEUE.push_back((*it));
        }

        int i = 0;
        while (BLOCK_QUEUE.size()>0)
        {
            if(i>=20) break;
            BLOCKS::BLOCK *blocCur = BLOCK_QUEUE.back();
            BLOCK_ORDER.push_back(blocCur);
            BLOCK_QUEUE.pop_back();

            printf("\n %d  ->  %s",i++,blocCur->name.c_str());
            
            
            for  (std::vector<LINES::LINE*>::iterator   itL = LINES::ALL_LINES_GUI.begin() ; itL != LINES::ALL_LINES_GUI.end(); itL++){
                if((*itL)->usedGrafo == true ) continue;
                if((*itL)->blockOut->name.compare(blocCur->name) == 0 ) (*itL)->usedGrafo = true;

                //if((*itL)->blockOut->name.compare(blocCur->name) == 0){
                //    
                //    int gaG = getActivesGrafo((*itL)->blockIn->name);
                //    cout<<"gag "<<(*itL)->blockIn->name<<" : "<<gaG<<" | ";
                //    if(gaG>=1){
                //        (*itL)->usedGrafo == true;
                //    } 
                //    if(gaG == 1) BLOCK_QUEUE.push_back((*itL)->blockIn);
                //}
            }

            for  (std::vector<LINES::LINE*>::iterator   itL = LINES::ALL_LINES_GUI.begin() ; itL != LINES::ALL_LINES_GUI.end(); itL++){
                if((*itL)->usedGrafo == true ) continue;
                int gaG = getActivesGrafo((*itL)->blockOut->name);
                if(gaG == 0) BLOCK_QUEUE.push_back((*itL)->blockOut);
            }

        }
        
        iterateBLOCKS_GUI{
            if((*it)->N_OUT == 0) BLOCK_ORDER.push_back((*it));
        }


        cout<<"\n**********************INICIANDO**********************\n";
        EVENTS::time_index = FIRST_LAP;
        EVENTS::time_begin = std::chrono::steady_clock::now();
        if(BLOCK_ORDER.size()>= 1){
            for  (std::vector<BLOCKS::BLOCK*>::iterator   itL = BLOCK_ORDER.begin() ; itL != BLOCK_ORDER.end(); itL++){
                 (*itL)->Exec();
                 cout<<" || "<<(*itL)->name;
                 if (EVENTS::SimulationTaskMutex_end.load()) break;
            }       
        }

        if (EVENTS::SimulationTaskMutex_end.load()) return;

        EVENTS::time_index = 0;
        EVENTS::time_begin = std::chrono::steady_clock::now();
        while (true)
        {   
            if (EVENTS::SimulationTaskMutex_end.load()) break;
            
            if(BLOCK_ORDER.size()>= 1){
                for  (std::vector<BLOCKS::BLOCK*>::iterator   itL = BLOCK_ORDER.begin() ; itL != BLOCK_ORDER.end(); itL++){
                    (*itL)->Exec();
                }       
            }
            

            EVENTS::time_index ++;
            while(std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::steady_clock::now() - EVENTS::time_begin).count()/1000000000.f <= EVENTS::time_index*EVENTS::Ts);  
        }
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        float time_task = std::chrono::duration_cast<std::chrono::milliseconds> (end - EVENTS::time_begin).count()/1000.f;
        std::cout << "Time difference = " << time_task << "[S]" << std::endl;
        printf(" N Cicles %d\n ",EVENTS::time_index);      
        printf(" Ts : %f  , Task TS : %f \n ",EVENTS::Ts,time_task/(float)EVENTS::time_index);      

        EVENTS::time_index = LAST_LAP;
        if(BLOCK_ORDER.size()>= 1){
            for  (std::vector<BLOCKS::BLOCK*>::iterator   itL = BLOCK_ORDER.begin() ; itL != BLOCK_ORDER.end(); itL++){
                 (*itL)->Exec();
            }       
        }
    }
};