#include "SDL.h"
#include "TableBoard.h"
#undef main

#include <stdio.h>
#include <conio.h>
#include <assert.h> 
#include <stdlib.h>
#include <time.h>

bool ExecuteTests();

int main( int argc, char* argv[] )
{
    srand((unsigned int)time(NULL));
    ExecuteTests();
    _getch();
    return 0;
}

//tests
bool ExecuteTests()
{
    //TESTS
    CTableBoard tableboard;
    tableboard.GenerateTableBoard();

    //Verify size
    assert(tableboard.m_arrTable.size() == TABLESIZE);
    for(size_t i = 0; i < tableboard.m_arrTable.size(); i++)
    {
        assert(tableboard.m_arrTable[i].size() == TABLESIZE);
    }

    //Verify cells
    for(size_t i = 0; i < tableboard.m_arrTable.size(); i++)
    {
        CTableBoard::TableRow arrRow = tableboard.m_arrTable[i];
        for(size_t j = 0; j < arrRow.size(); j++)
        {
            CTableCell* pCell = arrRow[j];
            assert(pCell);
            assert(pCell->m_nMarker > 0);
            assert(pCell->m_nMarker <= MAX_CELL_MARKER);
        }
    }

    return true;
}