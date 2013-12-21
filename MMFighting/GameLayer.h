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
#include "AudioManager.h"
#include "UiLayer.h"
//#include "GameScene.h"



using namespace cocos2d;

class GameLayerDelegate{
public:
//    virtual ~ GameLayerDelegate(){};
    virtual void updateHp(float hurt) = 0;
    virtual void updateScore(int score) = 0;
    virtual void decreaseHeart() = 0;
};

class GameLayer : public CCLayer, public CCJoyStickDelegate, PlayerSpriteDelegate
{
public:
    GameLayer();
    ~GameLayer();
    
    AudioManager *audioManager;
    
    GameLayerDelegate *delegate;
    
    virtual bool init();
    CREATE_FUNC(GameLayer);
    
    void onCCJoyStickUpdate(CCNode *sender, float angle, CCPoint direction, float power);
    void onCCJoyStickActivated(CCNode* sender);
    void onCCJoyStickDeactivated(CCNode* sender);
    
    void update(float dt);
    
    void updateEnemys(float dt);
    
    void updatePositions(float dt);
    
    CCJoystick *joyStick;
    CCSize winSize;
    PlayerSprite *playerSprite;
    CCSprite *healthSprite;

    
    
    void handAction(CCObject *pScene);
    void footAction(CCObject *pScene);
    
    CC_SYNTHESIZE_RETAIN(CCArray*, _enemys, Enemys);
    CCSpriteBatchNode *_actors;
//    CCSpriteBatchNode *playerNode;
    
    void addEnemys(int number);
    
    void initEffects();
    
    void playEffect(int i);
    
    int getHurtWithSprite(PlayerSprite *attackSprite, EnemySprite *beHitSprite);
    int getHurtWithSprite(EnemySprite *attackSprite, PlayerSprite *beHitSprite);
    
    int score;
    
    virtual void gameOver(void);
    virtual void updatePlayHP(float value);
    void addHealthSprite();
    
    int timeIndex;
    
    
//    void onCCJoyStickUpdate(CCNode *sender, float angle, CCPoint direction, float power);
};

#endif /* defined(__MMFighting__GameLayer__) */
