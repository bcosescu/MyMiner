#include "GemsResources.h"
#include "SDL_image.h"
#include <assert.h>
#include <iostream>

CGemsResources::CGemsResources(void)
{
}

bool CGemsResources::Initialize()
{
    SDL_Surface* pImg = NULL;
    pImg = IMG_Load("./Resources/Yellow.png");
    if(!pImg)
    {
        assert(false);
        std::cout << IMG_GetError() << std::endl;
        return false;
    }
    m_mapImgResources.insert(std::pair<eGemResource, SDL_Surface*>(eGMYellow, pImg));

    pImg = IMG_Load("./Resources/Green.png");
    if(!pImg)
    {
        assert(false);
        std::cout << IMG_GetError() << std::endl;
        return false;
    }
    m_mapImgResources.insert(std::pair<eGemResource, SDL_Surface*>(eGMGreen, pImg));

    pImg = IMG_Load("./Resources/Purple.png");
    if(!pImg)
    {
        assert(false);
        std::cout << IMG_GetError() << std::endl;
        return false;
    }
    m_mapImgResources.insert(std::pair<eGemResource, SDL_Surface*>(eGMPurple, pImg));

    pImg = IMG_Load("./Resources/Red.png");
    if(!pImg)
    {
        assert(false);
        std::cout << IMG_GetError() << std::endl;
        return false;
    }
    m_mapImgResources.insert(std::pair<eGemResource, SDL_Surface*>(eGMRed, pImg));

    pImg = IMG_Load("./Resources/Blue.png");
    if(!pImg)
    {
        assert(false);
        std::cout << IMG_GetError() << std::endl;
        return false;
    }
    m_mapImgResources.insert(std::pair<eGemResource, SDL_Surface*>(eGMBlue, pImg));

    return true;
}

SDL_Surface* CGemsResources::ResourceFor(CGemsResources::eGemResource resource)
{
    MAPRESOURCES::iterator it = m_mapImgResources.find(resource);
    if(it == m_mapImgResources.end())
        return NULL;

    return it->second;
}