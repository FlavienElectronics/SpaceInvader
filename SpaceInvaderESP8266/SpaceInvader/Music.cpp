#include "Music.h"

Music::Music(){ buzzerStartTime = 0; buzzerDuration = 0; buzzerActive = false; noteStartTime = 0; currentNote = 0; isPlaying = false; }
Music::~Music(){}

int Music::getSizeDuration(){ return 130; }

int Music::getDuration(int note){
  return durations[note];
}

int Music::getMelody(int note){
  return melody[note];
}

void Music::BUZZER_init(void){
  pinMode(BUZZER_PIN, OUTPUT);
  noTone(BUZZER_PIN);
}

void Music::BUZZER_Tone(int frequency, int duration){
  tone(BUZZER_PIN, frequency);
  buzzerStartTime = millis();           // Enregistre le temps de début
  buzzerDuration = duration;            // Enregistre la durée de fonctionnement
  buzzerActive = true;                  // Active l'état du buzzer pour indiquer qu'il est en cours
}

void Music::UPDATE_Buzzer(void){
  if (buzzerActive && (millis() - buzzerStartTime >= buzzerDuration)) {
    noTone(BUZZER_PIN);                 // Arrête le buzzer une fois la durée écoulée
    buzzerActive = false;               // Désactive l'état du buzzer
  }else if (buzzerActive){    // On s'occupe du son actif, il est plus important que la musique
    playMelody();
  }else{  // Si pas de son en cours, on joue la musique
    playMelody();
  }
}

// !!!!!!!!! MODIFIER LA METHODE POUR JOUER UN SOND PRIORITAIREMENT A LA MUSIQUE !

void Music::playMelody(void){
  //int melodySize = sizeof(myMusic.durations) / sizeof(int);
  int melodySize = getSizeDuration();
  int soundSize = 8;

  if (isPlaying == 2){
    if (millis() - noteStartTime_SOND >= 1000 / getDuration(currentNote_SOND) * 1.30) {
      noTone(BUZZER_PIN);         // Arrête la note actuelle
      isPlaying = 0;          // Indique que la note est terminée
      noteStartTime_SOND = millis();   // Réinitialise le temps pour la prochaine note
      currentNote_SOND++;              // Passe à la note suivante
    }
  }else if (isPlaying == 1) {
    if (millis() - noteStartTime >= 1000 / getDuration(currentNote) * 1.30) {
      noTone(BUZZER_PIN);         // Arrête la note actuelle
      isPlaying = 0;          // Indique que la note est terminée
      noteStartTime = millis();   // Réinitialise le temps pour la prochaine note
      currentNote++;              // Passe à la note suivante
    }
  }

  if (isPlaying == 0 && currentNote_SOND < soundSize) {
    int noteDuration = 1000 / getDuration(currentNote_SOND);
    tone(BUZZER_PIN, getMelody(currentNote_SOND), noteDuration);
    isPlaying = 2;
  }else if (isPlaying == 0 && currentNote < melodySize) {
    int noteDuration = 1000 / getDuration(currentNote);
    tone(BUZZER_PIN, getMelody(currentNote), noteDuration);
    isPlaying = 1;
  }

  if (currentNote_SOND >= soundSize) {
    currentNote_SOND = 0;
    isPlaying = 0;
    buzzerActive = false;
  }else if (currentNote >= melodySize) {
    currentNote = 0;
    isPlaying = 0;
  }
}