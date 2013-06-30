#include "TableCellRender.h"
#include "TableCell.h"
#include "GemsResources.h"
#include "Defines.h"
#include "TableCellAnimationBase.h"
#include "TableCellAnimationLeft.h"
#include "TableCellAnimationRight.h"
#include "TableCellAnimationUp.h"
#include "TableCellAnimationDown.h"
#include "TableBoardRender.h"

CTableCellRender::CTableCellRender(CTableBoardRender* pBoard, Uint16 nX, Uint16 nY, CTableCell* pCell)
{
    m_pTableBoardRender = pBoard;
    m_pCell = pCell;
    m_pCell->SetNotifier(this);
    m_nX = nX;
    m_nY = nY;
    m_bSelected = false;
}

CTableCellRender::~CTableCellRender(void)
{
}

bool CTableCellRender::Render(SDL_Surface* pSurface)
{
    if(!m_pCell)
        return false;

    SDL_Surface* pImage = CGemsResources::GetInstance().ResourceFor((CGemsResources::eGemResource)m_pCell->GetMarker());
    if(!pImage)
        return false;

    //Render pending animations
    if(m_animations.size())
    {
        CTableCellAnimationBasePtr spCurrentAnimation = m_animations.front();
        spCurrentAnimation->Render(pSurface);
        if(spCurrentAnimation->IsComplete())
        {
            m_animations.pop_front();
        }

        return true;
    }

    RenderSelected(pSurface);

    //Calculate offset image
    Uint16 xOffset = (CELL_RENDER_SIZE - pImage->w) / 2;
    Uint16 yOffset = (CELL_RENDER_SIZE - pImage->h) / 2;

    SDL_Rect imgRect;
    imgRect.x = m_nX + xOffset;
    imgRect.y = m_nY + yOffset;
    imgRect.w = pImage->w;
    imgRect.h = pImage->h;

    SDL_BlitSurface(pImage, NULL, pSurface, &imgRect);

    return true;
}

void CTableCellRender::RenderSelected(SDL_Surface* pSurface)
{
    if(!m_bSelected)
        return;

    SDL_Rect rc;
    rc.x = m_nX;
    rc.y = m_nY;
    rc.w = CELL_RENDER_SIZE;
    rc.h = 1;
    SDL_FillRect(pSurface, &rc, CELL_SELECTED_COLOR);

    rc.x = m_nX + CELL_RENDER_SIZE;
    rc.y = m_nY;
    rc.w = 1;
    rc.h = CELL_RENDER_SIZE;
    SDL_FillRect(pSurface, &rc, CELL_SELECTED_COLOR);

    rc.x = m_nX;
    rc.y = m_nY;
    rc.w = 1;
    rc.h = CELL_RENDER_SIZE;
    SDL_FillRect(pSurface, &rc, CELL_SELECTED_COLOR);

    rc.x = m_nX;
    rc.y = m_nY + CELL_RENDER_SIZE;
    rc.w = CELL_RENDER_SIZE;
    rc.h = 1;
    SDL_FillRect(pSurface, &rc, CELL_SELECTED_COLOR);
}

bool CTableCellRender::PointInCell(Uint16 nX, Uint16 nY) const
{
    return (nX >= m_nX) && (nX < m_nX + CELL_RENDER_SIZE) && (nY >= m_nY) && (nY < m_nY + CELL_RENDER_SIZE);
}

bool CTableCellRender::TryToSwap(CTableCellRender* pCellRender)
{
    if(!m_pCell)
        return false;
    
    CTableCell* pTheOtherCell = pCellRender->GetCell();
    if(m_pCell->IsEmpty() || pTheOtherCell->IsEmpty())
        return false;

    return m_pCell->Swap(pTheOtherCell);
}

void CTableCellRender::CellMovesRight(CTableCell*)
{
    CreateAnimation<CTableCellAnimationRight>();
}

void CTableCellRender::CellMovesLeft(CTableCell*)
{
    CreateAnimation<CTableCellAnimationLeft>();
}

void CTableCellRender::CellMovesUp(CTableCell*)
{
    CreateAnimation<CTableCellAnimationUp>();
}

void CTableCellRender::CellMovesDown(CTableCell*)
{
    CreateAnimation<CTableCellAnimationDown>();
}
