//
//  GameOverScene.h
//  MMFighting
//
//  Created by yaodd on 13-12-17.
//
//

#ifndef __MMFighting__GameOverScene__
#define __MMFighting__GameOverScene__

#include <iostream>
#include <cocos2d.h>
#include "AudioManager.h"
#include "GameOverLayer.h"


using namespace cocos2d;
class GameOverScene : public CCScene
{
public:
    GameOverScene(void);
    ~GameOverScene(void);
    CREATE_FUNC(GameOverScene);
    virtual bool init();
    
    AudioManager *audioManager;
    
    CCSize winSize;
    
    GameOverLayer *gameOverLayer;
};

#endif /* defined(__MMFighting__GameOverScene__) */
