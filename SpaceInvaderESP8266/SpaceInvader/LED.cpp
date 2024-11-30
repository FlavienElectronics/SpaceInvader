#include "LED.h"

LED::LED(){ led_state = OFF; };
LED::~LED(){}

void LED::LED_init(void){
  pinMode(LED_PIN, OUTPUT);
  LED_Control(OFF);
}

void LED::LED_Control(int ONOFF){
  if (ONOFF == OFF){
    digitalWrite(LED_PIN, LOW);
    led_state = OFF;
  }else if (ONOFF == ON){
    digitalWrite(LED_PIN, HIGH);
    led_state = ON;
  }else if (ONOFF == TOGGLE){
    if (led_state == ON){
      LED_Control(OFF);
    }else{
      LED_Control(ON);
    }
  }
}