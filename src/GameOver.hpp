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
    GameOver(float windowWidth, float windowHeight);
};

#endif