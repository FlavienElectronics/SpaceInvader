

/**
 * @file YouWon.hpp
 * @brief Header file for the YouWon class.
 * 
 * This file contains the declaration of the `YouWon` class, which is responsible for creating 
 * and displaying the "YOU WON!" message on the screen. It uses individual letter objects to form 
 * the message and positions them in the center of the screen. The class inherits from `LetterGroup` 
 * to manage a collection of letters and handle their layout and rendering.
 */

#ifndef YOUWON_HPP
#define YOUWON_HPP
#include "LetterGroup.hpp"

class YouWon : public LetterGroup
{
public:
    /**
     * @brief Constructor for the YouWon class.
     * 
     * The constructor initializes a series of letter objects that together form the message 
     * "YOU WON!!" and positions them on the screen. The message is centered based on the window's 
     * width, and letters are spaced properly to ensure they do not overlap.
     * 
     * @param colour The color of the text.
     * @param windowWidth The width of the game window used to center the text.
     * @param windowHeight The height of the game window used to position the text vertically.
     */
	YouWon(string colour, float windowWidth, float windowHeight);
};
#endif