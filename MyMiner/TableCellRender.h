#pragma once
#include "SDL.h"

class CTableCell;

class CTableCellRender
{
public:
    CTableCellRender(Uint16 nX, Uint16 nY, Uint16 nSize, CTableCell* pCell);
    ~CTableCellRender(void);

    bool        Render  (SDL_Surface* pSurface);

private:

    Uint16      m_nX;
    Uint16      m_nY;
    Uint16      m_nSize;
    CTableCell* m_pCell;
};
