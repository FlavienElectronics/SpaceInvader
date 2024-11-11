#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "SpaceShip.hpp"
//#include "Explosion.hpp"
class Explosion;

using namespace std;

#define VERBOSE_MONSTER


class Monster : public SpaceShip
{

protected:
	int direction; // 0 -> goes left | 1 -> goes right
	bool alive;
	int stat;
	Explosion* explo; // Circular inclusion

public:
	void updateParticule();
	Monster(sf::RenderWindow *win, float windowHeight, float windowWidth, float x_pos, float y_pos, string color);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	int getDirection();
	void changeDirection();
	void hide();
	void explode();
	~Monster();
	bool isAlive();
	friend class Explosion;
};
#endif