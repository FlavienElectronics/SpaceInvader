#include "UART.h"

UART::UART(){}
UART::~UART(){}

void UART::UART_init(void){
  Serial.begin(BAUDRATE);
}
void UART::UART_Send(const char* message){
  Serial.println(message);
}
String UART::UART_Read(void){
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