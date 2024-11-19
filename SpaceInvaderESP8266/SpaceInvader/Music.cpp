#include "Music.h"

Music::Music(){}
Music::~Music(){}

int Music::getSizeDuration(){ return 130; }
int Music::getDuration(int note){
  return durations[note];
}
int Music::getMelody(int note){
  return melody[note];
}