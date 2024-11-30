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

    LED();
    ~LED();

    void LED_init(void);
    void LED_Control(int ONOFF);
};

#endif