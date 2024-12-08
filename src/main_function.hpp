/**
 * @file main_function.hpp
 * @brief Contains game logic for managing the ship, monsters, projectiles, and game states.
 * 
 * This file defines the functions responsible for initializing, updating, and handling the core gameplay mechanics,
 * including ship movement, monster management, projectile updates, collision detection, and game state transitions
 * such as victory or game over. It also manages external communication with the microcontroller.
 * 
 * Each function is responsible for a specific gameplay feature or interaction, and all data structures
 * are passed by reference to minimize memory usage and maximize performance.
 * 
 * @version 1.0
 * @date 2024-12-08
 */

#include "main.hpp"

/**
 * @file main_function.hpp
 * @brief Contains game logic for managing the ship, monsters, projectiles, and game states.
 */

#ifndef MAIN_FUNCTION_HPP
#define MAIN_FUNCTION_HPP

/**
 * @brief Initializes the game by setting up the clock delays and allocating memory for the ship, monsters, and explosions.
 *
 * @param main_information The main information structure containing all game-related data.
 * @param clock_information The clock information structure containing timing data.
 */
void init(struct main_info &main_information, struct clock_info &clock_information);

/**
 * @brief Frees memory allocated for the ship, monster lines, and explosion vectors.
 *
 * @param main_information The main information structure containing all game-related data.
 */
void freeMem(main_info &main_information);

/**
 * @brief Manages the keyboard input for controlling the ship's movement and shooting.
 *
 * @param main_information The main information structure containing all game-related data.
 * @param clock_information The clock information structure containing timing data.
 */
void manageKeyboard(main_info &main_information, clock_info &clock_information);

/**
 * @brief Updates the collision detection between the ship and the monsters.
 *
 * @param main_information The main information structure containing all game-related data.
 */
void updateCollision(main_info &main_information);

/**
 * @brief Detects if the ship has been destroyed by a monster.
 *
 * @param main_information The main information structure containing all game-related data.
 */
void detectImpact(main_info &main_information);

/**
 * @brief Updates the projectiles fired by the ship and monsters.
 *
 * @param main_information The main information structure containing all game-related data.
 * @param clock_information The clock information structure containing timing data.
 */
void updateProjectile(main_info &main_information, clock_info &clock_information);

/**
 * @brief Manages the movement and direction changes of the monsters.
 *
 * @param main_information The main information structure containing all game-related data.
 * @param clock_information The clock information structure containing timing data.
 */
void manageMonsters(main_info &main_information, clock_info &clock_information);

/**
 * @brief Handles the explosion effects of destroyed monsters.
 *
 * @param main_information The main information structure containing all game-related data.
 * @param clock_information The clock information structure containing timing data.
 */
void manageExplosion(main_info &main_information, clock_info &clock_information);

/**
 * @brief Displays the game elements (ship, monsters) on the window, updating the screen.
 *
 * @param main_information The main information structure containing all game-related data.
 * @param clock_information The clock information structure containing timing data.
 */
void displayGame(main_info &main_information, clock_info &clock_information);

/**
 * @brief Forces the display of the game, bypassing the clock delays.
 *
 * @param main_information The main information structure containing all game-related data.
 */
void displayGame(main_info &main_information);

/**
 * @brief Handles the end of the game when the player loses, displaying a game-over screen.
 *
 * @param main_information The main information structure containing all game-related data.
 * @param clock_information The clock information structure containing timing data.
 */
void gameOver(main_info &main_information, clock_info &clock_information);

/**
 * @brief Displays a victory screen when all monsters are destroyed.
 *
 * @param main_information The main information structure containing all game-related data.
 * @param clock_information The clock information structure containing timing data.
 */
void youWon(main_info &main_information, clock_info &clock_information);

/**
 * @brief Manages the communication with the external microcontroller (uControler) through USART.
 *
 * @param main_information The main information structure containing all game-related data.
 * @param clock_information The clock information structure containing timing data.
 */
void manage_uControler(main_info &main_information, clock_info &clock_information);

/**
 * @brief Handles the commands received from the external microcontroller (uControler) to control the game.
 *
 * @param main_information The main information structure containing all game-related data.
 */
void handle_uControler_command(main_info &main_information);

#endif