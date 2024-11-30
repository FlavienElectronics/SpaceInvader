/*********************************************************************
 * @file  config.h
 * @author LESPIAUCQ Denis & CARVALHO Flavien (4 AE SE 3)
 *********************************************************************/
#ifndef CONFIG_H_
#define CONFIG_H_

#define White 0
#define Red 1
#define Blue 2
#define Green 3
#define Cyan 4
#define Orange 5
#define Dark 6

#define BUZZER_PIN 12           //D6 = GPIO12 sur ESP8266
#define BUZZER_FREQ_MIN 300
#define BUZZER_FREQ_MAX 3200

#define LED_PIN 13
#define ON      1
#define OFF     0
#define TOGGLE  2

#define POTAR_PIN         A0
#define ADC_REF           3.3
#define POTAR_VCC         3.3
#define POTAR_FULL_ANGLE  300
#define ADC_RESOLUTION    1024

#define BUTTON_PIN  14

#define BAUDRATE  921600

#endif