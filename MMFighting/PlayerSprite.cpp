//
//  PlayerSprite.cpp
//  MMFighting
//
//  Created by yaodd on 13-10-23.
//
//

#include "PlayerSprite.h"

const char walkImageName[20] = "walk";
const char dieImageName[20] = "die";
const char initImageName[20] = "initial";
const char hit1ImageName[20] = "hit1_";
const char hit2ImageName[20] = "hit2_";
const char hit3ImageName[20] = "hit3_";
const char hit4ImageName[20] = "hit4_";
const char beingHit1ImageName[20] = "beingHit1_";
const char beingHit2ImageName[20] = "beingHit2_";

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
    idleAnimate = getAnimate(1, initImageName, 0.1f);
    idleAnimate->retain();
    
    walkAnimate = getAnimate(11, walkImageName, 0.1f);
    walkAnimate->retain();
    
    dieAnimate = getAnimate(8, dieImageName, 0.2f);
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
    
    this->setHitbox(this->createBoundingBoxWithOrigin(ccp(-CENTER_TO_SIDE, -CENTER_TO_BOTTOM),
                                                      CCSizeMake(CENTER_TO_SIDE * 2, CENTER_TO_BOTTOM * 2)));
    this->setAttackBox(this->createBoundingBoxWithOrigin(ccp(CENTER_TO_SIDE, -10), CCSizeMake(20, 20)));
    
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
    this->actionType = actionType;
    CCAnimate *runAnimate;
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
        default:
            break;
    }
    
    if (this->actionType == kActionTypeWalk) {
        this->runAction(CCRepeatForever::create(runAnimate));
        
    }
    else if (this->actionType == kActionTypeNone){
        this->runAction(runAnimate);
    }
    else{
        CCObject *finished = CCCallFunc::create(this, callfunc_selector(PlayerSprite::runFinishedCallBack));
        CCArray *runArray = CCArray::create(runAnimate,finished,NULL);
        this->runAction(CCSequence::create(runArray));
    }
    
}

void PlayerSprite::runFinishedCallBack()
{
    this->actionType = kActionTypeNone;
//    CCSprite *temp_sprite = CCSprite::createWithSpriteFrameName(initImageName);
//    CCTexture2D *initT2D = temp_sprite->getTexture();
//    this->setTexture(initT2D);
//    this->runAction(idleAnimate);
    this->setAnimateAction(this->actionType);
    CCLog("call back");
    
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
                                                               (this->getScaleX() == 1 ? (- _attackBox.original.size.width - _hitBox.original.size.width) : 0),
                                                               _attackBox.original.origin.y));
}

void PlayerSprite::setPosition(CCPoint position)
{
    CCSprite::setPosition(position);
    this->transformBoxes();
}