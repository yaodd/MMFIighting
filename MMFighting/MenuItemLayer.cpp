//
//  MenuItemLayer.cpp
//  MMFighting
//
//  Created by yaodd on 13-10-23.
//
//

#include "MenuItemLayer.h"
#include "GameScene.h"
const char playImageNorName[20] = "play1.png";
const char playImagePreName[20] = "play2.png";
const char helpImageNorName[20] = "help1.png";
const char helpImagePreName[20] = "help2.png";
const char exitImageNorName[20] = "exit1.png";
const char exitImagePreName[20] = "exit2.png";

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
        CCSprite *playNor = CCSprite::create(playImageNorName);
        CCSprite *playPre = CCSprite::create(playImagePreName);
        CCMenuItemSprite *playItem = CCMenuItemSprite::create(playNor, playPre, this, menu_selector(MenuItemLayer::playAction));
        
        CCSprite *helpNor = CCSprite::create(helpImageNorName);
        CCSprite *helpPre = CCSprite::create(helpImagePreName);
        CCMenuItemSprite *helpItem = CCMenuItemSprite::create(helpNor, helpPre, this, menu_selector(MenuItemLayer::helpAction));
        
        CCSprite *exitNor = CCSprite::create(exitImageNorName);
        CCSprite *exitPre = CCSprite::create(exitImagePreName);
        CCMenuItemSprite *exitItem = CCMenuItemSprite::create(exitNor, exitPre, this, menu_selector(MenuItemLayer::exitAction));
        
        
        CCMenu *mainMenu = CCMenu::create(playItem,helpItem,exitItem,NULL);
        mainMenu->alignItemsVerticallyWithPadding(20);
        mainMenu->setPosition(winSize.width / 2, winSize.height / 2 - 160);
        this->addChild(mainMenu);
        pRet = true;
    } while (0);
    
    return true;
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
void MenuItemLayer::exitAction(CCObject *pScene)
{
    
}
