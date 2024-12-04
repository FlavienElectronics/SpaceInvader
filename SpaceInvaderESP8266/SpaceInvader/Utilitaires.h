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
    // Constructeur & déstructeur de la classe UTILITAIRES
    Utilitaires();
    ~Utilitaires();

    // Fonction permettant de retourner la commande envoyée depuis le PC
    String UTILITAIRE_ExtractCommand(const String &message);

    // Fonction permettant d'extraire la valeur associée à la commande
    String UTILITAIRE_ExtractValue(const String &message);
};

#endif