#ifndef MONSTER_LINE_HPP
#define MONSTER_LINE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Monster.hpp"
#include "SpaceShip.hpp"


class MonsterLine
{
private:
	int direction;
	Monster **block;
	int numberOfMonster;
	float spacing;

	sf::RenderWindow *window;
	float winHeight;
	float winWidth;

public:
	MonsterLine(sf::RenderWindow *win, float windowHeight, float windowWidth, float x_pos, float y_pos, int numberOfMonster, string color);
	Monster &operator[](int location);
	bool isLineDestoyed();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	bool isExplosing(int location);
	void updateParticule(int location);
	void explode(int location);
	bool isAlive(int location);
	void changeDirection();
	void updateCollision(const SpaceShip &ship, bool **vectorBool);
	void xSub();
	void xAdd();
	int getDirection();
	int getNumberOfMonster();
	int getNumberOfMonsterAlive();
	~MonsterLine();
};

#endif