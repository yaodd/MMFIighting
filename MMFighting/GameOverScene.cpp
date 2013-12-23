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
GameOverScene::GameOverScene(int score)
{
    this->score = score;
    this->init();
}

GameOverScene *GameOverScene::create(int score)
{
    GameOverScene *pRet = new GameOverScene(score);
    return pRet;
}

bool GameOverScene::init(){
    bool pRet = false;
    do {
        AudioManager::sharedManager()->playOverMusic();
//        gameOverLayer = GameOverLayer::create(123);
        
        gameOverLayer = GameOverLayer::create(this->score);
        this->addChild(gameOverLayer);
        pRet = true;
    } while (0);
    
    return pRet;
}