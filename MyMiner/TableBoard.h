#pragma once
#include "TableCell.h"
#include <vector>

#define TABLESIZE 8

class CTableBoard
{
    typedef std::vector<CTableCell*>    TableRow;
    typedef std::vector<TableRow>       TableBoard;
public:

    friend bool ExecuteTests();
    CTableBoard(void);
    ~CTableBoard(void);

    bool        ShuffleTableBoard       ();
    void        PrintTableBoard         ();

    //main table
    TableBoard m_arrTable;
};
