//
//  PlayerSprite.h
//  MMFighting
//
//  Created by yaodd on 13-10-23.
//
//

#ifndef __MMFighting__PlayerSprite__
#define __MMFighting__PlayerSprite__

#include <cocos2d.h>
#include "Defines.h"

enum ActionType {
    kActionTypeWalk,
    kActionTypeDie,
    kActionTypeHit_1,
    kActionTypeHit_2,
    kActionTypeHit_3,
    kActionTypeHit_4,
    kActionTypeBeingHit_1,
    kActionTypeBeingHit_2,
    kActionTypeNone,
    kActionSuperHit
    };
using namespace cocos2d;



class PlayerSprite : public CCSprite
{
private:
    CCAnimate *walkAnimate;
    CCAnimate *dieAnimate;
    CCAnimate *hitAnimate_1;
    CCAnimate *hitAnimate_2;
    CCAnimate *hitAnimate_3;
    CCAnimate *hitAnimate_4;
    CCAnimate *beingHitAnimate_1;
    CCAnimate *beingHitAnimate_2;
    CCAnimate *idleAnimate;
    CCAnimate *superHitAnimate;
    CCAnimate *getAnimate(int imageNum,const char *imageName,float dt);
    
    void runFinishedCallBack();
    
public:
    static PlayerSprite *playSprite();
    void myInit();
    PlayerSprite();
    ~PlayerSprite();
    ActionType actionType;
    CC_SYNTHESIZE(BoundingBox, _hitBox, Hitbox);
    CC_SYNTHESIZE(BoundingBox, _attackBox, AttackBox);
    CC_SYNTHESIZE(CCPoint, _desiredPosition, DesiredPosition);
    CC_SYNTHESIZE(CCPoint, _velocity, Velocity);
    CC_SYNTHESIZE(float, _walkSpeed, WalkSpeed);
    
    BoundingBox createBoundingBoxWithOrigin(CCPoint origin, CCSize size);
    void transformBoxes();
    void setPosition(CCPoint position);
    void setAnimateAction(ActionType actionType);
    void update(float dt);
    void walkWithDirection(CCPoint direction);
    int beingHitCount;
    
};

#endif /* defined(__MMFighting__PlayerSprite__) */
