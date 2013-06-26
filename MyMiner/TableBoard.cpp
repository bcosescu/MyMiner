#include "TableBoard.h"
#include <stdlib.h>
#include <iostream>

CTableBoard::CTableBoard(void)
{
    //Fill with empty cells
    for(size_t i = 0; i < TABLESIZE; i++)
    {
        TableRow arrRow;
        for(size_t j = 0; j < TABLESIZE; j++)
        {
            arrRow.push_back(new CTableCell());
        }

        m_arrTable.push_back(arrRow);
    }

    //Create links
    for(size_t i = 0; i < TABLESIZE; i++)
    {
        TableRow arrRow = m_arrTable[i];
        for(size_t j = 0; j < TABLESIZE; j++)
        {
            arrRow[j]->SetCellUp((i == 0 )? NULL : m_arrTable[i - 1][j]);
            arrRow[j]->SetCellDown((i == (TABLESIZE - 1) )? NULL : m_arrTable[i + 1][j]);
            arrRow[j]->SetCellLeft((j == 0 )? NULL : m_arrTable[i][j - 1]);
            arrRow[j]->SetCellRight((j == (TABLESIZE - 1) )? NULL : m_arrTable[i][j + 1]);
        }
    }
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

//Shuffle table board
bool CTableBoard::ShuffleTableBoard()
{
    for(size_t i = 0; i < TABLESIZE; i++)
    {
        TableRow arrRow = m_arrTable[i];
        for(size_t j = 0; j < TABLESIZE; j++)
        {
            arrRow[j]->SetMarker(rand() % MAX_CELL_MARKER + 1);
        }
    }

    return true;
}

//View table board - debug
void CTableBoard::PrintTableBoard()
{
    for(size_t i = 0; i < m_arrTable.size(); i++)
    {
        TableRow arrRow = m_arrTable[i];
        for(size_t j = 0; j < arrRow.size(); j++)
        {
            std::cout << arrRow[j]->GetMarker() << " ";
        }

        std::cout << std::endl;
    }
}