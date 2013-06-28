#include "TableBoardRender.h"
#include <iostream>
#include <assert.h>
#include "TableCellRender.h"
#include "Defines.h"
#include "TableBoard.h"

CTableBoardRender::CTableBoardRender(CTableBoard& tableboard)
: m_TableBoard(tableboard)
{
    m_pBackGroundImg = IMG_Load("./Resources/BackGround.jpg");
    if(!m_pBackGroundImg)
    {
        assert(false);
        std::cout << IMG_GetError() << std::endl;
    }

    memset((Uint8*)&m_rcMineEntrance, 0, sizeof(SDL_Rect));
    
    m_rcMineEntrance.x = 338;
    m_rcMineEntrance.y = 110;
    m_rcMineEntrance.w = TABLE_RENDER_SIZE;
    m_rcMineEntrance.h = TABLE_RENDER_SIZE;

    GenerateCellRenders();
}

CTableBoardRender::~CTableBoardRender(void)
{
    for(size_t i = 0; i < m_CellsRender.size(); i++)
    {
        CTableCellRender *pCellRender = m_CellsRender[i];
        if(pCellRender)
            delete pCellRender;
    }

    SDL_FreeSurface(m_pBackGroundImg);
}

bool CTableBoardRender::Render(SDL_Surface* pSurface)
{
    SDL_Rect imgRect;
    imgRect.x = 0;
    imgRect.y = 0;
    imgRect.w = GetWidth();
    imgRect.h = GetHeight();
    
    SDL_Rect screenRect = imgRect;
    SDL_BlitSurface(m_pBackGroundImg, &imgRect, pSurface, &screenRect);

    for(size_t i = 0; i < m_CellsRender.size(); i++)
        m_CellsRender[i]->Render(pSurface);

    return false;
}


void CTableBoardRender::GenerateCellRenders()
{
    Uint16 nCellRederWidth =  TABLE_RENDER_SIZE / TABLESIZE;

    for(int i = 0; i < TABLESIZE; i++)
    {
        for(int j = 0; j < TABLESIZE; j++)
        {
            CTableCellRender* pCellRender = new CTableCellRender(m_rcMineEntrance.x + i * nCellRederWidth, m_rcMineEntrance.y + j * nCellRederWidth, nCellRederWidth, m_TableBoard.GetCell(i,j));
            m_CellsRender.push_back(pCellRender);
        }
    }
}