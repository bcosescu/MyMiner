#pragma once

#include "TableCellAnimationBase.h"

class CTableCellAnimationDown : public CTableCellAnimationBase
{

public:
    CTableCellAnimationDown(int nStartX, int nStartY, CGemsResources::eGemResource resource);
    ~CTableCellAnimationDown(void);

    virtual void    UpdateForAnimation      ();
};

