//
//  GameHelpLayer.cpp
//  MMFighting
//
//  Created by yaodd on 13-12-19.
//
//

#include "GameHelpLayer.h"
#include <string>

using namespace std;

const char helpBgImageName[20] = "backgroundHelp.png";
const char footImageName1[20] = "foot1.png";
const char footImageName2[20] = "foot2.png";
const char handImageName1[20] = "hand1.png";
const char handImageName2[20] = "hand2.png";
const char handShankImageName[20] = "handShank.png";
const char hitWinImageName[20] = "hitWin.png";
const char kickWinImageName[20] = "kickWin.png";
const char moveWinImageName[20] = "moveWin.png";
const char playImageName1[20] = "PLAY1.png";
const char playImageName2[20] = "PLAY2.png";
const char perImageName1[20] = "per1.png";
const char perImageName2[20] = "per2.png";
const char stickImageName[20] = "Stick.jpg";


#define BALL_RADIUS 25
#define MOVE_AREA_RADIUS 200
#define IS_FOLLOW_TOUCH false
#define IS_CAN_VISIBLE true
#define IS_AUTO_HIDE false
#define HAS_ANIMATION true
#define HIT_AREA_RADIUS 100

GameHelpLayer::GameHelpLayer()
{
    
}
GameHelpLayer::~GameHelpLayer()
{
    
}

bool GameHelpLayer::init()
{
    bool pRet = false;
    do {
        
        winSize = CCDirector::sharedDirector()->getWinSize();
        CCSprite *background = CCSprite::createWithSpriteFrameName(helpBgImageName);
        background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        this->addChild(background);
        
        CCSprite *handNor = CCSprite::createWithSpriteFrameName(handImageName1);
        CCSprite *handPre = CCSprite::createWithSpriteFrameName(handImageName2);
        CCMenuItemSprite *handItem = CCMenuItemSprite::create(handNor, handPre, this, menu_selector(GameHelpLayer::handAction));
        
        CCSprite *footNor = CCSprite::createWithSpriteFrameName(footImageName1);
        CCSprite *footPre = CCSprite::createWithSpriteFrameName(footImageName2);
        CCMenuItemSprite *footItem = CCMenuItemSprite::create(footNor, footPre, this, menu_selector(GameHelpLayer::footAction));
       
        CCMenu *mainMenu = CCMenu::create(handItem,footItem,NULL);
        mainMenu->alignItemsVerticallyWithPadding(10);
        mainMenu->setPosition(350, winSize.height - 600);
        this->addChild(mainMenu);
        
        joyStick = CCJoystick::create( BALL_RADIUS, MOVE_AREA_RADIUS, IS_FOLLOW_TOUCH, IS_CAN_VISIBLE, IS_AUTO_HIDE, HAS_ANIMATION);
        //        joyStick->setBallTexture(ballImageName);
        joyStick->setDockTexture(handShankImageName);
        joyStick->setStickTexture(stickImageName);
        joyStick->setPosition(350, 495);
        joyStick->setDelegate(this);
        this->addChild(joyStick,2);
        char images[3][20] = {"hitWin.png","kickWin.png","moveWin.png"};
        for (int i = 0; i < 3; i ++) {
            CCSprite *label = CCSprite::createWithSpriteFrameName(images[i]);
            label->setPosition(ccp(920, winSize.height - (300 * i) - 400));
            this->addChild(label);
        }
        
        pRet = true;
    } while (0);
    
    return pRet;
}

#pragma CCJoystickDelegate method

void GameHelpLayer::onCCJoyStickUpdate(CCNode *sender, float angle, CCPoint direction, float power){
}

void GameHelpLayer::onCCJoyStickActivated(CCNode *sender){
    CCLOG("activated");
    
}

void GameHelpLayer::onCCJoyStickDeactivated(CCNode *sender){
    CCLOG("deactivated");
    
}

void GameHelpLayer::handAction(CCScene *pObject)
{
    
}
void GameHelpLayer::footAction(CCScene *pObject)
{
    
}