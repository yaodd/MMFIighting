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
#include "GameOverScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

#define BALL_RADIUS 25
#define MOVE_AREA_RADIUS 200
#define IS_FOLLOW_TOUCH false
#define IS_CAN_VISIBLE true
#define IS_AUTO_HIDE false
#define HAS_ANIMATION true
#define HIT_AREA_RADIUS 200

#define PLAYER_TAG  111111
#define ENEMY_TAG   222222
#define SCORE_SMALL   5
#define SCORE_MIDDLE  8
#define SCORE_LARGE   10

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
const char actionTPName[30] = "MMFightingAllImage.pvr.ccz";
const char actionPlistName[20] = "action.plist";
const char effect1[20] = "effect1.mp3";
const char effect2[20] = "effect2.mp3";
const char effect3[20] = "effect3.mp3";
const char effect4[20] = "effect4.mp3";
const char effect5[20] = "effect5.mp3";
const char effect6[20] = "effect6.mp3";
const char healthImageName[20] = "health.png";

GameLayer::GameLayer(){
//    this->init();
}
GameLayer::~GameLayer(){
    
    this->unscheduleUpdate();
    CCLog("over");
    saveData();     //退出前保存游戏数据
}
//保存游戏数据
void GameLayer::saveData(){
    int healthValue = playerSprite->getHealthPoint();
    int lifeNumber = playerSprite->getLifeNumber();
    int scoreValue = this->score;
    CCPoint point = playerSprite->getPosition();

    CCUserDefault::sharedUserDefault()->setIntegerForKey("playHealth", healthValue);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("playLife", lifeNumber);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("score", scoreValue);
    CCUserDefault::sharedUserDefault()->setFloatForKey("playerX", point.x);
    CCUserDefault::sharedUserDefault()->setFloatForKey("playerY", point.y);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("timeIndex", timeIndex);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("enemyCount", _enemys->count());
    for (int i = 0; i < _enemys->count(); i++) {
        EnemySprite *enemy = (EnemySprite *)_enemys->objectAtIndex(i);
        CCString *keyStrX = CCString::createWithFormat("enemy%d_x",i);
        const char *keyX = keyStrX->getCString();
        CCString *keyStrY = CCString::createWithFormat("enemy%d_y",i);
        const char *keyY = keyStrY->getCString();
        CCUserDefault::sharedUserDefault()->setFloatForKey(keyX, enemy->getPositionX());
        CCUserDefault::sharedUserDefault()->setFloatForKey(keyY, enemy->getPositionY());
        
        CCString *keyHealthStr = CCString::createWithFormat("enemy%d_health",i);
        const char *keyHealth = keyHealthStr->getCString();
        CCUserDefault::sharedUserDefault()->setIntegerForKey(keyHealth,enemy->getHealthPoint());
        
        CCString *keySpeedStr = CCString::createWithFormat("enemy%d_speed",i);
        const char *keySpeed = keySpeedStr->getCString();
        CCUserDefault::sharedUserDefault()->setFloatForKey(keySpeed, enemy->getWalkSpeed());
    }
    CCUserDefault::sharedUserDefault()->flush();
    CCLog("life %d health %d",lifeNumber,healthValue);
}
//加载游戏数据
void GameLayer::loadData()
{
    initHealth = CCUserDefault::sharedUserDefault()->getIntegerForKey("playHealth", 123);
    initLife = CCUserDefault::sharedUserDefault()->getIntegerForKey("playLife",3);
    initScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("score", 0);
    initPoint.x = CCUserDefault::sharedUserDefault()->getFloatForKey("playerX",300);
    initPoint.y = CCUserDefault::sharedUserDefault()->getFloatForKey("playerY",300);
    initTimeIndex = CCUserDefault::sharedUserDefault()->getIntegerForKey("timeIndex", 0);
    int enemyCount = CCUserDefault::sharedUserDefault()->getIntegerForKey("enemyCount", 0);
    for (int i = 0; i < enemyCount; i ++) {
        CCPoint point;
        CCString *keyStrX = CCString::createWithFormat("enemy%d_x",i);
        const char *keyX = keyStrX->getCString();
        CCString *keyStrY = CCString::createWithFormat("enemy%d_y",i);
        const char *keyY = keyStrY->getCString();
//        point.x = CCUserDefault::sharedUserDefault()->getFloatForKey(keyX);
//        point.y = CCUserDefault::sharedUserDefault()->getFloatForKey(keyY);
        point = ccp(CCUserDefault::sharedUserDefault()->getFloatForKey(keyX), CCUserDefault::sharedUserDefault()->getFloatForKey(keyY));
        CCString *keyHeathStr = CCString::createWithFormat("enemy%d_health",i);
        const char *keyHealth = keyHeathStr->getCString();
        int enemyHealth = CCUserDefault::sharedUserDefault()->getIntegerForKey(keyHealth);
        
        CCString *keySpeedStr = CCString::createWithFormat("enemy%d_speed",i);
        const char *keySpeed = keySpeedStr->getCString();
        float speed = CCUserDefault::sharedUserDefault()->getFloatForKey(keySpeed);
        
        EnemySprite *enemy = EnemySprite::enemySprite(0);
        enemy->setPosition(point);
        enemy->setWalkSpeed(speed);
        enemy->setHealthPoint(enemyHealth);
        initEnemyArr->addObject(enemy);

    }
    CCLog("life %d health %d",initLife,initHealth);
}
//清空游戏数据
void GameLayer::clearData()
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey("playHealth", 123);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("playLife", 3);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("score", 0);
    CCUserDefault::sharedUserDefault()->setFloatForKey("playerX", 300);
    CCUserDefault::sharedUserDefault()->setFloatForKey("playerY", 300);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("timeIndex", 0);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("enemyCount", 0);
    CCUserDefault::sharedUserDefault()->flush();

}
//重载create函数
GameLayer *GameLayer::create(bool isNew, GameLayerDelegate *delegate)
{
    GameLayer *gameLayer = new GameLayer(isNew,delegate);
    return gameLayer;
    
}
GameLayer::GameLayer(bool isNew,GameLayerDelegate *delegate)
{
    this->isNew = isNew;
    this->delegate = delegate;
    this->init();
}


bool GameLayer::init(){
    bool pRet = false;
    do {
        initHealth = 123;
        initLife = 3;
        initScore = 0;
        initPoint = ccp(300, 300);
        initTimeIndex = 0;
        initEnemyArr = CCArray::createWithCapacity(1000);
        if (!isNew) {
            loadData();     //如果是继续游戏，则首先加载游戏数据
        }
        score = initScore;
        
        winSize = CCDirector::sharedDirector()->getWinSize();
        audioManager = AudioManager::sharedManager();
        this->initEffects();
//        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(actionPlistName);
        _actors = CCSpriteBatchNode::create(actionTPName);
        _actors->getTexture()->setAliasTexParameters();
        this->addChild(_actors, 1);
        
        CCSprite *background = CCSprite::createWithSpriteFrameName(bgImageName);
        background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        this->addChild(background,0);
        CCLOG("ddddddddd");
        
        
        
        
        playerSprite = PlayerSprite::playSprite();
        playerSprite->setPosition(initPoint);
        playerSprite->setLifeNumber(initLife);
        playerSprite->setDesiredPosition(playerSprite->getPosition());
        playerSprite->setTag(PLAYER_TAG);
        playerSprite->setHealthPoint(initHealth);
        playerSprite->delegate = this;
        _actors->addChild(playerSprite);
        playerSprite->setAnimateAction(kActionTypeNone);
        
        _enemys = NULL;
        this->setEnemys(CCArray::createWithCapacity(1000));
//        this->addEnemys(1);
        this->initEnemy();
        aliveEnemy = _enemys->count();
        joyStick = CCJoystick::create( BALL_RADIUS, MOVE_AREA_RADIUS,HIT_AREA_RADIUS, IS_FOLLOW_TOUCH, IS_CAN_VISIBLE, IS_AUTO_HIDE, HAS_ANIMATION);
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
        
        hitMenu = CCMenu::create(handButton,footButton,NULL);
        hitMenu->setRotation(-40);
        hitMenu->setPosition(ccp(2048 - 1000, 800));
        hitMenu->alignItemsHorizontallyWithPadding(30);
        this->addChild(hitMenu,2);
        timeIndex = initTimeIndex;
        killNumber = 0;
        healthSprite = NULL;
        this->delegate->updateHp(playerSprite->getHealthPoint());
        this->delegate->updateScore(score);
        this->delegate->initPlayerHeart(initLife);
        this->scheduleUpdate();
        pRet = true;
    } while (0);
    
    return pRet;
}
//初始化上次游戏敌人
void GameLayer::initEnemy()
{
    CCObject *pObjcet;
    CCARRAY_FOREACH(initEnemyArr, pObjcet)
    {
        EnemySprite *enemy = (EnemySprite *)pObjcet;
        _actors->addChild(enemy);
        _enemys->addObject(enemy);
        enemy->setDesiredPosition(enemy->getPosition());
        enemy->delegate = this;
    }
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
//刷新layer
void GameLayer::update(float dt){
//    CCLog("update %f",dt);
    
    timeIndex++;        //时间计数器，数值为timeIndex/60秒
    if (timeIndex % 300 == 0 || timeIndex == 60) {  //第一个敌人在1秒后出现，之后的敌人每隔5秒出现
        if (aliveEnemy <= 7) {       //若敌人数大于10，则不再增加敌人
            addEnemys(1);
        }
    }
    if (timeIndex % 1800 == 0) {            //每隔30秒添加一个生命补给
        addHealthSprite();
    }
    if (timeIndex % 180 == 0) {             //每隔3秒增加现有敌人速度10
        CCObject *pObject;
        CCARRAY_FOREACH(_enemys, pObject)
        {
            EnemySprite *sprite = (EnemySprite *)pObject;
            if (sprite->getWalkSpeed() <= 300) {    //最大速度为300
                sprite->setWalkSpeed(sprite->getWalkSpeed() + 10);
            }
            
            
        }
    }
    if (timeIndex % 60 == 0) {          //生命补给出现10秒后如果还存在则消失
        if (healthSprite != NULL) {
            healthSprite->setTag(healthSprite->getTag() + 1);
            if (healthSprite->getTag() == 10) {
                healthSprite->removeFromParent();
                healthSprite = NULL;
            }
        }
    }

    playerSprite->update(dt);
    this->updateEnemys(dt);
    this->updatePositions(dt);
    CCObject *pObject = NULL;
    CCARRAY_FOREACH(_actors->getChildren(), pObject){   //更新火柴人的Z坐标值
        CCSprite *sprite = (CCSprite *)pObject;
        _actors->reorderChild(sprite, (int)(768 * 2 - sprite->getPosition().y));
    }
    
    if (healthSprite != NULL) {                         //如果主角拾取到生命补给则+20生命值，生命补给消失
        if (playerSprite->getTouchBox().actual.intersectsRect(healthSprite->boundingBox())) {
            int value = (playerSprite->getHealthPoint() + 20 < HEALTH_POINT_DEFAULT) ? (playerSprite->getHealthPoint() + 20) : HEALTH_POINT_DEFAULT;//生命值最大限制为123
            playerSprite->setHealthPoint(value);
            this->delegate->updateHp(value);
            healthSprite->removeFromParent();
            healthSprite = NULL;
        }
    }
    
    
    
}

//添加数量为number的敌人
void GameLayer::addEnemys(int number){
    
    for (int i = 0; i < number; i ++) {
        EnemySprite *enemy = EnemySprite::enemySprite(0);
        _actors->addChild(enemy);
        _enemys->addObject(enemy);
        int minX = CENTER_TO_SIDE;
        int maxX = MAP_WIDTH - CENTER_TO_SIDE;
        int minY = CENTER_TO_BOTTOM;
        int maxY = MAP_HEIGHT + CENTER_TO_BOTTOM;
        enemy->setPosition(ccp(random_range(minX, maxX), random_range(minY, maxY)));
        enemy->setDesiredPosition(enemy->getPosition());
        enemy->setTag(ENEMY_TAG);
        enemy->delegate = this;
        aliveEnemy++;
//        enemy->setOpacity(0);
//        CCActionInterval *fadeIn = CCFadeIn::create(0.5);
//        enemy->runAction(fadeIn);
//        enemy->setAnimateAction(kActionStateNone);
        
        
        
    }
}

#pragma CCJoystickDelegate method
//遥感在触摸过程中
void GameLayer::onCCJoyStickUpdate(CCNode *sender, float angle, CCPoint direction, float power){
    if (playerSprite->actionType != kActionTypeDie) {
        playerSprite->walkWithDirection(direction);
    }
}
//遥感开始触摸
void GameLayer::onCCJoyStickActivated(CCNode *sender){
    CCLOG("activated");

}
//遥感释放
void GameLayer::onCCJoyStickDeactivated(CCNode *sender){
    CCLOG("deactivated");
    if (playerSprite->actionType != kActionTypeDie) {
        playerSprite->stopAllActions();
        playerSprite->setAnimateAction(kActionTypeNone);
    }
    
}
//使用手攻击，不同状态，招式不同
void GameLayer::handAction(CCObject *pScene){
//    CCLOG("before");
    if (playerSprite->actionType == kActionTypeBeingHit_1 || playerSprite->actionType == kActionTypeBeingHit_2 || playerSprite->actionType == kActionSuperHit || playerSprite->actionType == kActionTypeDie) {
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
                            score += SCORE_SMALL;
                        }
                        if (playerSprite->actionType == kActionTypeHit_2) {
                            actionState = kActionStateBeingHit_2;
                            i = 2;
                            score += SCORE_SMALL;
                        }
                        if (playerSprite->actionType == kActionTypeHit_4) {
                            actionState = kActionStateDie;
                            i = 3;
                            score += SCORE_MIDDLE;
                        }
                        //                              CCLog("action---------------------------");
                        int hurt = this->getHurtWithSprite(playerSprite, testSprite);
                        testSprite->setHealthPoint(testSprite->getHealthPoint() - hurt);
                        if (testSprite->getHealthPoint() <= 0) {
                            score += SCORE_MIDDLE;
                            actionState = kActionStateDie;
                            aliveEnemy--;
                        }
                        
                        audioManager->playEffect(i);
                        testSprite->setAnimateAction(actionState);
                        this->delegate->updateScore(score);
                    }
                }
            }
        }
    }
}
//使用脚攻击----大招
void GameLayer::footAction(CCObject *pScene){
    CCLOG("foot");
    if (playerSprite->actionType == kActionTypeDie || playerSprite->actionType == kActionSuperHit || playerSprite->getHealthPoint() <= 7) {
        return;
    }
    
    playerSprite->setAnimateAction(kActionSuperHit);
    playerSprite->setHealthPoint(playerSprite->getHealthPoint() - 7);
//    this->delegate->updatePlayHP(playerSprite->getHealthPoint());
    this->delegate->updateHp(playerSprite->getHealthPoint());
    CCObject *pObject = NULL;
    EnemySprite *testSprite = NULL;
    CCARRAY_FOREACH(_enemys, pObject){
        testSprite = (EnemySprite *)pObject;
        //            CCLog("%f %f",testSprite->getPosition().x,testSprite->getPosition().y);
        
        if (testSprite->actionState != kActionStateDie)
        {
            if (fabsf(playerSprite->getPosition().y - testSprite->getPosition().y) < 50)
            {
                if (playerSprite->getAttackBox().actual.intersectsRect(testSprite->getHitbox().actual) ||
                    testSprite->getAttackBox().actual.intersectsRect(playerSprite->getHitbox().actual))
                {
                    ActionState actionState;
                    actionState = kActionStateDie;
                    testSprite->setAnimateAction(actionState);
                    score += SCORE_LARGE;
                    this->delegate->updateScore(score);
//                    this->playEffect(6);
                    audioManager->playEffect(6);
                    
                }
            }
        }
    }
}
//添加一个生命补给函数
void GameLayer::addHealthSprite()
{
    healthSprite = CCSprite::createWithSpriteFrameName(healthImageName);
    healthSprite->setScale(0.6);
    int minX = CENTER_TO_SIDE;
    int maxX = MAP_WIDTH - CENTER_TO_SIDE;
    int minY = 50;
    int maxY = MAP_HEIGHT + 0;
    int realX = random_range(minX, maxX);
    int realY = random_range(minY, maxY);
    healthSprite->setPosition(ccp(realX, realY + 800));
    healthSprite->setOpacity(0);
    CCActionInterval *fadeIn = CCFadeIn::create(0.5);
    CCFiniteTimeAction *seq = CCSequence::create(fadeIn,fadeIn->reverse(),NULL);
    healthSprite->runAction(CCRepeatForever::create((CCActionInterval *)seq));
    CCActionInterval *move = CCMoveTo::create(1, ccp(realX, realY));
    CCActionInterval *out = CCEaseBounceOut::create(move);
    healthSprite->runAction(out);
    healthSprite->setTag(0);
    this->addChild(healthSprite);
    
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
        if (enemy->actionState != kActionStateDie && enemy->actionState != kActionStateBeingHit_1 && enemy->actionState != kActionStateBeingHit_2 && playerSprite->actionType != kActionTypeDie) {
//            //1
//            alive++;
            //2检查当前应用程序时间的推移是否超过了机器人的下一次决定时间。如果超过了，意味着机器人需要作出一个新的决定。
            if (CURTIME > enemy->getNextDecisionTime()) {
                distanceSQ = ccpDistanceSQ(enemy->getPosition(), playerSprite->getPosition());
                //3检查机器人是否足够接近英雄，以便于有机会出拳攻击落在英雄身上。如果接近英雄了，那么就进行一个随机选择，看是要朝着英雄出拳，还是要继续空闲着。
                if (distanceSQ >=10 * 10 && distanceSQ <= 50 * 50) {
                    enemy->setNextDecisionTime(CURTIME + frandom_range(0.1, 0.5) * 1000);
                    randomChoice = random_range(0, 2);
                    if (0 == randomChoice) {
                        if (playerSprite->getPosition().x > enemy->getPosition().x) {
                            enemy->setScaleX(-SCALE_DEFAULT);
                        }else{
                            enemy->setScaleX(SCALE_DEFAULT);
                        }
                        //4假如机器人决定攻击，我们就用之前检测英雄攻击时相同的方式来进行检测碰撞。
                        enemy->setNextDecisionTime(enemy->getNextDecisionTime() + frandom_range(0.1,0.5) * 1000);
//                        CCLog("before");
                        enemy->setAnimateAction(kActionStateHit1);
//                        CCLog("after");
                        if (enemy->actionState == kActionStateHit1 && (/*playerSprite->actionType != kActionTypeHit_1 && playerSprite->actionType != kActionTypeHit_2 && playerSprite->actionType != kActionTypeHit_3 && playerSprite->actionType != kActionTypeHit_4 &&*/playerSprite->actionType != kActionSuperHit && playerSprite->actionType != kActionTypeDie)) {
//                            enemy->setAnimateAction(kActionStateHit1);
                            if (fabsf(playerSprite->getPosition().y - enemy->getPosition().y) < 30) {
                                if (enemy->getAttackBox().actual.intersectsRect(playerSprite->getHitbox().actual)) {
                                    CCLOG("being_hit ,%f %f %f %f",enemy->getAttackBox().actual.origin.x,enemy->getAttackBox().actual.origin.y,playerSprite->getHitbox().actual.origin.x,playerSprite->getHitbox().actual.origin.y);

                                    ActionType actionType;
                                    int i = 0;
                                    if (playerSprite->actionType == kActionTypeBeingHit_1) {
                                        actionType = kActionTypeBeingHit_2;
                                        i = 1;
                                    }
                                    else {
                                        actionType = kActionTypeBeingHit_1;
                                        i = 2;
                                    }
                                    
//                                    playerSprite->retain();
                                    int hurt = this->getHurtWithSprite(enemy, playerSprite);
                                    playerSprite->setHealthPoint(playerSprite->getHealthPoint() - hurt);
                                    this->delegate->updateHp(playerSprite->getHealthPoint());

                                    if (playerSprite->getHealthPoint() <= 0) {
                                        actionType = kActionTypeDie;
                                        playerSprite->setLifeNumber(playerSprite->getLifeNumber() - 1);
                                    }
                                    CCLOG("before");
                                    playerSprite->setAnimateAction(actionType);
                                    CCLOG("after");
                                    
                                    audioManager->playEffect(i);
//                                    CCLOG("finished hurt %d",hurt);
                                }
                            }
                        }
                    }
                    else if (1 == randomChoice){

                        CCPoint moveDirection = ccpNormalize(ccpSub(playerSprite->getPosition(), enemy->getPosition()));
                        //                        enemy->setPosition(moveDirection);
                        enemy->walkWithDirection(moveDirection);
                    }else{
                        CCLog("222222222222222");
                        enemy->setAnimateAction(kActionStateNone);
                        
                    }
                } else if (distanceSQ <= winSize.width * winSize.width){
                    //5如果机器人和英雄之间的距离小于屏幕宽度，那么机器人将作出决定，要么朝着英雄移动，要么继续空闲。机器人的移动基于英雄位置和机器人位置产生的法向量。
                    enemy->setNextDecisionTime(CURTIME + frandom_range(0.5, 1.0) * 1000);
                    randomChoice = random_range(0, 3);
                    if (randomChoice == 0) {
                        CCPoint moveDirection = ccpNormalize(ccpSub(playerSprite->getPosition(), enemy->getPosition()));
//                        enemy->setPosition(moveDirection);
                        enemy->walkWithDirection(moveDirection);
//                        CCLOG("move %f %f",moveDirection.x,moveDirection.y);
//                        this->updatePositions(dt);
                    }
                    else if (randomChoice == 1){
                        enemy->setAnimateAction(kActionStateNone);
                    } else{
                        int minX = CENTER_TO_SIDE;
                        int maxX = MAP_WIDTH - CENTER_TO_SIDE;
                        int minY = CENTER_TO_BOTTOM;
                        int maxY = MAP_HEIGHT + CENTER_TO_BOTTOM;
                        CCPoint targetPoint = ccp(random_range(minX, maxX), random_range(minY, maxY));
                        CCPoint moveDirection = ccpNormalize(ccpSub(targetPoint, enemy->getPosition()));
                        enemy->walkWithDirection(moveDirection);
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
    hurt = (attackSprite->getAttack() - beHitSprite->getDefend()) * 1.0 * (1 + (attackSprite->getActivity() - beHitSprite->getActivity()) / attackSprite->getAttack() * 1.0);
    CCLog("hurt %d",hurt);
    return hurt;
}
int GameLayer::getHurtWithSprite(EnemySprite *attackSprite, PlayerSprite *beHitSprite){
    int hurt = 0;
    
    //普通伤害值 = （攻击方->攻击力  - 防御方防御力）*（1+(攻击方敏捷值-防御方敏捷值)/攻击方值）
    hurt = (attackSprite->getAttack() - beHitSprite->getDefend()) * 1.0 * (1 + (attackSprite->getActivity() - beHitSprite->getActivity()) / attackSprite->getAttack() * 1.0);
    
    return hurt;
}
#pragma PlayerSpriteDelegate mark
void GameLayer::gameOver(){
    CCLog("gameOver");
//    CCUserDefault::purgeSharedUserDefault();
//    CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
    this->clearData();
    remove(CCUserDefault::getXMLFilePath().c_str());
    GameOverScene *gameOverScene = GameOverScene::create(this->score);
    CCDirector::sharedDirector()->replaceScene(gameOverScene);
}
void GameLayer::updatePlayHP(float value)
{
    this->delegate->updateHp(value);
    this->delegate->decreaseHeart();
}
#pragma EnemySpriteDelegate mark
void GameLayer::EnemySpriteBeKilled(){
    this->killNumber++;
    if (this->killNumber % 2 == 0) {
        CCLog("sssssssssssssssssss");
        audioManager->playSpecialEffect(1);
    }
}
void GameLayer::pauseMenu()
{
    hitMenu->setEnabled(false);
    
}
void GameLayer::resumeMenu()
{
    hitMenu->setEnabled(true);
}



