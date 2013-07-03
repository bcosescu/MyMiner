//Animate a cell moving right with size of the render cell
#pragma once

#include "TableCellAnimationBase.h"

class CTableCellAnimationRight : public CTableCellAnimationBase
{

public:
    CTableCellAnimationRight(int nStartX, int nStartY, CGemsResources::eGemResource resource);
    ~CTableCellAnimationRight(void);

    virtual void    UpdateForAnimation      ();
};
