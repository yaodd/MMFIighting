//
//  GameScene.cpp
//  MMFighting
//
//  Created by yaodd on 13-10-22.
//
//

#include "GameScene.h"
#include "GameLayer.h"
GameScene::GameScene(){
    this->init();
}
GameScene::~GameScene(){
    
}

bool GameScene::init(){
    bool pRet = false;
    do {
        GameLayer *gameLayer = GameLayer::create();
        this->addChild(gameLayer);
        
        pRet = true;
    } while (0);
    return pRet;
}