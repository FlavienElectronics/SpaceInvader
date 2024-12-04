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
    //Constructeur & déstructeur de la classe BOUTON
    Bouton();
    ~Bouton();

    // Initilisation de la broche du bouton en tant qu'entrée numérique
    void BUTTON_init(void);

    // Permet de retourner l'état actif du bouton
    int BUTTON_Read(void);
};

#endif