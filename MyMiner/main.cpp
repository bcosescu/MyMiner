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

    CMainWindow mainWindow;

    mainWindow.Initialize();
    mainWindow.GameLoop();

    return 0;
}