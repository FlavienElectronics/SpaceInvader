/*********************************************************************
 * @file  Apllication.h
 * @author <mettre l'adresse mail ou nom prenom>
 * @brief Fichier header de l'application
 *********************************************************************/
#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <Arduino.h>
#include <string>
#include <iostream>
#include <Wire.h>
#include "rgb_lcd.h"
#include "Music.h"
//#include "pitches.h"

#define RED 1
#define BLU 2
#define GRN 3

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

using namespace std;

class Application
{
  public :

    Application();
    ~Application();

    void init(void);

    void run(void);

    void LCD_init(void);
    void LCD_Print(const char* message, int x, int y, int color);
    void LCD_Score(int score);
    void LCD_Clear(void);

    void BUZZER_init(void);
    void BUZZER_Tone(int frequency, int _delay);
    void UPDATE_Buzzer(void);
    void playMelody(void);

    void LED_init(void);
    void LED_Control(int ONOFF);
    void LCD_Welcome(void);

    void UART_init(void);
    void UART_Send(const char* message);
    String UART_Read(void);

    void POTAR_init(void);
    float POTAR_Read(void);

    void BUTTON_init(void);
    int BUTTON_Read(void);

    String UTILITAIRE_ExtractCommand(const String &message);
    String UTILITAIRE_ExtractValue(const String &message);
    void HardReset(void);

    void BUZZER_NextGrade(void);
};
#endif