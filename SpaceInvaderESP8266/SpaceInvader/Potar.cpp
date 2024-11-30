#include "Potar.h"

Potar::Potar(){ old_potar_value = -1; }
Potar::~Potar(){};

void Potar::POTAR_init(void){
  pinMode(POTAR_PIN, INPUT);
}

float Potar::POTAR_Read(void){
  float voltage;
  int sensor_value = analogRead(POTAR_PIN);
  voltage = (float)sensor_value*ADC_REF/(ADC_RESOLUTION - 1);
  float degrees = (voltage*POTAR_FULL_ANGLE)/POTAR_VCC;
  return degrees;
}