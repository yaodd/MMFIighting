//
//  GameScene.cpp
//  MMFighting
//
//  Created by yaodd on 13-10-22.
//
//

#include "GameScene.h"
#include "GameLayer.h"
#include "UiLayer.h"
GameScene::GameScene(){
}
GameScene::~GameScene(){
    
}

bool GameScene::init(){
    bool pRet = false;
    do {
        audioManager = AudioManager::sharedManager();
        audioManager->playGameMusic();
        GameLayer *gameLayer = GameLayer::create();
        this->addChild(gameLayer);
        UiLayer *uiLayer = UiLayer::create();
        this->addChild(uiLayer);

        
        pRet = true;
    } while (0);
    return pRet;
}