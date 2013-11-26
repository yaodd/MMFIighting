//
//  UiLayer.cpp
//  mmFight
//
//  Created by 王智锐 on 11/10/13.
//
//

#include "UiLayer.h"

const char pauseNormal_char[30] = {"stop1.png"};
const char pauseSelected_char[30] = {"stop2.png"};
const char musicOn_char[30] = {"sound1.png"};
const char musicClose_char[30] = {"sound2.png"};
const char resumeNormal_char[30] = {"continue1.png"};
const char resumeSelected_char[30] = {"continue2.png"};
const char newgameNormal_char[30] = {"newgame1.png"};
const char newgameSelected_char[30] = {"newgame2.png"};
const char gameMenuPlistName[30] = "GameMenu.plist";
const char pauseLayerImageName[30] = "window.png";
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
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(gameMenuPlistName);
        hp = HaemalStrand::create();
//       hp->setPosition(0,0);
        this->addChild(hp,1000);
        CCLog("hp%f %f ",hp->getPosition().x,hp->getPosition().y);
        ((HaemalStrand*)hp)->updateHaemalStrand(100.0f);
        CCLog("start anchor %f %f",hp->getAnchorPoint().x,hp->getPosition().x);
        
        this->initMenu();
        ret = true;
    }while(false);
    return ret;
}

void UiLayer::initMenu(){
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite *tempnormalSprite = CCSprite::createWithSpriteFrameName(pauseNormal_char);
    CCSprite *tempselectedSprite = CCSprite::createWithSpriteFrameName(pauseSelected_char);
    pauseButton = CCMenuItemSprite::create(tempnormalSprite, tempselectedSprite, this, menu_selector(UiLayer::popUpTheMenuLayer));
    pauseButton->setPosition(ccp(size.width - pauseButton->getContentSize().width/2,size.height-pauseButton->getContentSize().height/2));
    pauseButton->retain();
    
    musicOpen = CCMenuItemImage::create(musicOn_char, musicOn_char);
    musicClosed = CCMenuItemImage::create(musicClose_char, musicClose_char);
    musicButton = CCMenuItemToggle::createWithTarget(this, menu_selector(UiLayer::toggleWithTheMusic), musicOpen,musicClosed,NULL);
    musicButton->setPosition(ccp(pauseButton->getPosition().x -
                                 pauseButton->getContentSize().width/2-
                                 musicButton->getContentSize().width/2,
                                 pauseButton->getPosition().y));
    menu = CCMenu::create(pauseButton,musicButton,NULL);
    
    //menu = CCMenu::create(pauseButton,NULL);
    menu->retain();
    menu->setPosition(CCPointZero);
    this->addChild(menu);
    initWithParticle();
}

void UiLayer::updateHp(float value){
    
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
    CCDirector::sharedDirector()->pause();
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    if(pauseLayer == NULL){
        pauseLayer = CCLayerColor::create(ccc4(123, 123, 123, 0), 800, 800);
        
        pauseLayer->setPosition(ccp(size.width/2-400,size.height/2-400));
        
        pauseLayer->retain();
        CCSprite *layerBgSprite = CCSprite::createWithSpriteFrameName(pauseLayerImageName);
        layerBgSprite->setPosition(ccp(800 / 2, 800 / 2));
        pauseLayer->retain();
        pauseLayer->addChild(layerBgSprite);
        resumeMenuItem = CCMenuItemImage::create(resumeNormal_char, resumeSelected_char, this, menu_selector(UiLayer::resumeGame));
        newgameMenuItem = CCMenuItemImage::create(newgameNormal_char, newgameSelected_char, this, menu_selector(UiLayer::exitGame));
        //pauseMenu
        resumeMenuItem->setPosition(ccp(400,400+resumeMenuItem->getContentSize().height/2));
        newgameMenuItem->setPosition(ccp(400,400-newgameMenuItem->getContentSize().height/2));
        pauseMenu = CCMenu::create(resumeMenuItem,newgameMenuItem,NULL);
        pauseMenu->setPosition(CCPointZero);
        pauseMenu->retain();
        pauseLayer->addChild(pauseMenu);
        this->addChild(pauseLayer);
    }else{
        pauseLayer->setPosition(ccp(size.width/2-400,size.height/2-400));
    }
    
}

void UiLayer::exitGame(CCObject *pObject){
    CCLog("exit game");
}

void UiLayer::resumeGame(CCObject *pObject){
    CCLog("resume game");
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    pauseLayer->setPosition(ccp(-size.width/2,-size.height/2));
    CCDirector::sharedDirector()->resume();
}

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