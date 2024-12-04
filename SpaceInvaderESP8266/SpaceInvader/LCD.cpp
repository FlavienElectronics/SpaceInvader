#include "LCD.h"

rgb_lcd LCD_RGB;
LED MyLED;

LCD::LCD(){ old_score = -1; MyLED.LED_Control(OFF); };
LCD::~LCD(){};

void LCD::LCD_init(void)
{
  LCD_RGB.begin(16, 2);         // LCD 2 lignes, 16 caractères
  LCD_RGB.setRGB(10, 10, 10);   // Fond blanc
  LCD_RGB.setCursor(0, 0);
}

void LCD::LCD_Clear(void){
  LCD_RGB.setCursor(0,0);
  LCD_RGB.print("                ");
  LCD_RGB.setCursor(0,1);
  LCD_RGB.print("                ");
}

void LCD::LCD_Print(const char* message, int x, int y, int color, bool cls)
{
  if (cls == true){ LCD_Clear(); }
  if (color == Red){
    LCD_RGB.setRGB(250, 0, 0);  // Fond Rouge
  }else if (color == Blue){
    LCD_RGB.setRGB(0, 0, 250);  // Fond Bleu
  }else if (color == White){
    LCD_RGB.setRGB(250, 250, 250);  // Fond Blanc
  }else if (color == Green){
    LCD_RGB.setRGB(0, 250, 0);  // Fond Vert
  }else if (color == Cyan){
    LCD_RGB.setRGB(43, 255, 255);  // Fond Cyan
  }else if (color == Orange){
    LCD_RGB.setRGB(250, 128, 0);  // Fond Orange
  }else if (color == Dark){
    LCD_RGB.setRGB(15, 15, 15);  // Fond sombre
  }
  LCD_RGB.setCursor(x, y);
  LCD_RGB.print(message);
}

void LCD::LCD_Score(int score){
  if (score != old_score){
    old_score = score;
    LCD_Clear();

    if (score < 10){
      LCD_RGB.setCursor(8,1);
      LCD_RGB.print(score);
    }else if (score < 1000){
      LCD_RGB.setCursor(7,1);
      LCD_RGB.print(score);
    }
    
    if (score > 15){
      LCD_Print("GOD OF GODS", 3, 0, Red, false);
    }else if (score > 14){
      LCD_Print("SUPREM IMPERATOR", 0, 0, Red, false);
    }else if (score > 13){
      LCD_Print("The TERMINATOR", 1, 0, Red, false);
    }else if (score > 12){
      LCD_Print("Exterminator", 2, 0, Red, false);
    }else if (score > 11){
      LCD_Print("Corsaire", 4, 0, Orange, false);
    }else if (score > 10){
      LCD_Print("Chef supreme", 2, 0, Cyan, false);
    }else if (score > 9){
      LCD_Print("Commandant", 2, 0, Green, false);
    }else if (score > 8){;
      LCD_Print("Amiral", 5, 0, White, false);
    }else if (score > 7){
      LCD_Print("Contre-amiral", 1, 0, Orange, false);
    }else if (score > 6){
      LCD_Print("Capitaine", 3, 0, Cyan, false);
    }else if (score > 5){
      LCD_Print("Lieutenant", 3, 0, Blue, false);
    }else if (score > 4){
      LCD_Print("Aspirant Chef", 1, 0, Green, false);
    }else if (score > 3){
      LCD_Print("Aspirant", 4, 0, White, false);
    }else if (score > 2){
      LCD_Print("Major 2 l'espace", 0, 0, Cyan, false);
    }else if (score > 1){
      LCD_Print("Mousse", 5, 0, Green, false);
    }else if (score > 0){
      LCD_Print("Novice", 5, 0, Blue, false);
    }else if (score >= 0){
      LCD_Print("Bleu de l'espace", 0, 0, White, false);
    }else if (score == -1){
      // GameOver
      LCD_Print("GAME OVER", 4, 0, Red, true);
      LCD_Print("PRESS START !", 2, 1, Red, false);
      MyLED.LED_Control(ON);

    }
  }
}