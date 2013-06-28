#include "TableBoardRender.h"
#include <iostream>
#include <assert.h>

CTableBoardRender::CTableBoardRender(void)
{
    m_pBackGroundImg = IMG_Load("./Resources/BackGround.jpg");
    if(!m_pBackGroundImg)
    {
        assert(false);
        std::cout << IMG_GetError() << std::endl;
    }
}

CTableBoardRender::~CTableBoardRender(void)
{
}

bool CTableBoardRender::Render(SDL_Surface* pSurface)
{
    SDL_Rect imgRect;
    imgRect.x = 0;
    imgRect.y = 0;
    imgRect.w = GetWidth();
    imgRect.h = GetHeight();
    
    SDL_Rect screenRect = imgRect;
    SDL_BlitSurface(m_pBackGroundImg, &imgRect, pSurface, &screenRect);

    return false;
}
