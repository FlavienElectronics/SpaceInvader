/*********************************************************************
 * @file  Utilitaires.h
 * @author LESPIAUCQ Denis & CARVALHO Flavien (4 AE SE 3)
 *********************************************************************/
#ifndef UTILITAIRES_H_
#define UTILITAIRES_H_

#include <Arduino.h>
#include <iostream>
#include "config.h"

class Utilitaires{
public:
    Utilitaires();
    ~Utilitaires();

    String UTILITAIRE_ExtractCommand(const String &message);
    String UTILITAIRE_ExtractValue(const String &message);
};

#endif