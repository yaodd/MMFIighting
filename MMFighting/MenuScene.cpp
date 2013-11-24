//
//  MenuScene.cpp
//  MMFighting
//
//  Created by yaodd on 13-10-23.
//
//

#include "MenuScene.h"
#include "MenuBGLayer.h"
#include "MenuItemLayer.h"

MenuScene::MenuScene()
{
    
}

MenuScene::~MenuScene()
{
    
}

bool MenuScene::init(){
    bool pRet = false;
    do {
        MenuBGLayer *menuBGLayer = MenuBGLayer::create();
        this->addChild(menuBGLayer);
        MenuItemLayer *menuItemLayer = MenuItemLayer::create();
        this->addChild(menuItemLayer);
        pRet = true;
    } while (0);
    
    return pRet;
}
