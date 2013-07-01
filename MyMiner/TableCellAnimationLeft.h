#pragma once
#include "TableCellAnimationBase.h"

class CTableCellAnimationLeft : public CTableCellAnimationBase
{

public:
    CTableCellAnimationLeft(int nStartX, int nStartY, CGemsResources::eGemResource resource);
    ~CTableCellAnimationLeft(void);

    virtual void    UpdateForAnimation      (SDL_Surface* pSurface);
};
