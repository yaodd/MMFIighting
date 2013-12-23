//
//  MenuItemLayer.cpp
//  MMFighting
//
//  Created by yaodd on 13-10-23.
//
//

#include "MenuItemLayer.h"
#include "GameScene.h"
#include "GameHelpScene.h"

#include "Defines.h"
const char continueImageName1[20] = "Continue1.png";
const char continueImageName2[20] = "Continue2.png";
const char helpImageName1[20] = "HELP1.png";
const char helpImageName2[20] = "HELP2.png";
const char playImageName1[20] = "MenuPLAY1.png";
const char playImageName2[20] = "MenuPLAY2.png";

MenuItemLayer::MenuItemLayer()
{
    
}

MenuItemLayer::~MenuItemLayer()
{
    
}
//CCFiniteTimeAction *createMenuItemAction(float delay,float duration);
bool MenuItemLayer::init(){
    bool pRet = false;
    do {
        
        winSize = CCDirector::sharedDirector()->getWinSize();
        
        CCLog("size %f %f",winSize.width, winSize.height);
        
        CCSprite *continueNor = CCSprite::createWithSpriteFrameName(continueImageName1);
        CCSprite *continuePre = CCSprite::createWithSpriteFrameName(continueImageName2);
        CCMenuItemSprite *continueItem = CCMenuItemSprite::create(continueNor, continuePre, this, menu_selector(MenuItemLayer::continueAction));
        CCFiniteTimeAction *continueSeq = createMenuItemAction(0,0.5,-270 * 3 + 100);
        continueItem->runAction(continueSeq);
        
        CCSprite *playNor = CCSprite::createWithSpriteFrameName(playImageName1);
        CCSprite *playPre = CCSprite::createWithSpriteFrameName(playImageName2);
        CCMenuItemSprite *playItem = CCMenuItemSprite::create(playNor, playPre, this, menu_selector(MenuItemLayer::playAction));
        CCActionInterval *colorAction = CCTintBy::create(1, 0, -255, -255);
        CCActionInterval *colorBack = colorAction->reverse();
        
        CCFiniteTimeAction *seq = CCSequence::create(colorAction,colorBack,NULL);
//        playItem->runAction(seq);
        CCFiniteTimeAction *playSeq = createMenuItemAction(0.25,0.5,-270 * 3 + 100);
        playItem->runAction(playSeq);
        playItem->runAction(CCRepeatForever::create((CCActionInterval *)seq));
        
        CCSprite *helpNor = CCSprite::createWithSpriteFrameName(helpImageName1);
        CCSprite *helpPre = CCSprite::createWithSpriteFrameName(helpImageName2);
        CCMenuItemSprite *helpItem = CCMenuItemSprite::create(helpNor, helpPre, this, menu_selector(MenuItemLayer::helpAction));
        
        CCFiniteTimeAction *helpSeq = createMenuItemAction(0.5,0.5,-270 * 3 + 100);
        helpItem->runAction(helpSeq);
        
        CCMenu *mainMenu = CCMenu::create(continueItem,playItem,helpItem,NULL);
        mainMenu->alignItemsVerticallyWithPadding(30);
        mainMenu->setPosition(winSize.width + 270, winSize.height / 3 - 100);
//        mainMenu->run
        this->addChild(mainMenu);
        pRet = true;
    } while (0);
    
    return pRet;
}
/*
CCFiniteTimeAction *createMenuItemAction(float delay,float duration)
{
    CCActionInterval *move = CCMoveBy::create(duration, ccp(-270 * 3 + 100, 0));
    CCActionInterval *out = CCEaseElasticOut::create(move,1);
    CCActionInterval *delayTime = CCDelayTime::create(delay);
    CCFiniteTimeAction *seq = CCSequence::create(delayTime,out,NULL);
    
    return seq;
}*/


void MenuItemLayer::playAction(CCObject *pScene)
{
    CCLOG("play");
    CCScene *gameScene = GameScene::create(true);
    CCDirector::sharedDirector()->replaceScene(gameScene);
    
}
void MenuItemLayer::helpAction(CCObject *pScene)
{
    GameHelpScene *gameHelpScene = GameHelpScene::create();
    CCDirector::sharedDirector()->replaceScene(gameHelpScene);
}
void MenuItemLayer::continueAction(CCObject *pScene)
{
    CCScene *gameScene = GameScene::create(false);
    CCDirector::sharedDirector()->replaceScene(gameScene);
}
