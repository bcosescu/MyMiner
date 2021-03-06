#include "MainWindow.h"
#include <assert.h>
#include <iostream>
#include "GemsResources.h"

CMainWindow::CMainWindow(CTableBoard& tableboard)
: m_TableBoardRender(tableboard)
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

    return CGemsResources::GetInstance().Initialize();
}

//Uninitilize main window
bool CMainWindow::UnInitialize()
{
    return CGemsResources::GetInstance().UnInitialize();
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
                case SDL_MOUSEBUTTONDOWN:
                {
                    HandleMouse(event.button);
                    break;
                }
                case SDL_KEYDOWN:
                {
                    HandleKey(event.key);
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_RETURN:
                        case SDLK_ESCAPE:
                        case SDLK_KP_ENTER:                        
                            bInGame = false;
                            break;
                    }
                    break;
                }

                case SDL_QUIT:
                {
                    bInGame = false;
                    break;
                }
            }
        }

        //Render the table board
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
    return m_TableBoardRender.HandleMouse(mouseEvent);
}