#include "TableCellAnimationRight.h"
#include "Defines.h"
#include <iostream>

CTableCellAnimationRight::CTableCellAnimationRight(int nStartX, int nStartY, CGemsResources::eGemResource resource)
: CTableCellAnimationBase(nStartX, nStartY, resource)
{
}

CTableCellAnimationRight::~CTableCellAnimationRight(void)
{
    std::cout << "~CTableCellAnimationRight\n";
}

void CTableCellAnimationRight::UpdateForAnimation(SDL_Surface* pSurface)
{
    if(!CanDraw())
        return;

    if(m_nX > m_nStartX + CELL_RENDER_SIZE)
        m_bComplete = true;
    else
        m_nX++;
}