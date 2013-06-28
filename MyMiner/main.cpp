#include "SDL.h"
#include "SDL_image.h"
#include "TableBoard.h"
#include "AutomatedTests.h"
#include "MainWindow.h"
#undef main

#include <time.h>
#include <conio.h>
#include <assert.h>
#include <iostream>

int main( int argc, char* argv[] )
{
    srand((unsigned int)time(NULL));
    CAutomatedTests::ExecuteTests();
    
    SDL_Init(SDL_INIT_VIDEO);
    atexit(SDL_Quit);

    CTableBoard tableboard;
    tableboard.LoadFromTemplate("0 0 0 2 0 0 0 0,\
                                 5 2 4 5 0 3 1 4,\
                                 1 2 2 2 0 4 2 5,\
                                 3 3 5 5 4 2 4 3,\
                                 1 2 1 1 3 5 2 1,\
                                 3 3 3 3 4 2 1 1,\
                                 4 4 3 4 5 5 3 1,\
                                 3 5 4 1 5 5 2 1");

    CMainWindow mainWindow(tableboard);

    mainWindow.Initialize();
    mainWindow.GameLoop();
    mainWindow.UnInitialize();

    return 0;
}