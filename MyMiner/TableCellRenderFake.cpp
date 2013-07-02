#include "TableCellRenderFake.h"

CTableCellRenderFake::CTableCellRenderFake(CTableBoardRender* pBoard, Uint16 nX, Uint16 nY)
: CTableCellRender(pBoard, nX, nY, NULL)
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