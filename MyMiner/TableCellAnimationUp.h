//Animate a cell moving up with the size of render cell

#pragma once

#include "TableCellAnimationBase.h"

class CTableCellAnimationUp : public CTableCellAnimationBase
{

public:
    CTableCellAnimationUp(int nStartX, int nStartY, CGemsResources::eGemResource resource);
    ~CTableCellAnimationUp(void);

    virtual void    UpdateForAnimation      ();
};
