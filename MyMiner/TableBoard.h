#pragma once
#include "TableCell.h"
#include <vector>

#define TABLESIZE 8

class CTableBoard
{
    typedef std::vector<CTableCell*>    TableRow;
    typedef std::vector<CTableCell*>    TableCells;
    typedef std::vector<TableRow>       TableBoard;

    enum eSearchDirection { eSDUp, eSDDown, eSDLeft, eSDRight };

public:

    friend bool ExecuteTests();
    CTableBoard(void);
    ~CTableBoard(void);

    bool        ShuffleTableBoard       ();
    void        PrintTableBoard         ();
    void        CollapseColumns         ();
    TableCells  CollapseColumns         (TableCells arrEmptyCells);

    void        SearchForMarker         (eSearchDirection eDirection, CTableCell* pCell, int nMarker, std::vector<CTableCell*>& arrCells);
    void        MatchTableBoard         ();

    void        IdentifyLargestCellCount   (CTableCell* pCell, TableCells& arrCells, CTableCell*& pStartCell);

    bool        LoadFromTemplate        (const char* strTemplate);

    //main table
    TableBoard m_arrTable;
};
