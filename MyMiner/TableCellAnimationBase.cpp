#include "TableCellAnimationBase.h"
#include "SDL.h"
#include "Defines.h"

CTableCellAnimationBase::CTableCellAnimationBase(int nStartX, int nStartY, CGemsResources::eGemResource resource)
{
    m_nSlowDown = 0;
    m_nStartX = nStartX;
    m_nStartY = nStartY;
    m_nX = nStartX;
    m_nY = nStartY;
    m_resource = resource;
    m_bComplete = false;
}

CTableCellAnimationBase::~CTableCellAnimationBase(void)
{
}

bool CTableCellAnimationBase::Render(SDL_Surface* pSurface)
{
    CleanPendingAnimations();

    if(!ContinueRendering())
        return false;

    UpdateForAnimation();

    SDL_Surface* pImage = CGemsResources::GetInstance().ResourceFor(m_resource);
    if(!pImage)
        return true;

    RenderImage(pImage, pSurface);
    return true;
}

void CTableCellAnimationBase::CleanPendingAnimations()
{
    AnimationsList::iterator it = m_PendingAnimations.begin();
    while(it != m_PendingAnimations.end())
    {
        CTableCellAnimationBasePtr spAnimation = *it;
        if(spAnimation->IsComplete())
        {
            m_PendingAnimations.erase(it);
            it = m_PendingAnimations.begin();
        }
        else
        {
            it++;
        }
    }
}

bool CTableCellAnimationBase::ContinueRendering()
{
    return (m_PendingAnimations.size() == 0);
}

void CTableCellAnimationBase::RenderImage(SDL_Surface* pImage, SDL_Surface* pSurface)
{
    Uint16 xOffset = (CELL_RENDER_SIZE - pImage->w) / 2;
    Uint16 yOffset = (CELL_RENDER_SIZE - pImage->h) / 2;

    SDL_Rect surfaceRect;
    surfaceRect.x = m_nX + xOffset;
    surfaceRect.y = m_nY + yOffset;
    surfaceRect.w = pImage->w;
    surfaceRect.h = pImage->h;

    SDL_BlitSurface(pImage, NULL, pSurface, &surfaceRect);
}

bool CTableCellAnimationBase::CanDraw()
{
    return true;
    m_nSlowDown++;
    if(m_nSlowDown % 5 == 0)
        return true;

    return false;
}