/*********************************************************************
 * @file  Apllication.h
 * @author <mettre l'adresse mail ou nom prenom>
 * @brief Fichier header de l'application
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