#include <windows.h>
#include <string.h>
#include <iostream>

std::string savefilename(char *filter = "All Files (*.blkReabRob)\0*.blkReabRob\0", HWND owner = NULL) {
  OPENFILENAME ofn;
  char fileName[MAX_PATH] = "";
  ZeroMemory(&ofn, sizeof(ofn));

  ofn.lStructSize = sizeof(OPENFILENAME);
  ofn.hwndOwner = owner;
  ofn.lpstrFilter = filter;
  ofn.lpstrFile = fileName;
  ofn.nMaxFile = MAX_PATH;
  ofn.Flags = 0x00080000 | 0x00001000 | 0x00000004;
  ofn.lpstrDefExt = "";

  std::string fileNameStr;

  if ( GetSaveFileName(&ofn) )
    fileNameStr = fileName;

  return fileNameStr;
}

std::string openfilename(char *filter = "All Files (*.blkReabRob)\0*.blkReabRob\0", HWND owner = NULL) {
  OPENFILENAME ofn;
  char fileName[MAX_PATH] = "";
  ZeroMemory(&ofn, sizeof(ofn));

  ofn.lStructSize = sizeof(OPENFILENAME);
  ofn.hwndOwner = owner;
  ofn.lpstrFilter = filter;
  ofn.lpstrFile = fileName;
  ofn.nMaxFile = MAX_PATH;
  ofn.Flags = 0x00080000 | 0x00001000 | 0x00000004;
  ofn.lpstrDefExt = "";

  std::string fileNameStr;

  if ( GetOpenFileName(&ofn) )
    fileNameStr = fileName;

  return fileNameStr;
}

#include "libs.cpp"

void ADDMenuBar();

#define IO_BEGIN_FILE "[BEGIN]\0"
#define IO_BLOCK_FILE "\n[BLOCK]\0"
#define IO_LINE_FILE  "\n[LINE]\0"
#define IO_END_FILE   "\n[END]\0"




int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1; 
    }              

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | 0 );
    //window_flags |= ((SDL_WindowFlags)SDL_WINDOW_FULLSCREEN_DESKTOP);
    //window_flags |= (SDL_WindowFlags)SDL_WINDOW_FULLSCREEN;

    SDL_Window* window = SDL_CreateWindow("AppExo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync
    
    
     
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    io.ConfigFlags |= ImGuiWindowFlags_NoBackground;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

 
    GUI::StyleApp();
    //ImGui::StyleColorsLight();
    
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 1.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
 

    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL2_Init();

    {// Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);    
    }

    GUI::init();
    BLOCKS::Init();
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.00f);

    
    while (!GUI::EVENTS::DONE)
    {
       

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                GUI::EVENTS::DONE = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                GUI::EVENTS::DONE = true;
        }


        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        GUI::createControls();
        
        ADDMenuBar();
             

        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());


        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
            SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
        }

        
        SDL_GL_SwapWindow(window);
        
        Sleep(50);
    }

    // Cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


void ADDMenuBar(){
    ImGui::Begin("MainWindow");
        if (ImGui::BeginMenuBar()){

            if (ImGui::BeginMenu("Examples")){

                if(ImGui::MenuItem("SPAR"        , NULL, false)){
                    BLOCKS::AddBLOCK((TypeBlock_)BLKType_CAN_CFG);
                    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(100,100);
                    
                    BLOCKS::AddBLOCK((TypeBlock_)BLKType_NUMK);
                    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(100,200);

                    BLOCKS::AddBLOCK((TypeBlock_)BLKType_FUNGEN);
                    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(100,300);

                    BLOCKS::AddBLOCK((TypeBlock_)BLKType_EPOS);
                    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(100,400);
                    ((BLOCKS::BlockEPOS*) BLOCKS::ALL_BLOCKS_GUI.back())->Properties.nodeId=3;

                    BLOCKS::AddBLOCK((TypeBlock_)BLKType_EPOS);
                    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(100,500);
                    ((BLOCKS::BlockEPOS*) BLOCKS::ALL_BLOCKS_GUI.back())->Properties.nodeId=2;
                    
                    BLOCKS::AddBLOCK((TypeBlock_)BLKType_SPAR);
                    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(300,200);

                    BLOCKS::AddBLOCK((TypeBlock_)BLKType_NUMK);
                    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(50,500);

                    
                    LINES::ALL_LINES_GUI.push_back( new LINES::LINE() );
                    LINES::ALL_LINES_GUI.back()->posIn = 1;
                    LINES::ALL_LINES_GUI.back()->posOut = 1;
                    LINES::ALL_LINES_GUI.back()->blockOut = BLOCKS::ALL_BLOCKS_GUI[BLKType_COUNT + 1];
                    LINES::ALL_LINES_GUI.back()->blockIn = BLOCKS::ALL_BLOCKS_GUI[BLKType_COUNT + 5];
                    LINES::ALL_LINES_GUI.back()->blockIn->IN_ARMA[LINES::ALL_LINES_GUI.back()->posIn] = &(LINES::ALL_LINES_GUI.back()->blockOut->OUT_ARMA[LINES::ALL_LINES_GUI.back()->posOut]);


                    LINES::ALL_LINES_GUI.push_back( new LINES::LINE() );
                    LINES::ALL_LINES_GUI.back()->posIn = 2;
                    LINES::ALL_LINES_GUI.back()->posOut = 1;
                    LINES::ALL_LINES_GUI.back()->blockOut = BLOCKS::ALL_BLOCKS_GUI[BLKType_COUNT + 1];
                    LINES::ALL_LINES_GUI.back()->blockIn = BLOCKS::ALL_BLOCKS_GUI[BLKType_COUNT + 5];
                    LINES::ALL_LINES_GUI.back()->blockIn->IN_ARMA[LINES::ALL_LINES_GUI.back()->posIn] = &(LINES::ALL_LINES_GUI.back()->blockOut->OUT_ARMA[LINES::ALL_LINES_GUI.back()->posOut]);


                    LINES::ALL_LINES_GUI.push_back( new LINES::LINE() );
                    LINES::ALL_LINES_GUI.back()->posIn = 3;
                    LINES::ALL_LINES_GUI.back()->posOut = 1;
                    LINES::ALL_LINES_GUI.back()->blockOut = BLOCKS::ALL_BLOCKS_GUI[BLKType_COUNT + 2];
                    LINES::ALL_LINES_GUI.back()->blockIn = BLOCKS::ALL_BLOCKS_GUI[BLKType_COUNT + 5];
                    LINES::ALL_LINES_GUI.back()->blockIn->IN_ARMA[LINES::ALL_LINES_GUI.back()->posIn] = &(LINES::ALL_LINES_GUI.back()->blockOut->OUT_ARMA[LINES::ALL_LINES_GUI.back()->posOut]);


                    LINES::ALL_LINES_GUI.push_back( new LINES::LINE() );
                    LINES::ALL_LINES_GUI.back()->posIn = 4;
                    LINES::ALL_LINES_GUI.back()->posOut = 1;
                    LINES::ALL_LINES_GUI.back()->blockOut = BLOCKS::ALL_BLOCKS_GUI[BLKType_COUNT + 3];
                    LINES::ALL_LINES_GUI.back()->blockIn = BLOCKS::ALL_BLOCKS_GUI[BLKType_COUNT + 5];
                    LINES::ALL_LINES_GUI.back()->blockIn->IN_ARMA[LINES::ALL_LINES_GUI.back()->posIn] = &(LINES::ALL_LINES_GUI.back()->blockOut->OUT_ARMA[LINES::ALL_LINES_GUI.back()->posOut]);


                    LINES::ALL_LINES_GUI.push_back( new LINES::LINE() );
                    LINES::ALL_LINES_GUI.back()->posIn = 5;
                    LINES::ALL_LINES_GUI.back()->posOut = 2;
                    LINES::ALL_LINES_GUI.back()->blockOut = BLOCKS::ALL_BLOCKS_GUI[BLKType_COUNT + 3];
                    LINES::ALL_LINES_GUI.back()->blockIn = BLOCKS::ALL_BLOCKS_GUI[BLKType_COUNT + 5];
                    LINES::ALL_LINES_GUI.back()->blockIn->IN_ARMA[LINES::ALL_LINES_GUI.back()->posIn] = &(LINES::ALL_LINES_GUI.back()->blockOut->OUT_ARMA[LINES::ALL_LINES_GUI.back()->posOut]);


                    LINES::ALL_LINES_GUI.push_back( new LINES::LINE() );
                    LINES::ALL_LINES_GUI.back()->posIn = 6;
                    LINES::ALL_LINES_GUI.back()->posOut = 3;
                    LINES::ALL_LINES_GUI.back()->blockOut = BLOCKS::ALL_BLOCKS_GUI[BLKType_COUNT + 3];
                    LINES::ALL_LINES_GUI.back()->blockIn = BLOCKS::ALL_BLOCKS_GUI[BLKType_COUNT + 5];
                    LINES::ALL_LINES_GUI.back()->blockIn->IN_ARMA[LINES::ALL_LINES_GUI.back()->posIn] = &(LINES::ALL_LINES_GUI.back()->blockOut->OUT_ARMA[LINES::ALL_LINES_GUI.back()->posOut]);


                    LINES::ALL_LINES_GUI.push_back( new LINES::LINE() );
                    LINES::ALL_LINES_GUI.back()->posIn = 7;
                    LINES::ALL_LINES_GUI.back()->posOut = 1;
                    LINES::ALL_LINES_GUI.back()->blockOut = BLOCKS::ALL_BLOCKS_GUI[BLKType_COUNT + 4];
                    LINES::ALL_LINES_GUI.back()->blockIn = BLOCKS::ALL_BLOCKS_GUI[BLKType_COUNT + 5];
                    LINES::ALL_LINES_GUI.back()->blockIn->IN_ARMA[LINES::ALL_LINES_GUI.back()->posIn] = &(LINES::ALL_LINES_GUI.back()->blockOut->OUT_ARMA[LINES::ALL_LINES_GUI.back()->posOut]);


                    LINES::ALL_LINES_GUI.push_back( new LINES::LINE() );
                    LINES::ALL_LINES_GUI.back()->posIn = 1;
                    LINES::ALL_LINES_GUI.back()->posOut = 1;
                    LINES::ALL_LINES_GUI.back()->blockOut = BLOCKS::ALL_BLOCKS_GUI[BLKType_COUNT + 5];
                    LINES::ALL_LINES_GUI.back()->blockIn = BLOCKS::ALL_BLOCKS_GUI[BLKType_COUNT + 3];
                    LINES::ALL_LINES_GUI.back()->blockIn->IN_ARMA[LINES::ALL_LINES_GUI.back()->posIn] = &(LINES::ALL_LINES_GUI.back()->blockOut->OUT_ARMA[LINES::ALL_LINES_GUI.back()->posOut]);


                    LINES::ALL_LINES_GUI.push_back( new LINES::LINE() );
                    LINES::ALL_LINES_GUI.back()->posIn = 1;
                    LINES::ALL_LINES_GUI.back()->posOut = 1;
                    LINES::ALL_LINES_GUI.back()->blockOut = BLOCKS::ALL_BLOCKS_GUI[BLKType_COUNT + 6];
                    LINES::ALL_LINES_GUI.back()->blockIn = BLOCKS::ALL_BLOCKS_GUI[BLKType_COUNT + 4];
                    LINES::ALL_LINES_GUI.back()->blockIn->IN_ARMA[LINES::ALL_LINES_GUI.back()->posIn] = &(LINES::ALL_LINES_GUI.back()->blockOut->OUT_ARMA[LINES::ALL_LINES_GUI.back()->posOut]);
                }
                
                if(ImGui::MenuItem("LOAD"        , NULL, false)){
                    
                    std::string FileNameSTR = openfilename();
                    if(FileNameSTR.length()>0){

                        FILE *fptr;
                        if ((fptr = fopen(FileNameSTR.c_str(),"rb")) == NULL){
                            printf("Error! opening file");
                            return;
                        }

                        char info[100]  = "";
                        fread(&info, sizeof(info), 1, fptr); 

                        if(strcmp(info,IO_BEGIN_FILE) == 0){
                            while(true){
                                
                                fread(&info, sizeof(info), 1, fptr); 

                                    if(strcmp(info,IO_BEGIN_FILE) == 0){}
                                else if(strcmp(info,IO_END_FILE  ) == 0){break;}
                                else if(strcmp(info,IO_BLOCK_FILE) == 0){
                                    BLOCKS::BLOCK * blk = new BLOCKS::BLOCK();
                                    blk->load(fptr);

                                    BLOCKS::AddBLOCK((TypeBlock_)blk->dataBlock.type);
                                    BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(blk->dataBlock.posX,blk->dataBlock.posY);
                                    BLOCKS::ALL_BLOCKS_GUI.back()->sizeBlock = ImVec2(blk->dataBlock.sizeX,blk->dataBlock.sizeY);
                                    BLOCKS::ALL_BLOCKS_GUI.back()->N_IN  = blk->dataBlock.N_IN;
                                    BLOCKS::ALL_BLOCKS_GUI.back()->N_OUT = blk->dataBlock.N_OUT;
                                    BLOCKS::ALL_BLOCKS_GUI.back()->UpadateIO();
                                }
                                else if(strcmp(info,IO_LINE_FILE) == 0){
                                    LINES::LINE * ln = new LINES::LINE();
                                    ln->load(fptr);

                                    LINES::ALL_LINES_GUI.push_back( new LINES::LINE() );
                                    LINES::ALL_LINES_GUI.back()->posIn = ln->dataLine.posIn;
                                    LINES::ALL_LINES_GUI.back()->posOut = ln->dataLine.posOut;
                                    LINES::ALL_LINES_GUI.back()->blockOut = BLOCKS::ALL_BLOCKS_GUI[ln->dataLine.idxOut+BLKType_COUNT];
                                    LINES::ALL_LINES_GUI.back()->blockIn = BLOCKS::ALL_BLOCKS_GUI[ln->dataLine.idxIn+BLKType_COUNT];
                                    LINES::ALL_LINES_GUI.back()->blockIn->IN_ARMA[LINES::ALL_LINES_GUI.back()->posIn] = &(LINES::ALL_LINES_GUI.back()->blockOut->OUT_ARMA[LINES::ALL_LINES_GUI.back()->posOut]);
                                }
                                else break;

                            }
                        }else{
                            printf("ERROR con el archivo");
                        }

                        fclose(fptr);    
                    }

                }

                if(ImGui::MenuItem("SAVE"        , NULL, false)){
                    std::string FileNameSTR = savefilename();
                    if(FileNameSTR.length()>0){
                        FILE *fptr;

                        if ((fptr = fopen(FileNameSTR.c_str(),"wb")) == NULL){
                            printf("Error! opening file");
                            return;
                        }

                        char info[100];

                        sprintf(info,IO_BEGIN_FILE);
                        fwrite(&info, sizeof(info), 1, fptr); 


                        iterateBLOCKS_GUI{
                            sprintf(info,IO_BLOCK_FILE);
                            fwrite(&info, sizeof(info), 1, fptr); 
                            (*it)->save(fptr);
                        }

                        iterateLINES_GUI{
                            sprintf(info,IO_LINE_FILE);
                            fwrite(&info, sizeof(info), 1, fptr); 
                            (*it)->save(fptr);
                        }

                        sprintf(info,IO_END_FILE);
                        fwrite(&info, sizeof(info), 1, fptr); 

                        fclose(fptr);     
                    }
                    // iterateBLOCKS_GUI{
                    //     printf("\n");
                    //     printf("\nBLOCKS::AddBLOCK((TypeBlock_)%d);",(*it)->TYPE);
                    //     printf("\nBLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(%ff,%ff);",(*it)->posBlock.x,(*it)->posBlock.y);
                    //     printf("\nBLOCKS::ALL_BLOCKS_GUI.back()->sizeBlock = ImVec2(%ff,%ff);",(*it)->sizeBlock.x,(*it)->sizeBlock.y);
                    //     printf("\nBLOCKS::ALL_BLOCKS_GUI.back()->N_IN  = %d;",(*it)->N_IN );
                    //     printf("\nBLOCKS::ALL_BLOCKS_GUI.back()->N_OUT = %d;",(*it)->N_OUT);
                    //     printf("\nBLOCKS::ALL_BLOCKS_GUI.back()->UpadateIO();");
                    // }

                    // iterateLINES_GUI{
                    //     printf("\n");
                    //     printf("\nLINES::ALL_LINES_GUI.push_back( new LINES::LINE() );");
                    //     printf("\nLINES::ALL_LINES_GUI.back()->posIn = %d;",(*it)->posIn);
                    //     printf("\nLINES::ALL_LINES_GUI.back()->posOut = %d;",(*it)->posOut);
                    //     printf("\nLINES::ALL_LINES_GUI.back()->blockOut = BLOCKS::ALL_BLOCKS_GUI[%d+BLKType_COUNT];",(*it)->blockOut->indexBLOCKS);
                    //     printf("\nLINES::ALL_LINES_GUI.back()->blockIn = BLOCKS::ALL_BLOCKS_GUI[%d+BLKType_COUNT];",(*it)->blockIn->indexBLOCKS);
                    //     printf("\nLINES::ALL_LINES_GUI.back()->blockIn->IN_ARMA[LINES::ALL_LINES_GUI.back()->posIn] = &(LINES::ALL_LINES_GUI.back()->blockOut->OUT_ARMA[LINES::ALL_LINES_GUI.back()->posOut]);");
                    // }

                    // BLOCKS::AddBLOCK((TypeBlock_)BLKType_CAN_CFG);
                    // BLOCKS::ALL_BLOCKS_GUI.back()->posBlock = ImVec2(100,100);
                }

                ImGui::EndMenu();
            }
       
            ImGui::EndMenuBar();
        }
        ImGui::End();
}