#include "TableBoard.h"
#include <stdlib.h>
#include <iostream>
#include <assert.h>
#include <sstream>
#include <map>
#include <algorithm>
#include <conio.h>
#include "CellChangesInterface.h"

//helpers to move from std::map to std::vector
template<typename tPair>
struct second_t 
{ 
    typename tPair::second_type operator()( const typename tPair& p ) const { return p.second; }
};

template<typename tMap> 
second_t<typename tMap::value_type> second(const tMap& m)
{ 
    return second_t<typename tMap::value_type>(); 
}

//helper function clear a cell
void EmptyCell(CTableCell* pCell)
{
    pCell->ResetMarker();
}

CTableBoard::CTableBoard(void)
{
    m_pNotifier = NULL;

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

    //Create a fake row cell
    m_FakeCellRow.push_back(new CTableCell());
    for(size_t i = 1; i < TABLESIZE; i++)
    {
        CTableCell* pCell = new CTableCell();
        pCell->SetCellLeft(m_FakeCellRow[i - 1]);
        m_FakeCellRow[i - 1]->SetCellRight(pCell);
        m_FakeCellRow.push_back(pCell);
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

    for(size_t i = 0; i < m_FakeCellRow.size(); i++)
    {
        CTableCell* pCell = m_FakeCellRow[i];
        delete pCell;
    }
}

//Could this cell be collapsed
bool CTableBoard::CanCollapse(CTableCell* pCell)
{
    if(!pCell || pCell->IsEmpty())
        return false;

    std::vector<CTableCell*> arrCellsVertically;
    SearchForMarker(eSDUp, pCell, pCell->GetMarker(), arrCellsVertically);
    SearchForMarker(eSDDown, pCell, pCell->GetMarker(), arrCellsVertically);

    std::vector<CTableCell*> arrCellsHorizontaly;
    SearchForMarker(eSDLeft, pCell, pCell->GetMarker(), arrCellsHorizontaly);
    SearchForMarker(eSDRight, pCell, pCell->GetMarker(), arrCellsHorizontaly);

    return (arrCellsVertically.size() > 1) ||
           (arrCellsHorizontaly.size() > 1);
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

//Verify and collapse columns if cells are empty
void CTableBoard::CollapseColumns()
{
    for(size_t j = 0; j < TABLESIZE; j++)
    {
        for(size_t i = TABLESIZE - 1; i-- > 0;)
        {
            CTableCell* pCell = m_arrTable[i][j];
            while(pCell->GetCellDown() && pCell->GetCellDown()->IsEmpty())
            {
                pCell->Swap(pCell->GetCellDown());
                pCell = pCell->GetCellDown();
            }
        }
    }
}

//Collapse columns starting from a vector of empty cells
CTableBoard::TableCells CTableBoard::MoveCellsDown(TableCells arrEmptyCells)
{
    TableCells newEmptyCells;
    std::map<CTableCell*, CTableCell*> mapOldEmptyCells;

    //Place empty cells in columns
    for(size_t i = 0; i < arrEmptyCells.size(); i++)
        mapOldEmptyCells.insert(std::pair<CTableCell*, CTableCell*>(arrEmptyCells[i], arrEmptyCells[i]));

    std::vector<TableCells> arrEmptyColumns;
    std::map<CTableCell*, CTableCell*>::iterator it = mapOldEmptyCells.begin();
    while(it != mapOldEmptyCells.end())
    {
        CTableCell* pCell = it->first;
        //First move up at the end of column and then start down
        while(pCell->GetCellUp() && pCell->GetCellUp()->IsEmpty())
        {
            pCell = pCell->GetCellUp();
        }

        //Move down and store empty cells
        TableCells arrColumn;
        while(pCell && pCell->IsEmpty())
        {
            arrColumn.push_back(pCell);
            mapOldEmptyCells.erase(pCell);
            pCell = pCell->GetCellDown();
        }
        arrEmptyColumns.push_back(arrColumn);
        it = mapOldEmptyCells.begin();
    }

    //Move cells down
    for(size_t i = 0; i < arrEmptyColumns.size(); i++)
    {
        TableCells arrEmptyColumn = arrEmptyColumns[i];
        TableCells arrNewEmptyCells = CollapseColumn(arrEmptyColumn);
        std::copy(arrNewEmptyCells.begin(), arrNewEmptyCells.end(), std::back_inserter(newEmptyCells));
    }

    return newEmptyCells;
}

//Collapse column on the empty cells 
CTableBoard::TableCells CTableBoard::CollapseColumn(TableCells arrEmptyColumn)
{
    TableCells newEmptyCells;
    std::map<CTableCell*, CTableCell*> mapNewEmptyCells;

    for(TableCells::iterator it = arrEmptyColumn.begin(); it != arrEmptyColumn.end();it++)
    {
        CTableCell* pCell = *it;

        TableCells arrNonEmptyCells;
        //Move empty cell up
        while(pCell->GetCellUp() && pCell->IsEmpty())
        {
            if(!pCell->GetCellUp()->IsEmpty())
            {
                mapNewEmptyCells.erase(pCell);
                arrNonEmptyCells.push_back(pCell->GetCellUp());
                pCell->Swap(pCell->GetCellUp());
                mapNewEmptyCells.insert(std::pair<CTableCell*, CTableCell*>(pCell->GetCellUp(), pCell->GetCellUp()));
            }

            pCell = pCell->GetCellUp();
        }

        if(m_pNotifier)
        {
            TableCells arrEmptyCells;
            std::copy(it, arrEmptyColumn.end(), std::back_inserter(arrEmptyCells));
            m_pNotifier->ColumnCollapsed(arrEmptyCells, arrNonEmptyCells);
        }
    }

    std::transform(mapNewEmptyCells.begin(), mapNewEmptyCells.end(), std::back_inserter(newEmptyCells), second(mapNewEmptyCells));
    return newEmptyCells;
}

//Search for the same marker in the specified direction
void CTableBoard::SearchForMarker(eSearchDirection eDirection, CTableCell* pCell, int nMarker, TableCells& arrCells)
{
    if(!pCell || nMarker == 0 || nMarker > MAX_CELL_MARKER)
        return;

    CTableCell* pNextCell = NULL;

    switch(eDirection)
    {
        case eSDUp:    pNextCell = pCell->GetCellUp(); break;
        case eSDDown:  pNextCell = pCell->GetCellDown(); break;
        case eSDLeft:  pNextCell = pCell->GetCellLeft(); break;
        case eSDRight: pNextCell = pCell->GetCellRight(); break;
        default:
        {
            assert(false);
            return;
        }
    }

    if(pNextCell)
    {
        if(pNextCell->GetMarker() != nMarker)
            return;

        arrCells.push_back(pNextCell);
        SearchForMarker(eDirection, pNextCell, nMarker, arrCells);
    }
}

//Search the whole table board for matching lines and columns
void CTableBoard::MatchTableBoard()
{
    while(1)
    {
        bool bCollapsedColumns = false;

        for(size_t i = 0; i < TABLESIZE; i++)
        {
            for(size_t j = 0; j < TABLESIZE; j++)
            {
                CTableCell* pCell = m_arrTable[i][j];

                if(pCell->IsEmpty())
                    continue;

                TableCells arrCells;
                CTableCell* pStartingCell = NULL;
                IdentifyLargestCellCount(pCell, arrCells, pStartingCell);

                arrCells.push_back(pStartingCell);

                if(arrCells.size() > 1)
                {
                    if(m_pNotifier)
                        m_pNotifier->CellsToBeDestroyed(arrCells);

                    std::for_each(arrCells.begin(), arrCells.end(), &EmptyCell);

                    if(m_pNotifier)
                        m_pNotifier->CellsDestroyed(arrCells);

                    bCollapsedColumns = true;
                    MoveCellsDown(arrCells);
                }
            }
        }

        if(!bCollapsedColumns)
            break;
    }
}

//Recursive function to detect the largest possibility of matching cells
void CTableBoard::IdentifyLargestCellCount(CTableCell* pCell, TableCells& arrCells, CTableCell*& pStartCell)
{
    if(!pCell)
        return;

    TableCells arrCellsCol;
    SearchForMarker(eSDUp, pCell, pCell->GetMarker(), arrCellsCol);
    SearchForMarker(eSDDown, pCell, pCell->GetMarker(), arrCellsCol);

    TableCells arrCellsLine;
    SearchForMarker(eSDLeft, pCell, pCell->GetMarker(), arrCellsLine);
    SearchForMarker(eSDRight, pCell, pCell->GetMarker(), arrCellsLine);

    TableCells arrResultingCells;
    if(arrCellsCol.size() > 1)
        arrResultingCells.insert(arrResultingCells.end(), arrCellsCol.begin(), arrCellsCol.end());

    if(arrCellsLine.size() > 1)
        arrResultingCells.insert(arrResultingCells.end(), arrCellsLine.begin(), arrCellsLine.end());

    if(arrResultingCells.size() > arrCells.size())
    {
        arrCells = arrResultingCells;
        pStartCell = pCell;

        for(size_t i = 0; i < arrResultingCells.size(); i++)
        {
            IdentifyLargestCellCount(arrResultingCells[i], arrCells, pStartCell);
        }
    }
}

//Generate a random marker
int CTableBoard::GenerateRandomMarker(CTableCell* pCell)
{
    if(!pCell || !pCell->IsEmpty())
        return 0;

    int nGeneratedMarker = 0;
    bool bMarkerIsGood = false;
    
    while(!bMarkerIsGood)
    {
        nGeneratedMarker = rand() % MAX_CELL_MARKER + 1;

        TableCells arrCellsVertically;
        SearchForMarker(eSDUp, pCell, nGeneratedMarker, arrCellsVertically);
        SearchForMarker(eSDDown, pCell, nGeneratedMarker, arrCellsVertically);

        TableCells arrCellsHorizontaly;
        SearchForMarker(eSDLeft, pCell, nGeneratedMarker, arrCellsHorizontaly);
        SearchForMarker(eSDRight, pCell, nGeneratedMarker, arrCellsHorizontaly);
        
        bMarkerIsGood = (arrCellsVertically.size() <= 1) && (arrCellsHorizontaly.size() <= 1);
    }

    return nGeneratedMarker;
}

//Fill empty cells in tableboard 
void CTableBoard::FillWithRandomMarker()
{
    for(size_t j = 0; j < TABLESIZE; j++)
    {
        TableCells filledCollumn;
        for(size_t i = 0; i < TABLESIZE; i++)
        {
            if(m_arrTable[i][j]->IsEmpty())
            {
                int nMarker = GenerateRandomMarker(m_arrTable[i][j]);
                m_arrTable[i][j]->SetMarker(nMarker);
                filledCollumn.push_back(m_arrTable[i][j]);
            }
        }

        if(filledCollumn.size() == 0)
            continue;

        //Create extra cells that we link to the cells in tableboard and the we delete them
        TableCells extraCells;
        for(size_t ii = 0; ii < filledCollumn.size() - 1; ii++)
        {
            CTableCell* pCell = new CTableCell(filledCollumn[ii]->GetMarker());
            pCell->SetCellUp(extraCells.size() == 0 ? NULL : extraCells.back());
            pCell->SetCellDown(NULL);
            pCell->SetCellLeft(NULL);
            pCell->SetCellRight(NULL);

            if(extraCells.size())
                extraCells.back()->SetCellDown(pCell);

            extraCells.push_back(pCell);
            filledCollumn[ii]->SetMarker(0);
        }

        //Copy first filledColumn in our fake cell
        m_FakeCellRow[j]->SetMarker(filledCollumn.back()->GetMarker());
        filledCollumn.back()->SetMarker(0);

        //Link fake cell with the above cells
        if(extraCells.size())
        {
            m_FakeCellRow[j]->SetCellUp(extraCells.back());
            extraCells.back()->SetCellDown(m_FakeCellRow[j]);
        }

        //Link fake cell with the actual tableboard
        m_arrTable[0][j]->SetCellUp(m_FakeCellRow[j]);
        m_FakeCellRow[j]->SetCellDown(m_arrTable[0][j]);

        CollapseColumn(filledCollumn);
        
        //Delete links
        for(size_t ii = 0; ii < extraCells.size(); ii++)
        {
            delete extraCells[ii];
        }

        //Cleanup links
        m_arrTable[0][j]->SetCellUp(NULL);
        m_FakeCellRow[j]->SetCellUp(NULL);
        m_FakeCellRow[j]->SetCellDown(NULL);
        m_FakeCellRow[j]->ResetMarker();
    }
}

//Clear all markers
void CTableBoard::ClearTableBoard()
{
    for(size_t i = 0; i < TABLESIZE; i++)
    {
        for(size_t j = 0; j < TABLESIZE; j++)
        {
            m_arrTable[i][j]->ResetMarker();
        }
    }
}

//Fill cell with predefine markers - helper
bool CTableBoard::LoadFromTemplate(const char* strTemplate)
{
    struct tokens: std::ctype<char> 
    {
        tokens(): std::ctype<char>(get_table()) {}

        static std::ctype_base::mask const* get_table()
        {
            typedef std::ctype<char> cctype;
            static const cctype::mask *const_rc = cctype::classic_table();

            static cctype::mask rc[cctype::table_size];
            std::memcpy(rc, const_rc, cctype::table_size * sizeof(cctype::mask));

            rc[','] = std::ctype_base::space; 
            rc[' '] = std::ctype_base::space; 
            return &rc[0];
        }
    };

    std::string strTmp(strTemplate);
    std::stringstream ss(strTmp);
    ss.imbue(std::locale(std::locale(), new tokens()));
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> vstrings(begin, end);

    assert(vstrings.size() == TABLESIZE * TABLESIZE);
    for(size_t i = 0; i < vstrings.size(); i++)
    {
        std::istringstream stream(vstrings[i]);
        int nMarker;
        stream >> nMarker;

        m_arrTable[i / TABLESIZE][i % TABLESIZE]->SetMarker(nMarker);

    }
    return false;
}