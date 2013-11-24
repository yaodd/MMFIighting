//
//  MenuScene.h
//  MMFighting
//
//  Created by yaodd on 13-10-23.
//
//

#ifndef __MMFighting__MenuScene__
#define __MMFighting__MenuScene__

#include "cocos2d.h"
#include "AudioManager.h"
using namespace cocos2d;
class MenuScene : public :: CCScene
{
public:
    MenuScene(void);
    ~MenuScene(void);
    
    virtual bool init();
    CREATE_FUNC(MenuScene);
    
    AudioManager *audioManager;
};

#endif /* defined(__MMFighting__MenuScene__) */
