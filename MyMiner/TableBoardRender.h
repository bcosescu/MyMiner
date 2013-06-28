#pragma once

#include "SDL_image.h"

class CTableBoardRender
{
public:
    CTableBoardRender(void);
    ~CTableBoardRender(void);

    int             GetWidth    () const { return m_pBackGroundImg->w; };
    int             GetHeight   () const { return m_pBackGroundImg->h; };

    bool            Render      (SDL_Surface* pSurface);

private:
    SDL_Surface*    m_pBackGroundImg;
};
