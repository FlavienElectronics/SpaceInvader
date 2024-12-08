/**
 * @file GameOver.hpp
 * @brief Declaration of the GameOver class, responsible for displaying the "GAME OVER" message.
 * 
 * This file contains the definition of the `GameOver` class, which inherits from the `LetterGroup` class.
 * The `GameOver` class is responsible for displaying a "GAME OVER" message in the game, typically shown
 * when the player loses or completes the game. It initializes a group of letters to form the "GAME OVER" text
 * and positions them appropriately in the center of the screen. The class leverages the `LetterGroup` class to manage 
 * the creation and positioning of each individual letter. The color and position of the text can be customized.
 * 
 * @version 1.0
 * @date 2024-12-08
 */

#ifndef GAMEOVER_HPP
#define GAMEOVER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "LetterGroup.hpp"

class GameOver : public LetterGroup
{
public:
    /**
     * @brief Constructor for the GameOver class.
     *
     * This class is responsible for initializing the "GAME OVER" text as a group of letters
     * positioned in the center of the window. It calculates the placement of each letter
     * and spaces them appropriately.
     *
     * @param colour A string representing the color of the letters (e.g., "red", "blue").
     * @param windowWidth The width of the game window, used for centering the text.
     * @param windowHeight The height of the game window, used for placing the text vertically.
     */
    GameOver(string colour, float windowWidth, float windowHeight);
};

#endif