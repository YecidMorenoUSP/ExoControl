#define SIMULATION_H

#define FIRST_LAP -1
#define LAST_LAP  -2



namespace SIM{
    
    void setLOG(std::string txt);

    namespace EVENTS{
        //float Ts = 1.0f/2000.0f;
        float Ts = 1.0f/200.00f;

        
        std::atomic<bool> pauseSimulation(false);
        
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
        // std::cout<<"\n["<<name<<"] Req : ";
        iterateLINES_GUI{
            if((*it)->usedGrafo == true) continue;
            if((*it)->blockIn->name.compare(name) == 0){
                count ++;
                // std::cout<<" "<<(*it)->blockOut->name<<" & ";
            }
        }
        return count;
    }

    int getActivesGrafoOUT(std::string name){
        int count = 0;
        // std::cout<<"\n["<<name<<"] Open : ";
        iterateLINES_GUIL{
            if((*itL)->usedGrafo == true) continue;
            if((*itL)->blockOut->name.compare(name) == 0){
                count ++;
                // std::cout<<" "<<(*itL)->blockIn->name<<" & ";
            }
        }
        return count;
    }

    std::vector<BLOCKS::BLOCK*> getReqBlocks(std::string name){
        std::vector<BLOCKS::BLOCK*> aux;

        // std::cout<<"\n["<<name<<"] Req : ";
        iterateLINES_GUI{
            if((*it)->usedGrafo == true) continue;
            if((*it)->blockIn->name.compare(name) == 0){
                // std::cout<<" "<<(*it)->blockOut->name<<" & ";
                aux.push_back((*it)->blockOut);
            }
        }

        return aux;
    }

    std::vector<BLOCKS::BLOCK*> getOpenBlocks(std::string name){
        std::vector<BLOCKS::BLOCK*> aux;

        // std::cout<<"\n["<<name<<"] Req : ";
        iterateLINES_GUI{
            if((*it)->usedGrafo == true) continue;
            if((*it)->blockOut->name.compare(name) == 0){
                if(std::find(aux.begin(),aux.end(),(*it)->blockIn) == aux.end()){
                    aux.push_back((*it)->blockIn);
                }
                
            }
        }        

        return aux;
    }

 
    int getIndexBLOCKS(BLOCKS::BLOCK* block){
        int index = -1;

        iterateBLOCKS_GUI{
            if((*it)->name.compare(block->name) == 0){
                return (it-BLOCKS::ALL_BLOCKS_GUI.begin());
            }
        }

        return -1;
    }

    void releaseGrafosOpen(std::string name){
        iterateLINES_GUI{
            if((*it)->usedGrafo == true) continue;
            if((*it)->blockOut->name.compare(name) == 0){
                (*it)->usedGrafo = true;
            }
        }
    }

    bool BackPath(BLOCKS::BLOCK* block,std::string name){
        std::vector<BLOCKS::BLOCK*> Visitados;
        std::vector<BLOCKS::BLOCK*> BLOCK_QUEUE;

        BLOCK_QUEUE.push_back(block);
        
        bool visited;
        while(BLOCK_QUEUE.size()>0){
            visited = false;
            for  (std::vector<BLOCKS::BLOCK*>::iterator it = Visitados.begin() ; it != Visitados.end(); it++){
                if((*it)->name.compare(BLOCK_QUEUE.back()->name) == 0) {
                    visited = true;
                    break;
                }
            }

            if(visited){
                BLOCK_QUEUE.pop_back();
                continue;
            }

            Visitados.push_back(BLOCK_QUEUE.back());
            BLOCK_QUEUE.pop_back();

            iterateLINES_GUIL{
            if((*itL)->blockIn->name.compare(Visitados.back()->name) == 0)
                 BLOCK_QUEUE.push_back((*itL)->blockOut);
            }



        }
        

        for  (std::vector<BLOCKS::BLOCK*>::iterator it = Visitados.begin() ; it != Visitados.end(); it++){
            if((*it)->name.compare(name) == 0) return true;
        }

        return false;

    }

    void RUN(){

        SIM::EVENTS::pauseSimulation.store(false);
        

        // Limpiamos los grafos
        for  (std::vector<LINES::LINE*>::iterator   itL = LINES::ALL_LINES_GUI.begin() ; itL != LINES::ALL_LINES_GUI.end(); itL++){
            (*itL)->usedGrafo = false;
            if((*itL)->blockIn->name.compare((*itL)->blockOut->name) == 0)
                (*itL)->usedGrafo = true;
        }
        // Limpiamos los bloques visitados
        iterateBLOCKS_GUI{
            (*it)->VISITED = false;
        }

        /*
            1. Lo primero que debemos hacer es agregar a la cola los bloques existentes con máxima prioridad 6-10.
            2. Adicinamos los bloques desconectados
            3. Seguidamente usamos todas las fuentes como los bloques siguientes

            4. Adicionamos todos los sumideros para finalizar la ejecucion
            5. Agregar a la cola los bloques existentes con mínima prioridad 1-4.

        */

        std::vector<BLOCKS::BLOCK*> BLOCK_QUEUE;
        std::vector<BLOCKS::BLOCK*> BLOCK_ORDER;

        // 1. Lo primero que debemos hacer es agregar a la cola los bloques existentes con máxima prioridad 6-10.
        for(int indexPriority = 0 ; indexPriority <= 10 ; indexPriority ++)
        iterateBLOCKS_GUI{
            if(!(*it)->ACTIVE) continue;
            if((*it)->priority != indexPriority) continue;
            if(getActivesGrafo((*it)->name) == 0){
                if((*it)->priority == indexPriority){
                    if_exist_BLOCK_QUEUE{
                        BLOCK_QUEUE.push_back((*it));                    
                    }
                }
            }
        }           
        
        while (BLOCK_QUEUE.size()>0)
        {
            BLOCKS::BLOCK *blocCur = BLOCK_QUEUE.back();

            std::vector<BLOCKS::BLOCK*> reqs = getReqBlocks(blocCur->name);
            if(reqs.size() == 0 || blocCur->VISITED == true){

                 if(std::find(BLOCK_ORDER.begin(),BLOCK_ORDER.end(),BLOCK_QUEUE.back())==BLOCK_ORDER.end())
                    BLOCK_ORDER.push_back(BLOCK_QUEUE.back());

                 BLOCK_QUEUE.pop_back();
                 
                 std::vector<BLOCKS::BLOCK*> open = getOpenBlocks(blocCur->name);

                 if(open.size()>0){
                     releaseGrafosOpen(blocCur->name);
                     for  (std::vector<BLOCKS::BLOCK*>::iterator it = open.begin() ; it != open.end(); it++){
                         if(std::find(BLOCK_QUEUE.begin(),BLOCK_QUEUE.end(),(*it))==BLOCK_QUEUE.end())
                                 BLOCK_QUEUE.insert(BLOCK_QUEUE.begin(),(*it));

                     }

                 }
            }
            else{
                // BLOCK_QUEUE.insert(BLOCK_QUEUE.end(),reqs.begin(),reqs.end());
                for  (std::vector<BLOCKS::BLOCK*>::iterator it = reqs.begin() ; it != reqs.end(); it++){
                         if(std::find(BLOCK_QUEUE.begin(),BLOCK_QUEUE.end(),(*it))==BLOCK_QUEUE.end())
                                 BLOCK_QUEUE.insert(BLOCK_QUEUE.begin(),(*it));

                }
            }
          
            blocCur->VISITED = true;
        }
        
        // * * * * * * * * * * * INICIO TEST * * * * * * * * * * * *
        cout<<"\nTest . . .\n";
        for  (std::vector<BLOCKS::BLOCK*>::iterator it = BLOCK_ORDER.begin() ; it != BLOCK_ORDER.end(); it++){
                cout<<" || "<<(*it)->name;
        }    
        // * * * * * * * * * * * FIN TEST * * * * * * * * * * * * * 

        cout<<"\n**********************INICIANDO**********************\n";
        EVENTS::time_index = FIRST_LAP;
        EVENTS::time_begin = std::chrono::steady_clock::now();
        if(BLOCK_ORDER.size()>= 1){
            for (std::vector<BLOCKS::BLOCK*>::iterator   itL = BLOCK_ORDER.begin() ; itL != BLOCK_ORDER.end(); itL++){
                cout<<" || "<<(*itL)->name;
                try{
                    (*itL)->Exec();
                }catch(...){
                    EVENTS::SimulationTaskMutex_end.store(true);
                }
                if (EVENTS::SimulationTaskMutex_end.load()) break;
                while (SIM::EVENTS::pauseSimulation.load()){std::this_thread::yield();};       
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
                     while (SIM::EVENTS::pauseSimulation.load()){std::this_thread::yield();};
                }       
            }  
            EVENTS::time_index ++;
            while(std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::steady_clock::now() - EVENTS::time_begin).count()/1000000000.f <= EVENTS::time_index*EVENTS::Ts);  
        }
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        float time_task = std::chrono::duration_cast<std::chrono::milliseconds> (end - EVENTS::time_begin).count()/1000.f;
        // std::cout << "Time difference = " << time_task << "[S]" << std::endl;
        // printf(" N Cicles %d\n ",EVENTS::time_index);      
        // printf(" Ts : %f  , Task TS : %f \n ",EVENTS::Ts,time_task/(float)EVENTS::time_index);     
        setLOG(""); 

        std::ostringstream forLog; 
        forLog<<"Time difference = " << time_task << "[S]"<<"\n";
        forLog<<" Time Ts : "<<EVENTS::Ts<<"\n"
              <<" Task TS : "<<time_task/(float)EVENTS::time_index<<"\n";
        setLOG(forLog.str()); 

        EVENTS::time_index = LAST_LAP;
        if(BLOCK_ORDER.size()>= 1){
            for  (std::vector<BLOCKS::BLOCK*>::iterator   itL = BLOCK_ORDER.begin() ; itL != BLOCK_ORDER.end(); itL++){
                 (*itL)->Exec();
                 
            }      
        }
    }
};
