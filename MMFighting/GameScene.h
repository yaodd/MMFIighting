//
//  GameScene.h
//  MMFighting
//
//  Created by yaodd on 13-10-22.
//
//

#ifndef __MMFighting__GameScene__
#define __MMFighting__GameScene__

#include <iostream>
#include <cocos2d.h>
#include "CCJoystick.h"
using namespace cocos2d;
class GameScene : public CCScene
{
public:
    GameScene(void);
    ~GameScene(void);
    
    virtual bool init();
    CREATE_FUNC(GameScene);
    
};
#endif /* defined(__MMFighting__GameScene__) */
