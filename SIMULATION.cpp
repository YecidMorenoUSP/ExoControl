#ifndef SIMULATION_H
    #include "SIMULATION.h"
#endif

namespace SIM{
     void setLOG(std::string txt){
        if(txt == "") GUI::LOG_MSG = "";
        else GUI::LOG_MSG = txt;
    }
};