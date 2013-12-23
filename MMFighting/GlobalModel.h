//
//  GlobalModel.h
//  MMFighting
//
//  Created by yaodd on 13-12-27.
//
//

#ifndef __MMFighting__GlobalModel__
#define __MMFighting__GlobalModel__

#include <iostream>
#include <cocos2d.h>
#include "PlayerHolder.h"
using namespace cocos2d;

class GlobalModel : public CCObject
{
private:
    GlobalModel();
    ~GlobalModel();
public:
//    CC_SYNTHESIZE(<#varType#>, <#varName#>, <#funName#>)
    static GlobalModel *sharedGlobalModel();
    CC_SYNTHESIZE(CCArray *, rankArray, RankArray);
    CC_SYNTHESIZE(PlayerHolder *, userHolder, UserHolder);
    
    virtual bool init();
};
#endif /* defined(__MMFighting__GlobalModel__) */
