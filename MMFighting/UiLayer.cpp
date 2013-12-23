//
//  UiLayer.cpp
//  mmFight
//
//  Created by 王智锐 on 11/10/13.
//
//

#include "UiLayer.h"
#include <string.h>
#include "GameScene.h"
#include "MenuScene.h"
#define PLAY_HEART_NUMBER_DEFAULT   3
using namespace std;
using namespace cocos2d;

const char pauseNormal_char[30] = {"stop1.png"};
const char pauseSelected_char[30] = {"stop2.png"};
const char musicOn_char[30] = {"sound1.png"};
const char musicClose_char[30] = {"sound2.png"};
const char resumeNormal_char[30] = {"continue1.png"};
const char resumeSelected_char[30] = {"continue2.png"};
const char newgameNormal_char[30] = {"newgame1.png"};
const char newgameSelected_char[30] = {"newgame2.png"};
const char backNormal_char[30] = {"back1.png"};
const char backSelected_char[30] = {"back2.png"};
const char gameMenuPlistName[30] = "GameMenu.plist";
const char pauseLayerImageName[30] = "window.png";
const char heartImageName[20] = "heart.png";

const string digStr = ":123456789";
string intToStr(int a);
//  抛物线运动并同时旋转    -Himi
//mSprite：需要做抛物线的精灵
//startPoint:起始位置
//endPoint:中止位置
//startA:起始角度
//endA:中止角度
//dirTime:起始位置到中止位置的所需时间
CCAction *getActionWithParabola(CCSprite *mSprite, CCPoint startPoint,CCPoint endPoint, float startAngle, float endAngle, float time){
    float sx = startPoint.x;
    float sy = startPoint.y;
    float ex =endPoint.x+50;
    float ey =endPoint.y+150;
    int h = mSprite->getContentSize().height*0.5;
    //设置精灵的起始角度
    mSprite->setRotation(startAngle);
    ccBezierConfig bezier; // 创建贝塞尔曲线
    bezier.controlPoint_1 = ccp(sx, sy); // 起始点
    bezier.controlPoint_2 = ccp(sx+(ex-sx)*0.5, sy+(ey-sy)*0.5+200); //控制点
    bezier.endPosition = ccp(endPoint.x-30, endPoint.y+h); // 结束位置
    CCBezierTo *actionMove = CCBezierTo::create(time, bezier);
    //创建精灵旋转的动作
    CCRotateTo *actionRotate =CCRotateTo::create(time, endAngle);
    //将两个动作封装成一个同时播放进行的动作
    CCAction * action = CCSpawn::create(actionMove,actionRotate,NULL);
    return action;
}

UiLayer::UiLayer(void){
    
}

UiLayer::~UiLayer(){
    
}
/*
UiLayer* create(){
    UiLayer *layer = new UiLayer();
    if(layer){
        layer->init();
        return layer;
    }
    return NULL;
}*/

bool UiLayer::init(){
    bool ret;
    do{
        audioManager = AudioManager::sharedManager();
        CCSize size = CCDirector::sharedDirector()->getWinSize();
//        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(gameMenuPlistName);
        hp = HaemalStrand::create();
//       hp->setPosition(0,0);
        this->addChild(hp,1000);
        CCLog("hp%f %f ",hp->getPosition().x,hp->getPosition().y);
//        ((HaemalStrand*)hp)->updateHaemalStrand(100.0f);
        CCLog("start anchor %f %f",hp->getAnchorPoint().x,hp->getPosition().x);
        
        this->initMenu();
        const char *arr = intToStr(0).c_str();
        gameScoreLabel = CCLabelAtlas::create(arr, "digit.png", 112, 200, '1');
        gameScoreLabel->setPosition(ccp(900, 1320));
        _heartArray = NULL;
        this->addChild(gameScoreLabel);
        
        this->initPauseLayer();
        ret = true;
    }while(false);
    return ret;
}
string intToStr(int a)
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
void UiLayer::initHeart(int hearts){
    this->setHeartArray(CCArray::createWithCapacity(hearts));
    for (int i = 0; i < hearts; i ++) {
        CCSprite *heartSprite = CCSprite::createWithSpriteFrameName(heartImageName);
        heartSprite->setPosition(ccp(100 + 170 * i, 1300));
        this->addChild(heartSprite);
        _heartArray->addObject(heartSprite);
    }
}
void UiLayer::initMenu(){
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite *tempnormalSprite = CCSprite::createWithSpriteFrameName(pauseNormal_char);
    CCSprite *tempselectedSprite = CCSprite::createWithSpriteFrameName(pauseSelected_char);
    pauseButton = CCMenuItemSprite::create(tempnormalSprite, tempselectedSprite, this, menu_selector(UiLayer::popUpTheMenuLayer));
//    pauseButton->setPosition(ccp(size.width - pauseButton->getContentSize().width/2 + 50,size.height-pauseButton->getContentSize().height/2 + 50));
    pauseButton->retain();
    
    musicOpen = CCMenuItemImage::create(musicOn_char, musicOn_char);
    musicClosed = CCMenuItemImage::create(musicClose_char, musicClose_char);
    musicButton = CCMenuItemToggle::createWithTarget(this, menu_selector(UiLayer::toggleWithTheMusic), musicOpen,musicClosed,NULL);
//    musicButton->setPosition(ccp(pauseButton->getPosition().x - pauseButton->getContentSize().width/2 -musicButton->getContentSize().width/2 + 50,pauseButton->getPosition().y + 50));
    menu = CCMenu::create(pauseButton,musicButton,NULL);
    menu->setScale(0.8);
    
    //menu = CCMenu::create(pauseButton,NULL);
    menu->retain();
    menu->setPosition(ccp(size.width - 550, size.height - 350));
    menu->alignItemsHorizontallyWithPadding(20);
    this->addChild(menu);
    initWithParticle();
    
    
}
void UiLayer::initPauseLayer()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    pauseLayer = CCLayerColor::create(ccc4(123, 123, 123, 0), 800, 800);
    
    pauseLayer->setPosition(ccp(size.width/2-400,size.height/2-400));
    
    CCSprite *layerBgSprite = CCSprite::createWithSpriteFrameName(pauseLayerImageName);
    layerBgSprite->setPosition(ccp(800 / 2, 800 / 2));
    pauseLayer->retain();
    pauseLayer->addChild(layerBgSprite);
    resumeMenuItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(resumeNormal_char),CCSprite::createWithSpriteFrameName(resumeSelected_char), this, menu_selector(UiLayer::resumeGame));
    newgameMenuItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(newgameNormal_char), CCSprite::createWithSpriteFrameName(newgameSelected_char), this, menu_selector(UiLayer::exitGame));
    backMenuItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(backNormal_char), CCSprite::createWithSpriteFrameName(backSelected_char), this, menu_selector(UiLayer::backGame));
    
    //pauseMenu
//    resumeMenuItem->setPosition(ccp(400,400+resumeMenuItem->getContentSize().height/2));
//    newgameMenuItem->setPosition(ccp(400,400-newgameMenuItem->getContentSize().height/2));
    pauseMenu = CCMenu::create(resumeMenuItem,newgameMenuItem,backMenuItem,NULL);
    pauseMenu->setPosition(ccp(800 / 2, 800 / 2));
    pauseMenu->alignItemsVerticallyWithPadding(10);
    pauseLayer->addChild(pauseMenu);
    pauseLayer->setVisible(false);
    this->addChild(pauseLayer);
}

void UiLayer::updateHp(float value){
    ((HaemalStrand *)hp)->updateHaemalStrand(value);
}
void UiLayer::decreaseHeart(){
    int count = _heartArray->count();
    if (count > 0) {
        CCSprite *heart = (CCSprite *)_heartArray->lastObject();
//        _heartArray->removeLastObject();
        CCAction *paraAction = getActionWithParabola(heart, heart->getPosition(), ccp(heart->getPositionX() + 80, heart->getPositionY() - 500), heart->getRotation(), heart->getRotation() + 45, 1);
        CCActionInterval *fadeOut = CCFadeOut::create(1.5);
        CCObject *finished = CCCallFunc::create(this, callfunc_selector(UiLayer::deleteHeart));
        CCFiniteTimeAction *seq = CCSequence::create(fadeOut,finished,NULL);
        heart->runAction(paraAction);
        heart->runAction(seq);
//        heart->removeFromParent();
    }
    
}
void UiLayer::deleteHeart()
{
    CCSprite *heart = (CCSprite *)_heartArray->lastObject();
    _heartArray->removeLastObject();
    heart->removeFromParent();
}
void UiLayer::toggleWithTheMusic(CCObject* pObject){
    
    if(musicButton->selectedItem() == musicOpen){
        CCLog("开启");
        audioManager->effectIsOn = true;
        audioManager->resumeMusic();
    }else{
        CCLog("关闭");
        audioManager->effectIsOn = false;
        audioManager->pauseMusic();
    }
    
}

void UiLayer::popUpTheMenuLayer(CCObject* pObject){
    CCLog("popUpTheLayer");
    this->delegate->pauseMenu();
    CCDirector::sharedDirector()->pause();
    pauseLayer->setVisible(true);
    
}

void UiLayer::exitGame(CCObject *pObject){
    CCScene *gameScene = GameScene::create(true);
    CCDirector::sharedDirector()->replaceScene(gameScene);
    CCDirector::sharedDirector()->resume();
    CCLog("exit game");
}

void UiLayer::resumeGame(CCObject *pObject){
    CCLog("resume game");
    this->delegate->resumeMenu();
    pauseLayer->setVisible(false);
    CCDirector::sharedDirector()->resume();
}
void UiLayer::backGame(CCObject *pObject){
    CCScene *menuScene = MenuScene::create();
    CCDirector::sharedDirector()->replaceScene(menuScene);
    this->resumeGame(NULL);
    this->delegate->backToMainMenu();
}

void UiLayer::updateScore(int score)
{
    const char *arr = intToStr(score).c_str();
    gameScoreLabel->setString(arr);
}
//雪花效果
void UiLayer::initWithParticle(){
    //CCParticleSystemQuad *m_emmiter = new CCParticleSystemQuad();
    CCParticleSystemQuad *m_emitter=new CCParticleSystemQuad();
    m_emitter->initWithTotalParticles(300);//900个粒子对象
    //设置图片
    m_emitter->setTexture(CCTextureCache::sharedTextureCache()->addImage("snow.png"));
    //设置发射粒子的持续时间-1表示一直发射，0没有意义，其他值表示持续时间
    m_emitter->setDuration(-1);
    //设置中心方向,这个店是相对发射点，x正方向为右，y正方向为上
    m_emitter->setGravity(CCPoint(0,-240));
    
    
    //设置角度，角度的变化率
    m_emitter->setAngle(90);
    m_emitter->setAngleVar(360);
    
    
    //设置径向加速度，径向加速度的变化率
    m_emitter->setRadialAccel(50);
    m_emitter->setRadialAccelVar(0);
    
    //设置粒子的切向加速度，切向加速度的变化率
    m_emitter->setTangentialAccel(30);
    m_emitter->setTangentialAccelVar(0);
    
    
    //设置粒子的位置，位置的变化率
    m_emitter->setPosition(CCPoint(1024,1536));
    m_emitter->setPosVar(CCPoint(2048,0));
    
    //设置粒子声明，生命的变化率
    m_emitter->setLife(4);
    m_emitter->setLifeVar(2);
    
    
    //设置粒子开始的自旋转速度，开始自旋转速度的变化率
    m_emitter->setStartSpin(30);
    m_emitter->setStartSpinVar(60);
    
    //设置结束的时候的自旋转以及自旋转的变化率
    m_emitter->setEndSpin(60);
    m_emitter->setEndSpinVar(60);
    
    ccColor4F cc;
    cc.a=1.0f;
    cc.b=255.0f;
    cc.g=255.0f;
    cc.r=255.0f;
    ccColor4F cc2;
    cc2.a=0;
    cc2.b=0;
    cc2.g=0;
    cc2.r=0;
    //设置开始的时候的颜色以及颜色的变化率
    m_emitter->setStartColor(cc);
    m_emitter->setStartColorVar(cc2);
    
    //设置结束的时候的颜色以及颜色的变化率
    m_emitter->setEndColor(cc);
    m_emitter->setEndColorVar(cc2);
    
    //设置开始时候粒子的大小，以及大小的变化率
    m_emitter->setStartSize(50);
    m_emitter->setStartSizeVar(30);
    
    
    //设置粒子结束的时候的大小，以及大小的变化率
    m_emitter->setEndSize(20.0f);
    m_emitter->setEndSizeVar(10);
    
    //设置每秒钟产生粒子的数目
    m_emitter->setEmissionRate(25);
    
    addChild(m_emitter);
}
#pragma mark
#pragma pad
void UiLayer::keyBackClicked(void){
    CCLog("sssssssssssssss");
    if (pauseLayer->isVisible()) {
        CCDirector::sharedDirector()->pause();
    }
}
void UiLayer::keyMenuClicked(void){
     CCLog("bbbbbbbbbbbbbbb");
}