#include "GemsResources.h"
#include "SDL_image.h"
#include <assert.h>
#include <iostream>

CGemsResources::CGemsResources(void)
{
}

//Initialize
bool CGemsResources::Initialize()
{
    if(!LoadImg(eGMYellow, "./Resources/Yellow.png"))
        return false;

    if(!LoadImg(eGMGreen, "./Resources/Green.png"))
        return false;

    if(!LoadImg(eGMPurple, "./Resources/Purple.png"))
        return false;

    if(!LoadImg(eGMRed, "./Resources/Red.png"))
        return false;

    if(!LoadImg(eGMBlue, "./Resources/Blue.png"))
        return false;

    return true;
}

//Unintialize
bool CGemsResources::UnInitialize()
{

    for(MAPRESOURCES::iterator it = m_mapImgResources.begin(); it != m_mapImgResources.end(); it++)
    {
        SDL_FreeSurface(it->second);
    }
    return true;
}

//Retrieve SDL resource
SDL_Surface* CGemsResources::ResourceFor(CGemsResources::eGemResource resource)
{
    MAPRESOURCES::iterator it = m_mapImgResources.find(resource);
    if(it == m_mapImgResources.end())
        return NULL;

    return it->second;
}

//Load an image - helper
bool CGemsResources::LoadImg(eGemResource resource, const char* strImgPath)
{
    SDL_Surface* pImgTmp = NULL;
    pImgTmp = IMG_Load(strImgPath);
    if(!pImgTmp)
    {
        assert(false);
        std::cout << IMG_GetError() << std::endl;
        return false;
    }

    SDL_Surface* pImg = SDL_DisplayFormatAlpha(pImgTmp);
    if(!pImg)
    {
        assert(false);
        std::cout << IMG_GetError() << std::endl;
        return false;
    }
    SDL_FreeSurface(pImgTmp);

    m_mapImgResources.insert(std::pair<eGemResource, SDL_Surface*>(resource, pImg));

    return true;
}