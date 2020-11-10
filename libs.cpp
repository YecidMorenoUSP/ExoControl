#include <imgui.h>
#include <imgui.cpp>
#include <imgui_internal.h>
#include <imstb_textedit.h>
#include <imstb_truetype.h>
#include <imstb_rectpack.h>
#include <imgui_draw.cpp>
#include <imgui_widgets.cpp>

#include <imgui_plot2.hpp>
#include <imgui_plot2.cpp>

#include <imgui_impl_sdl.h>
#include <imgui_impl_sdl.cpp>
#include <imgui_impl_opengl2.h>
#include <imgui_impl_opengl2.cpp>
#include <SDL.h>
#include <SDL_opengl.h>
#include <math.h>
#include <stdio.h>
//#include <windows.h>



#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>
#include <imagenes_varios.cpp>
#include <iostream>
#include <thread>
#include <string>
#include <atomic>
#include <chrono>
#include <vector>


#include <imgui_demo.cpp>

#include <armadillo>
using namespace arma;

//#define DEV_MODE 
#define name_of(name) #name
#define PPCAT_NX(A, B) A ## B
#define PPCAT(A, B) PPCAT_NX(A, B)

#define COMMAND(NAME)  { #NAME, NAME ## _command }

#define PPCAT_FUNC_NX(A, B) #A _INIT(); #B 
#define PPCAT_FUNC(A, B) PPCAT_FUNC_NX(A, B)

#define STRINGIZE_NX(A) #A
#define STRINGIZE(A) STRINGIZE_NX(A)
#define PPCAT_INIT(A) PPCAT(A,_INIT)

#define initWithPyC(A) PPCAT( A, _INIT(); )



#include "GLOBAL.h"

#include "GUI.h"
#include "BLOCKS.h"
#include "LINES.h"
#include "SIMULATION.h"

#include "GUI.cpp"
#include "BLOCKS.cpp"
#include "LINES.cpp"
#include "SIMULATION.cpp"




