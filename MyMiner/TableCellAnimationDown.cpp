#include "TableCellAnimationDown.h"
#include "Defines.h"

CTableCellAnimationDown::CTableCellAnimationDown(int nStartX, int nStartY, CGemsResources::eGemResource resource)
: CTableCellAnimationBase(nStartX, nStartY, resource)
{
}

CTableCellAnimationDown::~CTableCellAnimationDown(void)
{
}


void CTableCellAnimationDown::UpdateForAnimation()
{
   if(m_nY > m_nStartY + CELL_RENDER_SIZE)
        m_bComplete = true;
    else
        m_nY++;
}