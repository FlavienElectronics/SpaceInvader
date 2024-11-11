#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "SpaceShip.hpp"
class Monster;

using namespace std;

#define VERBOSE

class Explosion : public SpaceShip
{
protected:
	int status = -1; //-1 = starting | 0 = explosion range 1| 1 = explosion range 2 | 2 = monster has exploded
	Point **pt;

public:
	virtual void grow(const Monster &monstr);
};
#endif