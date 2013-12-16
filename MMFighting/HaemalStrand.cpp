//
//  haemalStrand.cpp
//  mmFight
//
//  Created by 王智锐 on 11/10/13.
//
//

#include "HaemalStrand.h"

const char hpbackground_char[30] = {"hp1.png"};
const char hp_char[30] = {"hp2.png"};
 const float animateDuration = 0.5f;
/*
HaemalStrand* HaemalStrand::create(){
    HaemalStrand *Strand = new HaemalStrand();
    if(Strand){
        Strand->init();
        return Strand;
    }
    return NULL;
}
*/

HaemalStrand::HaemalStrand(void){
    isAnimationFinished = true;
}

HaemalStrand::~HaemalStrand(void){
    
}



bool HaemalStrand::init(){
    bool ret = false;
    do {
        previousScaleX = 1.0f;
        stepX = 0.0f;
        totalHp = 123.0f;
        nowHp = totalHp;
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        this->strandBackground = CCSprite::createWithSpriteFrameName(hpbackground_char);
        strandBackground->setPosition(ccp(10+strandBackground->getContentSize().width/2,size.height - strandBackground->getContentSize().height/2-10));
        this->addChild(strandBackground);
        haemal = CCSprite::createWithSpriteFrameName(hp_char);
        haemal->setAnchorPoint(ccp(0,0.5));
        haemal->setPosition(ccp(10,size.height -
                                haemal->getContentSize().height/2-10));
        this->addChild(haemal);
        ret = true;
    } while (false);
    return ret;
}

void HaemalStrand::setTotalHp(float value){
    this->totalHp = value;
}

void HaemalStrand::updateHaemalStrand(float value){
    float scaleX = value / totalHp;
    float times = animateDuration / 0.02f;
    //this->ignoreAnchorPointForPosition(true);
    previousScaleX = this->nowHp / totalHp;
    animateScaleX = previousScaleX;
    stepX = (previousScaleX - scaleX)/times;
    CCLog("%f",stepX);
    this->nowHp = value;
    
    if(!isAnimationFinished){
        this->unschedule(schedule_selector(HaemalStrand::hpAnimate));
        this->schedule(schedule_selector(HaemalStrand::hpAnimate), 0.02f);
    }else{
        this->schedule(schedule_selector(HaemalStrand::hpAnimate), 0.02f);
    }
}

void HaemalStrand::hpAnimate(float dt){
    //CCLog("timer");
    float res = animateScaleX -(nowHp /totalHp);
    res = res > 0.0f ? res :(-1)*res;
    if(res < 0.000001f ){

        this->unschedule(schedule_selector(HaemalStrand::hpAnimate));
        haemal->setScaleX(nowHp / totalHp);
        isAnimationFinished = true;
        CCLog("stop %f %f",haemal->getAnchorPoint().x,haemal->getPosition().x);
        return ;
    }
    animateScaleX -= stepX;
    haemal->setScaleX(animateScaleX);
    isAnimationFinished = false;
}