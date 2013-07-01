#include "TableCell.h"
#include <stdio.h>
#include "CellChangesInterface.h"

CTableCell::CTableCell()
: m_nMarker(0)
{
    m_pNotifier = NULL;
    m_pCellUp = NULL;
    m_pCellDown = NULL;
    m_pCellLeft = NULL;
    m_pCellRight = NULL;
}

CTableCell::CTableCell(int nMarker)
: m_nMarker(nMarker)
{
    m_pNotifier = NULL;
    m_pCellUp = NULL;
    m_pCellDown = NULL;
    m_pCellLeft = NULL;
    m_pCellRight = NULL;
}

CTableCell::~CTableCell(void)
{
}

void CTableCell::ResetMarker()
{
    if(m_pNotifier)
        m_pNotifier->CellDestroyed(this);

    SetMarker(0);
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

    if(!IsNeighbour(pCell))
        return false;

    if(pCell == m_pCellRight)
    {
        if(m_pNotifier)
            m_pNotifier->CellMovesRight(this);

        if(pCell->GetNotifier())
            pCell->GetNotifier()->CellMovesLeft(pCell);
    }

    if(pCell == m_pCellLeft)
    {
        if(m_pNotifier)
            m_pNotifier->CellMovesLeft(this);

        if(pCell->GetNotifier())
            pCell->GetNotifier()->CellMovesRight(pCell);
    }

    if(pCell == m_pCellUp)
    {
        if(m_pNotifier)
            m_pNotifier->CellMovesUp(this);

        if(pCell->GetNotifier())
            pCell->GetNotifier()->CellMovesDown(pCell);
    }

    if(pCell == m_pCellDown)
    {
        if(m_pNotifier)
            m_pNotifier->CellMovesDown(this);

        if(pCell->GetNotifier())
            pCell->GetNotifier()->CellMovesUp(pCell);
    }

    int nTmpMarker = m_nMarker;
    m_nMarker = pCell->GetMarker();
    pCell->SetMarker(nTmpMarker);

    return true;
}