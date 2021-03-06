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
    GameOverScene(int score);
    CREATE_FUNC(GameOverScene);
    virtual bool init();
    
    
    CCSize winSize;
    
    GameOverLayer *gameOverLayer;
    static GameOverScene *create(int score);
    
    int score;
    
};

#endif /* defined(__MMFighting__GameOverScene__) */
