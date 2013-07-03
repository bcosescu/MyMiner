#include "TableCellAnimationNone.h"

CTableCellAnimationNone::CTableCellAnimationNone()
: CTableCellAnimationBase(0, 0, CGemsResources::eGMNone)
{
}

CTableCellAnimationNone::~CTableCellAnimationNone(void)
{
}

//Only pending animations can stop this one
void CTableCellAnimationNone::UpdateForAnimation()
{
    m_bComplete = (m_PendingAnimations.size() == 0);
}