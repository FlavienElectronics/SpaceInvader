/*********************************************************************
 * @file  UART.h
 * @author LESPIAUCQ Denis & CARVALHO Flavien (4 AE SE 3)
 *********************************************************************/
#ifndef UART_H_
#define UART_H_

#include <Arduino.h>
#include <iostream>
#include "config.h"

class UART{
public:
    // Constructeur & déstructeur de la classe UART
    UART();
    ~UART();
    
    // Fonction de configuration et d'initialisation de la transmission UART
    void UART_init(void);

    // Fonction permettant l'envoie d'un message vers le PC
    void UART_Send(const char* message);

    // Fonction permettant de retourner le message réceptionné depuis le PC
    String UART_Read(void);
};

#endif