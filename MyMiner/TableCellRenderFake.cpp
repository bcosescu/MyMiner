#include "TableCellRenderFake.h"
#include "TableCellAnimationDrop.h"
#include "TableCell.h"
#include "TableBoardRender.h"

CTableCellRenderFake::CTableCellRenderFake(CTableBoardRender* pBoard, Uint16 nX, Uint16 nY, CTableCell* pCell)
: CTableCellRender(pBoard, nX, nY, pCell)
{
}

CTableCellRenderFake::~CTableCellRenderFake(void)
{
}


bool CTableCellRenderFake::Render(SDL_Surface* pSurface)
{
    //Render pending animations
    if(m_animations.size())
    {
        CTableCellAnimationBasePtr spCurrentAnimation = m_animations.front();
        bool bCouldRender = spCurrentAnimation->Render(pSurface);
        if(spCurrentAnimation->IsComplete())
        {
            m_animations.pop_front();
        }

    }

    return true;
}

void CTableCellRenderFake::CellMovesDown(CTableCell* pCell)
{
    if(pCell->IsEmpty())
        return;

    CreateAnimation<CTableCellAnimationDrop>();
}