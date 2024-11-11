#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Point.hpp"
#include "SpaceShip.hpp"
#include "Projectile.hpp"
#include "Explosion.hpp"

using namespace std;

#define VERBOSE


class Monster : public SpaceShip
{

protected:
	int direction; // 0 -> goes left | 1 -> goes right
	Explosion explo;

public:
	Monster(sf::RenderWindow *win, float windowHeight, float windowWidth, float x_pos, float y_pos, string color);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	int getDirection();
	void changeDirection();
	void hide();
	void explode();
	~Monster();
	friend Explosion;
};
#endif