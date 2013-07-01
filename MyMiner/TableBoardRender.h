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
    void                CellsToBeDestroyed      (std::vector<CTableCell*> arrCells);
    void                CellsDestroyed          (std::vector<CTableCell*> arrCells);
    void                ColumnCollapsed         (std::vector<CTableCell*> arrEmptyCells, std::vector<CTableCell*> arrCollapsedCells);

private:

    void                GenerateCellRenders     ();
    bool                PointInRect             (int x, int y, const SDL_Rect& rc) const;
    CTableCellRender*   GetRenderCell           (int x, int y);
    void                SelectCell              (CTableCellRender* pRenderCell);
    TableCellRenders    GetRenders              (std::vector<CTableCell*> arrCells);

    CTableBoard&        m_TableBoard;
    SDL_Surface*        m_pBackGroundImg;
    SDL_Rect            m_rcMineEntrance;
    CTableCellRender*   m_pSelectedCell;

    TableCellRenders    m_CellsRender;
    AnimationsList      m_PendingAnimations;
    AnimationsList      m_LastAnimations;
    TableCellRenders    m_LastCellsDestroyed;
};
