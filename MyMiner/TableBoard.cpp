#include "TableBoard.h"
#include <stdlib.h>
#include <iostream>
#include <assert.h>
#include <sstream>
#include <map>
#include <algorithm>
#include <conio.h>
#include "CellChangesInterface.h"

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
CTableBoard::TableCells CTableBoard::CollapseColumns(TableCells arrEmptyCells)
{
    TableCells newEmptyCells;
    std::map<CTableCell*, CTableCell*> mapNewEmptyCells;

    while(arrEmptyCells.size())
    {
        CTableCell* pCell = arrEmptyCells.back();
        CTableCell* pStartCell = pCell;
        
        bool bAllCellsAreEmpty = true;
        while(pCell->GetCellUp() && pCell->IsEmpty())
        {
            if(!pCell->GetCellUp()->IsEmpty())
            {
                mapNewEmptyCells.erase(pCell);
                pCell->Swap(pCell->GetCellUp());
                mapNewEmptyCells.insert(std::pair<CTableCell*, CTableCell*>(pCell->GetCellUp(), pCell->GetCellUp()));
                bAllCellsAreEmpty = false;
            }

            pCell = pCell->GetCellUp();
        }
    
        if(!pStartCell->IsEmpty() || bAllCellsAreEmpty)
            arrEmptyCells.pop_back();
    }

    std::transform(mapNewEmptyCells.begin(), mapNewEmptyCells.end(), std::back_inserter(newEmptyCells), second(mapNewEmptyCells));
    return newEmptyCells;
}

//Search for the same marker in the specified direction
void CTableBoard::SearchForMarker(eSearchDirection eDirection, CTableCell* pCell, int nMarker, std::vector<CTableCell*>& arrCells)
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
                    std::for_each(arrCells.begin(), arrCells.end(), &EmptyCell);
                    if(m_pNotifier)
                        m_pNotifier->EmptyCells();

                    bCollapsedColumns = true;
                    CollapseColumns(arrCells);
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

//Given a certain empty cell fill all neghibours
void CTableBoard::FillWithRandomMarker(CTableCell* pCell)
{
    if(!pCell || !pCell->IsEmpty())
        return;

    int nGeneratedMarker = rand() % MAX_CELL_MARKER + 1;

    TableCells arrCellsVertically;
    SearchForMarker(eSDUp, pCell, nGeneratedMarker, arrCellsVertically);
    SearchForMarker(eSDDown, pCell, nGeneratedMarker, arrCellsVertically);

    TableCells arrCellsHorizontaly;
    SearchForMarker(eSDLeft, pCell, nGeneratedMarker, arrCellsHorizontaly);
    SearchForMarker(eSDRight, pCell, nGeneratedMarker, arrCellsHorizontaly);
    
    bool bMarkerIsGood = (arrCellsVertically.size() <= 1) && (arrCellsHorizontaly.size() <= 1);
    if(bMarkerIsGood)
    {
        pCell->SetMarker(nGeneratedMarker);
        FillWithRandomMarker(pCell->GetCellUp());
        FillWithRandomMarker(pCell->GetCellDown());
        FillWithRandomMarker(pCell->GetCellLeft());
        FillWithRandomMarker(pCell->GetCellRight());
    }
    else
    {
        FillWithRandomMarker(pCell);
    }
}

//Fill empty cells in tableboard 
void CTableBoard::FillWithRandomMarker()
{
    for(size_t i = 0; i < TABLESIZE; i++)
        for(size_t j = 0; j < TABLESIZE; j++)
            if(m_arrTable[i][j]->IsEmpty())
                FillWithRandomMarker(m_arrTable[i][j]);
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

//Fill cell with predefine markers
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