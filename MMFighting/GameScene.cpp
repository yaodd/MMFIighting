//
//  GameScene.cpp
//  MMFighting
//
//  Created by yaodd on 13-10-22.
//
//

#include "GameScene.h"
GameScene::GameScene(){
//    this->init();
}
GameScene::~GameScene(){
    
}

bool GameScene::init(){
    bool pRet = false;
    do {
        audioManager = AudioManager::sharedManager();
        audioManager->playGameMusic();
        
        uiLayer = UiLayer::create();
        gameLayer = GameLayer::create();
        gameLayer->delegate = this;
        this->addChild(gameLayer);
        
        this->addChild(uiLayer);
        
        
        pRet = true;
    } while (0);
    return pRet;
}
void GameScene::updateUiLayer(float hurt){
    uiLayer->updateHp(hurt);
}