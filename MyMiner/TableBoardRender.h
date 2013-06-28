#pragma once

#include "SDL_image.h"
#include <vector>

class CTableBoard;
class CTableCellRender;

class CTableBoardRender
{

    typedef std::vector<CTableCellRender*> TableCellRenders;
public:

    CTableBoardRender(CTableBoard& tableboard);
    ~CTableBoardRender(void);

    int                 GetWidth                () const { return m_pBackGroundImg->w; };
    int                 GetHeight               () const { return m_pBackGroundImg->h; };

    bool                Render                  (SDL_Surface* pSurface);

    bool                HandleMouse             (const SDL_MouseButtonEvent& mouseEvent);

private:

    void                GenerateCellRenders     ();
    bool                PointInRect             (int x, int y, const SDL_Rect& rc) const;


    CTableBoard&        m_TableBoard;
    SDL_Surface*        m_pBackGroundImg;
    SDL_Rect            m_rcMineEntrance;
    CTableCellRender*   m_pSelectedCell;

    TableCellRenders    m_CellsRender;
};
