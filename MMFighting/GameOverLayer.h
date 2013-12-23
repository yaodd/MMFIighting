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
#include <HttpClient.h>
#include <cocos-ext.h>

using namespace cocos2d;
using namespace extension;

class GameOverLayer : public CCLayer,public CCTextFieldDelegate,CCTouchDelegate,CCIMEDelegate,CCStandardTouchDelegate
{
public:
    GameOverLayer(void);
    ~GameOverLayer(void);
    GameOverLayer(int score);
    CREATE_FUNC(GameOverLayer);
    virtual bool init();
    
    CCSize winSize;
    
    void playAction(CCObject *pScene);  //重新开始游戏
    void enterAction(CCObject *pScene); //提交用户名和分数
    void returnAction(CCObject *pScene);//返回到主菜单
    
    int score;                          //游戏结束时的分数
    
    static GameOverLayer *create(int score);
    
    //当用户启动虚拟键盘时的回调函数
    virtual bool onTextFieldAttachWithIME(CCTextFieldTTF *pSender);
    //当用户关闭虚拟键盘时的回调函数
    virtual bool onTextFieldDetachWithIME(CCTextFieldTTF *pSender);
    //当用户进行输入时的回调函数
    virtual bool onTextFieldInsertText(CCTextFieldTTF *pSender,const char *text,int nLen);
    //当用户删除文字时的回调函数
    virtual bool onTextFieldDeleteBackward(CCTextFieldTTF *pSender,const char *delText,int nLen);
    
    CCTextFieldTTF *nameTTF;            //用户名输入框
    
    // CCLayer Touch
    void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    void ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
    //检测键盘是否将要弹出
    virtual void keyboardWillShow(cocos2d::CCIMEKeyboardNotificationInfo& info);
//    virtual void keyboardDidShow(cocos2d::CCIMEKeyboardNotificationInfo& info);
    //检测键盘是否将要隐藏
    virtual void keyboardWillHide(cocos2d::CCIMEKeyboardNotificationInfo& info);
//    virtual void keyboardDidHide(cocos2d::CCIMEKeyboardNotificationInfo& info);
    void onRecordRequestCompleted(CCHttpClient* client, CCHttpResponse* response);
    void onHttpRequestCompleted(CCHttpClient* client, CCHttpResponse* response);
    
    CCMenuItemSprite *enterItem;
};

#endif /* defined(__MMFighting__GameOverLayer__) */
