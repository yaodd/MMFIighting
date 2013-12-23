//
//  GameOverLayer.cpp
//  MMFighting
//
//  Created by yaodd on 13-12-17.
//
//

#include "GameOverLayer.h"
#include "GameScene.h"
#include "MenuScene.h"
#include <string>
#include <Json.h>
#include "Dao.h"
#include "GlobalModel.h"
#include "RankListScene.h"

using namespace std;
const char bgImageName[20] = "backgroundOver.png";
const char enterImageName1[20] = "Enter1.png";
const char enterImageName2[20] = "Enter2.png";
const char playImageName1[20] = "GamePLAY1.png";
const char playImageName2[20] = "GamePLAY2.png";
const char returnImageName1[20] = "Return1.png";
const char returnImageName2[20] = "Return2.png";
const char gameoverPlistName[30] = "GameOver.plist";
const char scoreBgImageName[20] = "scoreBackgr.png";


const string digStr = ":123456789";

GameOverLayer::GameOverLayer()
{
    this->init();
}

GameOverLayer::~GameOverLayer()
{
    
}
GameOverLayer::GameOverLayer(int score)
{
    this->score = score;
    this->init();
}
GameOverLayer *GameOverLayer::create(int _score)
{
    GameOverLayer *pRet = new GameOverLayer(_score);
    
    return pRet;
}
//int转string函数
string intToStrOver(int a);
//生成一个抛物线动画
void moveWithParabola(CCNode *mSprite, CCPoint startPoint, CCPoint endPoint ,float time);
CCFiniteTimeAction *createOverMenuItemAction(float delay,float duration);

bool GameOverLayer::init()
{
    bool pRet = false;
    do {
        CCLOG("score %d",score);
        this->setTouchEnabled(true);
        
        winSize = CCDirector::sharedDirector()->getWinSize();
        CCSprite *background = CCSprite::createWithSpriteFrameName(bgImageName);
        background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        background->setOpacity(0);
        CCActionInterval *fade = CCFadeIn::create(0.5);
        background->runAction(fade);
        
        this->addChild(background,0);
        
        CCSprite *playNor = CCSprite::createWithSpriteFrameName(playImageName1);
        CCSprite *playPre = CCSprite::createWithSpriteFrameName(playImageName2);
        CCMenuItemSprite *playItem = CCMenuItemSprite::create(playNor, playPre, this, menu_selector(GameOverLayer::playAction));
        CCFiniteTimeAction *playSeq = createOverMenuItemAction(0.5, 0.5);
        playItem->runAction(playSeq);
        
        CCSprite *returnNor = CCSprite::createWithSpriteFrameName(returnImageName1);
        CCSprite *returnPre = CCSprite::createWithSpriteFrameName(returnImageName2);
        CCMenuItemSprite *returnItem = CCMenuItemSprite::create(returnNor, returnPre, this, menu_selector(GameOverLayer::returnAction));
        CCFiniteTimeAction *returnSeq = createOverMenuItemAction(0.25, 0.5);
        returnItem->runAction(returnSeq);
        
        CCSprite *enterNor = CCSprite::createWithSpriteFrameName(enterImageName1);
        CCSprite *enterPre = CCSprite::createWithSpriteFrameName(enterImageName2);
        enterItem = CCMenuItemSprite::create(enterNor, enterPre, this, menu_selector(GameOverLayer::enterAction));
        CCFiniteTimeAction *enterSeq = createOverMenuItemAction(0.0, 0.5);
        enterItem->runAction(enterSeq);
        
        
        CCMenu *mainMenu = CCMenu::create(enterItem,returnItem,playItem,NULL);
        mainMenu->alignItemsHorizontallyWithPadding(30);
        mainMenu->setPosition(winSize.width + 200, winSize.height / 3 + 20);
        this->addChild(mainMenu);
        float layerWidth = 425.0f;
        float layerHeight = 150.0f;
        CCLayer *scoreLayer = CCLayerColor::create(ccc4(123, 123, 123, 0), layerWidth, layerHeight);
        scoreLayer->setPosition(ccp(0 - layerWidth / 2, winSize.height / 2 + 200));
        this->addChild(scoreLayer);

        CCSprite *scoreBg = CCSprite::createWithSpriteFrameName(scoreBgImageName);
        scoreBg->setPosition(ccp(layerWidth / 2, layerHeight / 2));
        scoreLayer->addChild(scoreBg);
        
        const char *arr = intToStrOver(score).c_str();
        CCLabelAtlas *scoreLabel = CCLabelAtlas::create(arr, "digit.png", 112, 200, '1');
        scoreLabel->setPosition(ccp((layerWidth - scoreLabel->getContentSize().width) / 2, (layerHeight - scoreLabel->getContentSize().height) / 2));
        scoreLayer->addChild(scoreLabel);
        
        CCActionInterval *move = CCMoveTo::create(1.0, ccp(winSize.width / 2 - 140, winSize.height / 2 + 180));
        CCActionInterval *out = CCEaseBounceOut::create(move);
        scoreLayer->runAction(out);
        
        
        nameTTF = CCTextFieldTTF::textFieldWithPlaceHolder("请输入您的大名...", "Helvetica", 70);
        nameTTF->setDelegate(this);
        nameTTF->setPosition(ccp(winSize.width / 2 - 100, winSize.height / 3 + 180));
        nameTTF->setColor(ccc3(0, 0, 0));
        nameTTF->setColorSpaceHolder(ccc3(52, 52, 52));
        
        this->addChild(nameTTF);
    
        pRet = true;
    } while (0);
    
    return pRet;
}
string intToStrOver(int a)
{
    string str = "";
    do {
        int b = a % 10;
        str += digStr[b];
        a /= 10;
        
    } while (a != 0);
    for (int i = 0 ,k = str.length() - 1; i < str.length() / 2; i ++, k --) {
        char temp = str[i];
        str[i] = str[k];
        str[k] = temp;
    }
    return str;
}

//创建一个移动动画
CCFiniteTimeAction *createOverMenuItemAction(float delay,float duration)
{
    CCActionInterval *move = CCMoveBy::create(duration, ccp(-270 * 3 - 160, 0));
    CCActionInterval *out = CCEaseElasticOut::create(move,1);
    CCActionInterval *delayTime = CCDelayTime::create(delay);
    CCFiniteTimeAction *seq = CCSequence::create(delayTime,out,NULL);
    
    return seq;
}

//  抛物线    -Himi
//mSprite：需要做抛物线的精灵
//startPoint:起始位置
//endPoint:中止位置
//dirTime:起始位置到中止位置的所需时间
void moveWithParabola(CCNode *mSprite, CCPoint startPoint, CCPoint endPoint ,float time)
{
    float sx = startPoint.x;
    float sy = startPoint.y;
    float ex =endPoint.x+50;
    float ey =endPoint.y+150;
    int h = mSprite->getContentSize().height*0.5;
    ccBezierConfig bezier; // 创建贝塞尔曲线
    bezier.controlPoint_1 = ccp(sx, sy); // 起始点
    bezier.controlPoint_2 = ccp(sx+(ex-sx)*0.5, sy+(ey-sy)*0.5+200); //控制点
    bezier.endPosition = ccp(endPoint.x-30, endPoint.y+h); // 结束位置
//    CCBezierTo *actionMove = [CCBezierTo actionWithDuration:time bezier:bezier];
    CCBezierTo *actionMove = CCBezierTo::create(time, bezier);
    CCEaseElasticOut *out = CCEaseElasticOut::create(actionMove,1);
//    CCEaseExponentialOut *out = CCEaseExponentialOut::create(actionMove);
//    CCEaseBounceOut *out = CCEaseBounceOut::create(actionMove);
//    [mSprite runAction:actionMove];
    mSprite->runAction(out);
}
void GameOverLayer::playAction(CCObject *pScene){
    CCScene *gameScene = GameScene::create();
    CCDirector::sharedDirector()->replaceScene(gameScene);
}
void GameOverLayer::enterAction(CCObject *pScene){
//    CCScene *menuScene = MenuScene::create();
//    CCDirector::sharedDirector()->replaceScene(menuScene);
    if (strlen(nameTTF->getString()) != 0) {
        enterItem->setEnabled(false);
        Dao::sharedDao()->targetObject = this;
        Dao::sharedDao()->requestForUploadRecord(CCString::createWithFormat("%d",score), CCString::create(nameTTF->getString()));
    }
   
}
void GameOverLayer::returnAction(CCObject *pScene){
    CCScene *menuScene = MenuScene::create();
    CCDirector::sharedDirector()->replaceScene(menuScene);
}

//当用户启动虚拟键盘时的回调函数
bool GameOverLayer::onTextFieldAttachWithIME(CCTextFieldTTF *pSender)
{
    CCLOG("启动输入");

    return false;
    //return true:不启动
}
//当用户关闭虚拟键盘时的回调函数
bool GameOverLayer::onTextFieldDetachWithIME(CCTextFieldTTF *pSender)
{
    CCLOG("关闭输入");
    this->setPositionY(0);
    return false;
    //return true:不关闭
}

int lengthOfText(const char *text)
{
    int length = 0;
    for (int i = 0 ; i < strlen(text); i ++) {
        if (text[i] < 0) {
            length += 1;
            i++;
            continue;
        }
        else{
            length += 1;
        }
    }
    return length;
}

//当用户进行输入时的回调函数
bool GameOverLayer::onTextFieldInsertText(CCTextFieldTTF *pSender,const char *text,int nLen)
{
    CCString *textStr = CCString::createWithFormat("%s%s",pSender->getString(),text);
    int length = lengthOfText(textStr->getCString());
//    CCLOG("输入字符... %d",nLen);
    CCLog("%d",length);
    if (length > 10) {
        return true;
    }
    return false;
//    return true;//不会输入进字符
    
}
//当用户删除文字时的回调函数
bool GameOverLayer::onTextFieldDeleteBackward(CCTextFieldTTF *pSender,const char *delText,int nLen)
{
    CCLOG("删除字符");
    return false;
    //return true:不删除
}
void GameOverLayer::ccTouchesBegan(CCSet *pSet, CCEvent *pEvent){
    CCTouch *pTouch = (CCTouch *)pSet->anyObject();
    CCPoint location = pTouch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    if (nameTTF->boundingBox().containsPoint(location)) {
        nameTTF->attachWithIME();
        
    }else{
        nameTTF->detachWithIME();
    }

}
void GameOverLayer::ccTouchesMoved(CCSet *pSet, CCEvent *pEvent){
    
}
void GameOverLayer::ccTouchesCancelled(CCSet *pSet, CCEvent *pEvent){
    
}
void GameOverLayer::ccTouchesEnded(CCSet *pSet, CCEvent *pEvent){
    
}

void GameOverLayer::keyboardWillHide(CCIMEKeyboardNotificationInfo &info)
{
    CCActionInterval *moveTo = CCMoveTo::create(0.2, ccp(0, 0));
    this->runAction(moveTo);
}
void GameOverLayer::keyboardWillShow(CCIMEKeyboardNotificationInfo &info)
{
    CCActionInterval *moveTo = CCMoveTo::create(0.2, ccp(0, 300));
    this->runAction(moveTo);
}

void GameOverLayer::onRecordRequestCompleted(CCHttpClient* client, CCHttpResponse* response)
{
    
}
//提交分数的回调函数
void GameOverLayer::onHttpRequestCompleted(CCHttpClient* client, CCHttpResponse* response)
{
    if (!response)
    {
        return;
    }
    int s=response->getHttpRequest()->getRequestType();
    CCLog("request type %d",s);
    
    const char *tag;
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        tag = response->getHttpRequest()->getTag();
        CCLog("%s ------>oked", response->getHttpRequest()->getTag());
    }
    
    int statusCode = response->getResponseCode();
    CCLog("response code: %d", statusCode);
    
    
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    CCLog(statusString);
    
    if (!response->isSucceed())
    {
        CCLog("response failed");
        CCLog("error buffer: %s", response->getErrorBuffer());
        return;
    }
    
    std::vector<char> *buffer = response->getResponseData();
    printf("Http Test, dump data: ");
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        //        CCLog("%c", (*buffer)[i]);//这里打印从服务器返回的数据
        printf("%c",(*buffer)[i]);
        
    }
    printf("\n");
    
    string str = string(buffer->begin(),buffer->end());
    Json *json = Json_create(str.c_str());
    
    
//    Json *jsonSuccess = Json_getItem(json, "success");
    int success = Json_getInt(json, "success", 0);
    if (success == 0) {
        
        return;
    }else{
        if (!strcmp(tag, RECORD_HTTP_TAG)) {
            CCLog("上传成功");
            Dao::sharedDao()->requestForGetTop();
        }
        else if (!strcmp(tag, TOP_HTTP_TAG)){
            CCLog("下载成功");
            //将数据保存在一个单例中，以便排行榜界面使用
            GlobalModel *globalModel = GlobalModel::sharedGlobalModel();
            PlayerHolder *userHolder = new PlayerHolder();
            userHolder->setName(CCString::create(nameTTF->getString()));
            userHolder->setScore(CCString::createWithFormat("%d",score));
            globalModel->setUserHolder(userHolder);
//            userHolder->release();
            
            CCArray *rankArray = CCArray::createWithCapacity(10);
            //Json解析
            Json *jsonData = Json_getItem(json, "data");
            int len = Json_getSize(jsonData);
            for (int i = 0 ; i < len; i ++) {
                PlayerHolder *holder = new PlayerHolder();
                Json *jsonChild = Json_getItemAt(jsonData, i);
                CCString *nameStr = CCString::create(Json_getString(jsonChild, "name", "n"));
                CCString *scoreStr = CCString::create(Json_getString(jsonChild, "score", "s"));
                holder->setName(nameStr);
                holder->setScore(scoreStr);
                rankArray->addObject(holder);
                CCLog("%s",Json_getString(jsonChild, "name", "n"));
                CCLog("%s",Json_getString(jsonChild, "score", "s"));
            }
            globalModel->setRankArray(rankArray);
//            rankArray->release();
            enterItem->setEnabled(true);
            CCScene *rankListScene = RankListScene::create();
            CCDirector::sharedDirector()->replaceScene(rankListScene);//跳转到排行榜界面
        }
    }
    

}