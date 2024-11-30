/*********************************************************************
 * @file  Bouton.h
 * @author LESPIAUCQ Denis & CARVALHO Flavien (4 AE SE 3)
 *********************************************************************/
#ifndef BOUTON_H_
#define BOUTON_H_

#include <Arduino.h>
#include "config.h"

class Bouton{
public:
    Bouton();
    ~Bouton();

    void BUTTON_init(void);
    int BUTTON_Read(void);
};

#endif