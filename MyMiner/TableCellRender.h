#pragma once
#include "SDL.h"
#include "CellChangesInterface.h"
#include "TableCellAnimationBase.h"
#include <iostream>

class CTableCell;
class CTableBoardRender;

class CTableCellRender;
typedef std::vector<CTableCellRender*> TableCellRenders;

class CTableCellRender : public ICellChangesNotifier
{
public:

    CTableCellRender(CTableBoardRender* pBoard, Uint16 nX, Uint16 nY, CTableCell* pCell);
    virtual ~CTableCellRender(void);

    virtual bool    Render          (SDL_Surface* pSurface);
    virtual bool    PointInCell     (Uint16 nX, Uint16 nY) const;

    void            SetSelected     (bool bSelected) {m_bSelected = bSelected;}
    bool            IsSelected      () const {return m_bSelected;}
    bool            InAnimation     () const {return m_animations.size() != 0;}

    bool            TryToSwap       (CTableCellRender* pCellRender);

    CTableCell*     GetCell         () {return m_pCell;}
    void            GetAnimations   (AnimationsList&  animations) {animations = m_animations;}
    void            LinkRenders     (TableCellRenders cellsRenders);

    void            CellMovesRight  (CTableCell*);
    void            CellMovesLeft   (CTableCell*);
    void            CellMovesUp     (CTableCell*);
    void            CellMovesDown   (CTableCell*);
    void            CellDestroyed   (CTableCell*);
    void            CellWillBeEmpty (CTableCell*);

protected:

    void            RenderSelected  (SDL_Surface* pSurface);

    template<class T>
    void            CreateAnimation()
    {
        CTableCellAnimationBasePtr spAnimation(new T(m_nX, m_nY, (CGemsResources::eGemResource)m_pCell->GetMarker()));
    
        AnimationsList priorAnimations;
        if(m_pTableBoardRender->PendingScenes(priorAnimations))
            spAnimation->AddPendingAnimations(priorAnimations);

        m_pTableBoardRender->NewAnimationCreated(spAnimation);
        m_animations.push_back(spAnimation);
    }

    CTableBoardRender*  m_pTableBoardRender;
    Uint16              m_nX;
    Uint16              m_nY;
    bool                m_bSelected;
    CTableCell*         m_pCell;
    AnimationsList      m_animations;

};