/*********************************************************************
 * @file  Apllication.h
 * @author <mettre l'adresse mail ou nom prenom>
 * @brief Fichier header de l'application
 *********************************************************************/
#ifndef LED_H_
#define LED_H_

#include <Arduino.h>
#include "config.h"

class LED{
public:
    int led_state;

    LED();
    ~LED();

    void LED_init(void);
    void LED_Control(int ONOFF);
};

#endif