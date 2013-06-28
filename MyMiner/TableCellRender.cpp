#include "TableCellRender.h"
#include "TableCell.h"
#include "GemsResources.h"
#include "Defines.h"

CTableCellRender::CTableCellRender(Uint16 nX, Uint16 nY, Uint16 nSize, CTableCell* pCell)
{
    m_pCell = pCell;
    m_nX = nX;
    m_nY = nY;
    m_nSize = nSize;
    m_bSelected = false;
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

    RenderSelected(pSurface);

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

void CTableCellRender::RenderSelected(SDL_Surface* pSurface)
{
    if(!m_bSelected)
        return;

    SDL_Rect rc;
    rc.x = m_nX;
    rc.y = m_nY;
    rc.w = m_nSize;
    rc.h = 1;
    SDL_FillRect(pSurface, &rc, CELL_SELECTED_COLOR);

    rc.x = m_nX + m_nSize;
    rc.y = m_nY;
    rc.w = 1;
    rc.h = m_nSize;
    SDL_FillRect(pSurface, &rc, CELL_SELECTED_COLOR);

    rc.x = m_nX;
    rc.y = m_nY;
    rc.w = 1;
    rc.h = m_nSize;
    SDL_FillRect(pSurface, &rc, CELL_SELECTED_COLOR);

    rc.x = m_nX;
    rc.y = m_nY + m_nSize;
    rc.w = m_nSize;
    rc.h = 1;
    SDL_FillRect(pSurface, &rc, CELL_SELECTED_COLOR);
}

bool CTableCellRender::PointInCell(Uint16 nX, Uint16 nY) const
{
    return (nX >= m_nX) && (nX < m_nX + m_nSize) && (nY >= m_nY) && (nY < m_nY + m_nSize);
}

