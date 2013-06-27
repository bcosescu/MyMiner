#include "SDL.h"
#include "SDL_image.h"
#include "TableBoard.h"
#include "AutomatedTests.h"
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

    SDL_WM_SetCaption("My Miner", NULL);

    SDL_Surface *pBackGroundImg = IMG_Load("./Resources/BackGround.jpg");
    if(!pBackGroundImg)
    {
        assert(false);
        std::cout << IMG_GetError() << std::endl;
        return 0;
    }
    
    SDL_Surface *pScreen = SDL_SetVideoMode(pBackGroundImg->w, pBackGroundImg->h, 32, SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_ANYFORMAT);
    if(!pScreen)
    {
        assert(false);
        std::cout << SDL_GetError() << std::endl;
        return 0;
    }
    SDL_FillRect(pScreen , NULL , 0x66FF00);

    SDL_Event event;

    bool bInGame = true;
    while(bInGame)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_KEYDOWN:
                {
                    if(event.key.keysym.sym == SDLK_RETURN)
                        exit(0);
                    break;
                }

                case SDL_QUIT:
                    bInGame = false;
                break;
            }
        }

        SDL_Rect imgRect;
        imgRect.x = 0;
        imgRect.y = 0;
        imgRect.w = pBackGroundImg->w;
        imgRect.h = pBackGroundImg->h;

        SDL_Rect screenRect = imgRect;
        SDL_BlitSurface(pBackGroundImg, &imgRect, pScreen, &screenRect);
        SDL_Flip(pScreen);
    }

    return 0;
}