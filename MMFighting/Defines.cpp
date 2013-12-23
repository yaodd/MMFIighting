//
//  File.cpp
//  MMFighting
//
//  Created by yaodd on 13-12-28.
//
//

#include "Defines.h"

CCFiniteTimeAction *createMenuItemAction(float delay,float duration, float moveBy)
{
    CCActionInterval *move = CCMoveBy::create(duration, ccp(moveBy, 0));
    CCActionInterval *out = CCEaseElasticOut::create(move,1);
    CCActionInterval *delayTime = CCDelayTime::create(delay);
    CCFiniteTimeAction *seq = CCSequence::create(delayTime,out,NULL);
    
    return seq;
}