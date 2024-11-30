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