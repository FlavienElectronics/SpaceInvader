#ifndef MUSIC_H_
#define MUSIC_H_

#include <Arduino.h>
#include "pitches.h"
#include "config.h"

class Music{
private:
static int melody[];
static int durations[];
//static int melody_start[];
//static int durations_start[];
public:
    int buzzerStartTime;
    int buzzerDuration;
    bool buzzerActive;

    unsigned long noteStartTime;
    int currentNote;
    int isPlaying;      // 0 : aucune musique / 1 : musique / 2 : soun

    unsigned long noteStartTime_SOND;
    int currentNote_SOND;

    Music();
    ~Music();

    int getSizeDuration(void);
    int getDuration(int note);
    int getMelody(int note);
    void BUZZER_init(void);
    void BUZZER_Tone(int frequency, int duration);
    void UPDATE_Buzzer(void);
    void playMelody(void);
};

#endif