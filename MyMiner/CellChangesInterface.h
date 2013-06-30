#pragma once

class CTableCell;

class ICellChangesNotifier
{
public:

    virtual void    CellMovesRight      (CTableCell*) = 0;
    virtual void    CellMovesLeft       (CTableCell*) = 0;
    virtual void    CellMovesUp         (CTableCell*) = 0;
    virtual void    CellMovesDown       (CTableCell*) = 0;
    virtual void    CellDestroyed       (CTableCell*) = 0;
};

class ITableBoardNotifier
{
public:

    virtual void    EmptyCells          () = 0;
};