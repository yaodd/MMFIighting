//
//  CCJoystick.h
//  MMFighting
//
//  Created by yaodd on 13-10-22.
//
//

#ifndef __MMFighting__CCJoystick__
#define __MMFighting__CCJoystick__

#include <iostream>
#include <cocos2d.h>
using namespace cocos2d;
class CCJoyStickDelegate {
public:
    virtual void onCCJoyStickUpdate(CCNode* sender, float angle, CCPoint direction, float power) = 0;
    virtual void onCCJoyStickActivated(CCNode* sender){CC_UNUSED_PARAM(sender);}
    virtual void onCCJoyStickDeactivated(CCNode* sender){CC_UNUSED_PARAM(sender);}
};
class CCJoystick :public CCLayer {
public:
    static CCJoystick* create(int ballradius, int movearearadius, int hitAreaRadius, bool isfollowtouch, bool iscanvisible, bool isautohide, bool hasanimation);
    bool init(int ballradius, int movearearadius, int hitAreaRadius, bool isfollowtouch, bool iscanvisible, bool isautohide, bool hasanimation);
    void setDelegate(const CCJoyStickDelegate *pDelegate) { delegate = const_cast<CCJoyStickDelegate*>(pDelegate);}
    void setBallTexture(const char* imageName);
    void setStickTexture(const char* imageName);
    void setDockTexture(const char* imageName);
public:
    CCJoystick(void);
    virtual ~CCJoystick(void);
private:
    CCSprite* ball;
    CCSprite* stick;
    CCSprite* dock;
    int moveAreaRadius;
    int ballRadius;
    bool isFollowTouch;
    bool isCanVisible;
    bool isAutoHide;
    CCRect activeRect;
    int activeRadius;
    int hitAreaRadius;
    CCPoint currentPoint;
    bool isTouched;
    bool hasAnimation;
    float power;
    float angle;
    CCPoint direction;
    CCJoyStickDelegate *delegate;
private:
    void setHitAreaWithRadius(int radius);
    void setHitAreaWithRect(CCRect rect);
    void startTimer();
    void stopTimer();
    void timerUpdate();
    void onTouchBegan(CCPoint touchPoint);
    void resetTexturePosition();
    bool containsTouchLocation(CCTouch* touch);
    void updateTouchPoint(CCPoint touchPoint);
public:
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
};

#endif /* defined(__MMFighting__CCJoystick__) */
