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

    Application();
    ~Application();

    void init(void);

    void run(void);

    void UTILITAIRE_Welcome(void);
    void UTILITAIRE_HardReset(void);

    void BUZZER_NextGrade(void);
};
#endif