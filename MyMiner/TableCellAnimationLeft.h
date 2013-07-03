// Animate a cell moving to the left with the size of the render

#pragma once

#include "TableCellAnimationBase.h"

class CTableCellAnimationLeft : public CTableCellAnimationBase
{

public:
    CTableCellAnimationLeft(int nStartX, int nStartY, CGemsResources::eGemResource resource);
    ~CTableCellAnimationLeft(void);

    virtual void    UpdateForAnimation      ();
};
