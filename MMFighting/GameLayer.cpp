//
//  GameLayer.cpp
//  MMFighting
//
//  Created by yaodd on 13-10-22.
//
//

#include "GameLayer.h"
#include "CCAnimation.h"
#include "Defines.h"


using namespace cocos2d;

#define BALL_RADIUS 25
#define MOVE_AREA_RADIUS 200
#define IS_FOLLOW_TOUCH false
#define IS_CAN_VISIBLE true
#define IS_AUTO_HIDE false
#define HAS_ANIMATION true
#define HIT_AREA_RADIUS 100

#define PLAYER_TAG  111111
#define ENEMY_TAG   222222

const char ballImageName[20] = "Ball_hl.png";
const char dockImageName[20] = "Joystick.png";
const char stickImageName[20] = "Stick.jpg";
const char bgImageName[20] = "gameBg.jpg";
const char handImageNameNor[20] = "hand1.png";
const char footImageNameNor[20] = "foot1.png";
const char handImageNamePre[20] = "hand2.png";
const char footImageNamePre[20] = "foot2.png";
const char initImageNames[10][20] = {"e_initial.png","","","","","","","","",""};
const char initImageName[20] = "initial.png";
const char actionTPName[20] = "action.pvr.ccz";
const char actionPlistName[20] = "action.plist";

GameLayer::GameLayer(){
//    this->init();
}
GameLayer::~GameLayer(){
    this->unscheduleUpdate();
}

bool GameLayer::init(){
    bool pRet = false;
    do {
        
        winSize = CCDirector::sharedDirector()->getWinSize();
        
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(actionPlistName);
        _actors = CCSpriteBatchNode::create(actionTPName);
        _actors->getTexture()->setAliasTexParameters();
        this->addChild(_actors,5);
        
        CCSprite *background = CCSprite::create(bgImageName);
        background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        this->addChild(background,0);
        
        joyStick = CCJoystick::create( BALL_RADIUS, MOVE_AREA_RADIUS, IS_FOLLOW_TOUCH, IS_CAN_VISIBLE, IS_AUTO_HIDE, HAS_ANIMATION);
//        joyStick->setBallTexture(ballImageName);
        joyStick->setDockTexture(dockImageName);
        joyStick->setStickTexture(stickImageName);
        joyStick->setPosition(300, 300);
        joyStick->setDelegate(this);
        this->addChild(joyStick);
        
        playerSprite = PlayerSprite::playSprite();
        playerSprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        playerSprite->setTag(PLAYER_TAG);
        _actors->addChild(playerSprite);
        
        CCSprite *handSpriteNor = CCSprite::create(handImageNameNor);
        CCSprite *handSpritePre = CCSprite::create(handImageNamePre);
        CCMenuItemSprite *handButton = CCMenuItemSprite::create(handSpriteNor, handSpritePre, this, menu_selector(GameLayer::handAction));
        CCSprite *footSpriteNor = CCSprite::create(footImageNameNor);
        CCSprite *footSpritePre = CCSprite::create(footImageNamePre);
        CCMenuItemSprite *footButton = CCMenuItemSprite::create(footSpriteNor, footSpritePre, this, menu_selector(GameLayer::footAction));
        
        CCMenu *hitMenu = CCMenu::create(handButton,footButton,NULL);
        hitMenu->setPosition(ccp(2048 - 300, 300));
        hitMenu->alignItemsHorizontallyWithPadding(20);
        this->addChild(hitMenu);
        
//        testSprite = EnemySprite::enemySprite(0);
//        testSprite->setPosition(ccp(winSize.width / 3 * 2, winSize.height / 2));
//        this->addChild(testSprite); //(int)(768 * 2 - testSprite->getPosition().y));
//        testSprite->setZOrder((int)(768 * 2 - testSprite->getPosition().y));
        
        _enemys = CCArray::create();
//        enemyNode = CCSpriteBatchNode::create(initImageNames[0]);
//        this->addChild(enemyNode,100);
        this->initEnemys();
        
        this->scheduleUpdate();
        pRet = true;
        
    } while (0);
    
    return pRet;
}

void GameLayer::update(float dt){
//    CCLog("update");
    CCObject *pObject = NULL;
    CCARRAY_FOREACH(_actors->getChildren(), pObject){
        CCSprite *sprite = (CCSprite *)pObject;
        _actors->reorderChild(sprite, (int)(768 * 2 - sprite->getPosition().y));
    }
}

void GameLayer::initEnemys(){
    int enemyCount = 50;
    this->setEnemys(CCArray::createWithCapacity(enemyCount));
    
    for (int i = 0; i < enemyCount; i ++) {
        EnemySprite *enemy = EnemySprite::enemySprite(0);
        int minX = CENTER_TO_SIDE;
        int maxX = winSize.width - CENTER_TO_SIDE;
        int minY = CENTER_TO_BOTTOM;
        int maxY = winSize.height - CENTER_TO_BOTTOM;
        enemy->setPosition(ccp(random_range(minX, maxX), random_range(minY, maxY)));
//        enemyNode->addChild(enemy);
        enemy->setTag(ENEMY_TAG);
        _actors->addChild(enemy);
        _enemys->addObject(enemy);
        
        
        
    }
}

#pragma CCJoystickDelegate method

void GameLayer::onCCJoyStickUpdate(CCNode *sender, float angle, CCPoint direction, float power){
//    CCLOG("angle %f",angle);
//    CCLOG("point %f %f",direction.x,direction.y);
//    CCLOG("power %f",power);
    if (playerSprite->actionType == kActionTypeNone || playerSprite->actionType == kActionTypeWalk) {
        if (playerSprite->actionType == kActionTypeNone) {
            playerSprite->setAnimateAction(kActionTypeWalk);
        }
        CCPoint point = playerSprite->getPosition();
        
        float resultX = point.x + direction.x * 5;
        float resultY = point.y + direction.y * 5;
//        CCLOG("x %f y %f",point.x,point.y);
        if (resultX - CENTER_TO_SIDE >= 0 && resultX+ CENTER_TO_SIDE <= 2048) {
            point.x = resultX;
        }
        if (resultY - CENTER_TO_BOTTOM >= 0 && resultY + CENTER_TO_BOTTOM <= 1534) {
            point.y = resultY;
        }
        playerSprite->setPosition(point);
//        playerSprite->setZOrder((int)(768 * 2 - point.y));
        
        
        if (direction.x < 0) {
//            playerSprite->setRotationY(0.0f);
            playerSprite->setScaleX(1.0f);
        }
        if (direction.x >= 0) {
            playerSprite->setScaleX(-1.0f);
        }

    }
    
    
}

void GameLayer::onCCJoyStickActivated(CCNode *sender){
    CCLOG("activated");
//    testSprite->setZOrder((int)(768 * 2 - testSprite->getPosition().y));
    playerSprite->setAnimateAction(kActionTypeWalk);
}

void GameLayer::onCCJoyStickDeactivated(CCNode *sender){
    CCLOG("deactivated");
    playerSprite->stopAllActions();
//    CCSprite *temp_sprite = CCSprite::createWithSpriteFrameName(initImageName);
//    CCTexture2D *initT2D = temp_sprite->getTexture();
//    playerSprite->setTexture(initT2D);
    playerSprite->setAnimateAction(kActionTypeNone);
    
}
//出拳
void GameLayer::handAction(CCObject *pScene){
    CCLOG("hand");
    if (playerSprite->actionType != kActionTypeHit_4) {
        playerSprite->stopAllActions();//出招前停止所有动作，除非是第四招
    }
    
    if (playerSprite->actionType == kActionTypeWalk || playerSprite->actionType == kActionTypeNone) {//第一招
        playerSprite->setAnimateAction(kActionTypeHit_1);
    }
    else if (playerSprite->actionType == kActionTypeHit_1) {//第二招
        playerSprite->setAnimateAction(kActionTypeHit_2);
    }
    else if (playerSprite->actionType == kActionTypeHit_2){//第三招
        playerSprite->setAnimateAction(kActionTypeHit_3);
    }
    else if (playerSprite->actionType == kActionTypeHit_3){//第四招
        playerSprite->setAnimateAction(kActionTypeHit_4);
    }
    
    if (playerSprite->actionType == kActionTypeHit_1 || playerSprite->actionType == kActionTypeHit_2
        || playerSprite->actionType == kActionTypeHit_3 || playerSprite->actionType == kActionTypeHit_4)
    {
        CCObject *pObject = NULL;
        EnemySprite *testSprite = NULL;
        CCARRAY_FOREACH(_enemys, pObject){
            testSprite = (EnemySprite *)pObject;
            CCLog("%f %f",testSprite->getPosition().x,testSprite->getPosition().y);
        
        if (testSprite->actionState != kActionStateDie)
        {
            if (fabsf(playerSprite->getPosition().y - testSprite->getPosition().y) < 20)
            {
                if (playerSprite->getAttackBox().actual.intersectsRect(testSprite->getHitbox().actual))
                {
                    ActionState actionState;
                    if (playerSprite->actionType == kActionTypeHit_1 || playerSprite->actionType == kActionTypeHit_3) {
                        actionState = kActionStateBeingHit_1;
                    }
                    if (playerSprite->actionType == kActionTypeHit_2) {
                        actionState = kActionStateBeingHit_2;
                    }
                    if (playerSprite->actionType == kActionTypeHit_4) {
                        actionState = kActionStateDie;
                    }
                    CCLog("action---------------------------");
                    testSprite->setAnimateAction(actionState);
                }
            }
        }
        }
        
    }
    
}

void GameLayer::footAction(CCObject *pScene){
    CCLOG("foot");
    /*
    testSprite->setAnimateAction(kActionStateHit1);
    if (testSprite->actionState == kActionStateHit1) {
        if (playerSprite->actionType != kActionTypeDie) {
            if (fabs(testSprite->getPosition().y - testSprite->getPosition().y) < 20) {
                if (testSprite->getAttackBox().actual.intersectsRect(playerSprite->getHitbox().actual)){
                    playerSprite->setAnimateAction(kActionTypeDie);
                }
            }
        }
    }
     */
}









