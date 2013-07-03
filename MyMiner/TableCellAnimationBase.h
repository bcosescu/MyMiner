// Base class for all animations

#pragma once
#include "GemsResources.h"
#include <vector>
#include <list>
#include "smart_ptr.h"

class CTableCellAnimationBase;

typedef smart_ptr::strong_ptr<CTableCellAnimationBase>  CTableCellAnimationBasePtr;
typedef std::list<CTableCellAnimationBasePtr>           AnimationsList;
typedef std::vector<CTableCellAnimationBasePtr>         AnimationsVector;

class CTableCellAnimationBase
{
public:

    CTableCellAnimationBase(int nStartX, int nStartY, CGemsResources::eGemResource resource);
    virtual ~CTableCellAnimationBase(void);

    bool            IsComplete                  () const {return m_bComplete;}
    CGemsResources::eGemResource   
                    GetResource                 () const {return m_resource;}

    bool            Render                      (SDL_Surface* pSurface);

    void            AddPendingAnimations        (const AnimationsList& pendingAnimations) {m_PendingAnimations = pendingAnimations;}
    void            CleanPendingAnimations      ();

    //overrides
    virtual void    UpdateForAnimation          () {}
    virtual bool    ContinueRendering           ();
    virtual void    RenderImage                 (SDL_Surface* pImage, SDL_Surface* pSurface);

protected:

    bool            CanDraw             ();

    int                             m_nStartX;      // x-coordinate for a starting animation
    int                             m_nStartY;      // y-coordinate for a starting animation
    int                             m_nX;           // x-coordinate current for animation
    int                             m_nY;           // y-coordinate current for animation
    CGemsResources::eGemResource    m_resource;     // resource to draw
    bool                            m_bComplete;    // animation status
    AnimationsList                  m_PendingAnimations; //don't start before these animations
    int                             m_nSlowDown;    // slow down factor - helper

};