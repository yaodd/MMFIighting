//
//  GameOverLayer.h
//  MMFighting
//
//  Created by yaodd on 13-12-17.
//
//

#ifndef __MMFighting__GameOverLayer__
#define __MMFighting__GameOverLayer__

#include <iostream>
#include <cocos2d.h>

using namespace cocos2d;

class GameOverLayer : public CCLayer,public CCTextFieldDelegate,CCTouchDelegate,CCStandardTouchDelegate
{
public:
    GameOverLayer(void);
    ~GameOverLayer(void);
    GameOverLayer(int score);
    CREATE_FUNC(GameOverLayer);
    virtual bool init();
    
    CCSize winSize;
    
    void playAction(CCObject *pScene);
    void enterAction(CCObject *pScene);
    void returnAction(CCObject *pScene);
    
    int score;
    
    static GameOverLayer *create(int score);
    
    //当用户启动虚拟键盘时的回调函数
    virtual bool onTextFieldAttachWithIME(CCTextFieldTTF *pSender);
    //当用户关闭虚拟键盘时的回调函数
    virtual bool onTextFieldDetachWithIME(CCTextFieldTTF *pSender);
    //当用户进行输入时的回调函数
    virtual bool onTextFieldInsertText(CCTextFieldTTF *pSender,const char *text,int nLen);
    //当用户删除文字时的回调函数
    virtual bool onTextFieldDeleteBackward(CCTextFieldTTF *pSender,const char *delText,int nLen);
    
    // CCLayer Touch
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
};

#endif /* defined(__MMFighting__GameOverLayer__) */
