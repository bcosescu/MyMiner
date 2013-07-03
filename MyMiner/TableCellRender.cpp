#include "TableCellRender.h"
#include "TableCell.h"
#include "GemsResources.h"
#include "Defines.h"
#include "TableCellAnimationBase.h"
#include "TableCellAnimationLeft.h"
#include "TableCellAnimationRight.h"
#include "TableCellAnimationUp.h"
#include "TableCellAnimationDown.h"
#include "TableCellAnimationCellDestroyed.h"
#include "TableCellAnimationNone.h"
#include "TableBoardRender.h"

//specialize for CTableCellAnimationNone
template<>
void CTableCellRender::CreateAnimation<CTableCellAnimationNone>()
{
    CTableCellAnimationBasePtr spAnimation(new CTableCellAnimationNone());

    AnimationsList priorAnimations;
    if(m_pTableBoardRender->LastScenes(priorAnimations))
        spAnimation->AddPendingAnimations(priorAnimations);

    m_animations.push_back(spAnimation);
}

CTableCellRender::CTableCellRender(CTableBoardRender* pBoard, Uint16 nX, Uint16 nY, CTableCell* pCell)
{
    m_pTableBoardRender = pBoard;
    m_pCell = pCell;
    
    if(m_pCell)
        m_pCell->SetNotifier(this);

    m_nX = nX;
    m_nY = nY;
    m_bSelected = false;
}

CTableCellRender::~CTableCellRender(void)
{
}

//Render the cell on screen
bool CTableCellRender::Render(SDL_Surface* pSurface)
{
    if(!m_pCell)
        return false;

    //Render pending animations first
    if(m_animations.size())
    {
        CTableCellAnimationBasePtr spCurrentAnimation = m_animations.front();
        bool bCouldRender = spCurrentAnimation->Render(pSurface);
        if(spCurrentAnimation->IsComplete())
        {
            m_animations.pop_front();
        }

        if(bCouldRender)
            return true;
    }

    //Draw the last animation resource
    CGemsResources::eGemResource resource = m_animations.size() ? m_animations.front()->GetResource() : (CGemsResources::eGemResource)m_pCell->GetMarker();
    SDL_Surface* pImage = CGemsResources::GetInstance().ResourceFor(resource);
    if(!pImage)
        return false;

    //Draw static image if no animation

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

//If selected draw a special rectangle to mark it as selected
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

//helper function
bool CTableCellRender::PointInCell(Uint16 nX, Uint16 nY) const
{
    return (nX >= m_nX) && (nX < m_nX + CELL_RENDER_SIZE) && (nY >= m_nY) && (nY < m_nY + CELL_RENDER_SIZE);
}

//switch with another render - only the value is swaped
bool CTableCellRender::TryToSwap(CTableCellRender* pCellRender)
{
    if(!m_pCell)
        return false;
    
    CTableCell* pTheOtherCell = pCellRender->GetCell();
    if(m_pCell->IsEmpty() || pTheOtherCell->IsEmpty())
        return false;

    return m_pCell->Swap(pTheOtherCell);
}

//notification from the cell that a move to the right is place
void CTableCellRender::CellMovesRight(CTableCell* pCell)
{
    if(pCell->IsEmpty())
        return;

    CreateAnimation<CTableCellAnimationRight>();

    AnimationsList priorAnimations;
    m_pTableBoardRender->PendingScenes(priorAnimations);
}

//notification from the cell that a move to the left is place
void CTableCellRender::CellMovesLeft(CTableCell* pCell)
{
    if(pCell->IsEmpty())
        return;

    CreateAnimation<CTableCellAnimationLeft>();

    AnimationsList priorAnimations;
    m_pTableBoardRender->PendingScenes(priorAnimations);
}

//notification from the cell that a move up is place
void CTableCellRender::CellMovesUp(CTableCell* pCell)
{
    if(pCell->IsEmpty())
        return;

    CreateAnimation<CTableCellAnimationUp>();

    AnimationsList priorAnimations;
    m_pTableBoardRender->PendingScenes(priorAnimations);
}

//notification from the cell that a move down is place
void CTableCellRender::CellMovesDown(CTableCell* pCell)
{
    if(pCell->IsEmpty())
        return;

    CreateAnimation<CTableCellAnimationDown>();

    AnimationsList priorAnimations;
    m_pTableBoardRender->PendingScenes(priorAnimations);
}

//notification from the cell that is being destroyed
void CTableCellRender::CellDestroyed(CTableCell* pCell)
{
    if(pCell->IsEmpty())
        return;

    CreateAnimation<CTableCellAnimationCellDestroyed>();

    AnimationsList priorAnimations;
    m_pTableBoardRender->PendingScenes(priorAnimations);
}

//link animations between renders
void CTableCellRender::LinkRenders(TableCellRenders cellsRenders)
{
    CTableCellAnimationBasePtr spAnimation(new CTableCellAnimationNone());
    for(size_t i = 0; i < cellsRenders.size(); i++)
    {
        AnimationsList animations;
        cellsRenders[i]->GetAnimations(animations);
        spAnimation->AddPendingAnimations(animations);
    }

    m_animations.push_back(spAnimation);
}