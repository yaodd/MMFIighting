//
//  Dao.h
//  MMFighting
//
//  Created by yaodd on 13-12-25.
//
//

#ifndef __MMFighting__Dao__
#define __MMFighting__Dao__

#include <iostream>
#include <cocos2d.h>
#include <HttpClient.h>

#define RECORD_HTTP_TAG     "record"
#define TOP_HTTP_TAG        "top"


using namespace cocos2d;
using namespace extension;
class Dao : public CCObject
{
private:
    CCDictionary *request(CCString *urlString, CCDictionary *dict);
public:
    Dao();
    ~Dao();
    
    static Dao *sharedDao();
//    void onHttpRequestCompleted(CCHttpClient* client, CCHttpResponse* response);
    void MD5(unsigned char* input,int inputLength, unsigned char* output);
    void requestForUploadRecord(CCString *score,CCString *name);
    void requestForGetTop();
    CCObject *targetObject;

};

#endif /* defined(__MMFighting__Dao__) */
