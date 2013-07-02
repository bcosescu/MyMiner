#include "TableCellAnimationDown.h"
#include "Defines.h"
#include <iostream>

CTableCellAnimationDown::CTableCellAnimationDown(int nStartX, int nStartY, CGemsResources::eGemResource resource)
: CTableCellAnimationBase(nStartX, nStartY, resource)
{
}

CTableCellAnimationDown::~CTableCellAnimationDown(void)
{
    std::cout << "~CTableCellAnimationDown\n";
}

void CTableCellAnimationDown::UpdateForAnimation()
{
    if(!CanDraw())
        return;

   if(m_nY > m_nStartY + CELL_RENDER_SIZE)
        m_bComplete = true;
    else
        m_nY += SPEED_ANIMATION;
}