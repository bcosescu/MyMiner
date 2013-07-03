#include "TableCellAnimationCellDestroyed.h"
#include "Defines.h"
#include "SDL.h"
#include <iostream>

CTableCellAnimationCellDestroyed::CTableCellAnimationCellDestroyed(int nStartX, int nStartY, CGemsResources::eGemResource resource)
: CTableCellAnimationBase(nStartX, nStartY, resource)
{
    m_nKeepCounter = 0;
}

CTableCellAnimationCellDestroyed::~CTableCellAnimationCellDestroyed(void)
{
    std::cout << "~CTableCellAnimationCellDestroyed\n";
}

void CTableCellAnimationCellDestroyed::UpdateForAnimation()
{
    if(!CanDraw())
        return;

    if(m_nKeepCounter > 20)
    {
        m_bComplete = true;
        return;
    }
    else
        m_nKeepCounter++;
}

void CTableCellAnimationCellDestroyed::RenderImage(SDL_Surface* pImage, SDL_Surface* pSurface)
{
    SDL_Rect rc;
    rc.x = m_nX;
    rc.y = m_nY;
    rc.w = CELL_RENDER_SIZE;
    rc.h = CELL_RENDER_SIZE;
    SDL_FillRect(pSurface, &rc, CELL_DESTROY_COLOR);
    CTableCellAnimationBase::RenderImage(pImage, pSurface);
}

void CTableCellAnimationCellDestroyed::PrintAnimations(int nIdent)
{
    PrintIdent(nIdent);
    std::cout << "CTableCellAnimationCellDestroyed\n";
    CTableCellAnimationBase::PrintAnimations(nIdent);
}
