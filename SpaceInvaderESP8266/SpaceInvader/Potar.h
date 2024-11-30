/*********************************************************************
 * @file  Potar.h
 * @author LESPIAUCQ Denis & CARVALHO Flavien (4 AE SE 3)
 *********************************************************************/
#ifndef POTAR_H_
#define POTAR_H_

#include <Arduino.h>
#include "config.h"

class Potar{
public:
    int old_potar_value;

    Potar();
    ~Potar();

    void POTAR_init(void);
    float POTAR_Read(void);
};

#endif