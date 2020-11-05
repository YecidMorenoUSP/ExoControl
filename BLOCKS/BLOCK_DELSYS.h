#ifndef BLOCKS_H
    #include "BLOCKS.h"   
#endif


#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>
#include <Ws2tcpip.h>

#define name_of_class  PPCAT(Block, name_of_object)
#define name_of_type   PPCAT(BLKType_, name_of_object)
#define name_of_block  STRINGIZE(name_of_object)
#define name_of_init   PPCAT(name_of_class,_INIT)

#define START_COMMAND_DELSYS "START\r\n\r\n"
#define STOP_COMMAND_DELSYS  "STOP\r\n\r\n"
#define QUIT_COMMAND_DELSYS  "QUIT\r\n\r\n"





namespace BLOCKS{

 class name_of_class : public BLOCK {
        private:
            static int count;
            SOCKET commSock;
            SOCKET emgSock;
            struct VARS{
                double * dataEMG;
                char response[32];
                char tmp[128];
                char tmp2[100000];
                int k;
                char emgbuf[4*16];		
                char accbuf[4*3*16];
                char imemgbuf[4*16];
                unsigned long bytesRead;
                float EMG_VALUES[16];
                float emgsample;
            }VARS;

            struct Properties{
                bool Connect = false;
                bool  EMG_Active[16];
            }Properties;

            void SendCommandWithResponse(char * command, char * response)
            {
                int n;
                char tmp[128];

                strcpy_s(tmp,128, command);
                tmp[strlen(command)-2]=0;	//trip last CR/LF 
                printf("Command: %s", tmp);	//display to userj


                
                if (send(commSock,command,(int) strlen(command),(int) 0) == SOCKET_ERROR) 
                {
                    printf("Can't send command.\n");
                    _exit(1);
                }

                n=recv(commSock, tmp, sizeof(tmp), 0);
                tmp[n-2]=0;	//strip last CR/LF
                printf("Response: %s", tmp);	//display to user
                strcpy_s(response, 128 ,tmp);	//return the response line

            }
            bool ConnectEMG()
            {

                Properties.Connect = false;
                
                    char response[32];//buffee for response

                    WSADATA wsaData;	//Windows socket data
                    int iResult;	//result of call




                    /*Comprueba que se inicializa los winsocks (es lo primero que se debehacer antes de llamar las otras funciones)
                    y comprueba que sea compatible con el sistema por medio de MAKEWORD 2,2 DLL */
                    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
                        if (iResult != 0)
                    {
                            cout<<"\nWSAStartup failed\n";
                            return false;	
                        }


                // Leer del TextBox
                    
                    char ip[] = "127.0.0.1";

                    //Verificar si la IP es valida y cumple con el protocolo
                        char* port = NULL;
                        struct addrinfo aiHints;
                        struct addrinfo *aiList = NULL;
                        int retVal;

                        memset(&aiHints, 0, sizeof(aiHints));
                        aiHints.ai_family = AF_INET;
                        aiHints.ai_socktype = SOCK_STREAM;
                        aiHints.ai_protocol = IPPROTO_TCP;


                        if ((retVal = getaddrinfo(ip, port, &aiHints, &aiList)) != 0)
                    {
                        cout<<"\ngetaddrinfo error: " ;
                        return false;
                    } 
                        else
                    {
                        cout<<"\n Valido";
                    }

                        //Conexion con el  Trigno
                        commSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
                        sockaddr_in sinRemote;
                        sinRemote.sin_family = AF_INET;
                        sinRemote.sin_addr.s_addr = ((sockaddr_in*)(aiList->ai_addr))->sin_addr.s_addr;
                        sinRemote.sin_port = htons(50040);

                        //Try to connect 
                        if (connect(commSock, (sockaddr*)&sinRemote, sizeof(sockaddr_in)) == SOCKET_ERROR)
                        {
                        cout<<"\nCan't connect to Trigno Server!";
                            return false;	//server is not responding
                        }
                        else
                        {
                            cout<<"\nConnected to Trigno Server.\n";
                        }

                        
                        emgSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
                        sinRemote.sin_port = htons(50041);
                        if (connect(emgSock, (sockaddr*)&sinRemote, sizeof(sockaddr_in)) == SOCKET_ERROR)
                        {
                            printf("Error initializing Trigno EMG data connection (can't connect).\n"); //"11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
                        return false;
                        }
                        Properties.Connect = true;
                        return true;

            }
            void DisconnectEMG()
            {

                if(!Properties.Connect) return;
                SendCommandWithResponse(STOP_COMMAND_DELSYS, VARS.tmp);
                closesocket(commSock);
                closesocket(emgSock);
                Properties.Connect = false;
                        
                    cout<<"\nEMG Disconnect";
                        //server is not responding
                    
            
            }
            void StartCaptureEMG(){
                if(!Properties.Connect) return;
                SendCommandWithResponse(START_COMMAND_DELSYS, VARS.tmp);
                ioctlsocket(emgSock, FIONREAD, &VARS.bytesRead);
                recv(emgSock, VARS.tmp2, VARS.bytesRead, 0);
            }
            void StopCaptureEMG(){
                if(!Properties.Connect) return;
                    SendCommandWithResponse(STOP_COMMAND_DELSYS, VARS.tmp);
            }
            bool CaptureEMG(){
                ioctlsocket(emgSock, FIONREAD, &VARS.bytesRead);	
                if(VARS.bytesRead >= sizeof(VARS.emgbuf)){ 
                                
                        VARS.k=recv(emgSock, VARS.emgbuf, sizeof(VARS.emgbuf), 0);
                        for(int s = 1 ; s <= 16 ; s++){
                            memcpy(&VARS.emgsample, &VARS.emgbuf[4*(s-1)], sizeof(VARS.emgsample));
                            VARS.EMG_VALUES[s-1] = VARS.emgsample;

                        }

                        //cout<<""<<emgsample<<"   BR : "<<bytesRead<<" t : "<< total_time <<endl;
                        ioctlsocket(emgSock, FIONREAD, &VARS.bytesRead);
                        recv(emgSock, VARS.tmp2, VARS.bytesRead, 0);
                }
                    
                ioctlsocket(commSock, FIONREAD, &VARS.bytesRead);
                    if (VARS.bytesRead > 0)
                    {
                        recv(commSock, VARS.tmp, VARS.bytesRead, 0);
                        VARS.tmp[VARS.bytesRead] = '\0';
                        if (strstr(VARS.tmp, "STOPPED\r\n") != NULL)
                            return false;
                    } 

                return true;

            }
   
   
            virtual void showProperties(){
                ImGui::Begin("Properties",&GUI::EVENTS::showProperties,0);   
                    if(ImGui::Button(Properties.Connect ? "Disconnect" : "Connect")){
                        if(Properties.Connect) DisconnectEMG();
                        else ConnectEMG();
                    }
                    //if(Properties.Connect){
                    //    char strTemp[100];
                    //    for(int i = 0 ; i < 16 ; i++){
                    //        sprintf(strTemp,"%d##Sensor",i+1);
                    //        ImGui::Checkbox(strTemp,&Properties.EMG_Active[i]);
                    //    }
                    //}
                ImGui::End();
            }

        public:
        
            name_of_class(){
                name = name_of_block;
                TYPE = name_of_type;

                N_IN  = 0;
                N_OUT = 16;

                sizeBlock = ImVec2(100,200);
                
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
                 if(SIM::EVENTS::time_index == FIRST_LAP){
                     StartCaptureEMG();
                     if(!Properties.Connect){
                        LOCAL.double_clicked_count = 50;
                        GUI::MODAL_WARNING::setModal("SIMULATION FAILED","DELSYS : Not connected","");
                        SIM::EVENTS::SimulationTaskMutex_end.store(true); 
                     }
                     return;
                 }
                 if(SIM::EVENTS::time_index == LAST_LAP){
                     StopCaptureEMG();
                     return;
                 }
                 CaptureEMG();
                 for(int i = 0 ; i < 16 ; i++){
                    OUT_ARMA[i+1] =  VARS.EMG_VALUES[i];
                 }
                 
            }
            
            virtual BLOCK * Create(){
                return new name_of_class();
            }
            
            virtual void DrawADD(){
                ImDrawList* draw_list = ImGui::GetWindowDrawList();
                if(Properties.Connect)
                    draw_list->AddCircleFilled(LOCAL.posBlock_Global.Max - ImVec2(90,10),5,GUI::getColorU32(GUICol_Green));  
                else
                    draw_list->AddCircleFilled(LOCAL.posBlock_Global.Max - ImVec2(90,10),5,GUI::getColorU32(GUICol_White));  
                
                for(int i  = 1 ; i <= N_OUT ; i++)
                    draw_list->AddText(posOut[i]-ImGui::CalcTextSize("0")*.5f,GUI::getColorU32(GUICol_BlockText),std::to_string(i).c_str());          
               
            }    
            
    };

    void name_of_init(){
        ALL_BLOCKS_GUI[name_of_type] = new name_of_class();
        cout << "\n   "<< STRINGIZE(name_of_class)  <<": Cargado ";
    }
 
 

};
