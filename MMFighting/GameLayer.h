//
//  GameLayer.h
//  MMFighting
//
//  Created by yaodd on 13-10-22.
//
//

#ifndef __MMFighting__GameLayer__
#define __MMFighting__GameLayer__

#include <cocos2d.h>
#include "CCJoystick.h"
#include "PlayerSprite.h"
#include "EnemySprite.h"
#include "AudioManager.h"
#include "UiLayer.h"
//#include "GameScene.h"



using namespace cocos2d;

class GameLayerDelegate{
public:
//    virtual ~ GameLayerDelegate(){};
    virtual void updateHp(float hurt) = 0;
    virtual void updateScore(int score) = 0;
    virtual void decreaseHeart() = 0;
    virtual void initPlayerHeart(int hearts) = 0;
};

class GameLayer : public CCLayer, public CCJoyStickDelegate, PlayerSpriteDelegate,EnemySpriteDelegate
{
public:
    GameLayer();
    GameLayer(bool isNew,GameLayerDelegate *delegate);
    ~GameLayer();
    
    AudioManager *audioManager;
    
    GameLayerDelegate *delegate;
    
    virtual bool init();
    CREATE_FUNC(GameLayer);
    
    void onCCJoyStickUpdate(CCNode *sender, float angle, CCPoint direction, float power);
    void onCCJoyStickActivated(CCNode* sender);
    void onCCJoyStickDeactivated(CCNode* sender);
    
    void update(float dt);      //游戏主要动作在里面进行
    
    void updateEnemys(float dt);//更新敌人
    
    void updatePositions(float dt);//更新精灵位置
    
    CCJoystick *joyStick;       //遥感
    CCSize winSize;             //设备窗口大小
    PlayerSprite *playerSprite; //主角
    CCSprite *healthSprite;     //生命补给

    
    
    void handAction(CCObject *pScene);  //普通攻击
    void footAction(CCObject *pScene);  //大招
    
    CC_SYNTHESIZE_RETAIN(CCArray*, _enemys, Enemys);    //存放敌人的数组
    CCSpriteBatchNode *_actors;                         //存放所有火柴人的数组
    static GameLayer *create(bool isNew, GameLayerDelegate *delegate);
    void addEnemys(int number);                         //添加一个敌人
    
    void initEffects();
    
    void playEffect(int i);
    
    int getHurtWithSprite(PlayerSprite *attackSprite, EnemySprite *beHitSprite);    //敌人伤害计算
    int getHurtWithSprite(EnemySprite *attackSprite, PlayerSprite *beHitSprite);    //主角伤害计算
    
    int score;                               //分数
    int killNumber;                         //杀人数，暂时不用
    
    virtual void gameOver(void);            //游戏结束
    virtual void updatePlayHP(float value); //跟新血条
    virtual void EnemySpriteBeKilled();     //敌人被杀死
    void addHealthSprite();                 //添加一个生命补给
    
    int timeIndex;                          //时间急速器
    
    void saveData();                        //保存游戏数据
    void loadData();                        //加载游戏数据
    void clearData();                       //清空游戏数据
    
//    CCPointArray *enemyPointArr;            
    
    CCArray *initEnemyArr;                  //上次游戏的敌人数据
    int initScore;                          //上次游戏分数
    int initHealth;                         //上次游戏主角生命值
    CCPoint initPoint;                      //上次游戏主角位置
    int initTimeIndex;                      //上次游戏时间计数器
    int initLife;                           //上次游戏主角生命数量
    
    void initEnemy();                       //初始化敌人，主要是为继续游戏设置
    bool isNew;                             //是否为新游戏
    
    void pauseMenu();                       //暂停
    void resumeMenu();                      //回复
    CCMenu *hitMenu;                        //攻击按钮菜单
    
    int aliveEnemy;
    
    
//    void onCCJoyStickUpdate(CCNode *sender, float angle, CCPoint direction, float power);
};

#endif /* defined(__MMFighting__GameLayer__) */
