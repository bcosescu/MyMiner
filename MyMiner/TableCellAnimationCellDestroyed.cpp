#include "TableCellAnimationCellDestroyed.h"
#include "Defines.h"

CTableCellAnimationCellDestroyed::CTableCellAnimationCellDestroyed(int nStartX, int nStartY, CGemsResources::eGemResource resource)
: CTableCellAnimationBase(nStartX, nStartY, resource)
{
    m_nKeepCounter = 0;
}

CTableCellAnimationCellDestroyed::~CTableCellAnimationCellDestroyed(void)
{
}

void CTableCellAnimationCellDestroyed::UpdateForAnimation()
{
   if(m_nKeepCounter > 10)
        m_bComplete = true;
    else
        m_nKeepCounter++;
}
