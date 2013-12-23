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
class GameScene : public CCScene,GameLayerDelegate,UiLayerDelegate
{
public:
    GameScene(void);
    GameScene(bool isNew);
    ~GameScene(void);
    
    virtual bool init();
    CREATE_FUNC(GameScene);
    virtual void updateHp(float hurt);
    virtual void updateScore(int score);
    virtual void pauseMenu();
    virtual void resumeMenu();
    virtual void decreaseHeart();
    virtual void initPlayerHeart(int hearts);
    AudioManager *audioManager;
    GameLayer *gameLayer;
    UiLayer *uiLayer;
    virtual void backToMainMenu();
    static GameScene *create(bool isNew);
    bool isNew;
};
#endif /* defined(__MMFighting__GameScene__) */
