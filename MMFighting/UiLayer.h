//
//  UiLayer.h
//  mmFight
//
//  Created by 王智锐 on 11/10/13.
//
//

#ifndef __mmFight__UiLayer__
#define __mmFight__UiLayer__

#include "cocos2d.h"
#include "HaemalStrand.h"
#include "AudioManager.h"
using namespace cocos2d;

class UiLayer : public CCLayer{
    
public:
    //member
    AudioManager *audioManager;
    CCNode *hp;
    CCMenuItemToggle *musicButton;
    CCMenuItemSprite *pauseButton;
    CCMenuItemImage *musicOpen;
    CCMenuItemImage *musicClosed;
    CCMenu *menu;
    CCMenu *pauseMenu;
    CCMenuItemSprite *resumeMenuItem;
    CCMenuItemSprite *newgameMenuItem;
    CCMenuItemSprite *backMenuItem;
    CCLayer *pauseLayer;
//    CCScene *gameScene;//游戏场景弱引用
    //function
    UiLayer(void);
    ~UiLayer(void);
    virtual bool init();
    CREATE_FUNC(UiLayer);
    void updateHp(float value);
    void initMenu();
    void popUpTheMenuLayer(CCObject* pObject);
    void toggleWithTheMusic(CCObject* pObject);
    void initWithParticle();
    void exitGame(CCObject* pObject);
    void resumeGame(CCObject* pObject);
    void backGame(CCObject *pObject);
    void updateScore(int scroe);
    
    CCLabelAtlas *gameScoreLabel;
    CC_SYNTHESIZE_RETAIN(CCArray*, _heartArray, HeartArray);
    void initHeart();
    void decreaseHeart();
    
    void initPauseLayer();
};

#endif /* defined(__mmFight__UiLayer__) */
