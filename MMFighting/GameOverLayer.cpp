//
//  GameOverLayer.cpp
//  MMFighting
//
//  Created by yaodd on 13-12-17.
//
//

#include "GameOverLayer.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "DTCursorTextField.h"
#include <string>

using namespace std;
const char bgImageName[20] = "backgroundOver.png";
const char enterImageName1[20] = "Enter1.png";
const char enterImageName2[20] = "Enter2.png";
const char playImageName1[20] = "GamePLAY1.png";
const char playImageName2[20] = "GamePLAY2.png";
const char returnImageName1[20] = "Return1.png";
const char returnImageName2[20] = "Return2.png";
const char gameoverPlistName[30] = "GameOver.plist";
const char scoreBgImageName[20] = "scoreBackgr.png";

const string digStr = ":123456789";

GameOverLayer::GameOverLayer()
{
    this->init();
}

GameOverLayer::~GameOverLayer()
{
    
}
GameOverLayer::GameOverLayer(int score)
{
    this->score = score;
    this->init();
}
GameOverLayer *GameOverLayer::create(int _score)
{
    GameOverLayer *pRet = new GameOverLayer(_score);
    
    return pRet;
}
string intToStrOver(int a);
void moveWithParabola(CCNode *mSprite, CCPoint startPoint, CCPoint endPoint ,float time);
CCFiniteTimeAction *createOverMenuItemAction(float delay,float duration);

bool GameOverLayer::init()
{
    bool pRet = false;
    do {
        CCLOG("score %d",score);
        this->setTouchEnabled(true);
        
        winSize = CCDirector::sharedDirector()->getWinSize();
        CCSprite *background = CCSprite::createWithSpriteFrameName(bgImageName);
        background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        background->setOpacity(0);
        CCActionInterval *fade = CCFadeIn::create(0.5);
        background->runAction(fade);
        
        this->addChild(background,0);
        
        CCSprite *playNor = CCSprite::createWithSpriteFrameName(playImageName1);
        CCSprite *playPre = CCSprite::createWithSpriteFrameName(playImageName2);
        CCMenuItemSprite *playItem = CCMenuItemSprite::create(playNor, playPre, this, menu_selector(GameOverLayer::playAction));
        CCFiniteTimeAction *playSeq = createOverMenuItemAction(0.5, 0.5);
        playItem->runAction(playSeq);
        
        CCSprite *returnNor = CCSprite::createWithSpriteFrameName(returnImageName1);
        CCSprite *returnPre = CCSprite::createWithSpriteFrameName(returnImageName2);
        CCMenuItemSprite *returnItem = CCMenuItemSprite::create(returnNor, returnPre, this, menu_selector(GameOverLayer::returnAction));
        CCFiniteTimeAction *returnSeq = createOverMenuItemAction(0.25, 0.5);
        returnItem->runAction(returnSeq);
        
        CCSprite *enterNor = CCSprite::createWithSpriteFrameName(enterImageName1);
        CCSprite *enterPre = CCSprite::createWithSpriteFrameName(enterImageName2);
        CCMenuItemSprite *enterItem = CCMenuItemSprite::create(enterNor, enterPre, this, menu_selector(GameOverLayer::enterAction));
        CCFiniteTimeAction *enterSeq = createOverMenuItemAction(0.0, 0.5);
        enterItem->runAction(enterSeq);
        
        
        CCMenu *mainMenu = CCMenu::create(enterItem,returnItem,playItem,NULL);
        mainMenu->alignItemsHorizontallyWithPadding(30);
        mainMenu->setPosition(winSize.width + 200, winSize.height / 3 + 20);
        this->addChild(mainMenu);
        float layerWidth = 425.0f;
        float layerHeight = 150.0f;
        CCLayer *scoreLayer = CCLayerColor::create(ccc4(123, 123, 123, 0), layerWidth, layerHeight);
        scoreLayer->setPosition(ccp(0 - layerWidth / 2, winSize.height / 2 + 200));
        this->addChild(scoreLayer);

        CCSprite *scoreBg = CCSprite::createWithSpriteFrameName(scoreBgImageName);
        scoreBg->setPosition(ccp(layerWidth / 2, layerHeight / 2));
        scoreLayer->addChild(scoreBg);
        
        const char *arr = intToStrOver(score).c_str();
        CCLabelAtlas *scoreLabel = CCLabelAtlas::create(arr, "digit.png", 112, 200, '1');
        scoreLabel->setPosition(ccp((layerWidth - scoreLabel->getContentSize().width) / 2, (layerHeight - scoreLabel->getContentSize().height) / 2));
        scoreLayer->addChild(scoreLabel);
        
        CCActionInterval *move = CCMoveTo::create(1.0, ccp(winSize.width / 2 - 140, winSize.height / 2 + 180));
        CCActionInterval *out = CCEaseBounceOut::create(move);
        scoreLayer->runAction(out);
        
        
        CCTextFieldTTF *nameTTF = CCTextFieldTTF::textFieldWithPlaceHolder("请输入您的大名...", "Helvetica", 100);
        nameTTF->setDelegate(this);
        nameTTF->setPosition(ccp(winSize.width / 2 - 200, winSize.height / 3 + 200));
//        nameTTF->Setcolo
//        nameTTF->attachWithIME();
        
//        nameTTF->setDesignedSize(CCSizeMake(1000, 1000));
        this->addChild(nameTTF);
        
        
        
        
        //moveWithParabola(scoreLayer, ccp(0, winSize.height / 2), ccp(winSize.width / 2, winSize.height / 2), 1.5);
        
        pRet = true;
    } while (0);
    
    return pRet;
}
string intToStrOver(int a)
{
    string str = "";
    do {
        int b = a % 10;
        str += digStr[b];
        a /= 10;
        
    } while (a != 0);
    for (int i = 0 ,k = str.length() - 1; i < str.length() / 2; i ++, k --) {
        char temp = str[i];
        str[i] = str[k];
        str[k] = temp;
    }
    return str;
}


CCFiniteTimeAction *createOverMenuItemAction(float delay,float duration)
{
    CCActionInterval *move = CCMoveBy::create(duration, ccp(-270 * 3 - 160, 0));
    CCActionInterval *out = CCEaseElasticOut::create(move,1);
    CCActionInterval *delayTime = CCDelayTime::create(delay);
    CCFiniteTimeAction *seq = CCSequence::create(delayTime,out,NULL);
    
    return seq;
}

//  抛物线    -Himi
//mSprite：需要做抛物线的精灵
//startPoint:起始位置
//endPoint:中止位置
//dirTime:起始位置到中止位置的所需时间
void moveWithParabola(CCNode *mSprite, CCPoint startPoint, CCPoint endPoint ,float time)
{
    float sx = startPoint.x;
    float sy = startPoint.y;
    float ex =endPoint.x+50;
    float ey =endPoint.y+150;
    int h = mSprite->getContentSize().height*0.5;
    ccBezierConfig bezier; // 创建贝塞尔曲线
    bezier.controlPoint_1 = ccp(sx, sy); // 起始点
    bezier.controlPoint_2 = ccp(sx+(ex-sx)*0.5, sy+(ey-sy)*0.5+200); //控制点
    bezier.endPosition = ccp(endPoint.x-30, endPoint.y+h); // 结束位置
//    CCBezierTo *actionMove = [CCBezierTo actionWithDuration:time bezier:bezier];
    CCBezierTo *actionMove = CCBezierTo::create(time, bezier);
    CCEaseElasticOut *out = CCEaseElasticOut::create(actionMove,1);
//    CCEaseExponentialOut *out = CCEaseExponentialOut::create(actionMove);
//    CCEaseBounceOut *out = CCEaseBounceOut::create(actionMove);
//    [mSprite runAction:actionMove];
    mSprite->runAction(out);
}
void GameOverLayer::playAction(CCObject *pScene){
    CCScene *gameScene = GameScene::create();
    CCDirector::sharedDirector()->replaceScene(gameScene);
}
void GameOverLayer::enterAction(CCObject *pScene){
    
}
void GameOverLayer::returnAction(CCObject *pScene){
    CCScene *menuScene = MenuScene::create();
    CCDirector::sharedDirector()->replaceScene(menuScene);
}

//当用户启动虚拟键盘时的回调函数
bool GameOverLayer::onTextFieldAttachWithIME(CCTextFieldTTF *pSender)
{
    CCLOG("启动输入");
    return false;
    //return true:不启动
}
//当用户关闭虚拟键盘时的回调函数
bool GameOverLayer::onTextFieldDetachWithIME(CCTextFieldTTF *pSender)
{
    CCLOG("关闭输入");
    return false;
    //return true:不关闭
}
//当用户进行输入时的回调函数
bool GameOverLayer::onTextFieldInsertText(CCTextFieldTTF *pSender,const char *text,int nLen)
{
    CCLOG("输入字符...");
    return false;
    //return true:不会输入进字符
    
}
//当用户删除文字时的回调函数
bool GameOverLayer::onTextFieldDeleteBackward(CCTextFieldTTF *pSender,const char *delText,int nLen)
{
    CCLOG("删除字符");
    return false;
    //return true:不删除
}
bool GameOverLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    
    CCLog("touch");
    return true;
}
void GameOverLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    
}