//
//  RankListScene.cpp
//  MMFighting
//
//  Created by yaodd on 13-12-26.
//
//

#include "RankListScene.h"
#include "RankListLayer.h"

RankListScene::RankListScene()
{
    
}
RankListScene::~RankListScene(){
    
}

bool RankListScene::init()
{
    bool pRet = false;
    do {
        
        RankListLayer *rankListLayer = RankListLayer::create();
        this->addChild(rankListLayer);
        pRet = true;
    } while (0);
    
    return pRet;
}