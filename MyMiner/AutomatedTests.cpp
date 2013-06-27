#include "AutomatedTests.h"
#include "TableBoard.h"
#include "TableCell.h"
#include <stdio.h>
#include <assert.h> 
#include <stdlib.h>
#include <iostream>


CAutomatedTests::CAutomatedTests(void)
{
}

CAutomatedTests::~CAutomatedTests(void)
{
}

void CAutomatedTests::ExecuteTests()
{
    CTableBoard tableboard;
    //Verify size
    assert(tableboard.m_arrTable.size() == TABLESIZE);
    for(size_t i = 0; i < tableboard.m_arrTable.size(); i++)
    {
        assert(tableboard.m_arrTable[i].size() == TABLESIZE);
    }

    std::cout << "Test 1 Pass\n";

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

    std::cout << "Test 2 Pass\n";
    tableboard.ClearTableBoard();
    tableboard.FillWithRandomMarker(tableboard.m_arrTable[0][0]);

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

            std::vector<CTableCell*> arrCellsVertically;
            tableboard.SearchForMarker(CTableBoard::eSDUp, pCell, pCell->GetMarker(), arrCellsVertically);
            tableboard.SearchForMarker(CTableBoard::eSDDown, pCell, pCell->GetMarker(), arrCellsVertically);

            assert(arrCellsVertically.size() < 2);

            std::vector<CTableCell*> arrCellsHorizontaly;
            tableboard.SearchForMarker(CTableBoard::eSDLeft, pCell, pCell->GetMarker(), arrCellsHorizontaly);
            tableboard.SearchForMarker(CTableBoard::eSDRight, pCell, pCell->GetMarker(), arrCellsHorizontaly);

            assert(arrCellsHorizontaly.size() < 2);

        }
    }
    std::cout << "Test 3 Pass\n";
    
    //Redo table board
    tableboard.LoadFromTemplate("5 2 4 2 4 3 1 4,\
                                 1 2 2 5 3 2 2 2,\
                                 3 3 5 2 4 4 2 5,\
                                 3 3 3 5 3 2 4 3,\
                                 1 2 1 1 3 5 2 1,\
                                 3 3 3 3 3 2 1 1,\
                                 4 4 3 4 5 5 3 1,\
                                 3 5 4 1 5 5 2 1");

    //Verify if element 5,4 has the required marker count vertically and horizontally
    CTableCell* pCell = tableboard.m_arrTable[5][4];

    std::vector<CTableCell*> arrCellsVertically;
    tableboard.SearchForMarker(CTableBoard::eSDUp, pCell, pCell->GetMarker(), arrCellsVertically);
    tableboard.SearchForMarker(CTableBoard::eSDDown, pCell, pCell->GetMarker(), arrCellsVertically);

    assert(arrCellsVertically.size() == 2);

    std::vector<CTableCell*> arrCellsHorizontaly;
    tableboard.SearchForMarker(CTableBoard::eSDLeft, pCell, pCell->GetMarker(), arrCellsHorizontaly);
    tableboard.SearchForMarker(CTableBoard::eSDRight, pCell, pCell->GetMarker(), arrCellsHorizontaly);

    assert(arrCellsHorizontaly.size() == 4);

    //Verify element 7,7
    pCell = tableboard.m_arrTable[7][7];
    arrCellsVertically.clear();
    tableboard.SearchForMarker(CTableBoard::eSDUp, pCell, pCell->GetMarker(), arrCellsVertically);
    tableboard.SearchForMarker(CTableBoard::eSDDown, pCell, pCell->GetMarker(), arrCellsVertically);

    assert(arrCellsVertically.size() == 3);

    arrCellsHorizontaly.clear();
    tableboard.SearchForMarker(CTableBoard::eSDLeft, pCell, pCell->GetMarker(), arrCellsHorizontaly);
    tableboard.SearchForMarker(CTableBoard::eSDRight, pCell, pCell->GetMarker(), arrCellsHorizontaly);

    assert(arrCellsHorizontaly.size() == 0);

    std::cout << "Test 4 Pass\n";

    std::cout << "Before:\n";
    tableboard.PrintTableBoard();

    pCell = tableboard.m_arrTable[5][4];

    CTableBoard::TableCells arrCells;
    tableboard.SearchForMarker(CTableBoard::eSDUp, pCell, pCell->GetMarker(), arrCells);
    arrCells.push_back(pCell);
    tableboard.SearchForMarker(CTableBoard::eSDDown, pCell, pCell->GetMarker(), arrCells);
    tableboard.SearchForMarker(CTableBoard::eSDLeft, pCell, pCell->GetMarker(), arrCells);
    tableboard.SearchForMarker(CTableBoard::eSDRight, pCell, pCell->GetMarker(), arrCells);

    for(size_t i = 0; i < arrCells.size(); i++)
        arrCells[i]->ResetMarker();

    std::cout << "After:\n";
    tableboard.PrintTableBoard();
    std::cout << "Test 5 Pass\n";
    
    CTableBoard::TableCells newEmptyCells = tableboard.CollapseColumns(arrCells);

    assert(newEmptyCells.size() == arrCells.size());
    tableboard.PrintTableBoard();
    
    std::cout << "Test 6 Pass\n";

    tableboard.LoadFromTemplate("0 0 0 2 0 0 0 0,\
                                 5 2 4 5 0 3 1 4,\
                                 1 2 2 2 0 4 2 5,\
                                 3 3 5 5 4 2 4 3,\
                                 1 2 1 1 3 5 2 1,\
                                 3 3 3 3 4 2 1 1,\
                                 4 4 3 4 5 5 3 1,\
                                 3 5 4 1 5 5 2 1");

    std::cout << "Before:\n";
    tableboard.PrintTableBoard();

    pCell = tableboard.m_arrTable[4][7];

    arrCells.clear();
    tableboard.SearchForMarker(CTableBoard::eSDUp, pCell, pCell->GetMarker(), arrCells);
    arrCells.push_back(pCell);
    tableboard.SearchForMarker(CTableBoard::eSDDown, pCell, pCell->GetMarker(), arrCells);
    tableboard.SearchForMarker(CTableBoard::eSDLeft, pCell, pCell->GetMarker(), arrCells);
    tableboard.SearchForMarker(CTableBoard::eSDRight, pCell, pCell->GetMarker(), arrCells);

    for(size_t i = 0; i < arrCells.size(); i++)
        arrCells[i]->ResetMarker();

    newEmptyCells = tableboard.CollapseColumns(arrCells);
    assert(newEmptyCells.size() == arrCells.size());
    std::cout << "After:\n";
    tableboard.PrintTableBoard();

    std::cout << "Test 7 Pass\n";

    //Redo table board
    tableboard.LoadFromTemplate("5 2 4 2 4 3 1 4,\
                                 1 2 2 5 3 2 2 2,\
                                 3 3 5 2 4 4 2 5,\
                                 3 3 3 5 3 2 4 3,\
                                 1 2 1 1 3 5 2 1,\
                                 3 3 3 3 3 2 1 1,\
                                 4 4 3 4 5 5 3 1,\
                                 3 5 4 1 5 5 2 1");

    std::cout << "Before:\n";
    tableboard.PrintTableBoard();
    tableboard.MatchTableBoard();
    std::cout << "After:\n";
    tableboard.PrintTableBoard();
    std::cout << "Test 8 Pass\n";

    //Redo table board
    tableboard.LoadFromTemplate("5 2 1 2 4 3 1 4,\
                                 1 1 1 1 1 1 1 2,\
                                 3 3 1 1 4 4 2 5,\
                                 1 3 3 1 3 2 4 3,\
                                 1 1 1 1 1 1 2 1,\
                                 1 3 2 3 3 2 1 2,\
                                 4 4 3 4 5 5 3 1,\
                                 3 5 4 1 5 5 2 1");

    pCell = tableboard.m_arrTable[0][2];
    arrCells.clear();
    CTableCell* pStartsFrom = NULL;
    tableboard.IdentifyLargestCellCount(pCell, arrCells, pStartsFrom);

    assert(arrCells.size() == 9);
    assert(pStartsFrom == tableboard.m_arrTable[1][3]);
    std::cout << "Test 9 Pass\n";

    tableboard.ClearTableBoard();
    tableboard.FillWithRandomMarker(tableboard.m_arrTable[0][0]);
    tableboard.PrintTableBoard();
    std::cout << "Test 10 Pass\n";

    //Redo table board
    tableboard.LoadFromTemplate("0 0 0 0 0 0 0 4,\
                                 0 0 0 0 4 3 1 2,\
                                 0 0 1 0 4 4 2 5,\
                                 0 0 1 0 3 2 4 3,\
                                 5 0 3 2 1 1 2 1,\
                                 3 2 2 3 3 2 1 2,\
                                 4 4 3 4 5 5 3 1,\
                                 3 5 4 1 5 5 2 1");

    tableboard.FillWithRandomMarker(tableboard.m_arrTable[0][0]);
    tableboard.PrintTableBoard();
    std::cout << "Test 11 Pass\n";

}
