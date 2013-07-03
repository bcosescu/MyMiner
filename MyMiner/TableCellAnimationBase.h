#pragma once
#include "GemsResources.h"
#include <vector>
#include <list>
#include "smart_ptr.h"

#define SPEED_ANIMATION 1

class CTableCellAnimationBase;

typedef smart_ptr::strong_ptr<CTableCellAnimationBase> CTableCellAnimationBasePtr;
typedef std::list<CTableCellAnimationBasePtr>   AnimationsList;
typedef std::vector<CTableCellAnimationBasePtr> AnimationsVector;

class CTableCellAnimationBase
{
public:

    CTableCellAnimationBase(int nStartX, int nStartY, CGemsResources::eGemResource resource);
    virtual ~CTableCellAnimationBase(void);

    bool            IsComplete                  () const {return m_bComplete;}

    bool            Render                      (SDL_Surface* pSurface);

    void            AddPendingAnimations        (const AnimationsList& pendingAnimations) {m_PendingAnimations = pendingAnimations;}
    void            CleanPendingAnimations      ();
    virtual void    UpdateForAnimation          () {}
    virtual bool    ContinueRendering           ();
    virtual void    RenderImage                 (SDL_Surface* pImage, SDL_Surface* pSurface);

    CGemsResources::eGemResource   GetResource         () const {return m_resource;}

    virtual void    PrintAnimations             (int nIdent);
    void            PrintIdent                  (int nIdent);

protected:

    bool            CanDraw             ();

    int                             m_nStartX;
    int                             m_nStartY;
    int                             m_nX;
    int                             m_nY;
    CGemsResources::eGemResource    m_resource;
    bool                            m_bComplete;
    AnimationsList                  m_PendingAnimations;
    int                             m_nSlowDown;

};