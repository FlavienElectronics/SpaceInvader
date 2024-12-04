/*********************************************************************
 * @file  LED.h
 * @author LESPIAUCQ Denis & CARVALHO Flavien (4 AE SE 3)
 *********************************************************************/
#ifndef LED_H_
#define LED_H_

#include <Arduino.h>
#include "config.h"

class LED{
public:
    int led_state;

    // Constructeur & déstructeur de la classe LED
    LED();
    ~LED();

    // Fonction d'initilisation de la LED
    void LED_init(void);

    // Fonction permettant le contrôle de la LED (ON, OFF ou TOGGLE)
    void LED_Control(int ONOFF);
};

#endif