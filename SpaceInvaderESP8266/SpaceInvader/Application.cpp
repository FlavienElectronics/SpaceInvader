/*********************************************************************
 * @file  Apllication.cpp
 * @author <mettre l'adresse mail ou nom prenom>
 * @brief Fichier source de l'application
 *********************************************************************/
#include "Application.h"

using namespace std;

rgb_lcd LCD;

int tmp_cpt = 0;
int old_score = 0;

int buzzerStartTime = 0;
int buzzerDuration = 0;
bool buzzerActive = false;

// Variables pour gérer le timing de la mélodie
unsigned long noteStartTime = 0;
int currentNote = 0;
bool isPlaying = false;

int old_potar_value = -1;

int led_state = OFF;

int First_Start = 1;

// ********** MELODIE : Game of Thrones **********

int melody[] = {
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

int durations[] = {
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

// **********

Application::Application()
{
  // Code
  ; 
}
  
Application::~Application()
{
  // Code
  ;
}  

void Application::init(void)
{
  LCD_init();
  BUZZER_init();
  LED_init();
  UART_init();
  POTAR_init();
  BUTTON_init();
}

// ********** BUTTON **********

void Application::BUTTON_init(void){
  pinMode(BUTTON_PIN, INPUT);
}

int Application::BUTTON_Read(void){
  return digitalRead(BUTTON_PIN);
}

// ********** POTAR **********

void Application::POTAR_init(void){
  pinMode(POTAR_PIN, INPUT);
}

float Application::POTAR_Read(void){
  float voltage;
  int sensor_value = analogRead(POTAR_PIN);
  voltage = (float)sensor_value*ADC_REF/(ADC_RESOLUTION - 1);
  float degrees = (voltage*POTAR_FULL_ANGLE)/POTAR_VCC;
  return degrees;
}

// ********** UART **********

void Application::UART_init(void){
  Serial.begin(BAUDRATE);
}

void Application::UART_Send(const char* message){
  Serial.println(message);
}

String Application::UART_Read(void){
  String receivedText = ""; // Initialisation de la chaîne de caractères

  // Attendre que des données soient disponibles
  while (Serial.available() > 0) {
    char receivedChar = Serial.read(); // Lit un caractère
    if (receivedChar == '\n') {        // Vérifie si le caractère est un saut de ligne
      break;                           // Sort de la boucle si le saut de ligne est atteint
    }
    receivedText += receivedChar;      // Ajoute le caractère à la chaîne
  }

  return receivedText; // Retourne le texte reçu
}

// ********** LED **********

void Application::LED_init(void){
  pinMode(LED_PIN, OUTPUT);
  LED_Control(OFF);
}

void Application::LED_Control(int ONOFF){
  if (ONOFF == OFF){
    digitalWrite(LED_PIN, LOW);
    led_state = OFF;
  }else if (ONOFF == ON){
    digitalWrite(LED_PIN, HIGH);
    led_state = ON;
  }else if (ONOFF == TOGGLE){
    if (led_state == ON){
      LED_Control(OFF);
    }else{
      LED_Control(ON);
    }
  }
}

// ********** BUZZER **********

void Application::BUZZER_init(void){
  pinMode(BUZZER_PIN, OUTPUT);
  noTone(BUZZER_PIN);
}

void Application::BUZZER_Tone(int frequency, int duration){
  tone(BUZZER_PIN, frequency);
  //delay(_delay);
  buzzerStartTime = millis();           // Enregistre le temps de début
  buzzerDuration = duration;            // Enregistre la durée de fonctionnement
  buzzerActive = true;                  // Active l'état du buzzer pour indiquer qu'il est en cours
}

void Application::BUZZER_NextGrade(void){

}

void Application::UPDATE_Buzzer(void){
  if (buzzerActive && (millis() - buzzerStartTime >= buzzerDuration)) {
    noTone(BUZZER_PIN);                 // Arrête le buzzer une fois la durée écoulée
    buzzerActive = false;               // Désactive l'état du buzzer
  }else if (buzzerActive){    // On s'occupe du son actif, il est plus important que la musique
    
    
  }else{  // Si pas de son en cours, on joue la musique
    playMelody();
  }
}

void Application::playMelody(void){
  int melodySize = sizeof(durations) / sizeof(int);

  if (isPlaying) {
    if (millis() - noteStartTime >= 1000 / durations[currentNote] * 1.30) {
      noTone(BUZZER_PIN);         // Arrête la note actuelle
      isPlaying = false;          // Indique que la note est terminée
      noteStartTime = millis();   // Réinitialise le temps pour la prochaine note
      currentNote++;              // Passe à la note suivante
    }
  }

  if (!isPlaying && currentNote < melodySize) {
    int noteDuration = 1000 / durations[currentNote];
    tone(BUZZER_PIN, melody[currentNote], noteDuration);
    isPlaying = true;
  }

  if (currentNote >= melodySize) {
    currentNote = 0;
    isPlaying = false;
  }
}

// ********** LCD **********

void Application::LCD_init(void)
{
  LCD.begin(16, 2);         // LCD 2 lignes, 16 caractères
  LCD.setRGB(10, 10, 10);   // Fond blanc
  LCD.setCursor(0, 0);
}

void Application::LCD_Clear(void){
  LCD.setCursor(0,0);
  LCD.print("                ");
  LCD.setCursor(0,1);
  LCD.print("                ");
}

void Application::LCD_Print(const char* message, int x, int y, int color)
{
  LCD_Clear();
  if (color == RED){
    LCD.setRGB(250, 0, 0);  // Fond Rouge
  }else if (color == BLU){
    LCD.setRGB(0, 0, 250);  // Fond Bleu
  }
  LCD.setCursor(x, y);
  LCD.print(message);
}

void Application::LCD_Score(int score){
  if (score != old_score){
    old_score = score;
    LCD_Clear();

    if (score < 10){
      LCD.setCursor(8,1);
      LCD.print(score);
    }else if (score < 1000){
      LCD.setCursor(7,1);
      LCD.print(score);
    }
    
    if (score > 999){
      LCD.setCursor(3, 0);
      LCD.print("GOD OF GODS");
    }else if (score > 70){
      LCD.setCursor(0, 0);
      LCD.print("SUPREM IMPERATOR");
    }else if (score > 65){
      LCD.setCursor(1, 0);
      LCD.print("The TERMINATOR");
    }else if (score > 60){
      LCD.setCursor(2, 0);
      LCD.print("Exterminator");
    }else if (score > 55){
      LCD.setCursor(2, 0);
      LCD.print("Corsaire");
    }else if (score > 50){
      LCD.setCursor(2, 0);
      LCD.print("Chef supreme");
    }else if (score > 45){
      LCD.setCursor(2, 0);
      LCD.print("Commandant");
    }else if (score > 40){
      LCD.setCursor(5, 0);
      LCD.print("Amiral");
    }else if (score > 35){
      LCD.setCursor(1, 0);
      LCD.print("Contre-amiral");
    }else if (score > 30){
      LCD.setCursor(3, 0);
      LCD.print("Capitaine");
    }else if (score > 25){
      LCD.setCursor(3, 0);
      LCD.print("Lieutenant");
    }else if (score > 25){
      LCD.setCursor(1, 0);
      LCD.print("Aspirant Chef");
    }else if (score > 20){
      LCD.setCursor(4, 0);
      LCD.print("Aspirant");
    }else if (score > 15){
      LCD.setCursor(0, 0);
      LCD.print("Major 2 l'espace");
      BUZZER_Tone(1000,150);
    }else if (score > 10){
      LCD.setCursor(5, 0);
      LCD.print("Mousse");
    }else if (score > 5){
      LCD.setCursor(5, 0);
      LCD.print("Novice");
    }else if (score >= 0){
      LCD.setCursor(0, 0);
      LCD.print("Bleu de l'espace");
    }else if (score == -1){
      // GameOver
      LCD.setCursor(4, 0);
      LCD.print("GAME OVER");
      LCD.setCursor(2, 1);
      LCD.print("PRESS START !");
    }
  }
}

void Application::LCD_Welcome(void){
  LCD.setRGB(100, 175, 195);
  LCD.setCursor(2, 0);
  LCD.print("SPACE INVADER");
  LCD.setCursor(2, 1);
  LCD.print("PRESS START !");
  while ((BUTTON_Read() != HIGH)){ delay(50); }
  First_Start = 0;
  LCD.setRGB(10, 10, 10);
  LCD_Score(0);
}

// ********** UTILITAIRES **********

String Application::UTILITAIRE_ExtractCommand(const String &message){
  int startIdx = message.indexOf('[');
  int endIdx = message.indexOf(']');
  // Vérifie si les indices sont valides et que la commande est bien formée
  if (startIdx != -1 && endIdx != -1 && endIdx > startIdx + 1) {
    return message.substring(startIdx + 1, endIdx);
  } else {
    return "";
  }
}

String Application::UTILITAIRE_ExtractValue(const String &message){
  int endIdx = message.indexOf(']');
  if (endIdx != -1 && endIdx < message.length() - 1) {
    return message.substring(endIdx + 1);
  } else {
    return "";
  }
}

void Application::HardReset(void){
  tmp_cpt = 0;
  old_score = 0;
  buzzerStartTime = 0;
  buzzerDuration = 0;
  buzzerActive = false;
  noteStartTime = 0;
  currentNote = 0;
  isPlaying = false;
  old_potar_value = -1;
  led_state = OFF;
  First_Start = 1;
  init();
}

// ********** RUN **********

void Application::run(void)
{

  if (First_Start == 1){
    LCD_Welcome();
  }

  // LECTURE ET ENVOIE DE LA VALEUR DU POTENTIOMETRE
  int pot_value = POTAR_Read();
  if (old_potar_value != pot_value){
    old_potar_value = pot_value;
    char buffer[64];
    sprintf(buffer, "[POT]%.0f", 100*POTAR_Read()/POTAR_FULL_ANGLE);
    UART_Send(buffer);
  }
  
  // DETECTION ET ENVOIE DU CLICK DU BOUTON
  if (BUTTON_Read() == HIGH){
    UART_Send("[BTN]");
  }

  if (Serial.available() > 0) { // Vérifie si des données sont disponibles
    String message = UART_Read();

    Serial.print("Message reçu : ");
    Serial.println(message);

    String command = UTILITAIRE_ExtractCommand(message);
    String value = UTILITAIRE_ExtractValue(message);

    if (command == "SCR" && value != ""){
      int SCORE = value.toInt();
      LCD_Score(SCORE);
    }else if (command == "GOR"){
      LCD_Score(-1);
    }else if (command == "RST"){
      HardReset();
    }
  }

  // UPDATES
  UPDATE_Buzzer();

}

