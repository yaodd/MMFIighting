//
//  GameOverLayer.cpp
//  MMFighting
//
//  Created by yaodd on 13-12-17.
//
//

#include "GameOverLayer.h"

const char bgImageName[20] = "backgroundOver.png";
const char enterImageName1[20] = "Enter1.png";
const char enterImageName2[20] = "Enter2.png";
const char playImageName1[20] = "GamePLAY1.png";
const char playImageName2[20] = "GamePLAY2.png";
const char returnImageName1[20] = "Return1.png";
const char returnImageName2[20] = "Return2.png";
const char gameoverPlistName[30] = "GameOver.plist";

GameOverLayer::GameOverLayer()
{
    
}
GameOverLayer::~GameOverLayer()
{
    
}
bool GameOverLayer::init()
{
    bool pRet = false;
    do {
//        CCLabelAtlas *label = CCLabelAtlas::create(<#const char *string#>, <#const char *charMapFile#>, <#unsigned int itemWidth#>, <#unsigned int itemHeight#>, <#unsigned int startCharMap#>)
        winSize = CCDirector::sharedDirector()->getWinSize();
//        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(gameoverPlistName);
        CCSprite *background = CCSprite::createWithSpriteFrameName(bgImageName);
        background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        this->addChild(background,0);
        
        CCSprite *playNor = CCSprite::createWithSpriteFrameName(playImageName1);
        CCSprite *playPre = CCSprite::createWithSpriteFrameName(playImageName2);
        CCMenuItemSprite *playItem = CCMenuItemSprite::create(playNor, playPre, this, menu_selector(GameOverLayer::playAction));
        
        CCSprite *returnNor = CCSprite::createWithSpriteFrameName(returnImageName1);
        CCSprite *returnPre = CCSprite::createWithSpriteFrameName(returnImageName2);
        CCMenuItemSprite *returnItem = CCMenuItemSprite::create(returnNor, returnPre, this, menu_selector(GameOverLayer::returnAction));
        
        CCSprite *enterNor = CCSprite::createWithSpriteFrameName(enterImageName1);
        CCSprite *enterPre = CCSprite::createWithSpriteFrameName(enterImageName2);
        CCMenuItemSprite *enterItem = CCMenuItemSprite::create(enterNor, enterPre, this, menu_selector(GameOverLayer::enterAction));
        
        
        CCMenu *mainMenu = CCMenu::create(enterItem,returnItem,playItem,NULL);
        mainMenu->alignItemsHorizontallyWithPadding(30);
        mainMenu->setPosition(winSize.width / 4 * 3, winSize.height / 3 - 100);
        this->addChild(mainMenu);

        pRet = true;
    } while (0);
    
    return pRet;
}
void GameOverLayer::playAction(CCObject *pScene){
    
}
void GameOverLayer::enterAction(CCObject *pScene){
    
}
void GameOverLayer::returnAction(CCObject *pScene){
    
}