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

    memset((Uint8*)&m_rcMineEntrance, 0, sizeof(SDL_Rect));
    
    m_rcMineEntrance.x = 338;
    m_rcMineEntrance.y = 110;
    m_rcMineEntrance.w = 320;
    m_rcMineEntrance.h = 320;


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
    SDL_FillRect(pSurface, &m_rcMineEntrance, 0xAA0000);

    return false;
}
