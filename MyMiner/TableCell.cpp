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
