//
//  MenuBGLayer.cpp
//  MMFighting
//
//  Created by yaodd on 13-11-24.
//
//

#include "MenuBGLayer.h"

const char MainMenuTPName[20] = "MainMenu.pvr.ccz";
const char MainMenuPlistName[20] = "MainMenu.plist";
const char menuBgImageName[20] = "background.png";
const char animationImageName[20] = "IMG00";
const char gameNameImageName[20] = "GameName.png";



MenuBGLayer::MenuBGLayer()
{
    
}
MenuBGLayer::~MenuBGLayer()
{
    
}
bool MenuBGLayer::init(){
    bool pRet = false;
    do {
        winSize = CCDirector::sharedDirector()->getWinSize();
       
        
        CCSprite *background = CCSprite::createWithSpriteFrameName(menuBgImageName);
        background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        this->addChild(background,0);
        
        CCSprite *nameSprite = CCSprite::createWithSpriteFrameName(gameNameImageName);
        nameSprite->setPosition(ccp(0 - winSize.width / 2, winSize.height / 4 * 3 - 100));
        this->addChild(nameSprite,0);
        CCActionInterval *move = CCMoveTo::create(1, ccp(winSize.width / 2, winSize.height / 4 * 3 - 100));
        
//        CCEaseElasticOut *out = CCEaseElasticOut::create(move,0.5);
//        CCEaseBackOut *out = CCEaseBackOut::create(move);
        CCEaseBounceOut *out = CCEaseBounceOut::create(move);
        nameSprite->runAction(out);
        
        CCString *initStr = CCString::createWithFormat("%s000.png",animationImageName);
        CCSprite *bgAnimateSprite = CCSprite::createWithSpriteFrameName(initStr->getCString());
        bgAnimateSprite->setPosition(ccp(winSize.width / 4, winSize.height / 4));
        bgAnimateSprite->setScale(4.0f);
        this->addChild(bgAnimateSprite,0);
        CCAnimate *animate = getAnimate(177, animationImageName, 0.1);
        animate->retain();
        bgAnimateSprite->runAction(CCRepeatForever::create(animate));
        
        pRet = true;
    } while (0);
    return pRet;
}

CCAnimate *MenuBGLayer::getAnimate(int imageNum,const char  *imageName,float dt)
{
    int num = imageNum;
    CCSpriteFrame *pAction[num];
    for (int i = 0; i < num; i ++) {
        CCString *string = CCString::createWithFormat("%s%03d.png",imageName, i);
        const char *imageName = string->getCString();
        //        pAction[i] = CCSpriteFrame::create(imageName, CCRect(0, 0, 280, 196));
        pAction[i] = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(imageName);
        
    }
    CCArray *pArr=CCArray::createWithCapacity(num);
    for (int i = 0; i < num; i ++) {
        pArr->addObject(pAction[i]);
        
    }
    CCAnimation *pRunAnimation=CCAnimation::createWithSpriteFrames(pArr,dt);
    //        CC_BREAK_IF(!pRunAnimation);
    
    CCAnimate *pRunDouga=CCAnimate::create(pRunAnimation);
    
    return pRunDouga;
    
}
