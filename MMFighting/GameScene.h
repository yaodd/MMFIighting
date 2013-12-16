//
//  GameScene.h
//  MMFighting
//
//  Created by yaodd on 13-10-22.
//
//

#ifndef __MMFighting__GameScene__
#define __MMFighting__GameScene__

#include <iostream>
#include <cocos2d.h>
#include "CCJoystick.h"
#include "AudioManager.h"
#include "GameLayer.h"
#include "UiLayer.h"
//#include "GameScene.h"

using namespace cocos2d;
class GameScene : public CCScene,GameLayerDelegate
{
public:
    GameScene(void);
    ~GameScene(void);
    
    virtual bool init();
    CREATE_FUNC(GameScene);
    virtual void updateHp(float hurt);
    virtual void updateScore(int score);
    virtual void decreaseHeart();
    AudioManager *audioManager;
    GameLayer *gameLayer;
    UiLayer *uiLayer;
};
#endif /* defined(__MMFighting__GameScene__) */
