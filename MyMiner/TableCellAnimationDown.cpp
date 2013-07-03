#include "TableCellAnimationDown.h"
#include "Defines.h"
#include <iostream>

int CTableCellAnimationDown::nCount = 0;

CTableCellAnimationDown::CTableCellAnimationDown(int nStartX, int nStartY, CGemsResources::eGemResource resource)
: CTableCellAnimationBase(nStartX, nStartY, resource)
{
    std::cout << "CTableCellAnimationDown " << nCount++ << "\n";
}

CTableCellAnimationDown::~CTableCellAnimationDown(void)
{
    std::cout << "~CTableCellAnimationDown " << nCount-- << "\n";
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
void CTableCellAnimationDown::PrintAnimations(int nIdent)
{
    PrintIdent(nIdent);
    std::cout << "CTableCellAnimationDown\n";
    CTableCellAnimationBase::PrintAnimations(nIdent);
}