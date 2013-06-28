#pragma once
#include <map>

struct SDL_Surface;

class CGemsResources
{
public:

    enum eGemResource { eGMRed = 1, eGMYellow, eGMPurple, eGMGreen, eGMBlue};

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

    MAPRESOURCES        m_mapImgResources;
};
