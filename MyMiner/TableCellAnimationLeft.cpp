#include "TableCellAnimationLeft.h"
#include "Defines.h"

CTableCellAnimationLeft::CTableCellAnimationLeft(int nStartX, int nStartY, CGemsResources::eGemResource resource)
: CTableCellAnimationBase(nStartX, nStartY, resource)
{
}

CTableCellAnimationLeft::~CTableCellAnimationLeft(void)
{
}


void CTableCellAnimationLeft::UpdateForAnimation()
{
    if(m_nX < m_nStartX - CELL_RENDER_SIZE)
        m_bComplete = true;
    else
        m_nX--;
}