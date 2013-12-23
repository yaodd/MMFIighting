//
//  PlayerHolder.h
//  MMFighting
//
//  Created by yaodd on 13-12-26.
//
//

#ifndef __MMFighting__PlayerHolder__
#define __MMFighting__PlayerHolder__

#include <iostream>
#include <cocos2d.h>

using namespace cocos2d;
class PlayerHolder : public CCObject
{
private:
    CCString *name;
    CCString *score;
public:
    PlayerHolder();
    ~PlayerHolder();
    void setName(CCString *_name);
    void setScore(CCString *_score);
    CCString *getName();
    CCString *getScore();
};

#endif /* defined(__MMFighting__PlayerHolder__) */
