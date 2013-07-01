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
    //CAutomatedTests::ExecuteTests();
    
    SDL_Init(SDL_INIT_VIDEO);
    atexit(SDL_Quit);

    CTableBoard tableboard;
    //tableboard.FillWithRandomMarker();
    tableboard.LoadFromTemplate("1 4 4 1 1 3 1 3,\
                                 3 3 5 4 4 2 1 2,\
                                 1 4 2 2 4 3 4 4,\
                                 3 2 3 3 5 2 5 2,\
                                 5 2 5 4 3 4 3 2,\
                                 3 4 2 1 1 3 5 1,\
                                 4 5 1 1 5 5 3 1,\
                                 1 1 4 4 1 1 5 4");
    std::cout << "Initial:\n";
    tableboard.PrintTableBoard();

    CMainWindow mainWindow(tableboard);

    mainWindow.Initialize();
    mainWindow.GameLoop();
    mainWindow.UnInitialize();

    return 0;
}