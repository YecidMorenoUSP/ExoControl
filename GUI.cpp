//Este archivo debe ser incluido despues de IMGUI

/*
    Posicion de la ventana actual o frame respecto a la pantalla del pc , posicion global: 
    ImVec2 pos = ImGui::GetWindowPos();

    Posicion del cursor, es la posicion donde se va a poner el siguinte item, no es la ezquina :
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    window->DC.CursorPos

    Dibujar respecto a la posicion global
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    draw_list->

*/

#ifndef GUI_H
    #include "GUI.h"   
#endif
//#define DEV_MODE
#ifdef DEV_MODE

    namespace GUI{
        
        namespace EVENTS{
            bool showStyleEditor   = false;
            bool showExamples      = false;
            bool showBlockTest     = false;
            bool showDevTools      = true;
        }

        void showAllConsole(){
            cout<<endl;
            for (std::vector<BLOCKS::BLOCK*>::iterator it = BLOCKS::ALL_BLOCKS_GUI.begin() + BLKType_COUNT ; it != BLOCKS::ALL_BLOCKS_GUI.end(); it++)
                cout<<(*it)->name<<"\t";
            cout<<endl;
        }
        
        

        void debugWindow(){

            ImGui::Checkbox("DEV >> Style Editor",&EVENTS::showStyleEditor);
            if(EVENTS::showStyleEditor)ImGui::ShowStyleEditor();


            ImGui::Checkbox("DEV >> Demo Window",&EVENTS::showExamples);
            if(EVENTS::showExamples) ImGui::ShowDemoWindow();

            if(ImGui::Button("DEV >> Create BLock")){             
                BLOCKS::AddBLOCK(BLKType_SUM);   
                //showBlocksBeginEnd(0,10);
            }
  
            static char blockName [100] = {0};
            ImGui::InputText("##NaneBlock",blockName,IM_ARRAYSIZE(blockName),0);
            if(ImGui::Button("DEV >> Delete BLock")){   
       
                BLOCKS::DROOPBLOCK(BLOCKS::getIDBLOCK(blockName));
                
            }
        }
    } 

#endif


namespace GUI{

    namespace MODAL_WARNING{
        void setModal(std::string Title,std::string Body,std::string Ask){
            MODAL_WARNING::Title = Title;
            MODAL_WARNING::Body  = Body;
            MODAL_WARNING::Ask   = Ask;
            MODAL_WARNING::show = true;
        }
        void showModal(){
            if(!MODAL_WARNING::show)return;
            ImGui::OpenPopup(Title.c_str());
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

            if (ImGui::BeginPopupModal(Title.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
            {
                ImGui::Text(Body.c_str());
                ImGui::Separator();

                if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); show = false; }
                ImGui::EndPopup();
            }
        }
    };

    void init(){
        cout << "\n>> Cargando Texturas : ";
        loadTextures("Textures/GUITex_Default.png",GUITex_Default);
        loadTextures("Textures/GUITex_Exo1.png",GUITex_Exo1);
        loadTextures("Textures/GUITex_Exo2.png",GUITex_Exo2);
        loadTextures("Textures/GUITex_Exo3.png",GUITex_Exo3);
        loadTextures("Textures/GUITex_Exo_blur_1.png",GUITex_Exo_blur_1);
        loadTextures("Textures/GUITex_Exo_blur_2.png",GUITex_Exo_blur_2);
        loadTextures("Textures/GUITex_Exo_blur_3.png",GUITex_Exo_blur_3);
        loadTextures("Textures/GUITex_Xsens_Off.png",GUITex_Xsens_Off);
        loadTextures("Textures/GUITex_Xsens_On.png",GUITex_Xsens_On);
        loadTextures("Textures/GUITex_Delsys_Off.png",GUITex_Delsys_Off);
        loadTextures("Textures/GUITex_Delsys_On.png",GUITex_Delsys_On);
        loadTextures("Textures/GUITex_Btn_Run.png",GUITex_Btn_Run);
        loadTextures("Textures/GUITex_Btn_Pause.png",GUITex_Btn_Pause);
        loadTextures("Textures/GUITex_REROB.png",GUITex_REROB);
        cout << "\n   Texturas cargadas ";
    }

    void StyleApp(){
                
        ImGui::GetStyle().WindowMenuButtonPosition = ImGuiDir_None;

        ImVec4* colors_ = ImGui::GetStyle().Colors;

        colors_[ImGuiCol_Text]                   = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
        colors_[ImGuiCol_TextDisabled]           = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
        colors_[ImGuiCol_WindowBg]               = ImVec4(0.97f, 0.97f, 0.97f, 1.00f);
        colors_[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors_[ImGuiCol_PopupBg]                = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors_[ImGuiCol_Border]                 = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);
        colors_[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors_[ImGuiCol_FrameBg]                = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors_[ImGuiCol_FrameBgHovered]         = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
        colors_[ImGuiCol_FrameBgActive]          = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        colors_[ImGuiCol_TitleBg]                = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
        colors_[ImGuiCol_TitleBgActive]          = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
        colors_[ImGuiCol_TitleBgCollapsed]       = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
        colors_[ImGuiCol_MenuBarBg]              = ImVec4(0.89f, 0.89f, 0.89f, 1.00f);
        colors_[ImGuiCol_ScrollbarBg]            = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
        colors_[ImGuiCol_ScrollbarGrab]          = ImVec4(0.69f, 0.69f, 0.69f, 0.80f);
        colors_[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.49f, 0.49f, 0.49f, 0.80f);
        colors_[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
        colors_[ImGuiCol_CheckMark]              = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors_[ImGuiCol_SliderGrab]             = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
        colors_[ImGuiCol_SliderGrabActive]       = ImVec4(0.46f, 0.54f, 0.80f, 0.60f);
        colors_[ImGuiCol_Button]                 = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
        colors_[ImGuiCol_ButtonHovered]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors_[ImGuiCol_ButtonActive]           = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
        colors_[ImGuiCol_Header]                 = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
        colors_[ImGuiCol_HeaderHovered]          = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
        colors_[ImGuiCol_HeaderActive]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors_[ImGuiCol_Separator]              = ImVec4(0.39f, 0.39f, 0.39f, 0.08f);
        colors_[ImGuiCol_SeparatorHovered]       = ImVec4(0.14f, 0.44f, 0.80f, 0.78f);
        colors_[ImGuiCol_SeparatorActive]        = ImVec4(0.14f, 0.44f, 0.80f, 1.00f);
        colors_[ImGuiCol_ResizeGrip]             = ImVec4(0.80f, 0.80f, 0.80f, 0.56f);
        colors_[ImGuiCol_ResizeGripHovered]      = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        colors_[ImGuiCol_ResizeGripActive]       = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        colors_[ImGuiCol_Tab]                    = ImVec4(0.93f, 0.93f, 0.93f, 0.93f);
        colors_[ImGuiCol_TabHovered]             = ImVec4(0.26f, 0.59f, 0.98f, 0.09f);
        colors_[ImGuiCol_TabActive]              = ImVec4(0.97f, 0.97f, 0.97f, 1.00f);
        colors_[ImGuiCol_TabUnfocused]           = ImVec4(0.93f, 0.93f, 0.93f, 1.00f);
        colors_[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.97f, 0.97f, 0.97f, 1.00f);
        colors_[ImGuiCol_DockingPreview]         = ImVec4(0.26f, 0.59f, 0.98f, 0.22f);
        colors_[ImGuiCol_DockingEmptyBg]         = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
        colors_[ImGuiCol_PlotLines]              = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
        colors_[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colors_[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        colors_[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.45f, 0.00f, 1.00f);
        colors_[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
        colors_[ImGuiCol_DragDropTarget]         = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        colors_[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
        colors_[ImGuiCol_NavWindowingHighlight]  = ImVec4(0.70f, 0.70f, 0.70f, 0.70f);
        colors_[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.20f, 0.20f, 0.20f, 0.20f);
        colors_[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
    
        colors[GUICol_BlockFill]   = ImVec4(0.260f, 0.590f, 0.980f, 1.00f);
        colors[GUICol_BlockBorder] = ImVec4(0.9f, 0.9f, 0.9f, 1.00f);
        colors[GUICol_BlockIN]     = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
        colors[GUICol_BlockOUT]    = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
        colors[GUICol_BlockINHover]    = ImVec4(0.0f, 0.0f, 0.0f, 1.000f);
        colors[GUICol_BlockOUTHover]    = ImVec4(0.0f, 0.0f, 0.0f, 1.000f);
        colors[GUICol_BlockBorderActive]    = ImVec4(0.96f, 0.83f, 0.04f, 1.00f);
        colors[GUICol_BlockText]   = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
        colors[GUICol_Amarillo]    = ImVec4(0.984f, 0.757f, 0.000f, 1.000f);
        colors[GUICol_Black]    = ImVec4(0.0f, 0.0f, 0.0f, 1.000f);
        colors[GUICol_White]     = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
        colors[GUICol_Green]     = ImVec4(.20f, 1.0f, .20f, 1.00f);

    

    }

    ImU32 getColorU32(int indexColor){
        return ImGui::GetColorU32(colors[indexColor]);
    }

    void loadTextures(const char * name, GUI_Textures_ index){
        int aux[2] = {0,0};
        bool ret;
        ret = LoadTextureFromFile(name, &Texture[index].texture, &aux[0],&aux[1]);
        if(!ret){
            cout << "\n   Textura  "<<name<<" no encontrada";
            Texture[index] = Texture[GUITex_Default];
            return;}
        Texture[index].dimensions = ImVec2((int)aux[0],(int)aux[1]);
        IM_ASSERT(ret);
    }

    void createDocking(){
            
        static bool  sdemo ;

        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags =  ImGuiWindowFlags_NoDocking;//ImGuiWindowFlags_MenuBar |
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->GetWorkPos());
        ImGui::SetNextWindowSize(viewport->GetWorkSize());
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_MenuBar;
        
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        ImGui::Begin("MainWindow", &sdemo, window_flags);
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        ImGui::PopStyleVar(3);
        
        createMenuBar();

        ImGui::End();

    }

    void createMenuBar(){
        if (ImGui::BeginMenuBar()){

            if (ImGui::BeginMenu("Show")){

                ImGui::MenuItem("Blocks"        , NULL, &EVENTS::showBlocks);
                ImGui::MenuItem("Graphs"        , NULL, &EVENTS::showGraphs);
                ImGui::MenuItem("Real-Time"     , NULL, &EVENTS::showRealTime);
                ImGui::MenuItem("Game Serius"   , NULL, &EVENTS::showGameSerius);
                ImGui::MenuItem("Game Serius"   , NULL, &EVENTS::showBlocksProgramming);
                ImGui::MenuItem("Properties"    , NULL, &EVENTS::showProperties);
                

                #ifdef DEV_MODE
                    ImGui::Separator();
                    ImGui::Text("DEV_MODE");
                    ImGui::Checkbox("DevTools",&EVENTS::showDevTools);
                #endif

                ImGui::EndMenu();
            }
       
            ImGui::EndMenuBar();
        }
    }

    void createControls(){   

        #ifdef DEV_MODE
            if(EVENTS::showDevTools){
                ImGui::Begin("DevTools",&EVENTS::showDevTools,0);  
                    debugWindow();
                ImGui::End();
            }
        #endif

        createDocking();
        
        MODAL_WARNING::showModal();
       
        if(EVENTS::showGraphs){
            ImGui::Begin(" Graphs",&EVENTS::showGraphs,0);  
            ImGui::End();
        }
        if(EVENTS::showGameSerius){
            ImGui::Begin("Serius Game",&EVENTS::showGameSerius,0);  
            ImGui::End();
        }
        if(EVENTS::showBlocksProgramming){
            ImGui::Begin("Block logic",&EVENTS::showBlocksProgramming,0); 
            displayBlocksLogic();
            ImGui::End();
        }
        if(EVENTS::showRealTime){
            ImGui::Begin("Real-Time",&EVENTS::showRealTime,0);  
            ImGui::End();
        }
        if(EVENTS::showBlocks){
            ImGui::Begin("Blocks",&EVENTS::showBlocks,0);  
            displayBlocksGUI();
                //if(!ImGui::IsWindowFocused(0)) EVENTS::showProperties = false;
                //drawBlockTest();
            ImGui::End();
        }
        ImGui::Begin("Menu");                     
            displayMenu();
        ImGui::End();
        

        if(EVENTS::showProperties){
            ImGui::Begin("Properties",&EVENTS::showProperties,0);  
            ImGui::End();
        }
        
    }

    void displayBlocksGUI(){
          
            for (int i = 1 ; i < BLKType_COUNT ; i++){
                if(ImGui::Button(BLOCKS::ALL_BLOCKS_GUI[i]->name.c_str(),ImVec2(100,50))){
                    BLOCKS::AddBLOCK((TypeBlock_)i);                      
                }  
                
            }

    }

    void displayBlocksLogic(){

        ImDrawList* draw_list = ImGui::GetWindowDrawList();

        if(ImGui::ImageButton((void*)Texture[GUITex_Btn_Run+!SIM::EVENTS::SimulationTaskMutex_end.load()].texture,ImVec2(25,25))){                      
                if(SIM::EVENTS::SimulationTaskMutex_end.load()){
                    if(SIM::EVENTS::SimulationThread_.joinable())SIM::EVENTS::SimulationThread_.join();
                    SIM::EVENTS::SimulationTaskMutex_end.store(false);
                    SIM::EVENTS::SimulationThread_ = std::thread(SIM::RUN);
                }else{
                    SIM::EVENTS::SimulationTaskMutex_end.store(true); 
                    SIM::EVENTS::SimulationThread_.join();
                }          
        } 

        iterateBLOCKS_GUI{
            //cout<<"\n "<<(*(*it)->IN_ARMA[2])<<"  ";
            (*it)->Draw();
        }  
        
        if(BLOCKS::EVENTS::creatingLine >= 1){
            if(BLOCKS::EVENTS::creatingLine == 1) BLOCKS::EVENTS::newLinePosIN = ImGui::GetMousePos();
            draw_list->AddLine(BLOCKS::EVENTS::newLinePosOUT,BLOCKS::EVENTS::newLinePosIN,getColorU32(GUICol_Amarillo),2);
            if(BLOCKS::EVENTS::creatingLine == 2){
                
                LINES::LINE * ln = new LINES::LINE();

                ln->blockIn  = BLOCKS::EVENTS::blockInLine;
                ln->blockOut = BLOCKS::EVENTS::blockOutLine;
                ln->posIn    = BLOCKS::EVENTS::posInLineIndex;
                ln->posOut   = BLOCKS::EVENTS::posOutLineIndex;
                 
                ln->blockIn->IN_ARMA[BLOCKS::EVENTS::posInLineIndex] = &(ln->blockOut->OUT_ARMA[BLOCKS::EVENTS::posOutLineIndex]);
                
                LINES::ALL_LINES_GUI.push_back(ln);
                BLOCKS::EVENTS::creatingLine = 0;
                BLOCKS::EVENTS::newLinePosIN  = ImVec2(0,0);
                BLOCKS::EVENTS::newLinePosOUT = ImVec2(0,0);
            }
            if(ImGui::IsMouseReleased(0)){
                BLOCKS::EVENTS::newLinePosIN  = ImVec2(0,0);
                BLOCKS::EVENTS::newLinePosOUT = ImVec2(0,0);
                BLOCKS::EVENTS::creatingLine = 0;
                
            } 
        }

        iterateLINES_GUI{
            //cout<<"\n "<< (*it)->blockIn->posBlock.x;
            //draw_list->AddLine((*it)->posOut,(*it)->posIn,getColorU32(GUICol_Amarillo),2);
            bool eraseItem = false;
            (*it)->Draw(&eraseItem);
            if(eraseItem){
                (*it)->blockIn->IN_ARMA.clear();
                (*it)->blockIn->IN_ARMA.insert((*it)->blockIn->IN_ARMA.begin(),(*it)->blockIn->N_IN+1,new arma::fmat);  
                LINES::ALL_LINES_GUI.erase(it);
                break;
            }
        }
    }

    void displayMenu(){
        ImGuiWindow* windowCur = ImGui::GetCurrentWindow();          
        ImVec2 cur = windowCur->DC.CursorPos;

        ImGui::Text("FPS : %.1f", ImGui::GetIO().Framerate);
        if(ImGui::Button("Exit")) EVENTS::DONE = true;
        
        ImGui::SetCursorPos(windowCur->Size - ImVec2(windowCur->Size.x/2.f+50,170));
        ImGui::Image((void*)GUI::Texture[GUITex_REROB].texture,ImVec2(100,100));

        char txtEval[500];
        sprintf(txtEval,"José Yecid Moreno Villamizar");   
        ImVec2 sizeAux = ImGui::CalcTextSize(txtEval);
        ImGui::SetCursorPos(windowCur->Size - ImVec2(windowCur->Size.x/2.f+sizeAux.x/2.f,sizeAux.y + 30));
        ImGui::Text(txtEval);

        sprintf(txtEval,"N° USP : 11195127");
        sizeAux = ImGui::CalcTextSize(txtEval);
        ImGui::SetCursorPos(windowCur->Size - ImVec2(windowCur->Size.x/2.f+sizeAux.x/2.f,sizeAux.y + 10));
        ImGui::Text(txtEval);

    }
    
}

