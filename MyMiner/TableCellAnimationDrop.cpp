#include "TableCellAnimationDrop.h"
#include "Defines.h"
#include "SDL.h"
#include <assert.h>
#include <algorithm>

CTableCellAnimationDrop::CTableCellAnimationDrop(int nStartX, int nStartY, CGemsResources::eGemResource resource)
: CTableCellAnimationBase(nStartX, nStartY, resource)
{
    assert(resource != CGemsResources::eGMNone);
    m_nImgHeight = 0;
}

CTableCellAnimationDrop::~CTableCellAnimationDrop(void)
{
}

//This animation will only draw a portion of resource on the top row of the table board 
void CTableCellAnimationDrop::UpdateForAnimation()
{
    if(!CanDraw())
        return;

    SDL_Surface* pImage = CGemsResources::GetInstance().ResourceFor(m_resource);
    if(!pImage)
        return;

    if(m_nImgHeight > pImage->h + (CELL_RENDER_SIZE - pImage->h) / 2)
        m_bComplete = true;
    else
        m_nImgHeight++;
}

//Draw the image
void CTableCellAnimationDrop::RenderImage(SDL_Surface* pImage, SDL_Surface* pSurface)
{
    SDL_Rect imgRect;
    imgRect.x = 0;
    imgRect.y = pImage->h - std::min(m_nImgHeight, pImage->h);
    imgRect.w = pImage->w;
    imgRect.h = m_nImgHeight;

    Uint16 xOffset = (CELL_RENDER_SIZE - pImage->w) / 2;
    Uint16 yOffset = (CELL_RENDER_SIZE - pImage->h) / 2;

    SDL_Rect surfaceRect;
    surfaceRect.x = m_nX + xOffset;
    surfaceRect.y = m_nY + CELL_RENDER_SIZE + ((m_nImgHeight > pImage->h)?(m_nImgHeight - pImage->h) : 0);
    surfaceRect.w = pImage->w;
    surfaceRect.h = pImage->h;

    SDL_BlitSurface(pImage, &imgRect, pSurface, &surfaceRect);
}