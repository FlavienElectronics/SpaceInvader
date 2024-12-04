/*Ajouter des entête sous chaque fichier*/

#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Monster.hpp"

class Monster;


using namespace std;


class Explosion : public SpaceShip
{
protected:
	int status; //-1 = starting | 0 = explosion range 1| 1 = explosion range 2 | 2 = monster has exploded
	void clearPoints();

public:
	Explosion();

	virtual int grow(const Monster &monstr);
	friend Monster;
};
#endif