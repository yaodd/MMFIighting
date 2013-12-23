//
//  Dao.cpp
//  MMFighting
//
//  Created by yaodd on 13-12-25.
//
//

#include "Dao.h"
//#include "curl.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include <string.h>
#include <string>
#include "cocos-ext.h"
#include "Json.h"
#include "md5.h"
#include "GameOverLayer.h"
using namespace cocos2d;
using namespace extension;
using namespace std;

USING_NS_CC_EXT;

#define SALT    "welovecs"
#define BASE_URL    "http://222.200.191.17:8055/interface.php"

//#include "HttpRequest.h"
static Dao *pDao;
Dao::Dao()
{
    
}
Dao::~Dao()
{
    
}
Dao *Dao::sharedDao()
{
    if (pDao == NULL) {
        pDao = new Dao();
    }
    return pDao;
}
/**
 * @name request
 * @pam1 urlString：the url of the query's destination
 * @pam2 dict:to format the post array of the http .
 * @result return a NSDictionary contains the data what the protocol wo agree to.return nil 代表 联网失败。
 **/
CCDictionary *Dao::request(CCString *urlString, CCDictionary *dict)
{
    CCString *urlStr = CCString::createWithFormat("%s/%s",BASE_URL,urlString->getCString());
//    CCDictionary *response = CCDictionary::create();
    CCArray *arr = dict->allKeys();
    CCString *postDataStr = CCString::create("");
    for (int i = 0; i < dict->count(); i ++) {
        if (i > 0) {
            CCString *temp = CCString::create("&");
//            postDataStr = CCString::createWithFormat("%s")
        }
    }
//    unsigned int len;
    const char *score;
    CCHttpRequest *request = new CCHttpRequest();
    request->setUrl(urlStr->getCString());
    request->setRequestType(CCHttpRequest::kHttpPost);
    
    const char *error;
    CCHttpResponse *response = new CCHttpResponse(request);
    response->setErrorBuffer(error);
    
    CCHttpClient *client = CCHttpClient::getInstance();
    client->setTimeoutForConnect(3.0f);
    client->send(request);
    
}

void Dao::requestForUploadRecord(CCString *score, CCString *name)
{
    
    CCString *urlStr = CCString::createWithFormat("%s?mod=score&action=record",BASE_URL);
    unsigned char md5Output[16];
//    CCString *md5InputStr = CCString::createWithFormat("admin");
    CCString *md5InputStr = CCString::createWithFormat("%s%s%s",SALT,name->getCString(),score->getCString());
    unsigned char *md5Input = (unsigned char *)(const_cast<char *>(md5InputStr->getCString()));
    CCLog("%s",md5InputStr->getCString());
    this->MD5(md5Input, md5InputStr->length(), md5Output);
    char finalOutput[33];
    string temp;
    for (int i = 0; i < 16; i ++) {
        printf("%02x",md5Output[i]);
        char val[3] = {0};
        sprintf(val, "%02x",md5Output[i]);
        temp.append(string(val));
    }
    for (int i = 0; i < 32; i++) {
        finalOutput[i] = temp[i];
    }
    finalOutput[32] = '\0';
    printf("\n%s",finalOutput);
   
    
    CCString *postDataStr = CCString::createWithFormat("name=%s&score=%s&hash=%s",name->getCString(),score->getCString(),finalOutput);
    
    CCLog("postdatastr----->%s",postDataStr->getCString());
    CCHttpRequest* request = new CCHttpRequest();
    request->setUrl(urlStr->getCString());
    request->setRequestType(CCHttpRequest::kHttpPost);
    request->setRequestData(postDataStr->getCString(), postDataStr->length());
    request->setResponseCallback(targetObject, httpresponse_selector(GameOverLayer::onHttpRequestCompleted));
    request->setTag(RECORD_HTTP_TAG);
    CCHttpClient::getInstance()->send(request);
    request->release();
}
void Dao::requestForGetTop()
{
    CCString *urlStr = CCString::createWithFormat("%s?mod=score&action=top",BASE_URL);
    CCHttpRequest* request = new CCHttpRequest();
    request->setUrl(urlStr->getCString());
    request->setRequestType(CCHttpRequest::kHttpPost);
//    request->setRequestData(postDataStr->getCString(), postDataStr->length());
    request->setResponseCallback(targetObject, httpresponse_selector(GameOverLayer::onHttpRequestCompleted));
    request->setTag(TOP_HTTP_TAG);
    CCHttpClient::getInstance()->send(request);
    request->release();

}
void Dao::MD5(unsigned char *input,int inputLength, unsigned char* output)
{
    MD5_CTX ctx;
    MD5Init(&ctx);
    MD5Update(&ctx, input, inputLength);
    MD5Final(&ctx, output);
}