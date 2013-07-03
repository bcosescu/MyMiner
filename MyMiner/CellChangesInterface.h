#pragma once
#include <vector>

class CTableCell;

//Notifications from a cell
class ICellChangesNotifier
{
public:

    virtual void    CellMovesRight      (CTableCell*) = 0;
    virtual void    CellMovesLeft       (CTableCell*) = 0;
    virtual void    CellMovesUp         (CTableCell*) = 0;
    virtual void    CellMovesDown       (CTableCell*) = 0;
    virtual void    CellDestroyed       (CTableCell*) = 0;
};

//Notifications from table board
class ITableBoardNotifier
{
public:

    virtual void    CellsToBeDestroyed (std::vector<CTableCell*>) = 0;
    virtual void    CellsDestroyed     (std::vector<CTableCell*>) = 0;
    virtual void    ColumnCollapsed    (std::vector<CTableCell*>, std::vector<CTableCell*>) = 0;
};