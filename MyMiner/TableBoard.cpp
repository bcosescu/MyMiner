#include "TableBoard.h"
#include <stdlib.h>
#include <iostream>
#include <assert.h>
#include <sstream>

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

                    int nMarkerCountCol = 0;
                    SearchForMarker(CTableBoard::eSDUp, pCell, nGeneratedMarker, nMarkerCountCol);
                    SearchForMarker(CTableBoard::eSDDown, pCell, nGeneratedMarker, nMarkerCountCol);

                    int nMarkerCountRow = 0;
                    SearchForMarker(CTableBoard::eSDLeft, pCell, nGeneratedMarker, nMarkerCountRow);
                    SearchForMarker(CTableBoard::eSDRight, pCell, nGeneratedMarker, nMarkerCountRow);

                    
                    bMarkerIsGood = (nMarkerCountRow <= 1) && (nMarkerCountCol <= 1);
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

//Search for the same marker in the specified direction
void CTableBoard::SearchForMarker(eSearchDirection eDirection, CTableCell* pCell, int nMarker, int& nCountMarker)
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

        SearchForMarker(eDirection, pNextCell, nMarker, ++nCountMarker);
    }
}

//Fill cell with predifine markers
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