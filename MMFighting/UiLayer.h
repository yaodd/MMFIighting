//
//  UiLayer.h
//  mmFight
//
//  Created by 王智锐 on 11/10/13.
//
//  游戏界面UI层

#ifndef __mmFight__UiLayer__
#define __mmFight__UiLayer__

#include "cocos2d.h"
#include "HaemalStrand.h"
#include "AudioManager.h"

using namespace cocos2d;

class UiLayerDelegate{
public:
    virtual void backToMainMenu() = 0;
    virtual void pauseMenu() = 0;
    virtual void resumeMenu() = 0;
};

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
    UiLayerDelegate *delegate;
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
    void exitGame(CCObject* pObject);   //重新开始游戏
    void resumeGame(CCObject* pObject); //恢复游戏
    void backGame(CCObject *pObject);   //返回到主菜单
    void updateScore(int scroe);        //更新分数显示
    
    CCLabelAtlas *gameScoreLabel;
    CC_SYNTHESIZE_RETAIN(CCArray*, _heartArray, HeartArray);
    void initHeart(int hearts);         //初始化主角生命数量
    void decreaseHeart();               //主角死了一次
    
    void initPauseLayer();              //初始化暂停界面
    
    virtual void keyBackClicked(void);
    virtual void keyMenuClicked(void);
    
    void deleteHeart();         //删除一颗心
};

#endif /* defined(__mmFight__UiLayer__) */
