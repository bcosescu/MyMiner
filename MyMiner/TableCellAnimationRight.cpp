#include "TableCellAnimationRight.h"
#include "Defines.h"

CTableCellAnimationRight::CTableCellAnimationRight(int nStartX, int nStartY, CGemsResources::eGemResource resource)
: CTableCellAnimationBase(nStartX, nStartY, resource)
{
}

CTableCellAnimationRight::~CTableCellAnimationRight(void)
{
}

void CTableCellAnimationRight::UpdateForAnimation()
{
    if(!CanDraw())
        return;

    if(m_nX > m_nStartX + CELL_RENDER_SIZE)
        m_bComplete = true;
    else
        m_nX += SPEED_ANIMATION;
}