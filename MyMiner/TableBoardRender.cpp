#include "TableBoardRender.h"
#include <iostream>
#include <assert.h>
#include "TableCellRender.h"
#include "Defines.h"
#include "TableBoard.h"

CTableBoardRender::CTableBoardRender(CTableBoard& tableboard)
: m_TableBoard(tableboard)
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
    m_rcMineEntrance.w = TABLE_RENDER_SIZE;
    m_rcMineEntrance.h = TABLE_RENDER_SIZE;

    m_pSelectedCell = NULL;
    GenerateCellRenders();
}

CTableBoardRender::~CTableBoardRender(void)
{
    for(size_t i = 0; i < m_CellsRender.size(); i++)
    {
        CTableCellRender *pCellRender = m_CellsRender[i];
        if(pCellRender)
            delete pCellRender;
    }

    SDL_FreeSurface(m_pBackGroundImg);
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

    for(size_t i = 0; i < m_CellsRender.size(); i++)
        m_CellsRender[i]->Render(pSurface);

    return false;
}

bool CTableBoardRender::HandleMouse(const SDL_MouseButtonEvent& mouseEvent)
{
    if(mouseEvent.button != SDL_BUTTON_LEFT)
        return true;

    if(!PointInRect(mouseEvent.x, mouseEvent.y, m_rcMineEntrance))
    {
        SelectCell(NULL);
        return true;
    }

    CTableCellRender* pCellRender = GetRenderCell(mouseEvent.x, mouseEvent.y);
    if(pCellRender->InAnimation())
        return true;

    bool bSwapDone = true;

    if(!m_pSelectedCell)
    {
        SelectCell(pCellRender);
        return true;
    }
    else if (m_pSelectedCell == pCellRender)
    {
        SelectCell(NULL);
        return true;
    }
    else
    {
        bSwapDone = pCellRender->TryToSwap(m_pSelectedCell);
        if(!bSwapDone)
        {
            SelectCell(pCellRender);
            return true;
        }
    }

    if(bSwapDone)
    {
        //Analize tableboard for any changes
        bool bGoodMove = m_TableBoard.CanCollapse(m_pSelectedCell->GetCell()) ||
                         m_TableBoard.CanCollapse(pCellRender->GetCell());

        if(!bGoodMove)
        {
            //Swap cell back
            pCellRender->TryToSwap(m_pSelectedCell);
            SelectCell(NULL);
            return true;
        }

        //Save animations
        m_PendingAnimations.clear();
        AnimationsList animations;
        m_pSelectedCell->GetAnimations(animations);  
        assert(animations.size() != 0);
        m_PendingAnimations.insert(m_PendingAnimations.end(), animations.begin(), animations.end());

        animations.clear();
        pCellRender->GetAnimations(animations);  
        assert(animations.size() != 0);
        m_PendingAnimations.insert(m_PendingAnimations.end(), animations.begin(), animations.end());

        m_TableBoard.MatchTableBoard();
        m_TableBoard.FillWithRandomMarker();

    }

    SelectCell(NULL);
    return true;
}

void CTableBoardRender::EmptyCells()
{
    m_PendingAnimations.clear();
}

bool CTableBoardRender::PendingScenes(AnimationsList& listPendingAnimations)
{
    if(m_PendingAnimations.size() == 0)
        return false;

    listPendingAnimations = m_PendingAnimations;
    return true;
}

void CTableBoardRender::GenerateCellRenders()
{
    for(int i = 0; i < TABLESIZE; i++)
    {
        for(int j = 0; j < TABLESIZE; j++)
        {
            CTableCellRender* pCellRender = new CTableCellRender(this, m_rcMineEntrance.x + j * CELL_RENDER_SIZE, m_rcMineEntrance.y + i * CELL_RENDER_SIZE, m_TableBoard.GetCell(i, j));
            m_CellsRender.push_back(pCellRender);
        }
    }
}

bool CTableBoardRender::PointInRect(int x, int y, const SDL_Rect& rc) const
{
    return (x >= rc.x) && (x < rc.x + rc.w) && (y >= rc.y) && (y < rc.y + rc.h);
}

CTableCellRender* CTableBoardRender::GetRenderCell(int x, int y)
{
    for(size_t i = 0; i < m_CellsRender.size(); i++)
    {
        CTableCellRender* pCellRender = m_CellsRender[i];
        if(pCellRender->PointInCell(x, y))
            return pCellRender;
    }

    return NULL;
}

void CTableBoardRender::SelectCell(CTableCellRender* pCellRender)
{
    if(m_pSelectedCell)
    {
        m_pSelectedCell->SetSelected(false);
    }

    m_pSelectedCell = pCellRender;

    if(m_pSelectedCell)
    {        
        m_pSelectedCell->SetSelected(true);
    }
}