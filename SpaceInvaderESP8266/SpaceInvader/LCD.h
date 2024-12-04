/*********************************************************************
 * @file  LCD.h
 * @author LESPIAUCQ Denis & CARVALHO Flavien (4 AE SE 3)
 *********************************************************************/
#ifndef LCD_H_
#define LCD_H_

#include <Arduino.h>
#include <iostream>
#include "config.h"
#include <Wire.h>
#include "rgb_lcd.h"
#include "LED.h"

class LCD{
public:
    int old_score;

    // Constructeur & déstructeur de la classe LCD
    LCD();
    ~LCD();
    
    // Fonction d'initailisation et de configuration de l'écran LCD
    void LCD_init(void);

    // Fonction permettant d'effacement de l'ensemble des données écrites sur l'écran LCD
    void LCD_Clear(void);

    // Fonction d'impression de caractères (message et (x,y) de centrage) ainsi que la possibilité de choisir la couleur de fond et de supprimer ou non l'encien texte
    void LCD_Print(const char* message, int x, int y, int color, bool cls);

    // Fonction d'impression du score avec niveau du joueur associé
    void LCD_Score(int score);
};

#endif