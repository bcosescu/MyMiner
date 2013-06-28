#include "TableCell.h"
#include <stdio.h>

CTableCell::CTableCell()
: m_nMarker(0)
{
    m_pCellUp = NULL;
    m_pCellDown = NULL;
    m_pCellLeft = NULL;
    m_pCellRight = NULL;
}

CTableCell::CTableCell(int nMarker)
: m_nMarker(nMarker)
{
    m_pCellUp = NULL;
    m_pCellDown = NULL;
    m_pCellLeft = NULL;
    m_pCellRight = NULL;
}

CTableCell::~CTableCell(void)
{
}

bool CTableCell::IsNeighbour(CTableCell* pCell)
{
    if(!pCell)
        return false;

    return (m_pCellDown == pCell) ||
           (m_pCellUp == pCell) ||
           (m_pCellLeft == pCell) ||
           (m_pCellRight == pCell);
}

bool CTableCell::Swap(CTableCell* pCell)
{
    if(!pCell)
        return false;

    int nTmpMarker = m_nMarker;
    m_nMarker = pCell->GetMarker();
    pCell->SetMarker(nTmpMarker);

    return true;
}