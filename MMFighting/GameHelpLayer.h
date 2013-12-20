//
//  GameHelpLayer.h
//  MMFighting
//
//  Created by yaodd on 13-12-19.
//
//

#ifndef __MMFighting__GameHelpLayer__
#define __MMFighting__GameHelpLayer__

#include <iostream>
#include <cocos2d.h>
#include "CCJoystick.h"
#include "PlayerSprite.h"
using namespace cocos2d;

class GameHelpLayer : public CCLayer ,CCJoyStickDelegate
{
public:
    
    GameHelpLayer();
    ~GameHelpLayer();
    
    CREATE_FUNC(GameHelpLayer);
    
    virtual bool init();
    CCJoystick *joyStick;

    CCSize winSize;
    
    void handAction(CCScene *pObject);
    void footAction(CCScene *pObject);
    
    void preAction(CCScene *pObject);
    void playAction(CCScene *pObject);
    
    void onCCJoyStickUpdate(CCNode *sender, float angle, CCPoint direction, float power);
    void onCCJoyStickActivated(CCNode* sender);
    void onCCJoyStickDeactivated(CCNode* sender);
    
    PlayerSprite *player;
};

#endif /* defined(__MMFighting__GameHelpLayer__) */
