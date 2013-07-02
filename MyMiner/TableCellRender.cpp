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

bool CTableCellRender::Render(SDL_Surface* pSurface)
{
    if(!m_pCell)
        return false;

    //Render pending animations
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

    //Draw static image

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

void CTableCellRender::CellMovesRight(CTableCell* pCell)
{
    if(pCell->IsEmpty())
        return;

    CreateAnimation<CTableCellAnimationRight>();

    AnimationsList priorAnimations;
    m_pTableBoardRender->PendingScenes(priorAnimations);
    std::cout << "Cell moves RIGHT with pending animations = " << priorAnimations.size() << " marker = " << pCell->GetMarker() << "\n";
}

void CTableCellRender::CellMovesLeft(CTableCell* pCell)
{
    if(pCell->IsEmpty())
        return;

    CreateAnimation<CTableCellAnimationLeft>();

    AnimationsList priorAnimations;
    m_pTableBoardRender->PendingScenes(priorAnimations);
    std::cout << "Cell moves LEFT  with pending animations = " << priorAnimations.size() << " marker = " << pCell->GetMarker() << "\n";    
}

void CTableCellRender::CellMovesUp(CTableCell* pCell)
{
    if(pCell->IsEmpty())
        return;

    CreateAnimation<CTableCellAnimationUp>();

    AnimationsList priorAnimations;
    m_pTableBoardRender->PendingScenes(priorAnimations);
    std::cout << "Cell moves UP    with pending animations = " << priorAnimations.size() << " marker = " << pCell->GetMarker() << "\n";    
}

void CTableCellRender::CellMovesDown(CTableCell* pCell)
{
    if(pCell->IsEmpty())
        return;

    CreateAnimation<CTableCellAnimationDown>();

    AnimationsList priorAnimations;
    m_pTableBoardRender->PendingScenes(priorAnimations);
    std::cout << "Cell moves DOWN  with pending animations = " << priorAnimations.size() << " marker = " << pCell->GetMarker() << "\n";
}

void CTableCellRender::CellDestroyed(CTableCell* pCell)
{
    if(pCell->IsEmpty())
        return;

    CreateAnimation<CTableCellAnimationCellDestroyed>();

    AnimationsList priorAnimations;
    m_pTableBoardRender->PendingScenes(priorAnimations);
    std::cout << "Cell DESTROYED with pending animations = " << priorAnimations.size() << " marker = " << pCell->GetMarker() << "\n";
}

void CTableCellRender::CellWillBeEmpty(CTableCell* pCell)
{
    CreateAnimation<CTableCellAnimationNone>();

    AnimationsList priorAnimations;
    m_pTableBoardRender->LastScenes(priorAnimations);
    std::cout << "Cell NONE       with pending animations = " << priorAnimations.size() << " marker = " << pCell->GetMarker() << "\n";
}

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