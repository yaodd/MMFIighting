//
//  PlayerSprite.h
//  MMFighting
//
//  Created by yaodd on 13-10-23.
//
//  主角火柴人的类

#ifndef __MMFighting__PlayerSprite__
#define __MMFighting__PlayerSprite__

#include <cocos2d.h>
#include "Defines.h"
#define HEALTH_POINT_DEFAULT       123  //初始生命值

class PlayerSpriteDelegate{
public:
    virtual void gameOver(void) = 0;
    virtual void updatePlayHP(float value) = 0;
};

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
    void dieFinishHandler();
public:
    static PlayerSprite *playSprite();
    void myInit();
    PlayerSprite();
    ~PlayerSprite();
    ActionType actionType;
    CC_SYNTHESIZE(BoundingBox, _hitBox, Hitbox);
    CC_SYNTHESIZE(BoundingBox, _attackBox, AttackBox);
    CC_SYNTHESIZE(BoundingBox, _touchBox, TouchBox);
    CC_SYNTHESIZE(BoundingBox, _superHitBox, SuperHitBox);
    CC_SYNTHESIZE(CCPoint, _desiredPosition, DesiredPosition);
    CC_SYNTHESIZE(CCPoint, _velocity, Velocity);
    
    BoundingBox createBoundingBoxWithOrigin(CCPoint origin, CCSize size);
    void transformBoxes();
    void setPosition(CCPoint position);
    void setAnimateAction(ActionType actionType);
    void update(float dt);
    void walkWithDirection(CCPoint direction);
    void updatePosition(CCPoint resultPoint);

    int beingHitCount;
    //属性值
    CC_SYNTHESIZE(int, _healthPoint, HealthPoint);      //HP
    CC_SYNTHESIZE(int, _attack, Attack);                //攻击力
    CC_SYNTHESIZE(int, _defend, Defend);                //防御力
    CC_SYNTHESIZE(int, _activity, Activity);            //敏捷
    CC_SYNTHESIZE(float, _walkSpeed, WalkSpeed);        //速度
    CC_SYNTHESIZE(int, _lifeNumber, LifeNumber);        //生命数量
    
    PlayerSpriteDelegate *delegate;
};

#endif /* defined(__MMFighting__PlayerSprite__) */
