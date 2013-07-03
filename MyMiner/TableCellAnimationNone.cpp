#include "TableCellAnimationNone.h"
#include <iostream>

int CTableCellAnimationNone::nCount = 0;

CTableCellAnimationNone::CTableCellAnimationNone()
: CTableCellAnimationBase(0, 0, CGemsResources::eGMNone)
{
    //std::cout << "CTableCellAnimationNone " << ++nCount << "\n";
}

CTableCellAnimationNone::~CTableCellAnimationNone(void)
{
    //std::cout << "~CTableCellAnimationNone " << nCount-- << "\n";
}

void CTableCellAnimationNone::UpdateForAnimation()
{
    m_bComplete = (m_PendingAnimations.size() == 0);
}

void CTableCellAnimationNone::PrintAnimations(int nIdent)
{
    PrintIdent(nIdent);
    std::cout << "CTableCellAnimationNone\n";
    CTableCellAnimationBase::PrintAnimations(nIdent);
}