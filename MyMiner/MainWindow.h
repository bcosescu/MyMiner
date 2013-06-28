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

private:

    SDL_Surface*        m_pWindow;
    CTableBoardRender   m_TableBoardRender;
};
