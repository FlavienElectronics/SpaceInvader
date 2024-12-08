/*Ajouter des entête sous chaque fichier*/

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