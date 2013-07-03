// Table cell render

#pragma once
#include "SDL.h"
#include "CellChangesInterface.h"
#include "TableCellAnimationBase.h"

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

    // ICellChangesNotifier
    void            CellMovesRight  (CTableCell*);
    void            CellMovesLeft   (CTableCell*);
    void            CellMovesUp     (CTableCell*);
    void            CellMovesDown   (CTableCell*);
    void            CellDestroyed   (CTableCell*);

protected:

    void            RenderSelected  (SDL_Surface* pSurface);

    // Helper function to create an animation
    template<class T>
    void            CreateAnimation()
    {
        CTableCellAnimationBasePtr spAnimation(new T(m_nX, m_nY, (CGemsResources::eGemResource)m_pCell->GetMarker()));
    
        //if there are pending animations add them to this one
        AnimationsList priorAnimations;
        if(m_pTableBoardRender->PendingScenes(priorAnimations))
            spAnimation->AddPendingAnimations(priorAnimations);

        //notify table render that an animation was created
        m_pTableBoardRender->NewAnimationCreated(spAnimation);
        m_animations.push_back(spAnimation);
    }

    CTableBoardRender*  m_pTableBoardRender;        //table render
    Uint16              m_nX;                       //x-coordinate to position render
    Uint16              m_nY;                       //y-coordinate to position render
    bool                m_bSelected;                //selected or not
    CTableCell*         m_pCell;                    //matching cell in table
    AnimationsList      m_animations;               //animations to draw on render

};