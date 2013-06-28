#pragma once
#include "TableCell.h"
#include <vector>
#include "Defines.h"

class CTableBoard
{
    typedef std::vector<CTableCell*>    TableRow;
    typedef std::vector<CTableCell*>    TableCells;
    typedef std::vector<TableRow>       TableBoard;

    enum eSearchDirection { eSDUp, eSDDown, eSDLeft, eSDRight };

public:

    friend class CAutomatedTests;

    CTableBoard(void);
    ~CTableBoard(void);

    CTableCell* GetCell                 (int i, int j) { return m_arrTable[i][j];}
    void        PrintTableBoard         ();
    void        CollapseColumns         ();
    TableCells  CollapseColumns         (TableCells arrEmptyCells);

    void        SearchForMarker         (eSearchDirection eDirection, CTableCell* pCell, int nMarker, std::vector<CTableCell*>& arrCells);
    void        MatchTableBoard         ();

    void        IdentifyLargestCellCount(CTableCell* pCell, TableCells& arrCells, CTableCell*& pStartCell);
    void        FillWithRandomMarker    (CTableCell* pCell);
    void        FillWithRandomMarker    ();
    void        ClearTableBoard         ();

    bool        LoadFromTemplate        (const char* strTemplate);

private:

    //main table
    TableBoard  m_arrTable;
};
