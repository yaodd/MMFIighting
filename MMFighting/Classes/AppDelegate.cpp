//
//  MMFightingAppDelegate.cpp
//  MMFighting
//
//  Created by yaodd on 13-10-22.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "GameOverScene.h"

const char allImagePlistName[30] = "MMFightingAllImage.plist";
const char allImagePngName[30] = "MMFightingAllImage.png";
const char allImagePvrName[30] = "MMFightingAllImage.pvr.ccz";

const char allImagePlistName2[30] = "MMFightingAllImage2.plist";
const char allImagePngName2[30] = "MMFightingAllImage2.png";
const char allImagePvrName2[30] = "MMFightingAllImage2.pvr.ccz";


USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCEGLView *pEGLView = CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView(pEGLView);
    
    
    pEGLView->setDesignResolutionSize(2048, 1536, kResolutionNoBorder);
    
    
    
    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(allImagePlistName, allImagePvrName);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(allImagePlistName2,allImagePvrName2);
    // create a scene. it's an autorelease object
    CCScene *pScene = MenuScene::create();
//    CCScene *pScene = GameOverScene::create(12312);
    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
