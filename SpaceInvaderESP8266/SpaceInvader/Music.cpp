#include "Music.h"

Music::Music(){ buzzerStartTime = 0; buzzerDuration = 0; buzzerActive = false; noteStartTime = 0; currentNote = 0; isPlaying = false; noteStartTime_SOND = 0; currentNote_SOND = 0; }
Music::~Music(){}

int Music::getDuration(int note, int PrincipalMusic){
  if (PrincipalMusic == 0){
    return durations[note];
  }else{
    return durations_start[note];
  }
}

int Music::getMelody(int note, int PrincipalMusic){
  if (PrincipalMusic == 0){
    return melody[note];
  }else{
    return melody_start[note];
  }
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
  }else{
    playMelody();
  }
}

void Music::MelodyStart(void){
  isPlaying == 0;
  currentNote_SOND = 0;
}

void Music::playMelody(void){
  int melodySize = 130;
  int soundSize = 5;

  if (isPlaying == 2) {
    if (millis() - noteStartTime_SOND >= 1000 / getDuration(currentNote_SOND, 1) * 1.30){
      noTone(BUZZER_PIN);         // Arrête la note actuelle
      isPlaying = 0;      // Indique que la note est terminée
      noteStartTime_SOND = millis();   // Réinitialise le temps pour la prochaine note
      currentNote_SOND++;              // Passe à la note sui
    }
  }else if (isPlaying == 1){
    if (millis() - noteStartTime >= 1000 / getDuration(currentNote, 0) * 1.30){
      noTone(BUZZER_PIN);         // Arrête la note actuelle
      isPlaying = 0;          // Indique que la note est terminée
      noteStartTime = millis();   // Réinitialise le temps pour la prochaine note
      currentNote++;              // Passe à la note suivante
    }
  }

  if (isPlaying == 0 && currentNote_SOND < soundSize && currentNote_SOND != -1) {
    int noteDuration = 1000 / getDuration(currentNote_SOND, 1);
    tone(BUZZER_PIN, getMelody(currentNote_SOND, 1), noteDuration);
    isPlaying = 2;
  }else if (isPlaying == 0 && currentNote < melodySize) {
    int noteDuration = 1000 / getDuration(currentNote, 0);
    tone(BUZZER_PIN, getMelody(currentNote, 0), noteDuration);
    isPlaying = 1;
  }

  if (currentNote_SOND >= soundSize) {
    isPlaying = 0;
    currentNote_SOND = -1;
    currentNote = 0;
  }else if (currentNote >= melodySize) {
    currentNote = 0;
    isPlaying = 0;
  }
}