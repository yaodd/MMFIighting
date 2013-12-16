//
//  GameOverLayer.h
//  MMFighting
//
//  Created by yaodd on 13-12-17.
//
//

#ifndef __MMFighting__GameOverLayer__
#define __MMFighting__GameOverLayer__

#include <iostream>
#include <cocos2d.h>

using namespace cocos2d;

class GameOverLayer : public CCLayer
{
public:
    GameOverLayer(void);
    ~GameOverLayer(void);
    CREATE_FUNC(GameOverLayer);
    virtual bool init();
    
    CCSize winSize;
    
    void playAction(CCObject *pScene);
    void enterAction(CCObject *pScene);
    void returnAction(CCObject *pScene);
};

#endif /* defined(__MMFighting__GameOverLayer__) */
