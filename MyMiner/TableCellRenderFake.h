// Fake table render cell
#pragma once
#include "TableCellRender.h"

class CTableCellRenderFake : public CTableCellRender
{
public:
    CTableCellRenderFake(CTableBoardRender* pBoard, Uint16 nX, Uint16 nY, CTableCell* pCell);
    ~CTableCellRenderFake(void);

    virtual bool    Render          (SDL_Surface* pSurface);
    virtual bool    PointInCell     (Uint16 nX, Uint16 nY) const { return false; }

    //ICellChangesNotifier
    void            CellMovesRight  (CTableCell*) {}
    void            CellMovesLeft   (CTableCell*) {}
    void            CellMovesUp     (CTableCell*) {}
    void            CellMovesDown   (CTableCell*);
    void            CellDestroyed   (CTableCell*) {}
  
};
