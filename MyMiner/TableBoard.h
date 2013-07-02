#pragma once
#include "TableCell.h"
#include <vector>
#include "Defines.h"

class ITableBoardNotifier;

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
    void        FillWithRandomMarker    ();

    bool        CanCollapse             (CTableCell* pCell);
    void        MatchTableBoard         ();

    void        SetNotifier             (ITableBoardNotifier* pNotifier) { m_pNotifier = pNotifier; }

    void        PrintTableBoard         ();
    bool        LoadFromTemplate        (const char* strTemplate);

private:

    void        CollapseColumns         ();
    TableCells  MoveCellsDown           (TableCells arrEmptyCells);
    TableCells  CollapseColumn          (TableCells arrEmptyCells);

    void        SearchForMarker         (eSearchDirection eDirection, CTableCell* pCell, int nMarker, TableCells& arrCells);

    void        IdentifyLargestCellCount(CTableCell* pCell, TableCells& arrCells, CTableCell*& pStartCell);
    int         GenerateRandomMarker    (CTableCell* pCell);
    void        ClearTableBoard         ();


private:

    //main table
    TableBoard              m_arrTable;
    ITableBoardNotifier*    m_pNotifier;
};
