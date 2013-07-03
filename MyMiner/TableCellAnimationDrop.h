// Animate a cell from the top line beeing filled with a resource

#pragma once

#include "TableCellAnimationBase.h"

class CTableCellAnimationDrop : public CTableCellAnimationBase
{

public:
    CTableCellAnimationDrop(int nStartX, int nStartY, CGemsResources::eGemResource resource);
    ~CTableCellAnimationDrop(void);

    virtual void    UpdateForAnimation      ();
    virtual void    RenderImage             (SDL_Surface* pImage, SDL_Surface* pSurface);

protected:
    int             m_nImgHeight;   //the height of the image that was drawn so far
};
