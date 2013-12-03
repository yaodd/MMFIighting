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
#include "SimpleAudioEngine.h"
#include "GameScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

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
const char bgImageName[20] = "gameBackground.png";
const char handImageNameNor[20] = "hand1.png";
const char footImageNameNor[20] = "foot1.png";
const char handImageNamePre[20] = "hand2.png";
const char footImageNamePre[20] = "foot2.png";
const char initImageNames[10][20] = {"e_initial.png","","","","","","","","",""};
const char initImageName[20] = "initial.png";
const char actionTPName[20] = "action.pvr.ccz";
const char actionPlistName[20] = "action.plist";
const char effect1[20] = "effect1.mp3";
const char effect2[20] = "effect2.mp3";
const char effect3[20] = "effect3.mp3";
const char effect4[20] = "effect4.mp3";
const char effect5[20] = "effect5.mp3";
const char effect6[20] = "effect6.mp3";

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
        audioManager = AudioManager::sharedManager();
        this->initEffects();
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(actionPlistName);
        _actors = CCSpriteBatchNode::create(actionTPName);
        _actors->getTexture()->setAliasTexParameters();
        this->addChild(_actors, 1);
        
        CCSprite *background = CCSprite::createWithSpriteFrameName(bgImageName);
        background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        this->addChild(background,0);
        CCLOG("ddddddddd");
        
        
        
        
        playerSprite = PlayerSprite::playSprite();
        playerSprite->setPosition(ccp(300, 300));
        playerSprite->setDesiredPosition(playerSprite->getPosition());
        playerSprite->setTag(PLAYER_TAG);
        _actors->addChild(playerSprite);
        playerSprite->setAnimateAction(kActionTypeNone);
        
        _enemys = NULL;
        this->initEnemys();
        
        joyStick = CCJoystick::create( BALL_RADIUS, MOVE_AREA_RADIUS, IS_FOLLOW_TOUCH, IS_CAN_VISIBLE, IS_AUTO_HIDE, HAS_ANIMATION);
        //        joyStick->setBallTexture(ballImageName);
        joyStick->setDockTexture(dockImageName);
        joyStick->setStickTexture(stickImageName);
        joyStick->setPosition(200, 200);
        joyStick->setDelegate(this);
        this->addChild(joyStick,2);
        
        CCSprite *handSpriteNor = CCSprite::create(handImageNameNor);
        CCSprite *handSpritePre = CCSprite::create(handImageNamePre);
        CCMenuItemSprite *handButton = CCMenuItemSprite::create(handSpriteNor, handSpritePre, this, menu_selector(GameLayer::handAction));
        CCSprite *footSpriteNor = CCSprite::create(footImageNameNor);
        CCSprite *footSpritePre = CCSprite::create(footImageNamePre);
        CCMenuItemSprite *footButton = CCMenuItemSprite::create(footSpriteNor, footSpritePre, this, menu_selector(GameLayer::footAction));
        
        CCMenu *hitMenu = CCMenu::create(handButton,footButton,NULL);
        hitMenu->setPosition(ccp(2048 - 300, 300));
        hitMenu->alignItemsHorizontallyWithPadding(20);
        this->addChild(hitMenu,2);
        
        this->scheduleUpdate();
        pRet = true;
    } while (0);
    
    return pRet;
}

void GameLayer::initEffects(){
    SimpleAudioEngine::sharedEngine()->preloadEffect(effect1);
    SimpleAudioEngine::sharedEngine()->preloadEffect(effect2);
    SimpleAudioEngine::sharedEngine()->preloadEffect(effect3);
    SimpleAudioEngine::sharedEngine()->preloadEffect(effect4);
    SimpleAudioEngine::sharedEngine()->preloadEffect(effect5);
    SimpleAudioEngine::sharedEngine()->preloadEffect(effect6);

}
void GameLayer::playEffect(int i){
    CCString *string = CCString::createWithFormat("effect%d.mp3",i);
    const char *effect = string->getCString();
    SimpleAudioEngine::sharedEngine()->playEffect(effect, false);
}

void GameLayer::update(float dt){
//    CCLog("update");
    

    playerSprite->update(dt);
    this->updateEnemys(dt);
    this->updatePositions(dt);
    CCObject *pObject = NULL;
    CCARRAY_FOREACH(_actors->getChildren(), pObject){
        CCSprite *sprite = (CCSprite *)pObject;
        _actors->reorderChild(sprite, (int)(768 * 2 - sprite->getPosition().y));
    }
}

void GameLayer::initEnemys(){
    int enemyCount = 5;
    this->setEnemys(CCArray::createWithCapacity(enemyCount));
    
    for (int i = 0; i < enemyCount; i ++) {
        EnemySprite *enemy = EnemySprite::enemySprite(0);
        _actors->addChild(enemy);
        _enemys->addObject(enemy);
        int minX = CENTER_TO_SIDE + MAP_WIDTH / 2;
        int maxX = MAP_WIDTH - CENTER_TO_SIDE;
        int minY = CENTER_TO_BOTTOM;
        int maxY = MAP_HEIGHT - CENTER_TO_BOTTOM;
        enemy->setPosition(ccp(random_range(minX, maxX), random_range(minY, maxY)));
        enemy->setDesiredPosition(enemy->getPosition());
        enemy->setTag(ENEMY_TAG);
        
        enemy->setAnimateAction(kActionStateNone);
        
        
        
    }
}

#pragma CCJoystickDelegate method

void GameLayer::onCCJoyStickUpdate(CCNode *sender, float angle, CCPoint direction, float power){
    playerSprite->walkWithDirection(direction);
}

void GameLayer::onCCJoyStickActivated(CCNode *sender){
    CCLOG("activated");

}

void GameLayer::onCCJoyStickDeactivated(CCNode *sender){
    CCLOG("deactivated");
    playerSprite->stopAllActions();
    playerSprite->setAnimateAction(kActionTypeNone);
    
}
//出拳
void GameLayer::handAction(CCObject *pScene){
//    CCLOG("before");
    if (playerSprite->actionType == kActionTypeBeingHit_1 || playerSprite->actionType == kActionTypeBeingHit_2) {
        return;
    }
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
//            CCLog("%f %f",testSprite->getPosition().x,testSprite->getPosition().y);
        
            if (testSprite->actionState != kActionStateDie)
            {
                if (fabsf(playerSprite->getPosition().y - testSprite->getPosition().y) < 20)
                {
                    if (playerSprite->getAttackBox().actual.intersectsRect(testSprite->getHitbox().actual))
                    {
                        ActionState actionState;
                        int i = 0;
                        if (playerSprite->actionType == kActionTypeHit_1 || playerSprite->actionType == kActionTypeHit_3) {
                            actionState = kActionStateBeingHit_1;
                            i = 1;
                        }
                        if (playerSprite->actionType == kActionTypeHit_2) {
                            actionState = kActionStateBeingHit_2;
                            i = 2;
                        }
                        if (playerSprite->actionType == kActionTypeHit_4) {
                            actionState = kActionStateDie;
                            i = 3;
                        }
                        //                              CCLog("action---------------------------");
                        testSprite->setAnimateAction(actionState);
                        int hurt = this->getHurtWithSprite(playerSprite, testSprite);
                        testSprite->setHealthPoint(testSprite->getHealthPoint() - hurt);
                        audioManager->playEffect(i);
                        CCLog("hurt %d",hurt);
                    }
                }
            }
        }
    }
}
void GameLayer::footAction(CCObject *pScene){
    CCLOG("foot");
    if (playerSprite->actionType != kActionTypeDie && playerSprite->actionType != kActionSuperHit) {
        playerSprite->setAnimateAction(kActionSuperHit);
    }
    CCObject *pObject = NULL;
    EnemySprite *testSprite = NULL;
    CCARRAY_FOREACH(_enemys, pObject){
        testSprite = (EnemySprite *)pObject;
        //            CCLog("%f %f",testSprite->getPosition().x,testSprite->getPosition().y);
        
        if (testSprite->actionState != kActionStateDie)
        {
            if (fabsf(playerSprite->getPosition().y - testSprite->getPosition().y) < 50)
            {
                if (playerSprite->getAttackBox().actual.intersectsRect(testSprite->getHitbox().actual))
                {
                    ActionState actionState;
                    actionState = kActionStateDie;
                    testSprite->setAnimateAction(actionState);
//                    this->playEffect(6);
                    audioManager->playEffect(6);
                    
                }
            }
        }
    }
}

                    
//敌人AI
void GameLayer::updateEnemys(float dt){
//    CCLog("before");
    int alive = 0;
    float distanceSQ;
    int randomChoice = 0;
    CCObject *pObject = NULL;
//    EnemySprite *enemy = NULL;
//    CCLOG("enemy num %d",_enemys->count());
    CCARRAY_FOREACH(_enemys, pObject){
        EnemySprite *enemy = (EnemySprite *)pObject;
        enemy->update(dt);
        if (enemy->actionState != kActionStateDie) {
            //1
            alive++;
            //2
            if (CURTIME > enemy->getNextDecisionTime()) {
                distanceSQ = ccpDistanceSQ(enemy->getPosition(), playerSprite->getPosition());
                //3
                if (distanceSQ >=10 * 10 && distanceSQ <= 50 * 50) {
                    enemy->setNextDecisionTime(CURTIME + frandom_range(0.1, 0.5) * 1000);
                    randomChoice = random_range(0, 1);
                    if (0 == randomChoice) {
                        if (playerSprite->getPosition().x > enemy->getPosition().x) {
                            enemy->setScaleX(-1.0);
                        }else{
                            enemy->setScaleX(1.0);
                        }
                        //4
                        enemy->setNextDecisionTime(enemy->getNextDecisionTime() + frandom_range(0.1,0.5) * 2000);
//                        CCLog("before");
                        enemy->setAnimateAction(kActionStateHit1);
//                        CCLog("after");
                        if (enemy->actionState == kActionStateHit1 && (playerSprite->actionType != kActionTypeHit_1 && playerSprite->actionType != kActionTypeHit_2 && playerSprite->actionType != kActionTypeHit_3 && playerSprite->actionType != kActionTypeHit_4 && playerSprite->actionType != kActionSuperHit)) {
//                            enemy->setAnimateAction(kActionStateHit1);
                            if (fabsf(playerSprite->getPosition().y - enemy->getPosition().y) < 30) {
                                if (enemy->getAttackBox().actual.intersectsRect(playerSprite->getHitbox().actual)) {
                                    CCLOG("being_hit ,%f %f %f %f",enemy->getAttackBox().actual.origin.x,enemy->getAttackBox().actual.origin.y,playerSprite->getHitbox().actual.origin.x,playerSprite->getHitbox().actual.origin.y);

                                    ActionType actionType;
                                    int i = 0;
                                    if (playerSprite->actionType == kActionTypeNone || playerSprite->actionType == kActionTypeWalk || playerSprite->actionType == kActionTypeBeingHit_2) {
                                        actionType = kActionTypeBeingHit_1;
                                        i = 1;
                                    }
                                    else if (playerSprite->actionType == kActionTypeBeingHit_1) {
                                        actionType = kActionTypeBeingHit_2;
                                        i = 2;
                                    }
//                                    playerSprite->retain();
                                    playerSprite->setAnimateAction(actionType);
                                    int hurt = this->getHurtWithSprite(enemy, playerSprite);
                                    playerSprite->setHealthPoint(playerSprite->getHealthPoint() - hurt);
                                    this->delegate->updateUiLayer(playerSprite->getHealthPoint());
                                    audioManager->playEffect(i);
                                    CCLOG("finished hurt %d",hurt);
                                }
                            }
                        }
                    }
                    else{
                        enemy->setAnimateAction(kActionStateNone);
                    }
                } else if (distanceSQ <= winSize.width * winSize.width){
                    //5
                    enemy->setNextDecisionTime(CURTIME + frandom_range(0.5, 1.0) * 1000);
                    randomChoice = random_range(0, 2);
                    if (randomChoice == 0) {
                        CCPoint moveDirection = ccpNormalize(ccpSub(playerSprite->getPosition(), enemy->getPosition()));
//                        enemy->setPosition(moveDirection);
                        enemy->walkWithDirection(moveDirection);
//                        CCLOG("move %f %f",moveDirection.x,moveDirection.y);
//                        this->updatePositions(dt);
                    }
                    else {
                        enemy->setAnimateAction(kActionStateNone);
                    }
                }
            }
        }
    }
}
void GameLayer::updatePositions(float dt){
    playerSprite->setPosition(playerSprite->getDesiredPosition());
    CCObject *pObject = NULL;
    EnemySprite *enemy = NULL;
    CCARRAY_FOREACH(_enemys, pObject){
        enemy = (EnemySprite *)pObject;
        enemy->setPosition(enemy->getDesiredPosition());
    }
}

int GameLayer::getHurtWithSprite(PlayerSprite *attackSprite, EnemySprite *beHitSprite){
    int hurt = 0;
    
    //普通伤害值 = （攻击方->攻击力  - 防御方防御力）*（1+(攻击方敏捷值-防御方敏捷值)/攻击方值）
    hurt = (attackSprite->getAttack() - beHitSprite->getDefend()) * (1 + (attackSprite->getActivity() - beHitSprite->getActivity()) / attackSprite->getAttack());
    
    return hurt;
}
int GameLayer::getHurtWithSprite(EnemySprite *attackSprite, PlayerSprite *beHitSprite){
    int hurt = 0;
    
    //普通伤害值 = （攻击方->攻击力  - 防御方防御力）*（1+(攻击方敏捷值-防御方敏捷值)/攻击方值）
    hurt = (attackSprite->getAttack() - beHitSprite->getDefend()) * (1 + (attackSprite->getActivity() - beHitSprite->getActivity()) / attackSprite->getAttack());
    
    return hurt;
}



