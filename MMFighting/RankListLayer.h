//
//  RankListLayer.h
//  MMFighting
//
//  Created by yaodd on 13-12-26.
//
//  排行榜界面

#ifndef __MMFighting__RankListLayer__
#define __MMFighting__RankListLayer__

#include <iostream>
#include <cocos2d.h>
#include "cocos-ext.h"
USING_NS_CC_EXT;
using namespace cocos2d;
using namespace extension;

class RankListLayer : public CCLayer , public CCTableViewDataSource , public CCTableViewDelegate
{
public:
    
    RankListLayer();
    ~RankListLayer();
    
    virtual bool init();
    
    CREATE_FUNC(RankListLayer);
    
    CCSize winSize;     //设备窗口尺寸
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    //单元格点击事件
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    //单元格尺寸设定
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    //单元格索引
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    //单元格数量设定
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    
//    CCArray *dataArray;
    CC_SYNTHESIZE(CCArray *, myDataArr, MyDataArr);
    
    int rank;           //当前游戏玩家排名
    
    void initData();    //初始化排行榜数据
    
    void rankReturnAction(CCScene *pObject);        //返回到主菜单
    void rankPlayAction(CCScene *pObject);          //重新开始游戏
};

#endif /* defined(__MMFighting__RankListLayer__) */
