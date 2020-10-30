#define GUI_H

enum GUI_Colors_{
    GUICol_BlockFill,
    GUICol_BlockText,
    GUICol_Amarillo,
    GUICol_BlockBorder,
    GUICol_BlockIN,
    GUICol_BlockOUT,
    GUICol_BlockBorderActive,
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

    ImVec4 colors[GUICol_COUNT];

    ImVec2 dimensions[GUITexture_COUNT] ;
    ImVec2 dimensionsInit[GUITexture_COUNT] ;
    GLuint textures [GUITexture_COUNT]= {0};

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

    void loadTextures();

    void createDocking();

    void StyleApp();

    ImU32 getColorU32(int indexColor);

    void createMenuBar();

    void createControls();

    void displayBlocksGUI();

    void displayBlocksLogic();

}