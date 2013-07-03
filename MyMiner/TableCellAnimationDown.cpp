#include "TableCellAnimationDown.h"
#include "Defines.h"

CTableCellAnimationDown::CTableCellAnimationDown(int nStartX, int nStartY, CGemsResources::eGemResource resource)
: CTableCellAnimationBase(nStartX, nStartY, resource)
{
}

CTableCellAnimationDown::~CTableCellAnimationDown(void)
{
}

//This animation will complete when the cell goes down with size of the render
void CTableCellAnimationDown::UpdateForAnimation()
{
    if(!CanDraw())
        return;

   if(m_nY > m_nStartY + CELL_RENDER_SIZE)
        m_bComplete = true;
    else
        m_nY += SPEED_ANIMATION;
}