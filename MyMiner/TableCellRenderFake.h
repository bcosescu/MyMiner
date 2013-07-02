#pragma once
#include "TableCellRender.h"

class CTableCellRenderFake : public CTableCellRender
{
public:
    CTableCellRenderFake(CTableBoardRender* pBoard, Uint16 nX, Uint16 nY);
    ~CTableCellRenderFake(void);

    virtual bool    Render          (SDL_Surface* pSurface);
    virtual bool    PointInCell     (Uint16 nX, Uint16 nY) const { return false; }
  
};
