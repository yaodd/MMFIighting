//
//  GameHelpScene.h
//  MMFighting
//
//  Created by yaodd on 13-12-19.
//
//

#ifndef __MMFighting__GameHelpScene__
#define __MMFighting__GameHelpScene__

#include <iostream>
#include <cocos2d.h>
using namespace cocos2d;

class GameHelpScene : public CCScene
{
public:
    
    GameHelpScene();
    ~GameHelpScene();
    
    CREATE_FUNC(GameHelpScene);
    
    virtual bool init();
    
};

#endif /* defined(__MMFighting__GameHelpScene__) */
