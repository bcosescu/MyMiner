#include "TableCellAnimationUp.h"
#include "Defines.h"
#include <iostream>

CTableCellAnimationUp::CTableCellAnimationUp(int nStartX, int nStartY, CGemsResources::eGemResource resource)
: CTableCellAnimationBase(nStartX, nStartY, resource)
{
}

CTableCellAnimationUp::~CTableCellAnimationUp(void)
{
    std::cout << "~CTableCellAnimationUp\n";
}

void CTableCellAnimationUp::UpdateForAnimation(SDL_Surface* pSurface)
{
    if(!CanDraw())
        return;

    if(m_nY < m_nStartY - CELL_RENDER_SIZE)
        m_bComplete = true;
    else
        m_nY--;
}