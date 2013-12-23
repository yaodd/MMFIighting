//
//  EnemySprite.cpp
//  MMFighting
//
//  Created by yaodd on 13-11-4.
//
//  敌人火柴人的类

#include "EnemySprite.h"

#define HEALTH_POINT_DEFAULT       100      //初始生命值
#define ATTACK_DEFAULT             30       //初始攻击力
#define DEFEND_DEFAULT             10       //初始防御力
#define ACTIVITY_DEFAULT           10       //初始敏捷
#define WALKSPEED_DEFAULT          100      //初始移动速度



const char dieImageName[20] = "e_die";
const char walkImageName[20] = "e_walk";
const char hit1ImageName[20] = "e_hit1_";
const char beingHit1ImageName[20] = "e_beingHit1_";
const char beingHit2ImageName[20] = "e_beingHit2_";
const char initImageNames[10][20] = {"e_initial","","","","","","","","",""};

EnemySprite::EnemySprite()
{
    this->myInit();
}
EnemySprite::~EnemySprite()
{
    
}
EnemySprite *EnemySprite::enemySprite(int type)
{
    EnemySprite *enemySprite = new EnemySprite();
    
    if (enemySprite && enemySprite->initWithSpriteFrameName(CCString::createWithFormat("%s1.png",initImageNames[0])->getCString())) {
        enemySprite->myInit();
        enemySprite->autorelease();
        
        return enemySprite;
    }
    
    CC_SAFE_DELETE(enemySprite);
    return NULL;
}
//对象的初始化，包括各种动作和数值
void EnemySprite::myInit(){
    this->setScale(SCALE_DEFAULT);
    this->actionState = kActionStateNone;
    
    idleAnimate = getAnimate(1, initImageNames[0], 0.1f);
    idleAnimate->retain();
    
    walkAnimate = getAnimate(11, walkImageName, 0.1f);
    walkAnimate->retain();
    
    dieAnimate = getAnimate(4, dieImageName, 0.2f);
    dieAnimate->retain();
    
    beingHitAnimate_1 = getAnimate(1, beingHit1ImageName, 0.4f);
    beingHitAnimate_1->retain();
    
    beingHitAnimate_2 = getAnimate(1, beingHit2ImageName, 0.4f);
    beingHitAnimate_2->retain();
    
    hitAnimate1 = getAnimate(4, hit1ImageName, 0.1);
    hitAnimate1->retain();
    
    this->setHitbox(this->createBoundingBoxWithOrigin(ccp(-CENTER_TO_SIDE, -CENTER_TO_BOTTOM),CCSizeMake(CENTER_TO_SIDE * 2, CENTER_TO_BOTTOM * 2)));
    this->setAttackBox(this->createBoundingBoxWithOrigin(ccp(CENTER_TO_SIDE, -10), CCSizeMake(20, 20)));

    _nextDecisionTime = 0;
    
    this->setWalkSpeed(WALKSPEED_DEFAULT);
    _walkSpeed = WALKSPEED_DEFAULT;
    _healthPoint = HEALTH_POINT_DEFAULT;
    _defend = DEFEND_DEFAULT;
    _attack = ATTACK_DEFAULT;
    _activity = ACTIVITY_DEFAULT;
    
}
//生成动画的函数
CCAnimate *EnemySprite::getAnimate(int imageNum,const char  *imageName,float dt)
{
    int num = imageNum;
    CCSpriteFrame *pAction[num];
    for (int i = 0; i < num; i ++) {
        CCString *string = CCString::createWithFormat("%s%d.png",imageName, i + 1);
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
//运行动画的函数
void EnemySprite::setAnimateAction(ActionState actionState)
{
    this->actionState = actionState;
    CCAnimate *runAnimate;
    this->stopAllActions();
    switch (this->actionState) {
        case kActionStateNone:
            runAnimate = idleAnimate;
            break;
        case kActionStateWalk:
            runAnimate = walkAnimate;
            break;
        case kActionStateDie:
            runAnimate = dieAnimate;
            break;
        case kActionStateBeingHit_1:
            runAnimate = beingHitAnimate_1;
            break;
        case kActionStateBeingHit_2:
            runAnimate = beingHitAnimate_2;
            break;
        case kActionStateHit1:
            runAnimate = hitAnimate1;
        default:
            break;
    }
    
    if (this->actionState == kActionStateWalk) {
        this->runAction(CCRepeatForever::create(runAnimate));
            }
    else if (this->actionState == kActionStateNone){
        this->runAction(runAnimate);
        _velocity = CCPointZero;
    } else if (this->actionState == kActionStateDie){
        CCPoint point = this->getPosition();
        if (this->getScaleX() == SCALE_DEFAULT) {
            point.x = this->getPositionX() + 50;
        } else{
            point.x = this->getPositionX() - 50;
        }
//        _desiredPosition = point;
        this->updatePosition(point);
        CCDelayTime *delay = CCDelayTime::create(0.6);
        CCObject *finished = CCCallFunc::create(this, callfunc_selector(EnemySprite::runFinishedCallBack));
        CCArray *runArray = CCArray::create(runAnimate,delay,finished,NULL);
        this->runAction(CCSequence::create(runArray));
    }
    else{
        CCObject *finished = CCCallFunc::create(this, callfunc_selector(EnemySprite::runFinishedCallBack));
        CCArray *runArray = CCArray::create(runAnimate,finished,NULL);
        this->runAction(CCSequence::create(runArray));
    }
    
}

//动画结束回调

void EnemySprite::runFinishedCallBack()
{
    if (this->_healthPoint <= 0) {
//        this->removeFromParent();
        CCActionInterval *act = CCFadeIn::create(0);
        CCActionInterval *act2 = CCFadeOut::create(1);
        CCObject *finished = CCCallFunc::create(this, callfunc_selector(EnemySprite::dieFinishHandler));
        
        CCSequence *pActSeq = CCSequence::create(act,act2,finished,NULL);
        this->runAction(CCRepeat::create(pActSeq, 1));
        this->delegate->EnemySpriteBeKilled();
    }
    else{
        this->actionState = kActionStateNone;
        this->stopAllActions();
        this->setAnimateAction(this->actionState);
    }
    
}

void EnemySprite::dieFinishHandler(){
    this->removeFromParent();
}
//生成包围盒的函数
BoundingBox EnemySprite::createBoundingBoxWithOrigin(CCPoint origin, CCSize size)
{
    BoundingBox boundingBox;
    boundingBox.original.origin = origin;
    boundingBox.original.size = size;
    boundingBox.actual.origin = ccpAdd(this->getPosition(), ccp(boundingBox.original.origin.x, boundingBox.original.origin.y));
    boundingBox.actual.size = size;
    return boundingBox;
}
//根据方向改变包围盒

void EnemySprite::transformBoxes()
{
    _hitBox.actual.origin = ccpAdd(this->getPosition(), ccp(_hitBox.original.origin.x, _hitBox.original.origin.y));
    _attackBox.actual.origin = ccpAdd(this->getPosition(), ccp(_attackBox.original.origin.x +
                                                               (this->getScaleX() == SCALE_DEFAULT ? (- _attackBox.original.size.width - _hitBox.original.size.width) : 0),
                                                               _attackBox.original.origin.y));
}
//重写位置函数
void EnemySprite::setPosition(CCPoint position)
{
    CCSprite::setPosition(position);
    this->transformBoxes();
}
void EnemySprite::update(float dt){
    if (actionState == kActionStateWalk) {
        
        CCPoint resultPoint = ccpAdd(this->getPosition(),ccpMult(_velocity, dt));
        this->updatePosition(resultPoint);
    }
}
//更新对象位置
void EnemySprite::updatePosition(CCPoint resultPoint)
{
    CCPoint point = this->getPosition();
    if (resultPoint.x - CENTER_TO_SIDE >= 0 && resultPoint.x + CENTER_TO_SIDE <= MAP_WIDTH) {
        point.x = resultPoint.x;
    }
    if (resultPoint.y - CENTER_TO_BOTTOM >= 0 && resultPoint.y - CENTER_TO_BOTTOM <= MAP_HEIGHT) {
        point.y = resultPoint.y;
    }
    _desiredPosition = point;
}
//敌人移动
void EnemySprite::walkWithDirection(CCPoint direction){
    if (actionState == kActionStateNone)
    {
        this->stopAllActions();
        //        this->runAction(walkAnimate);
        actionState = kActionStateWalk;
        this->setAnimateAction(kActionStateWalk);
    }
    if (actionState == kActionStateWalk)
    {
        _velocity = ccp(direction.x * _walkSpeed, direction.y * _walkSpeed);
        if (_velocity.x >= 0)
        {
            this->setScaleX(-SCALE_DEFAULT);
        }
        else
        {
            this->setScaleX(SCALE_DEFAULT);
        }
    }
}