#pragma once

#include "TableCellAnimationBase.h"

class CTableCellAnimationUp : public CTableCellAnimationBase
{

public:
    CTableCellAnimationUp(int nStartX, int nStartY, CGemsResources::eGemResource resource);
    ~CTableCellAnimationUp(void);

    virtual void    UpdateForAnimation      (SDL_Surface* pSurface);
};
