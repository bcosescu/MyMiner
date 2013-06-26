#pragma once
#include "TableCell.h"
#include <vector>

#define TABLESIZE 8

class CTableBoard
{
    typedef std::vector<CTableCell*>    TableRow;
    typedef std::vector<TableRow>       TableBoard;

    enum eSearchDirection { eSDUp, eSDDown, eSDLeft, eSDRight };

public:

    friend bool ExecuteTests();
    CTableBoard(void);
    ~CTableBoard(void);

    bool        ShuffleTableBoard       ();
    void        PrintTableBoard         ();

    void        SearchForMarker         (eSearchDirection eDirection, CTableCell* pCell, int nMarker, int& nCountMarker);

    bool        LoadFromTemplate        (const char* strTemplate);

    //main table
    TableBoard m_arrTable;
};
