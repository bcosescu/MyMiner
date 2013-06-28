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
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    atexit(SDL_Quit);

    CTableBoard tableboard;
    tableboard.FillWithRandomMarker();

    CMainWindow mainWindow(tableboard);

    mainWindow.Initialize();
    mainWindow.GameLoop();
    mainWindow.UnInitialize();

    return 0;
}