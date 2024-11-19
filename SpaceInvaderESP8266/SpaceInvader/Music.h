#ifndef MUSIC_H_
#define MUSIC_H_

#include "pitches.h"

class Music{
private:
static int melody[];
static int durations[];
public:
    Music();
    ~Music();

    int getSizeDuration(void);
    int getDuration(int note);
    int getMelody(int note);
};

#endif