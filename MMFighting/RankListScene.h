//
//  RankListScene.h
//  MMFighting
//
//  Created by yaodd on 13-12-26.
//
//

#ifndef __MMFighting__RankListScene__
#define __MMFighting__RankListScene__

#include <iostream>
#include <cocos2d.h>
using namespace cocos2d;

class RankListScene : public CCScene
{
public:
    RankListScene();
    ~RankListScene();
    CREATE_FUNC(RankListScene);
    
    virtual bool init();
    
};

#endif /* defined(__MMFighting__RankListScene__) */
