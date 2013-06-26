#include "TableBoard.h"
#include <stdlib.h>

CTableBoard::CTableBoard(void)
{
}

CTableBoard::~CTableBoard(void)
{
    for(size_t i = 0; i < m_arrTable.size(); i++)
    {
        TableRow arrRow = m_arrTable[i];
        for(size_t j = 0; j < arrRow.size(); j++)
        {
            CTableCell* pCell = arrRow[j];
            delete pCell;
        }
    }
}

//Generate a table board
bool CTableBoard::GenerateTableBoard()
{
    if(m_arrTable.size())
        return false;

    for(size_t i = 0; i < TABLESIZE; i++)
    {
        TableRow arrRow;
        for(size_t j = 0; j < TABLESIZE; j++)
        {
            arrRow.push_back(new CTableCell(rand() % MAX_CELL_MARKER + 1));
        }

        m_arrTable.push_back(arrRow);
    }

    return true;
}