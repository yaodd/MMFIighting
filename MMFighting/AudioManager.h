//
//  AudioManager.h
//  MMFighting
//
//  Created by yaodd on 13-11-26.
//
//

#ifndef __MMFighting__AudioManager__
#define __MMFighting__AudioManager__

#include <iostream>

class AudioManager
{
public:
    static AudioManager *sharedManager();
    
    bool effectIsOn;
    bool musicIsOn;
    
    AudioManager();
    ~AudioManager();
    
    void init();
    
    void playEffect(int i);
    void playSpecialEffect(int i);
    void playMenuMusic();
    void playGameMusic();
    void playOverMusic();
    void pauseMusic();
    void resumeMusic();
//    void pauseGameMusic();
};

#endif /* defined(__MMFighting__AudioManager__) */
