//Singleton for retriving SDL images

#pragma once
#include <map>

struct SDL_Surface;

class CGemsResources
{
public:

    enum eGemResource { eGMNone = 0, eGMRed, eGMYellow, eGMPurple, eGMGreen, eGMBlue};

private:

    typedef std::map<eGemResource, SDL_Surface*> MAPRESOURCES;
    CGemsResources(void);
    CGemsResources(const CGemsResources&);
    CGemsResources& operator= (const CGemsResources&);


public:

    static CGemsResources&      GetInstance () { static CGemsResources instance; return instance; }
    bool                        Initialize  ();
    bool                        UnInitialize();
    SDL_Surface*                ResourceFor (eGemResource resource);
    
private:

    bool                        LoadImg     (eGemResource resource, const char* strImgPath);
    
    MAPRESOURCES                m_mapImgResources;
};
