//
//  EnemySprite.cpp
//  MMFighting
//
//  Created by yaodd on 13-11-4.
//
//

#include "EnemySprite.h"

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

void EnemySprite::myInit(){
    this->actionState = kActionStateNone;
    
    idleAnimate = getAnimate(1, initImageNames[0], 0.1f);
    idleAnimate->retain();
    
    walkAnimate = getAnimate(11, walkImageName, 0.1f);
    walkAnimate->retain();
    
    dieAnimate = getAnimate(3, dieImageName, 0.3f);
    dieAnimate->retain();
    
    beingHitAnimate_1 = getAnimate(1, beingHit1ImageName, 0.4f);
    beingHitAnimate_1->retain();
    
    beingHitAnimate_2 = getAnimate(1, beingHit2ImageName, 0.4f);
    beingHitAnimate_2->retain();
    
    hitAnimate1 = getAnimate(4, hit1ImageName, 0.1);
    hitAnimate1->retain();
    
    this->setHitbox(this->createBoundingBoxWithOrigin(ccp(-CENTER_TO_SIDE, -CENTER_TO_BOTTOM),
                                                      CCSizeMake(CENTER_TO_SIDE * 2, CENTER_TO_BOTTOM * 2)));
    this->setAttackBox(this->createBoundingBoxWithOrigin(ccp(CENTER_TO_SIDE, -10), CCSizeMake(20, 20)));

    
}

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
    }
    else{
        CCObject *finished = CCCallFunc::create(this, callfunc_selector(EnemySprite::runFinishedCallBack));
        CCArray *runArray = CCArray::create(runAnimate,finished,NULL);
        this->runAction(CCSequence::create(runArray));

    }
    
}

void EnemySprite::runFinishedCallBack()
{
    this->actionState = kActionStateNone;
//    CCSprite *temp_sprite = CCSprite::createWithSpriteFrameName(initImageNames[0]);
//    CCTexture2D *initT2D = temp_sprite->getTexture();
//    this->setTexture(initT2D);
    this->setAnimateAction(this->actionState);
    CCLog("call back");
    
}

BoundingBox EnemySprite::createBoundingBoxWithOrigin(CCPoint origin, CCSize size)
{
    BoundingBox boundingBox;
    boundingBox.original.origin = origin;
    boundingBox.original.size = size;
    boundingBox.actual.origin = ccpAdd(this->getPosition(), ccp(boundingBox.original.origin.x, boundingBox.original.origin.y));
    boundingBox.actual.size = size;
    return boundingBox;
}

void EnemySprite::transformBoxes()
{
    _hitBox.actual.origin = ccpAdd(this->getPosition(), ccp(_hitBox.original.origin.x, _hitBox.original.origin.y));
    _attackBox.actual.origin = ccpAdd(this->getPosition(), ccp(_attackBox.original.origin.x +
                                                               (this->getScaleX() == 1 ? (- _attackBox.original.size.width - _hitBox.original.size.width) : 0),
                                                               _attackBox.original.origin.y));
}

void EnemySprite::setPosition(CCPoint position)
{
    CCSprite::setPosition(position);
    this->transformBoxes();
}