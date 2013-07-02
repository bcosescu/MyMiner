#include "TableCellAnimationNone.h"
#include <iostream>

CTableCellAnimationNone::CTableCellAnimationNone()
: CTableCellAnimationBase(0, 0, CGemsResources::eGMNone)
{
}

CTableCellAnimationNone::~CTableCellAnimationNone(void)
{
    std::cout << "~CTableCellAnimationNone\n";
}

void CTableCellAnimationNone::UpdateForAnimation()
{
    m_bComplete = (m_PendingAnimations.size() == 0);
}