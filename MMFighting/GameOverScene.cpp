//
//  GameOverScene.cpp
//  MMFighting
//
//  Created by yaodd on 13-12-17.
//
//

#include "GameOverScene.h"

GameOverScene::GameOverScene(){
    
}
GameOverScene::~GameOverScene(){
    
}

bool GameOverScene::init(){
    bool pRet = false;
    do {
        winSize = CCDirector::sharedDirector()->getWinSize();
        audioManager = AudioManager::sharedManager();
        gameOverLayer = GameOverLayer::create();
        this->addChild(gameOverLayer);
        pRet = true;
    } while (0);
    
    return pRet;
}