#include "SDL.h"
#include "TableBoard.h"
#include "AutomatedTests.h"
#undef main

#include <time.h>
#include <conio.h>

int main( int argc, char* argv[] )
{
    srand((unsigned int)time(NULL));
    CAutomatedTests::ExecuteTests();
    _getch();
    return 0;
}