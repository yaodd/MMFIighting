//
//  MenuBGLayer.h
//  MMFighting
//
//  Created by yaodd on 13-11-24.
//
//

#ifndef __MMFighting__MenuBGLayer__
#define __MMFighting__MenuBGLayer__

#include "cocos2d.h"
using namespace cocos2d;

class MenuBGLayer : public CCLayer
{
public:
    MenuBGLayer();
    ~MenuBGLayer();
    
    bool virtual init();
    
    CREATE_FUNC(MenuBGLayer);
    
    CCSize winSize;
    CCAnimate *getAnimate(int imageNum,const char  *imageName,float dt);
};
#endif /* defined(__MMFighting__MenuBGLayer__) */
