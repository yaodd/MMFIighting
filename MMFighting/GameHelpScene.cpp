//
//  GameHelpScene.cpp
//  MMFighting
//
//  Created by yaodd on 13-12-19.
//
//

#include "GameHelpScene.h"
#include "GameHelpLayer.h"

GameHelpScene::GameHelpScene()
{
    
}
GameHelpScene::~GameHelpScene()
{
    
}
bool GameHelpScene::init()
{
    bool pRet = false;
    do {
        GameHelpLayer *gameHelpLayer = GameHelpLayer::create();
        this->addChild(gameHelpLayer);
        
        pRet = true;
    } while (0);
    
    return pRet;
}