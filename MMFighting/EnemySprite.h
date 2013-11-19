//
//  EnemySprite.h
//  MMFighting
//
//  Created by yaodd on 13-11-4.
//
//

#ifndef __MMFighting__EnemySprite__
#define __MMFighting__EnemySprite__

#include <cocos2d.h>
#include "Defines.h"

enum ActionState{
    kActionStateNone,
    kActionStateDie,
    kActionStateWalk,
    kActionStateHit1,
    kActionStateHit2,
    kActionStateHit3,
    kActionStateHit4,
    kActionStateBeingHit_1,
    kActionStateBeingHit_2
};
using namespace cocos2d;

class EnemySprite : public CCSprite
{
private:
    CCAnimate *idleAnimate;
    CCAnimate *dieAnimate;
    CCAnimate *walkAnimate;
    CCAnimate *hitAnimate1;
    CCAnimate *hitAnimate2;
    CCAnimate *hitAnimate3;
    CCAnimate *hitAnimate4;
    CCAnimate *beingHitAnimate_1;
    CCAnimate *beingHitAnimate_2;
    CCAnimate *getAnimate(int imageNum,const char *imageName,float dt);
    
    void runFinishedCallBack();
public:
    static EnemySprite *enemySprite(int type);
    EnemySprite();
    ~EnemySprite();
    void myInit();
    int type;
    ActionState actionState;
    
    CC_SYNTHESIZE(BoundingBox, _hitBox, Hitbox);
    CC_SYNTHESIZE(BoundingBox, _attackBox, AttackBox);
    
    BoundingBox createBoundingBoxWithOrigin(CCPoint origin, CCSize size);
    void transformBoxes();
    void setPosition(CCPoint position);

    
    void setAnimateAction(ActionState actionState);
    
    
    
};

#endif /* defined(__MMFighting__EnemySprite__) */
