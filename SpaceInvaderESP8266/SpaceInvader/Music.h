/*********************************************************************
 * @file  Music.h
 * @author LESPIAUCQ Denis & CARVALHO Flavien (4 AE SE 3)
 *********************************************************************/
#ifndef MUSIC_H_
#define MUSIC_H_

#include <Arduino.h>
#include "pitches.h"
#include "config.h"

class Music{
private:
static int melody[];
static int durations[];
static int melody_start[];
static int durations_start[];
public:
    // Paramètres de contrôle du buzzer en cas d'utilisation spécifique
    int buzzerStartTime;
    int buzzerDuration;
    bool buzzerActive;

    // Paramètres de contrôle de la note active pour la musique
    unsigned long noteStartTime;
    int currentNote;

    // Paramètres de contrôle de la note active pour l'effet sonore
    unsigned long noteStartTime_SOND;
    int currentNote_SOND;

    int isPlaying;      // 0 : aucune musique / 1 : musique / 2 : effet sonore

    // Constructeur & déstructeur de la classe MUSIC
    Music();
    ~Music();

    // Permet de retourner la durée d'une note spécifique pour la MUSIQUE ou L'EFFET SONORE
    int getDuration(int note, int PrincipalMusic);

    // Permet de retourner la note spécifique pour la MUSIQUE ou L'EFFET SONORE
    int getMelody(int note, int PrincipalMusic);

    // Fonction d'initialisation et de configuration du BUZZER
    void BUZZER_init(void);

    // Fonction permettant d'enclancher le buzzer à une fréquence et une durée spécifique
    void BUZZER_Tone(int frequency, int duration);

    // Fonction d'appel pour la mise à jour de l'état du buzzer (changement de note, extinction du buzzer, etc...)
    void UPDATE_Buzzer(void);

    // Fonction de gestion de la MUSIQUE et EFFET SONORE
    void playMelody(void);

    // Fonction permettant le démarrage de la musique
    void MelodyStart(void);
};

#endif