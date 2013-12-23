//
//  AudioManager.cpp
//  MMFighting
//
//  Created by yaodd on 13-11-26.
//
//

#include "AudioManager.h"
#include <cocos2d.h>
#include <SimpleAudioEngine.h>

static AudioManager *pAudioManager;

using namespace cocos2d;
using namespace CocosDenshion;

const char effect1[20] = "effect1.mp3";
const char effect2[20] = "effect2.mp3";
const char effect3[20] = "effect3.mp3";
const char effect4[20] = "effect4.mp3";
const char effect5[20] = "effect5.mp3";
const char effect6[20] = "effect6.mp3";
const char menuMusic[20] = "menuMusic.mp3";
const char gameMusic[20] = "gameMusic.mp3";
const char overMusic[20] = "overMusic.mp3";
const char specialEffect1[30] = "specialEffect1.amr";

AudioManager *AudioManager::sharedManager(){
    if (pAudioManager == NULL) {
        pAudioManager = new AudioManager();
        
    }
    return pAudioManager;
}
AudioManager::AudioManager()
{
    this->init();
}
AudioManager::~AudioManager()
{
    delete pAudioManager;
}

void AudioManager::init(){
    SimpleAudioEngine::sharedEngine()->preloadEffect(effect1);
    SimpleAudioEngine::sharedEngine()->preloadEffect(effect2);
    SimpleAudioEngine::sharedEngine()->preloadEffect(effect3);
    SimpleAudioEngine::sharedEngine()->preloadEffect(effect4);
    SimpleAudioEngine::sharedEngine()->preloadEffect(effect5);
    SimpleAudioEngine::sharedEngine()->preloadEffect(effect6);
    SimpleAudioEngine::sharedEngine()->preloadEffect(specialEffect1);
    
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(menuMusic);
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(gameMusic);
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(overMusic);
    
    effectIsOn = true;
    musicIsOn = true;
}
void AudioManager::playEffect(int i){
    if (!effectIsOn) {
        return;
    }
    CCString *string = CCString::createWithFormat("effect%d.mp3",i);
    const char *effect = string->getCString();
    SimpleAudioEngine::sharedEngine()->playEffect(effect, false);

}
void AudioManager::playSpecialEffect(int i){
    if (!effectIsOn) {
        SimpleAudioEngine::sharedEngine()->stopAllEffects();
    }
    CCString *string = CCString::createWithFormat("specialEffect%d.amr",i);
    const char *effect = string->getCString();
    SimpleAudioEngine::sharedEngine()->playEffect(effect, false);
}
void AudioManager::playGameMusic(){
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(gameMusic, true);
}
void AudioManager::playMenuMusic(){
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(menuMusic, true);
    
}
void AudioManager::playOverMusic(){
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(overMusic, true);
}
void AudioManager::pauseMusic(){
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}
void AudioManager::resumeMusic(){
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
//void AudioManager::pauseMenuMusic(){

//}