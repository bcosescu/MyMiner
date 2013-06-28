#include "TableCellRender.h"
#include "TableCell.h"
#include "GemsResources.h"

CTableCellRender::CTableCellRender(Uint16 nX, Uint16 nY, Uint16 nSize, CTableCell* pCell)
{
    m_pCell = pCell;
    m_nX = nX;
    m_nY = nY;
    m_nSize = nSize;
}

CTableCellRender::~CTableCellRender(void)
{
}

bool CTableCellRender::Render(SDL_Surface* pSurface)
{
    if(!m_pCell)
        return false;

    SDL_Surface* pImage = CGemsResources::GetInstance().ResourceFor((CGemsResources::eGemResource)m_pCell->GetMarker());
    if(!pImage)
        return false;

    //Calculate offset image
    Uint16 xOffset = (m_nSize - pImage->w) / 2;
    Uint16 yOffset = (m_nSize - pImage->h) / 2;

    SDL_Rect imgRect;
    imgRect.x = m_nX + xOffset;
    imgRect.y = m_nY + yOffset;
    imgRect.w = pImage->w;
    imgRect.h = pImage->h;

    SDL_BlitSurface(pImage, NULL, pSurface, &imgRect);

    return true;
}

