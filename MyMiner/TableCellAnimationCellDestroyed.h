#pragma once
#include "TableCellAnimationBase.h"

class CTableCellAnimationCellDestroyed : public CTableCellAnimationBase
{
public:
    CTableCellAnimationCellDestroyed(int nStartX, int nStartY, CGemsResources::eGemResource resource);
    ~CTableCellAnimationCellDestroyed(void);

    virtual void    UpdateForAnimation      ();
    virtual void    RenderImage             (SDL_Surface* pImage, SDL_Surface* pSurface);

    virtual void    PrintAnimations             (int nIdent);

private:

    int     m_nKeepCounter;
};
