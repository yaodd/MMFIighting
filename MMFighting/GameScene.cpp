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
GameScene::GameScene(bool isNew)
{
    this->isNew = isNew;
    this->init();
}

bool GameScene::init(){
    bool pRet = false;
    do {
        audioManager = AudioManager::sharedManager();
        audioManager->playGameMusic();
        
        uiLayer = UiLayer::create();
        uiLayer->delegate = this;
        gameLayer = GameLayer::create(this->isNew,this);
//        gameLayer->delegate = this;
        this->addChild(gameLayer);
        
        this->addChild(uiLayer);
        
        
        pRet = true;
    } while (0);
    return pRet;
}
GameScene *GameScene::create(bool isNew)
{
    GameScene *gameScene = new GameScene(isNew);
    return gameScene;
}
#pragma GameLayerDelegate mark
void GameScene::updateHp(float hurt){
    uiLayer->updateHp(hurt);
}
void GameScene::updateScore(int score){
    uiLayer->updateScore(score);
}
void GameScene::decreaseHeart(){
    uiLayer->decreaseHeart();
}
void GameScene::initPlayerHeart(int hearts)
{
    uiLayer->initHeart(hearts);
}
#pragma UiLayerDelegate mark
void GameScene::backToMainMenu()
{
    CCLog("runnnnnnnnnn");
    gameLayer->removeFromParent();
    gameLayer->release();
    uiLayer->removeFromParent();
}
void GameScene::pauseMenu(){
    gameLayer->pauseMenu();
}
void GameScene::resumeMenu()
{
    gameLayer->resumeMenu();
}