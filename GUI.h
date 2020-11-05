#define GUI_H

#define iterateBLOCKS_GUI for (std::vector<BLOCKS::BLOCK*>::iterator it = BLOCKS::ALL_BLOCKS_GUI.begin() + BLKType_COUNT ; it != BLOCKS::ALL_BLOCKS_GUI.end(); it++)
#define iterateLINES_GUI for  (std::vector<LINES::LINE*>::iterator   it = LINES::ALL_LINES_GUI.begin() ; it != LINES::ALL_LINES_GUI.end(); it++)

enum GUI_Colors_{
    GUICol_BlockFill,
    GUICol_BlockText,
    GUICol_Amarillo,
    GUICol_BlockBorder,
    GUICol_BlockIN,
    GUICol_BlockOUT,
    GUICol_BlockBorderActive,
    GUICol_BlockINHover,
    GUICol_BlockOUTHover,
    GUICol_Black,
    GUICol_White,
    GUICol_Green,
    GUICol_COUNT
};

enum GUI_Textures_{
    GUITex_Default,
    GUITex_Exo1,
    GUITex_Exo2,
    GUITex_Exo3,
    GUITex_Exo_blur_1,
    GUITex_Exo_blur_2,
    GUITex_Exo_blur_3,
    GUITex_Xsens_Off,
    GUITex_Xsens_On,
    GUITex_Delsys_Off,
    GUITex_Delsys_On,
    GUITex_Btn_Run,
    GUITex_Btn_Pause,
    GUITex_REROB,
    GUITexture_COUNT
};



namespace GUI{
     
    void StyleApp();
    void loadTextures(const char * name, GUI_Textures_ index);

    ImVec4 colors[GUICol_COUNT];
    namespace MODAL_WARNING{
        bool show = false;
        std::string Title = "Title";
        std::string Body  = "Body";
        std::string Ask   = "Ask";
        void setModal(std::string Title = "",std::string Body = "",std::string Ask = "");
        void showModal();
    }

    struct Texture_{
        ImVec2 dimensions;
        GLuint texture;    
    };

    Texture_ Texture[GUITexture_COUNT];

    namespace EVENTS{
         
        bool DONE = false;

        bool showProperties          = false;
        bool showBlocks              = true;
        bool showGraphs              = true;
        bool showRealTime            = true;
        bool showGameSerius          = true;
        bool showBlocksProgramming   = true;

    }

    void init();

    

    void createDocking();

    void StyleApp();

    ImU32 getColorU32(int indexColor);

    void createMenuBar();

    void createControls();

    void displayBlocksGUI();

    void displayBlocksLogic();

    void displayMenu();

}