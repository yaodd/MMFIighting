//
//  RankListLayer.cpp
//  MMFighting
//
//  Created by yaodd on 13-12-26.
//
//

#include "RankListLayer.h"
#include "PlayerHolder.h"
#include "GlobalModel.h"
#include "MenuScene.h"
#include "GameScene.h"
//#include "CornerColorLayer.h"
const char cuprunCrownImageName[30] = "cuprumCrown.png";
const char goldenCrownImageName[30] = "goldenCrown.png";
const char silverCrownImageName[30] = "silverCrown.png";
const char rankNameImageName[30] = "rankName.png";
const char rankScoresImageName[30] = "rankScores.png";
const char peopleLaughImageName[30] = "people_laugh.png";
const char peopleSadImageName[30] = "people_sad.png";
const char peopleSmileImageName[30] = "people_smile.png";
const char rankPlay1ImageName[30] = "rankPlay1.png";
const char rankPlay2ImageName[30] = "rankPlay2.png";
const char rankReturn1ImageName[30] = "rankReturn1.png";
const char rankReturn2ImageName[30] = "rankReturn2.png";

#define CROWN_SPRITE_TAG    111111
#define NAME_LABEL_TAG      222222
#define SCORE_LABEL_TAG     333333


RankListLayer::RankListLayer()
{
    
}
RankListLayer::~RankListLayer()
{
    this->myDataArr->release();
}


bool RankListLayer::init(){
    bool pRet = false;
    do {
//        dataArray = NULL;
//        dataArray = CCArray::createWithCapacity(100);
        this->setMyDataArr(CCArray::createWithCapacity(100));
        this->myDataArr->retain();
        this->initData();
        winSize = CCDirector::sharedDirector()->getWinSize();
        CCLayer *bgLayer = CCLayerColor::create(ccc4(109, 108, 108, 255), winSize.width, winSize.height);
        bgLayer->setPosition(0,0);
        this->addChild(bgLayer);
        
        
        CCSprite *people;
        if (rank < 3) {
            people = CCSprite::createWithSpriteFrameName(peopleLaughImageName);
        } else if (rank < 5)
        {
            people = CCSprite::createWithSpriteFrameName(peopleSmileImageName);
        } else{
            people = CCSprite::createWithSpriteFrameName(peopleSadImageName);
        }
        people->setPosition(ccp(300, winSize.height / 2 - 200));
        this->addChild(people);
        
        CCLayer *tableViewBg = CCLayerColor::create(ccc4(67, 67, 67, 255), 1200, 1100);
        tableViewBg->setPosition(ccp(750,250));
//        tableViewBg->sh
        this->addChild(tableViewBg);
        
        CCTableView *tableView = CCTableView::create(this, CCSizeMake(1200, 1100));
        CCFiniteTimeAction *tabelViewSeq = createMenuItemAction(0.15, 0.5, -(winSize.width / 2 - 750 + 1200));
        tableView->runAction(tabelViewSeq);
        tableView->setDirection(kCCScrollViewDirectionVertical);
        tableView->setPosition(ccp(winSize.width / 2 + 1200, 250));
        tableView->setDelegate(this);
        tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        this->addChild(tableView);
        tableView->reloadData();
        
        CCSprite *nameSprite = CCSprite::createWithSpriteFrameName(rankNameImageName);
        nameSprite->setPosition(ccp(winSize.width + 275, winSize.height - 150));
        this->addChild(nameSprite);
        CCFiniteTimeAction *nameSeq = createMenuItemAction(0, 0.5, -(winSize.width / 2 - 180 + 275 ));
        nameSprite->runAction(nameSeq);
        
        CCSprite *scroeSprite = CCSprite::createWithSpriteFrameName(rankScoresImageName);
        scroeSprite->setPosition(ccp(winSize.width + 275, winSize.height - 150));
        this->addChild(scroeSprite);
        CCFiniteTimeAction *scoreSeq = createMenuItemAction(0.25, 0.5, -(winSize.width/ 2 - 680 + 275));
        scroeSprite->runAction(scoreSeq);
        
        CCSprite *returnNor = CCSprite::createWithSpriteFrameName(rankReturn1ImageName);
        CCSprite *returnHig = CCSprite::createWithSpriteFrameName(rankReturn2ImageName);
        CCMenuItemSprite *returnItem = CCMenuItemSprite::create(returnNor, returnHig, this, menu_selector(RankListLayer::rankReturnAction));
        CCFiniteTimeAction *returnSeq = createMenuItemAction(0.25, 0.5, -(winSize.width / 2 - 180 + 275 ));
//        returnItem->runAction(returnSeq);
//        returnItem->setPosition(ccp(winSize.width + 275, 120));
        
        CCSprite *playNor = CCSprite::createWithSpriteFrameName(rankPlay1ImageName);
        CCSprite *playHig = CCSprite::createWithSpriteFrameName(rankPlay2ImageName);
        CCMenuItemSprite *playItem = CCMenuItemSprite::create(playNor, playHig, this, menu_selector(RankListLayer::rankPlayAction));
        CCFiniteTimeAction *playSeq = createMenuItemAction(0.5, 0.5, -(winSize.width/ 2 - 680 + 275));
//        playItem->runAction(playSeq);
//        playItem->setPosition(ccp(winSize.width + 275, 120));
        
        CCMenu *rankMenu = CCMenu::create(returnItem,playItem,NULL);
        rankMenu->alignItemsHorizontallyWithPadding(15);
        rankMenu->setPosition(ccp(winSize.width + 450,  120));
        CCFiniteTimeAction *menuSeq = createMenuItemAction(0.4, 0.5, -(winSize.width / 2));
        rankMenu->runAction(menuSeq);
//        rankMenu->setPosition(CCPointZero);
        this->addChild(rankMenu);
        pRet = true;
    } while (0);
    
    return pRet;
}
//初始化排名数据
void RankListLayer::initData()
{
    GlobalModel *globalModel = GlobalModel::sharedGlobalModel();
    PlayerHolder *userHoler = globalModel->getUserHolder();
    CCLog("rank name %s",globalModel->getUserHolder()->getName()->getCString());
    CCLog("rank score %s",globalModel->getUserHolder()->getScore()->getCString());
    CCLog("rank cout %d",globalModel->getRankArray()->count());
//    dataArray->retain();
    CCObject *objcet = NULL;
    CCARRAY_FOREACH(globalModel->getRankArray(), objcet)
    {
        PlayerHolder *holder = (PlayerHolder *)objcet;
        this->myDataArr->addObject(holder);
        if (holder->getName()) {
            if(strcmp(holder->getName()->getCString(), userHoler->getName()->getCString()) == 0)
            {
                rank = globalModel->getRankArray()->indexOfObject(holder);
            }
        }
        
    }
    
}

#pragma mark
#pragma CCTableViewDelegate
/*
void RankListLayer::toExtensionsMainLayer(cocos2d::CCObject *sender)
{
    
}

 */


void RankListLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    //点击单元格时输出一个包含被点击单元格索引号的日志
//    CCLOG("cell touched at index: %i", cell->getIdx());
}

CCSize RankListLayer::cellSizeForTable(CCTableView *table)
{
    //设定单元格的大小
    return CCSizeMake(1200, 200);
}

CCTableViewCell* RankListLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    //在这里产生自定义的单元格及内容
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
//        CCLog("index %d",idx);
        cell = new CCTableViewCell();
        cell->autorelease();
        
        CCSprite *crownSprite = CCSprite::createWithSpriteFrameName(silverCrownImageName);
        crownSprite->setPosition(ccp(120, 10 + crownSprite->getContentSize().height / 2));
        crownSprite->setTag(CROWN_SPRITE_TAG);
        cell->addChild(crownSprite);
        
        CCLabelTTF *nameLabel = CCLabelTTF::create("小明", "Helvetica", 80);
        nameLabel->setPosition(ccp(450, 10 + nameLabel->getContentSize().height / 2));
        nameLabel->setTag(NAME_LABEL_TAG);
//        nameLabel->setColor()
        cell->addChild(nameLabel);
        
        CCLabelTTF *scoreLabel = CCLabelTTF::create("121212", "Markerfelt-Thin", 80);

//        CCLabelBMFont *scoreLabel = CCLabelBMFont::create("121212", "Markerfelt-Thin", 120);
        scoreLabel->setPosition(ccp(950, 10 + scoreLabel->getContentSize().height / 2));
        scoreLabel->setTag(SCORE_LABEL_TAG);
        cell->addChild(scoreLabel);
        
        CCLayer *sepectorLayer = CCLayerColor::create(ccc4(255, 255, 255, 255), 1150, 5);
        sepectorLayer->setPosition(ccp(0, 0));
        cell->addChild(sepectorLayer);
        
        crownSprite->retain();
        nameLabel->retain();
        scoreLabel->retain();
    }
    
    CCSprite *crownSprite = (CCSprite *)cell->getChildByTag(CROWN_SPRITE_TAG);
    CCLabelTTF *nameLabel = (CCLabelTTF *)cell->getChildByTag(NAME_LABEL_TAG);
    CCLabelTTF *scroeLabel = (CCLabelTTF *)cell->getChildByTag(SCORE_LABEL_TAG);
    
//    CCLabelBMFont *scroeLabel = (CCLabelBMFont *)cell->getChildByTag(SCORE_LABEL_TAG);
    if (idx < 3) {
        crownSprite->setVisible(true);
        CCSpriteFrame *frame;
        if (idx == 0) {
            frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(goldenCrownImageName);
            nameLabel->setColor(ccc3(245, 241, 98));
            scroeLabel->setColor(ccc3(245, 241, 98));
        }
        if (idx == 1) {
            frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(silverCrownImageName);
            nameLabel->setColor(ccc3(159, 155, 185));
            scroeLabel->setColor(ccc3(159, 155, 185));
        }
        if (idx == 2) {
            frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(cuprunCrownImageName);
            nameLabel->setColor(ccc3(178, 134, 72));
            scroeLabel->setColor(ccc3(178, 134, 72));
        }
//        CCSpriteFrame *frame = =CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("headleft.png");
        crownSprite->setDisplayFrame(frame);
    }else{
        crownSprite->setVisible(false);
        scroeLabel->setColor(ccc3(255, 255, 255));
        nameLabel->setColor(ccc3(255, 255, 255));
    }
    CCLog("index %d",idx);

    PlayerHolder *holder = (PlayerHolder *)this->myDataArr->objectAtIndex(idx);
    CCLog("name %s",holder->getName()->getCString());
    CCLog("score %s",holder->getScore()->getCString());
    nameLabel->setString(holder->getName()->getCString());
    scroeLabel->setString(holder->getScore()->getCString());
    
    
    return cell;
}

unsigned int RankListLayer::numberOfCellsInTableView(CCTableView *table)
{
    //返回了20个单元格
    int number = this->getMyDataArr()->count();
    return number;
}

void RankListLayer::rankReturnAction(CCScene *pObject)
{
    CCScene *menuScene = MenuScene::create();
    CCDirector::sharedDirector()->replaceScene(menuScene);
}
void RankListLayer::rankPlayAction(CCScene *pObject)
{
    CCScene *gameScene = GameScene::create(true);
    CCDirector::sharedDirector()->replaceScene(gameScene);
}
