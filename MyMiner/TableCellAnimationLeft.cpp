#include "TableCellAnimationLeft.h"
#include "Defines.h"
#include <iostream>

CTableCellAnimationLeft::CTableCellAnimationLeft(int nStartX, int nStartY, CGemsResources::eGemResource resource)
: CTableCellAnimationBase(nStartX, nStartY, resource)
{
}

CTableCellAnimationLeft::~CTableCellAnimationLeft(void)
{
    std::cout << "~CTableCellAnimationLeft\n";
}

void CTableCellAnimationLeft::UpdateForAnimation()
{
    if(!CanDraw())
        return;

    if(m_nX < m_nStartX - CELL_RENDER_SIZE)
        m_bComplete = true;
    else
        m_nX -= SPEED_ANIMATION;
}

void CTableCellAnimationLeft::PrintAnimations(int nIdent)
{
    PrintIdent(nIdent);
    std::cout << "CTableCellAnimationLeft\n";
    CTableCellAnimationBase::PrintAnimations(nIdent);
}