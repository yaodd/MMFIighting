//
//  MenuItemLayer.h
//  MMFighting
//
//  Created by yaodd on 13-10-23.
//
//

#ifndef __MMFighting__MenuItemLayer__
#define __MMFighting__MenuItemLayer__

#include "cocos2d.h"
using namespace cocos2d;

class MenuItemLayer : public CCLayer
{
public:
    MenuItemLayer();
    ~MenuItemLayer();
    
    virtual bool init();
    
    CREATE_FUNC(MenuItemLayer);
    
    CCSize winSize;
    
    void playAction(CCObject *pScene);  
    void helpAction(CCObject *pScene);
    void continueAction(CCObject *pScene);
    
    
};

#endif /* defined(__MMFighting__MenuItemLayer__) */
