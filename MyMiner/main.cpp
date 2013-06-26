#include "SDL.h"
#include "TableBoard.h"
#undef main

#include <stdio.h>
#include <conio.h>
#include <assert.h> 
#include <stdlib.h>
#include <time.h>
#include <iostream>

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
    //Verify size
    assert(tableboard.m_arrTable.size() == TABLESIZE);
    for(size_t i = 0; i < tableboard.m_arrTable.size(); i++)
    {
        assert(tableboard.m_arrTable[i].size() == TABLESIZE);
    }

    //Verify number of links between cells
    for(size_t i = 0; i < tableboard.m_arrTable.size(); i++)
    {
        CTableBoard::TableRow arrRow = tableboard.m_arrTable[i];
        for(size_t j = 0; j < arrRow.size(); j++)
        {
            int nCountLinks = 0;
            if(arrRow[j]->GetCellUp() != NULL)
                nCountLinks++;

            if(arrRow[j]->GetCellDown() != NULL)
                nCountLinks++;

            if(arrRow[j]->GetCellRight() != NULL)
                nCountLinks++;

            if(arrRow[j]->GetCellLeft() != NULL)
                nCountLinks++;

            assert(nCountLinks > 1);
        }
    }

    tableboard.ShuffleTableBoard();

    //Verify markers in table cells
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

    tableboard.PrintTableBoard();

    //Redo table board
    tableboard.LoadFromTemplate("5 2 4 2 4 3 1 4,\
                                 1 2 2 5 3 2 2 2,\
                                 3 3 5 2 4 4 2 5,\
                                 3 3 3 5 3 2 4 3,\
                                 1 2 1 1 3 5 2 1,\
                                 3 3 3 3 3 2 1 1,\
                                 4 4 3 4 5 5 3 1,\
                                 3 5 4 1 5 5 2 1");

    //Verify if element 5,4 has the required marker count verticaly and horizontaly
    CTableCell* pCell = tableboard.m_arrTable[5][4];

    int nCountMarkerCol = 0;
    tableboard.SearchForMarker(CTableBoard::eSDUp, pCell, pCell->GetMarker(), nCountMarkerCol);
    tableboard.SearchForMarker(CTableBoard::eSDDown, pCell, pCell->GetMarker(), nCountMarkerCol);

    assert(nCountMarkerCol == 2);

    int nCountMarkerRow = 0;
    tableboard.SearchForMarker(CTableBoard::eSDLeft, pCell, pCell->GetMarker(), nCountMarkerRow);
    tableboard.SearchForMarker(CTableBoard::eSDRight, pCell, pCell->GetMarker(), nCountMarkerRow);

    assert(nCountMarkerRow == 4);

    //Verify element 7,7
    pCell = tableboard.m_arrTable[7][7];
    nCountMarkerCol = 0;
    tableboard.SearchForMarker(CTableBoard::eSDUp, pCell, pCell->GetMarker(), nCountMarkerCol);
    tableboard.SearchForMarker(CTableBoard::eSDDown, pCell, pCell->GetMarker(), nCountMarkerCol);

    assert(nCountMarkerCol == 3);

    nCountMarkerRow = 0;
    tableboard.SearchForMarker(CTableBoard::eSDLeft, pCell, pCell->GetMarker(), nCountMarkerRow);
    tableboard.SearchForMarker(CTableBoard::eSDRight, pCell, pCell->GetMarker(), nCountMarkerRow);

    assert(nCountMarkerRow == 0);
    return true;
}