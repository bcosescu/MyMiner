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

private:

    void                GenerateCellRenders     ();


    CTableBoard&        m_TableBoard;
    SDL_Surface*        m_pBackGroundImg;
    SDL_Rect            m_rcMineEntrance;

    TableCellRenders    m_CellsRender;
};
