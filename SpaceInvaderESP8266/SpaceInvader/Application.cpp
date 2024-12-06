/*********************************************************************
 * @file  Apllication.cpp
 * @author LESPIAUCQ Denis & CARVALHO Flavien (4 AE SE 3)
 *********************************************************************/
#include "Application.h"

using namespace std;

// ********** CLASSES **********

Music myMusic;    // GESTION DE LA MUSIQUE PAR LE BUZZER
Potar myPotar;    // GESTION DU POTENTIOMETRE
UART myUART;      // GESTION DE LA COMMUNICATION UART
LCD myLCD;        // GESTION DE L'AFFICHAGE LCD
LED myLED;        // GESTION DE LA LED
Bouton myBouton;  // GESTION DU BOUTON POUSSOIR
Utilitaires myUtilitaire;  // CLASSE DE FONCTIONS UTILITAIRES

// ********** MELODIE : Game of Thrones **********

int Music::melody[] = {
  NOTE_G4, NOTE_C4, NOTE_DS4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_DS4, NOTE_F4,
  NOTE_G4, NOTE_C4, NOTE_DS4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_DS4, NOTE_F4,
  NOTE_G4, NOTE_C4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_E4, NOTE_F4,
  NOTE_G4, NOTE_C4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_E4, NOTE_F4,
  NOTE_G4, NOTE_C4,
  
  NOTE_DS4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_DS4, NOTE_F4,
  NOTE_D4,
  NOTE_F4, NOTE_AS3,
  NOTE_DS4, NOTE_D4, NOTE_F4, NOTE_AS3,
  NOTE_DS4, NOTE_D4, NOTE_C4,
  
  NOTE_G4, NOTE_C4,
  
  NOTE_DS4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_DS4, NOTE_F4,
  NOTE_D4,
  NOTE_F4, NOTE_AS3,
  NOTE_DS4, NOTE_D4, NOTE_F4, NOTE_AS3,
  NOTE_DS4, NOTE_D4, NOTE_C4,
  NOTE_G4, NOTE_C4,
  NOTE_DS4, NOTE_F4, NOTE_G4,  NOTE_C4, NOTE_DS4, NOTE_F4,
  
  NOTE_D4,
  NOTE_F4, NOTE_AS3,
  NOTE_D4, NOTE_DS4, NOTE_D4, NOTE_AS3,
  NOTE_C4,
  NOTE_C5,
  NOTE_AS4,
  NOTE_C4,
  NOTE_G4,
  NOTE_DS4,
  NOTE_DS4, NOTE_F4,
  NOTE_G4,
  
  NOTE_C5,
  NOTE_AS4,
  NOTE_C4,
  NOTE_G4,
  NOTE_DS4,
  NOTE_DS4, NOTE_D4,
  NOTE_C5, NOTE_G4, NOTE_GS4, NOTE_AS4, NOTE_C5, NOTE_G4, NOTE_GS4, NOTE_AS4,
  NOTE_C5, NOTE_G4, NOTE_GS4, NOTE_AS4, NOTE_C5, NOTE_G4, NOTE_GS4, NOTE_AS4,
  
  REST, NOTE_GS5, NOTE_AS5, NOTE_C6, NOTE_G5, NOTE_GS5, NOTE_AS5,
  NOTE_C6, NOTE_G5, NOTE_GS5, NOTE_AS5, NOTE_C6, NOTE_G5, NOTE_GS5, NOTE_AS5
};

int Music::durations[] = {
  8, 8, 16, 16, 8, 8, 16, 16,
  8, 8, 16, 16, 8, 8, 16, 16,
  8, 8, 16, 16, 8, 8, 16, 16,
  8, 8, 16, 16, 8, 8, 16, 16,
  4, 4,
  
  16, 16, 4, 4, 16, 16,
  1,
  4, 4,
  16, 16, 4, 4,
  16, 16, 1,
  
  4, 4,
  
  16, 16, 4, 4, 16, 16,
  1,
  4, 4,
  16, 16, 4, 4,
  16, 16, 1,
  4, 4,
  16, 16, 4, 4, 16, 16,
  
  2,
  4, 4,
  8, 8, 8, 8,
  1,
  2,
  2,
  2,
  2,
  2,
  4, 4,
  1,
  
  2,
  2,
  2,
  2,
  2,
  4, 4,
  8, 8, 16, 16, 8, 8, 16, 16,
  8, 8, 16, 16, 8, 8, 16, 16,
  
  4, 16, 16, 8, 8, 16, 16,
  8, 16, 16, 16, 8, 8, 16, 16
};

//int Music::melody_start[] = { NOTE_AS3, NOTE_B3, NOTE_C5, NOTE_C5, NOTE_G5, NOTE_A4, NOTE_G7, NOTE_G8 };
//int Music::durations_start[] = { 8,4,4,2,4,2,2,1 };

// **********

Application::Application()
{
  First_Start = 1;
  ; 
}
  
Application::~Application()
{
  // Code
  ;
}  

void Application::init(void)
{
  myLCD.LCD_init();
  myMusic.BUZZER_init();
  myLED.LED_init();
  myUART.UART_init();
  myPotar.POTAR_init();
  myBouton.BUTTON_init();
}

// ********** UTILITAIRES **********

void Application::UTILITAIRE_Welcome(void){
  myLCD.LCD_Print("SPACE INVADER", 2, 0, Blue, true);
  myLCD.LCD_Print("PRESS START !", 2, 1, Blue, false);
  while ((myBouton.BUTTON_Read() != HIGH)){ delay(50); }
  First_Start = 0;
  myLCD.LCD_Score(0);
  myMusic.MelodyStart();
}

void Application::UTILITAIRE_HardReset(void){
  myLCD.old_score = 0;
  myMusic.buzzerStartTime = 0;
  myMusic.buzzerDuration = 0;
  myMusic.buzzerActive = false;
  myMusic.noteStartTime = 0;
  myMusic.currentNote = 0;
  myMusic.isPlaying = false;
  myPotar.old_potar_value = -1;
  myLED.led_state = OFF;
  First_Start = 1;
  init();
}

// ********** RUN **********

void Application::run(void)
{

  if (First_Start == 1){
    UTILITAIRE_Welcome();
  }

  // LECTURE ET ENVOIE DE LA VALEUR DU POTENTIOMETRE
  int pot_value = myPotar.POTAR_Read();
  char buffer[16];
  sprintf(buffer, "[POT]%.0f", 100*myPotar.POTAR_Read()/POTAR_FULL_ANGLE);
  myUART.UART_Send(buffer);
  /*if (myPotar.old_potar_value != pot_value){
    myPotar.old_potar_value = pot_value;
    char buffer[16];
    sprintf(buffer, "[POT]%.0f", 100*myPotar.POTAR_Read()/POTAR_FULL_ANGLE);
    myUART.UART_Send(buffer);
  }*/
  
  // DETECTION ET ENVOIE DU CLICK DU BOUTON
  if (myBouton.BUTTON_Read() == HIGH){
    myUART.UART_Send("[BTN]");
  }

  if (Serial.available() > 0) { // Vérifie si des données sont disponibles
    String message = myUART.UART_Read();

    Serial.print("Message reçu : ");
    Serial.println(message);

    String command = myUtilitaire.UTILITAIRE_ExtractCommand(message);
    String value = myUtilitaire.UTILITAIRE_ExtractValue(message);

    if (command == "SCR" && value != ""){
      int SCORE = value.toInt();
      myLCD.LCD_Score(SCORE);
    }else if (command == "GOR"){
      myLCD.LCD_Score(-1);
      myMusic.MelodyStart();
    }else if (command == "RST"){
      UTILITAIRE_HardReset();
    }
  }

  // UPDATES
  myMusic.UPDATE_Buzzer();

}
