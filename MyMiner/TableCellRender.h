#pragma once
#include "SDL.h"

class CTableCell;

class CTableCellRender
{
public:
    CTableCellRender(Uint16 nX, Uint16 nY, Uint16 nSize, CTableCell* pCell);
    ~CTableCellRender(void);

    bool        Render          (SDL_Surface* pSurface);
    bool        PointInCell     (Uint16 nX, Uint16 nY) const;

    void        SetSelected     (bool bSelected) {m_bSelected = bSelected;}
    bool        IsSelected      () const {return m_bSelected;}        

private:

    void        RenderSelected (SDL_Surface* pSurface);

    Uint16      m_nX;
    Uint16      m_nY;
    Uint16      m_nSize;
    bool        m_bSelected;
    CTableCell* m_pCell;
};
