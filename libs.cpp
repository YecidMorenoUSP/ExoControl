#if !defined(LIBS_H_MAIN)
#define LIBS_H_MAIN


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
#include <ctime>
#include <thread>
#include <string>
#include <atomic>
#include <chrono>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <mutex> 

#include <imgui_demo.cpp>

#include <armadillo>
using namespace arma;

#define __T1__  std::chrono::steady_clock::time_point T_T1;
#define __TIC__ T_T1 = std::chrono::steady_clock::now();
#define __T2__  std::chrono::steady_clock::time_point T_T2;
#define __TOC__ T_T2 = std::chrono::steady_clock::now();
#define __SHOWTL__ std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds> (T_T2 - T_T1).count() << "[ms]" << std::endl;




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

#endif // LIBS_H_MAIN
