#include "Bouton.h"

Bouton::Bouton(){}
Bouton::~Bouton(){}

void Bouton::BUTTON_init(void){
  pinMode(BUTTON_PIN, INPUT);
}

int Bouton::BUTTON_Read(void){
  return digitalRead(BUTTON_PIN);
}