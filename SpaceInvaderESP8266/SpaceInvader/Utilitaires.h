/*********************************************************************
 * @file  Apllication.h
 * @author <mettre l'adresse mail ou nom prenom>
 * @brief Fichier header de l'application
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