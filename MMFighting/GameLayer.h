//
//  GameLayer.h
//  MMFighting
//
//  Created by yaodd on 13-10-22.
//
//

#ifndef __MMFighting__GameLayer__
#define __MMFighting__GameLayer__

#include <cocos2d.h>
#include "CCJoystick.h"
#include "PlayerSprite.h"
#include "EnemySprite.h"



using namespace cocos2d;

class GameLayer : public CCLayer, public CCJoyStickDelegate
{
public:
    GameLayer();
    ~GameLayer();
    
    virtual bool init();
    CREATE_FUNC(GameLayer);
    
    void onCCJoyStickUpdate(CCNode *sender, float angle, CCPoint direction, float power);
    void onCCJoyStickActivated(CCNode* sender);
    void onCCJoyStickDeactivated(CCNode* sender);
    
    CCJoystick *joyStick;
    CCSize winSize;
    PlayerSprite *playerSprite;
    EnemySprite *testSprite;
    
    void handAction(CCObject *pScene);
    void footAction(CCObject *pScene);
    
    CC_SYNTHESIZE_RETAIN(CCArray*, _enemys, Enemys);
    CCSpriteBatchNode *enemyNode;
    
    void initEnemys();
    
    
    
    
//    void onCCJoyStickUpdate(CCNode *sender, float angle, CCPoint direction, float power);
};

#endif /* defined(__MMFighting__GameLayer__) */
