//
//  PlayerSprite.cpp
//  MMFighting
//
//  Created by yaodd on 13-10-23.
//
//

#include "PlayerSprite.h"

#define ATTACK_DEFAULT             20
#define DEFEND_DEFAULT             20
#define ACTIVITY_DEFAULT           20
#define WALKSPEED_DEFAULT          150
#define LIFE_NUMBER_DEFAULT        3

const char walkImageName[20] = "walk";
const char dieImageName[20] = "die";
const char initImageName[20] = "initial";
const char hit1ImageName[20] = "hit1_";
const char hit2ImageName[20] = "hit2_";
const char hit3ImageName[20] = "hit3_";
const char hit4ImageName[20] = "hit4_";
const char beingHit1ImageName[20] = "beingHit1_";
const char beingHit2ImageName[20] = "beingHit2_";
const char superHitImageName[20] = "super_hit_";
PlayerSprite::PlayerSprite()
{
    this->myInit();
}

PlayerSprite::~PlayerSprite()
{
    
}

PlayerSprite *PlayerSprite::playSprite()
{
    PlayerSprite *playSprite = new PlayerSprite();
    if (playSprite && playSprite->initWithSpriteFrameName(CCString::createWithFormat("%s1.png",initImageName)->getCString())) {
        playSprite->myInit();
        playSprite->autorelease();
        
        return playSprite;
    }
    CC_SAFE_DELETE(playSprite);
    return NULL;
}

void PlayerSprite::myInit()
{
    this->actionType = kActionTypeNone;
    this->setScale(SCALE_DEFAULT);
    idleAnimate = getAnimate(1, initImageName, 0.1f);
    idleAnimate->retain();
    
    walkAnimate = getAnimate(11, walkImageName, 0.1f);
    walkAnimate->retain();
    
    dieAnimate = getAnimate(5, dieImageName, 0.2f);
    dieAnimate->retain();
    
    hitAnimate_1 = getAnimate(3, hit1ImageName, 0.1f);
    hitAnimate_1->retain();
    
    hitAnimate_2 = getAnimate(1,hit2ImageName, 0.4f);
    hitAnimate_2->retain();
    
    hitAnimate_3 = getAnimate(1,hit3ImageName, 0.4f);
    hitAnimate_3->retain();
    
    hitAnimate_4 = getAnimate(6,hit4ImageName, 0.07f);
    hitAnimate_4->retain();
    
    beingHitAnimate_1 = getAnimate(1, beingHit1ImageName, 0.4f);
    beingHitAnimate_1->retain();
    
    beingHitAnimate_2 = getAnimate(1, beingHit2ImageName, 0.4f);
    beingHitAnimate_2->retain();
    
    superHitAnimate = getAnimate(9, superHitImageName, 0.1f);
    superHitAnimate->retain();
    
    this->setHitbox(this->createBoundingBoxWithOrigin(ccp(-CENTER_TO_SIDE, -CENTER_TO_BOTTOM),
                                                      CCSizeMake(CENTER_TO_SIDE * 2, CENTER_TO_BOTTOM * 2)));
    this->setAttackBox(this->createBoundingBoxWithOrigin(ccp(CENTER_TO_SIDE, -10), CCSizeMake(20, 20)));
//    this->setTouchBox(this->createBoundingBoxWithOrigin(ccp(0, -CENTER_TO_BOTTOM), CCSizeMake(CENTER_TO_SIDE, CENTER_TO_BOTTOM / 2)));
    this->_touchBox.original = CCRectMake(0, -CENTER_TO_BOTTOM, CENTER_TO_SIDE, CENTER_TO_BOTTOM / 2);
    beingHitCount = 0;
    _walkSpeed = WALKSPEED_DEFAULT;
    _healthPoint = HEALTH_POINT_DEFAULT;
    _defend = DEFEND_DEFAULT;
    _attack = ATTACK_DEFAULT;
    _activity = ACTIVITY_DEFAULT;
    _lifeNumber = LIFE_NUMBER_DEFAULT;
}

CCAnimate *PlayerSprite::getAnimate(int imageNum,const char  *imageName,float dt)
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

void PlayerSprite::setAnimateAction(ActionType actionType)
{
//    CCLOG("inininininin");
    this->actionType = actionType;
    CCAnimate *runAnimate;
    this->stopAllActions();
    switch (this->actionType) {
        case kActionTypeNone:
            runAnimate = idleAnimate;
            break;
        case kActionTypeWalk:
            runAnimate = walkAnimate;
            break;
        case kActionTypeDie:
            runAnimate = dieAnimate;
            break;
        case kActionTypeHit_1:
            runAnimate = hitAnimate_1;
            break;
        case kActionTypeHit_2:
            runAnimate = hitAnimate_2;
            break;
        case kActionTypeHit_3:
            runAnimate = hitAnimate_3;
            break;
        case kActionTypeHit_4:
            runAnimate = hitAnimate_4;
            break;
        case kActionTypeBeingHit_1:
            runAnimate = beingHitAnimate_1;
            break;
        case kActionTypeBeingHit_2:
            runAnimate = beingHitAnimate_2;
            break;
        case kActionSuperHit:
            runAnimate = superHitAnimate;
        default:
            break;
    }
    
    if (this->actionType == kActionTypeWalk) {
        this->runAction(CCRepeatForever::create(runAnimate));
        
    }
    else if (this->actionType == kActionTypeNone){
        this->runAction(runAnimate);
        _velocity = CCPointZero;
    } else if (this->actionType == kActionTypeDie){
        CCPoint point = this->getPosition();
        if (this->getScaleX() == SCALE_DEFAULT) {
            point.x = this->getPositionX() + 50;
        } else{
            point.x = this->getPositionX() - 50;
        }
//        _desiredPosition = point;
        this->updatePosition(point);
        CCObject *finished = CCCallFunc::create(this, callfunc_selector(PlayerSprite::runFinishedCallBack));
        CCArray *runArray = CCArray::create(runAnimate,finished,NULL);
        this->runAction(CCSequence::create(runArray));
    }
    else{
        CCObject *finished = CCCallFunc::create(this, callfunc_selector(PlayerSprite::runFinishedCallBack));
//        finished->retain();
//        runAnimate->retain();
        CCArray *runArray = CCArray::create(runAnimate,finished,NULL);
//        runArray->retain();
        this->runAction(CCSequence::create(runArray));
    }
}

void PlayerSprite::runFinishedCallBack()
{
    if (this->_healthPoint <= 0) {
        CCActionInterval *act = CCFadeIn::create(0);
        CCActionInterval *act2 = CCFadeOut::create(1);
        CCObject *finished = CCCallFunc::create(this, callfunc_selector(PlayerSprite::dieFinishHandler));
        
        CCSequence *pActSeq = CCSequence::create(act,act2,finished,NULL);
        this->runAction(CCRepeat::create(pActSeq, 4));
    }else{
        this->stopAllActions();
        this->actionType = kActionTypeNone;
        this->setAnimateAction(this->actionType);
    }
}
void PlayerSprite::dieFinishHandler(){
    if (this->_lifeNumber < 0) {
        this->delegate->gameOver();
    } else{
        this->setHealthPoint(HEALTH_POINT_DEFAULT);
        this->delegate->updatePlayHP(this->getHealthPoint());
        this->_desiredPosition = ccp(300, 300);
        this->setAnimateAction(kActionTypeNone);
    }
}

BoundingBox PlayerSprite::createBoundingBoxWithOrigin(CCPoint origin, CCSize size)
{
    BoundingBox boundingBox;
    boundingBox.original.origin = origin;
    boundingBox.original.size = size;
    boundingBox.actual.origin = ccpAdd(this->getPosition(), ccp(boundingBox.original.origin.x, boundingBox.original.origin.y));
    boundingBox.actual.size = size;
    return boundingBox;
}

void PlayerSprite::transformBoxes()
{
    _hitBox.actual.origin = ccpAdd(this->getPosition(), ccp(_hitBox.original.origin.x, _hitBox.original.origin.y));
    _attackBox.actual.origin = ccpAdd(this->getPosition(), ccp(_attackBox.original.origin.x +
                                                               (this->getScaleX() == SCALE_DEFAULT ? (- _attackBox.original.size.width - _hitBox.original.size.width) : 0),
                                                               _attackBox.original.origin.y));
    _touchBox.actual.origin = ccpAdd(this->getPosition(), ccp(_touchBox.original.origin.x, _touchBox.original.origin.y));
}

void PlayerSprite::setPosition(CCPoint position)
{
    CCSprite::setPosition(position);
    this->transformBoxes();
}
void PlayerSprite::update(float dt){
    if (actionType == kActionTypeWalk) {
        CCPoint resultPoint = ccpAdd(this->getPosition(),ccpMult(_velocity, dt));
        this->updatePosition(resultPoint);
    }
}
void PlayerSprite::updatePosition(CCPoint resultPoint)
{
    CCPoint point = this->getPosition();
    if (resultPoint.x - CENTER_TO_SIDE >= 0 && resultPoint.x + CENTER_TO_SIDE <= MAP_WIDTH) {
        point.x = resultPoint.x;
    }
    if (resultPoint.y - CENTER_TO_BOTTOM >= 0 && resultPoint.y - CENTER_TO_BOTTOM
        <= MAP_HEIGHT) {
        point.y = resultPoint.y;
    }
    _desiredPosition = point;
}
void PlayerSprite::walkWithDirection(CCPoint direction){
    if (actionType == kActionTypeNone)
    {
        this->stopAllActions();
//        this->runAction(walkAnimate);
        actionType = kActionTypeWalk;
        this->setAnimateAction(kActionTypeWalk);
    }
    if (actionType == kActionTypeWalk)
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