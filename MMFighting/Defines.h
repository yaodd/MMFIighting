//
//  Defines.h
//  MMFighting
//
//  Created by yaodd on 13-11-5.
//
//

#ifndef MMFighting_Defines_h
#define MMFighting_Defines_h

#include "cocos2d.h"

using namespace cocos2d;

typedef struct _BoundingBox{
    CCRect actual;
    CCRect original;
} BoundingBox;
#define CENTER_TO_BOTTOM 78.0f
#define CENTER_TO_SIDE 40.0f

#define CURTIME GetCurTime()

#ifndef UINT64_C
#define UINT64_C(val) vla##ui64
#endif
#define random_range(low,high) (rand() % (high - low + 1)) + low
#define frandom (float)rand() / UINT64_C(0x100000000)
#define frandom_range(low,high) ((high - low) * frandom) + low

inline float GetCurTime(){
    timeval time;
    gettimeofday(&time, NULL);
    unsigned long millisecs = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return (float)millisecs;
};

#endif
