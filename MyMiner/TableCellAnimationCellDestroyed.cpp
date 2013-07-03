#include "TableCellAnimationCellDestroyed.h"
#include "Defines.h"
#include "SDL.h"

CTableCellAnimationCellDestroyed::CTableCellAnimationCellDestroyed(int nStartX, int nStartY, CGemsResources::eGemResource resource)
: CTableCellAnimationBase(nStartX, nStartY, resource)
{
    m_nKeepCounter = 0;
}

CTableCellAnimationCellDestroyed::~CTableCellAnimationCellDestroyed(void)
{
}

//This animations will present the same thing for 20 times
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

//Render animation
void CTableCellAnimationCellDestroyed::RenderImage(SDL_Surface* pImage, SDL_Surface* pSurface)
{
    //Draw a rectangle to mark the cell is beeing destroyed and apply image
    SDL_Rect rc;
    rc.x = m_nX;
    rc.y = m_nY;
    rc.w = CELL_RENDER_SIZE;
    rc.h = CELL_RENDER_SIZE;
    SDL_FillRect(pSurface, &rc, CELL_DESTROY_COLOR);
    CTableCellAnimationBase::RenderImage(pImage, pSurface);
}