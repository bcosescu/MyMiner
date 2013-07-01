#pragma once

#include "TableCellAnimationBase.h"

class CTableCellAnimationNone : public CTableCellAnimationBase
{

public:
    CTableCellAnimationNone();
    ~CTableCellAnimationNone();

    virtual void    UpdateForAnimation      (SDL_Surface* pSurface);
    virtual bool    ContinueRendering       () {return true;}
};
