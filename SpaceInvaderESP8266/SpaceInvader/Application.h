/*********************************************************************
 * @file  Apllication.h
 * @author LESPIAUCQ Denis & CARVALHO Flavien (4 AE SE 3)
 *********************************************************************/
#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <Arduino.h>
#include <string>
#include <iostream>
#include "Music.h"
#include "Potar.h"
#include "UART.h"
#include "LCD.h"
#include "LED.h"
#include "Bouton.h"
#include "Utilitaires.h"

#include "config.h"

using namespace std;

class Application
{
  private:
	int First_Start;
	
  public :
    //Constructeur & déstructeur de la classe APPLICATION
    Application();
    ~Application();

    // Permet d'initialiser l'ensemble des constructeurs des classes utiles
    void init(void);

    // Fonction principale d'exécution du programme
    void run(void);

    // Fonction utilitaire permettant l'affichage de l'écran de bienvenue et le démarrage du jeu
    void UTILITAIRE_Welcome(void);

    // Fonction permettant le RESET complet des paramètres
    void UTILITAIRE_HardReset(void);
};
#endif