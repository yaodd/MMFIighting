//
//  MenuItemLayer.cpp
//  MMFighting
//
//  Created by yaodd on 13-10-23.
//
//

#include "MenuItemLayer.h"
#include "GameScene.h"
const char continueImageName1[20] = "Continue1.png";
const char continueImageName2[20] = "Continue2.png";
const char helpImageName1[20] = "HELP1.png";
const char helpImageName2[20] = "HELP2.png";
const char playImageName1[20] = "PLAY1.png";
const char playImageName2[20] = "PLAY2.png";

MenuItemLayer::MenuItemLayer()
{
    
}

MenuItemLayer::~MenuItemLayer()
{
    
}

bool MenuItemLayer::init(){
    bool pRet = false;
    do {
        
        winSize = CCDirector::sharedDirector()->getWinSize();
        CCSprite *playNor = CCSprite::createWithSpriteFrameName(playImageName1);
        CCSprite *playPre = CCSprite::createWithSpriteFrameName(playImageName2);
        CCMenuItemSprite *playItem = CCMenuItemSprite::create(playNor, playPre, this, menu_selector(MenuItemLayer::playAction));
        
        CCSprite *helpNor = CCSprite::createWithSpriteFrameName(helpImageName1);
        CCSprite *helpPre = CCSprite::createWithSpriteFrameName(helpImageName2);
        CCMenuItemSprite *helpItem = CCMenuItemSprite::create(helpNor, helpPre, this, menu_selector(MenuItemLayer::helpAction));
        
        CCSprite *continueNor = CCSprite::createWithSpriteFrameName(continueImageName1);
        CCSprite *continuePre = CCSprite::createWithSpriteFrameName(continueImageName2);
        CCMenuItemSprite *continueItem = CCMenuItemSprite::create(continueNor, continuePre, this, menu_selector(MenuItemLayer::continueAction));
        
        
        CCMenu *mainMenu = CCMenu::create(continueItem,playItem,helpItem,NULL);
        mainMenu->alignItemsVerticallyWithPadding(30);
        mainMenu->setPosition(winSize.width / 4 * 3, winSize.height / 3 - 100);
        this->addChild(mainMenu);
        pRet = true;
    } while (0);
    
    return pRet;
}

void MenuItemLayer::playAction(CCObject *pScene)
{
    CCLOG("play");
    CCScene *gameScene = GameScene::create();
    CCDirector::sharedDirector()->replaceScene(gameScene);
    
}
void MenuItemLayer::helpAction(CCObject *pScene)
{
    
}
void MenuItemLayer::continueAction(CCObject *pScene)
{
    
}
