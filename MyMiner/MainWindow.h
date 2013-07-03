// Main window for the game
#pragma once
#include "TableBoardRender.h"

class CMainWindow
{
public:
    CMainWindow(CTableBoard& tableboard);
    ~CMainWindow(void);

    bool                Initialize      ();
    bool                UnInitialize    ();
    bool                GameLoop        ();

private:

    bool                HandleKey       (const SDL_KeyboardEvent& keyEvent);
    bool                HandleMouse     (const SDL_MouseButtonEvent& mouseEvent);


    SDL_Surface*        m_pWindow;              //window object
    CTableBoardRender   m_TableBoardRender;     //table render
};
