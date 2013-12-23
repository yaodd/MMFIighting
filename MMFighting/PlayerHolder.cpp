//
//  PlayerHolder.cpp
//  MMFighting
//
//  Created by yaodd on 13-12-26.
//
//

#include "PlayerHolder.h"

PlayerHolder::PlayerHolder()
{
    this->name = CCString::create("");
    this->score = CCString::create("");
}
PlayerHolder::~PlayerHolder(){
    
}
void PlayerHolder::setName(CCString *_name)
{
    //自己写的set函数一定要写release再retain，否则会被释放
    this->name->release();
    this->name = _name;
    this->name->retain();
}
void PlayerHolder::setScore(CCString *_score)
{
    this->score->release();
    this->score = _score;
    this->score->retain();
}
CCString *PlayerHolder::getName(){
    return this->name;
}
CCString *PlayerHolder::getScore()
{
    return this->score;
}