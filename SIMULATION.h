#define SIMULATION_H

namespace SIM{
    namespace EVENTS{
        float Ts = 5e-3;
        
        std::atomic<bool> SimulationTaskMutex_end(true);

        std::thread SimulationThread_;

        std::chrono::steady_clock::time_point time_begin;
        std::chrono::steady_clock::time_point time_cur;

        long time_index;
    };

    float GET_NANOS(){
        return std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::steady_clock::now() - EVENTS::time_begin).count()/1000000000.f;
    }

    void RUN(){
        EVENTS::time_index = 0;
        EVENTS::time_begin = std::chrono::steady_clock::now();
        while (true)
        {
            if(LINES::ALL_LINES_GUI.size()>= 1){
                iterateLINES_GUI{
                    (*it)->blockOut->Exec();
                }
                LINES::ALL_LINES_GUI.back()->blockIn->Exec();
            
            }
            

            EVENTS::time_index ++;
            while(std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::steady_clock::now() - EVENTS::time_begin).count()/1000000000.f <= EVENTS::time_index*EVENTS::Ts);  
            if (EVENTS::SimulationTaskMutex_end.load()) break;
        }
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        float time_task = std::chrono::duration_cast<std::chrono::milliseconds> (end - EVENTS::time_begin).count()/1000.f;
        std::cout << "Time difference = " << time_task << "[S]" << std::endl;
        printf(" N Cicles %d\n ",EVENTS::time_index);      
        printf(" Ts : %f  , Task TS : %f \n ",EVENTS::Ts,time_task/(float)EVENTS::time_index);      
    }
};