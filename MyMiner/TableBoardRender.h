// Table board render - holds an array of cell renders 
#pragma once

#include "SDL_image.h"
#include <vector>
#include "TableCellAnimationBase.h"
#include "CellChangesInterface.h"
#include "TableCellRender.h"

class CTableBoard;

class CTableBoardRender : public ITableBoardNotifier
{

public:

    CTableBoardRender(CTableBoard& tableboard);
    ~CTableBoardRender(void);

    int                 GetWidth                () const { return m_pBackGroundImg->w; };
    int                 GetHeight               () const { return m_pBackGroundImg->h; };

    bool                Render                  (SDL_Surface* pSurface);

    bool                HandleMouse             (const SDL_MouseButtonEvent& mouseEvent);

    bool                PendingScenes           (AnimationsList& listPendingAnimations);
    bool                LastScenes              (AnimationsList& listLastAnimations);
    void                NewAnimationCreated     (CTableCellAnimationBasePtr spAnimation) {m_LastAnimations.push_back(spAnimation);}

    //ITableBoardNotifier
    void                CellsToBeDestroyed      (std::vector<CTableCell*> arrCells);
    void                CellsDestroyed          (std::vector<CTableCell*> arrCells);
    void                ColumnCollapsed         (std::vector<CTableCell*> arrEmptyCells, std::vector<CTableCell*> arrCollapsedCells);

private:

    void                GenerateCellRenders     ();
    bool                PointInRect             (int x, int y, const SDL_Rect& rc) const;
    CTableCellRender*   GetRenderCell           (int x, int y);
    void                SelectCell              (CTableCellRender* pRenderCell);
    TableCellRenders    GetRenders              (std::vector<CTableCell*> arrCells);

    CTableBoard&        m_TableBoard;           //tabla board object
    SDL_Surface*        m_pBackGroundImg;       //background image for the table
    SDL_Rect            m_rcMineEntrance;       //location of the table
    CTableCellRender*   m_pSelectedCell;        //current selected cell

    TableCellRenders    m_CellsRender;          //cells to be rendered
    AnimationsList      m_PendingAnimations;    //animations that should be drawn first
    AnimationsList      m_LastAnimations;       //latest animations created
    TableCellRenders    m_LastCellsDestroyed;   //latest renders for destroyed cells
};
