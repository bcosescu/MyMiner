//Animate a cell with an empty image

#pragma once

#include "TableCellAnimationBase.h"

class CTableCellAnimationNone : public CTableCellAnimationBase
{

public:
    CTableCellAnimationNone();
    ~CTableCellAnimationNone();

    virtual void    UpdateForAnimation      ();
    virtual bool    ContinueRendering       () {return true;}
};
