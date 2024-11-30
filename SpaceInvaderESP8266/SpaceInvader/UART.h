/*********************************************************************
 * @file  Apllication.h
 * @author <mettre l'adresse mail ou nom prenom>
 * @brief Fichier header de l'application
 *********************************************************************/
#ifndef UART_H_
#define UART_H_

#include <Arduino.h>
#include <iostream>
#include "config.h"

class UART{
public:
    UART();
    ~UART();
    
    void UART_init(void);
    void UART_Send(const char* message);
    String UART_Read(void);
};

#endif