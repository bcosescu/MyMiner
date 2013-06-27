#include "TableBoard.h"
#include <stdlib.h>
#include <iostream>
#include <assert.h>
#include <sstream>
#include <map>
#include <algorithm>
#include <conio.h>

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
    bool bRedoShuffle = false;

    while(1)
    {
        for(size_t i = 0; i < TABLESIZE && !bRedoShuffle; i++)
        {
            TableRow arrRow = m_arrTable[i];
            for(size_t j = 0; j < TABLESIZE && !bRedoShuffle; j++)
            {
                int nGeneratedMarker = rand() % MAX_CELL_MARKER + 1;

                CTableCell* pCell = arrRow[j];

                bool bMarkerIsGood = false;
                //Search if the marker is good(no 3 or more markers identical on the line and row)
                int nCountMarkers = 0;
                while(!bMarkerIsGood && nCountMarkers <= MAX_CELL_MARKER)
                {
                    nCountMarkers++;

                    std::vector<CTableCell*> arrCellsVertically;
                    SearchForMarker(CTableBoard::eSDUp, pCell, nGeneratedMarker, arrCellsVertically);
                    SearchForMarker(CTableBoard::eSDDown, pCell, nGeneratedMarker, arrCellsVertically);

                    std::vector<CTableCell*> arrCellsHorizontaly;
                    SearchForMarker(CTableBoard::eSDLeft, pCell, nGeneratedMarker, arrCellsHorizontaly);
                    SearchForMarker(CTableBoard::eSDRight, pCell, nGeneratedMarker, arrCellsHorizontaly);

                    
                    bMarkerIsGood = (arrCellsVertically.size() <= 1) && (arrCellsHorizontaly.size() <= 1);
                    if(!bMarkerIsGood)
                    {
                        nGeneratedMarker++;
                        if(nGeneratedMarker > MAX_CELL_MARKER)
                        {
                            nGeneratedMarker = 1;
                            continue;
                        }
                    }
                    else
                    {
                        arrRow[j]->SetMarker(nGeneratedMarker);
                    }
                }

                bRedoShuffle = !bMarkerIsGood && (nCountMarkers > MAX_CELL_MARKER);
            }
        }

        if(!bRedoShuffle)
        {
            break;
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