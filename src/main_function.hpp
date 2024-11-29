#include "main.hpp"

#ifndef MAIN_FUNCTION_HPP
#define MAIN_FUNCTION_HPP


void init(struct main_info &main_information);

void freeMem(main_info &main_information);

void manageKeyboard(main_info &main_information, clock_info &clock_information);

void updateCollision(main_info &main_information);

void detectImpact(main_info &main_information);

void updateProjectile(main_info &main_information, clock_info &clock_information);

void manageMonsters(main_info &main_information, clock_info clock_information);

void manageExplosion(main_info &main_information, clock_info clock_information);

void displayGame(main_info &main_information, clock_info clock_information);

#endif