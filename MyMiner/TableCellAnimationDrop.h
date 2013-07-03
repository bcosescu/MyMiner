#pragma once

#include "TableCellAnimationBase.h"

class CTableCellAnimationDrop : public CTableCellAnimationBase
{

public:
    CTableCellAnimationDrop(int nStartX, int nStartY, CGemsResources::eGemResource resource);
    ~CTableCellAnimationDrop(void);

    virtual void    UpdateForAnimation      ();
    virtual void    RenderImage             (SDL_Surface* pImage, SDL_Surface* pSurface);
    virtual void    PrintAnimations             (int nIdent);

protected:
    int         m_nImgHeight;
};
