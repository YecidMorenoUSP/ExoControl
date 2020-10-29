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
#define DEV_MODE
#ifdef DEV_MODE

    namespace GUI{
        
        namespace EVENTS{
            bool showStyleEditor   = false;
            bool showBlockTest     = false;
            bool showDevTools      = true;
        }

        void showBlocksGeginEnd(int A , int B ){
            for(int i = A ; i < B; i++)
                cout<<BLOCKS::ALL_BLOCKS[i].name<<"\t";   
            cout<<endl;
        }
        
        

        void debugWindow(){

            ImGui::Checkbox("DEV >> Style Editor",&EVENTS::showStyleEditor);
            if(EVENTS::showStyleEditor)ImGui::ShowStyleEditor();

            ImGui::Checkbox("DEV >> Block Test",&EVENTS::showBlockTest);
            //if(EVENTS::showBlockTest)drawBlockTest();

            if(ImGui::Button("DEV >> Create BLock")){             
                BLOCKS::AddBLOCK(BLKType_Default);   
                showBlocksGeginEnd(0,10);
            }
  
            static char blockName [100] = {0};
            ImGui::InputText("##NaneBlock",blockName,IM_ARRAYSIZE(blockName),0);
            if(ImGui::Button("DEV >> Delete BLock")){   
                ImGuiWindow* window = ImGui::GetCurrentWindow();          
                BLOCKS::DROOPBLOCK(window->GetID(blockName));
                
                showBlocksGeginEnd(0,10);
            }
        }
    } 

#endif


namespace GUI{

    void init(){
        loadTextures();
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
    
        colors[GUICol_BlockFill] = ImVec4(0.260f, 0.590f, 0.980f, 1.00f);
        colors[GUICol_BlockText] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
        colors[GUICol_Amarillo] =  ImVec4(0.984f, 0.757f, 0.000f, 1.000f);

    }


    ImU32 getColorU32(int indexColor){
        return ImGui::GetColorU32(colors[indexColor]);
    }

    void loadTextures(){
        
        int aux[2] = {0,0};
        bool ret;
        char buffer[40]={0};
        for(int i = 0 ; i < GUITexture_COUNT ; i++){
            
            //sprintf(buffer,"Textures/texture%d.png",i);
            //ret = LoadTextureFromFile(buffer, &textures[i], &aux[0],&aux[1]);
            //if(!ret) continue;
            //GE::dimensions[i] = ImVec2((int)aux[0],(int)aux[1]);
            //GE::dimensionsInit[i] = ImVec2((int)aux[0],(int)aux[1]);
            //IM_ASSERT(ret);

            //cout<<;
            
        }

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
        
       
        if(EVENTS::showGraphs){
            ImGui::Begin("Graphs",&EVENTS::showGraphs,0);  
            ImGui::End();
        }
        if(EVENTS::showGameSerius){
            ImGui::Begin("Serius Game",&EVENTS::showGameSerius,0);  
            ImGui::End();
        }
        if(EVENTS::showBlocksProgramming){
            ImGui::Begin("Block logic",&EVENTS::showBlocksProgramming,0); 

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
            ImGui::Text("FPS : %.1f", ImGui::GetIO().Framerate);
            if(ImGui::Button("Exit")) EVENTS::DONE = true;
        ImGui::End();
        

        if(EVENTS::showProperties){
            ImGui::Begin("Properties",&EVENTS::showProperties,0);  
            ImGui::End();
        }
        
    }

    void displayBlocksGUI(){
          
            for(int i = 1 ; i < BLKType_COUNT ; i++){
                if(ImGui::Button(BLOCKS::ALL_BLOCKS[i].name.c_str(),ImVec2(100,50))){
                    BLOCKS::AddBLOCK((TypeBlock_)i);   
                    showBlocksGeginEnd(0,10);
                }                
            }
    }

    void displayBlocksLogic(){

    }
}

