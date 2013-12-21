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

const char bgImageName[20] = "backgroundOver.png";
const char enterImageName1[20] = "Enter1.png";
const char enterImageName2[20] = "Enter2.png";
const char playImageName1[20] = "GamePLAY1.png";
const char playImageName2[20] = "GamePLAY2.png";
const char returnImageName1[20] = "Return1.png";
const char returnImageName2[20] = "Return2.png";
const char gameoverPlistName[30] = "GameOver.plist";
const char scoreBgImageName[20] = "scoreBackgr.png";

GameOverLayer::GameOverLayer()
{
    
}
GameOverLayer::~GameOverLayer()
{
    
}
void moveWithParabola(CCNode *mSprite, CCPoint startPoint, CCPoint endPoint ,float time);
bool GameOverLayer::init()
{
    bool pRet = false;
    do {
//        CCLabelAtlas *label = CCLabelAtlas::create(<#const char *string#>, <#const char *charMapFile#>, <#unsigned int itemWidth#>, <#unsigned int itemHeight#>, <#unsigned int startCharMap#>)
        winSize = CCDirector::sharedDirector()->getWinSize();
//        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(gameoverPlistName);
        CCSprite *background = CCSprite::createWithSpriteFrameName(bgImageName);
        background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        this->addChild(background,0);
        
        CCSprite *playNor = CCSprite::createWithSpriteFrameName(playImageName1);
        CCSprite *playPre = CCSprite::createWithSpriteFrameName(playImageName2);
        CCMenuItemSprite *playItem = CCMenuItemSprite::create(playNor, playPre, this, menu_selector(GameOverLayer::playAction));
        
        CCSprite *returnNor = CCSprite::createWithSpriteFrameName(returnImageName1);
        CCSprite *returnPre = CCSprite::createWithSpriteFrameName(returnImageName2);
        CCMenuItemSprite *returnItem = CCMenuItemSprite::create(returnNor, returnPre, this, menu_selector(GameOverLayer::returnAction));
        
        CCSprite *enterNor = CCSprite::createWithSpriteFrameName(enterImageName1);
        CCSprite *enterPre = CCSprite::createWithSpriteFrameName(enterImageName2);
        CCMenuItemSprite *enterItem = CCMenuItemSprite::create(enterNor, enterPre, this, menu_selector(GameOverLayer::enterAction));
        
        
        CCMenu *mainMenu = CCMenu::create(enterItem,returnItem,playItem,NULL);
        mainMenu->alignItemsHorizontallyWithPadding(30);
        mainMenu->setPosition(winSize.width / 4 * 3, winSize.height / 3 - 100);
        this->addChild(mainMenu);
        float layerWidth = 425.0f;
        float layerHeight = 150.0f;
        CCLayer *scoreLayer = CCLayerColor::create(ccc4(123, 123, 123, 0), layerWidth, layerHeight);
        CCSprite *scoreBg = CCSprite::createWithSpriteFrameName(scoreBgImageName);
        scoreBg->setPosition(ccp(layerWidth / 2, layerHeight / 2));
        scoreLayer->addChild(scoreBg);
        scoreLayer->setPosition(ccp(0, winSize.height * 2));
        this->addChild(scoreLayer);
        
        moveWithParabola(scoreLayer, ccp(0, winSize.height / 2), ccp(winSize.width / 2, winSize.height / 2), 1.5);
        
        pRet = true;
    } while (0);
    
    return pRet;
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