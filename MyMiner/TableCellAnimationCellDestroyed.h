//Animate a cell being destroyed - draw a filled rectangle and the resource

#pragma once
#include "TableCellAnimationBase.h"

class CTableCellAnimationCellDestroyed : public CTableCellAnimationBase
{
public:
    CTableCellAnimationCellDestroyed(int nStartX, int nStartY, CGemsResources::eGemResource resource);
    ~CTableCellAnimationCellDestroyed(void);

    virtual void    UpdateForAnimation      ();
    virtual void    RenderImage             (SDL_Surface* pImage, SDL_Surface* pSurface);

private:
    
    int             m_nKeepCounter;         // number of times to draw the animations   
};
