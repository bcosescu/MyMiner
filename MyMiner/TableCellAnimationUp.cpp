#include "TableCellAnimationUp.h"
#include "Defines.h"

CTableCellAnimationUp::CTableCellAnimationUp(int nStartX, int nStartY, CGemsResources::eGemResource resource)
: CTableCellAnimationBase(nStartX, nStartY, resource)
{
}

CTableCellAnimationUp::~CTableCellAnimationUp(void)
{
}


void CTableCellAnimationUp::UpdateForAnimation()
{

    if(m_nY < m_nStartY - CELL_RENDER_SIZE)
        m_bComplete = true;
    else
        m_nY--;
}