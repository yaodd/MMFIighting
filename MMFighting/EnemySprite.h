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
    void dieFinishHandler();
public:
    static EnemySprite *enemySprite(int type);
    EnemySprite();
    ~EnemySprite();
    void myInit();
    int type;
    ActionState actionState;
    
    CC_SYNTHESIZE(BoundingBox, _hitBox, Hitbox);
    CC_SYNTHESIZE(BoundingBox, _attackBox, AttackBox);
    CC_SYNTHESIZE(float, _nextDecisionTime, NextDecisionTime);
    CC_SYNTHESIZE(CCPoint, _desiredPosition, DesiredPosition);
    CC_SYNTHESIZE(CCPoint, _velocity, Velocity);
    
    BoundingBox createBoundingBoxWithOrigin(CCPoint origin, CCSize size);
    void transformBoxes();
    void setPosition(CCPoint position);

    
    void setAnimateAction(ActionState actionState);
    void update(float dt);
    void walkWithDirection(CCPoint direction);
    void updatePosition(CCPoint resultPoint);
    //属性值
    CC_SYNTHESIZE(int, _healthPoint, HealthPoint);      //HP
    CC_SYNTHESIZE(int, _attack, Attack);                //攻击力
    CC_SYNTHESIZE(int, _defend, Defend);                //防御力
    CC_SYNTHESIZE(int, _activity, Activity);            //敏捷
    CC_SYNTHESIZE(float, _walkSpeed, WalkSpeed);        //速度
    
};

#endif /* defined(__MMFighting__EnemySprite__) */
