/*********************************************************************
 * @file  Apllication.h
 * @author <mettre l'adresse mail ou nom prenom>
 * @brief Fichier header de l'application
 *********************************************************************/
#ifndef LCD_H_
#define LCD_H_

#include <Arduino.h>
#include <iostream>
#include "config.h"
#include <Wire.h>
#include "rgb_lcd.h"

class LCD{
public:
    int old_score;

    LCD();
    ~LCD();
    
    void LCD_init(void);
    void LCD_Clear(void);
    void LCD_Print(const char* message, int x, int y, int color, bool cls);
    void LCD_Score(int score);
};

#endif