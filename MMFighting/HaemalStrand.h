//
//  haemalStrand.h
//  mmFight
//
//  Created by 王智锐 on 11/10/13.
//
//

#ifndef __mmFight__HaemalStrand__
#define __mmFight__HaemalStrand__

#include "cocos2d.h"

using namespace cocos2d;

class HaemalStrand : public CCNode{

   
public:
    //member
    CCSprite *strandBackground;
    CCSprite *haemal;
    CCSprite *maskLayer;;

    bool isAnimationFinished;
    float totalHp;
    float nowHp;
    float animateScaleX;
    float previousScaleX;
    float stepX;
    //function
    HaemalStrand(void);
    ~HaemalStrand(void);
    CREATE_FUNC(HaemalStrand);
    virtual bool init();
    void setTotalHp(float value);
    void updateHaemalStrand(float value);
    void hpAnimate(float dt);
};



#endif /* defined(__mmFight__haemalStrand__) */
