#include "MainWindow.h"
#include <assert.h>
#include <iostream>

CMainWindow::CMainWindow(void)
{
    SDL_WM_SetCaption("My Miner", NULL);
    m_pWindow = NULL;
}

CMainWindow::~CMainWindow(void)
{
}

//Initialize main window
bool CMainWindow::Initialize()
{ 
    m_pWindow = SDL_SetVideoMode(m_TableBoardRender.GetWidth(), m_TableBoardRender.GetHeight(), 32, SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_ANYFORMAT);
    if(!m_pWindow)
    {
        assert(false);
        std::cout << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

//Game loop...where the magic happens
bool CMainWindow::GameLoop()
{
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
                    HandleKey(event.key);
                    if(event.key.keysym.sym == SDLK_RETURN)
                        bInGame = false;
                    break;
                }

                case SDL_QUIT:
                {
                    bInGame = false;
                    break;
                }
            }
        }

        
        m_TableBoardRender.Render(m_pWindow);
        SDL_Flip(m_pWindow);
    }


    return true;
}

//Handle key inputs
bool CMainWindow::HandleKey(const SDL_KeyboardEvent& keyEvent)
{
    return false;
}

//Handle mouse inputs
bool CMainWindow::HandleMouse(const SDL_MouseButtonEvent& mouseEvent)
{
    return false;
}