//
//  GameHelpLayer.cpp
//  MMFighting
//
//  Created by yaodd on 13-12-19.
//
//

#include "GameHelpLayer.h"
#include "MenuScene.h"
#include <string>
#include "GameHelpScene.h"
#include "GameScene.h"

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
const char playImageName1[20] = "HelpPLAY1.png";
const char playImageName2[20] = "HelpPLAY2.png";
const char perImageName1[20] = "pre1.png";
const char perImageName2[20] = "pre2.png";
const char stickImageName[20] = "Stick.jpg";


#define BALL_RADIUS 25
#define MOVE_AREA_RADIUS 175
#define IS_FOLLOW_TOUCH false
#define IS_CAN_VISIBLE true
#define IS_AUTO_HIDE false
#define HAS_ANIMATION true
#define HIT_AREA_RADIUS 300

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
//        CCLOG("ddddddddd");
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
        
        
        
        char images[3][20] = {"hitWin.png","kickWin.png","moveWin.png"};
        for (int i = 0; i < 3; i ++) {
            CCSprite *label = CCSprite::createWithSpriteFrameName(images[i]);
            label->setPosition(ccp(920, winSize.height - (300 * i) - 400));
            this->addChild(label);
        }
        player = PlayerSprite::playSprite();
        player->setPosition(ccp(winSize.width / 2 + 500, winSize.height / 2 + 200));
        player->setScale(2.0);
        this->addChild(player);
        
        joyStick = CCJoystick::create( BALL_RADIUS, MOVE_AREA_RADIUS, HIT_AREA_RADIUS, IS_FOLLOW_TOUCH, IS_CAN_VISIBLE, IS_AUTO_HIDE, HAS_ANIMATION);
        //        joyStick->setBallTexture(ballImageName);
        joyStick->setDockTexture(handShankImageName);
        joyStick->setStickTexture(stickImageName);
        joyStick->setPosition(350, 495);
        joyStick->setDelegate(this);
        this->addChild(joyStick,1000);
        
        CCSprite *preNor = CCSprite::createWithSpriteFrameName(perImageName1);
        CCSprite *preClick = CCSprite::createWithSpriteFrameName(perImageName2);
        
        CCMenuItemSprite *preItem = CCMenuItemSprite::create(preNor, preClick, this, menu_selector(GameHelpLayer::preAction));
        
        CCSprite *playNor = CCSprite::createWithSpriteFrameName(playImageName1);
        CCSprite *playClick = CCSprite::createWithSpriteFrameName(playImageName2);
        CCMenuItemSprite *playItem = CCMenuItemSprite::create(playNor, playClick, this, menu_selector(GameHelpLayer::playAction));
        
        CCMenu *menu = CCMenu::create(preItem,playItem,NULL);
        menu->setPosition(ccp(winSize.width / 2, 200));
        menu->alignItemsHorizontallyWithPadding(800);
        this->addChild(menu);
        
        pRet = true;
    } while (0);
    
    return pRet;
}

#pragma CCJoystickDelegate method

void GameHelpLayer::onCCJoyStickUpdate(CCNode *sender, float angle, CCPoint direction, float power){
    player->walkWithDirection(direction);
    if (direction.x < 0) {
        player->setScaleX(2.0);
    }
    else{
        player->setScaleX(-2.0);
    }
}

void GameHelpLayer::onCCJoyStickActivated(CCNode *sender){
    CCLOG("activated");
    
}

void GameHelpLayer::onCCJoyStickDeactivated(CCNode *sender){
    CCLOG("deactivated");
    player->stopAllActions();
    player->setAnimateAction(kActionTypeNone);
}

void GameHelpLayer::handAction(CCScene *pObject)
{
    if (player->actionType == kActionTypeBeingHit_1 || player->actionType == kActionTypeBeingHit_2) {
        return;
    }
    if (player->actionType != kActionTypeHit_4) {
        player->stopAllActions();//出招前停止所有动作，除非是第四招
    }
    
    if (player->actionType == kActionTypeWalk || player->actionType == kActionTypeNone) {//第一招
        player->setAnimateAction(kActionTypeHit_1);
    }
    else if (player->actionType == kActionTypeHit_1) {//第二招
        player->setAnimateAction(kActionTypeHit_2);
    }
    else if (player->actionType == kActionTypeHit_2){//第三招
        player->setAnimateAction(kActionTypeHit_3);
    }
    else if (player->actionType == kActionTypeHit_3){//第四招
        player->setAnimateAction(kActionTypeHit_4);
    }

}
void GameHelpLayer::footAction(CCScene *pObject)
{
    if (player->actionType != kActionTypeDie && player->actionType != kActionSuperHit) {
        player->setAnimateAction(kActionSuperHit);
    }

}
void GameHelpLayer::preAction(CCScene *pObject)
{
    CCScene *menuScene = MenuScene::create();
    CCDirector::sharedDirector()->replaceScene(menuScene);
    
}
void GameHelpLayer::playAction(CCScene *pObject)
{
    CCScene *gameScene = GameScene::create();
    CCDirector::sharedDirector()->replaceScene(gameScene);
}