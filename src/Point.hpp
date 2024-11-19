#ifndef POINT_HPP
#define POINT_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Point : public sf::RectangleShape
{
private:
	float x, y;
	int size;
	string color;

public :
	Point();
	Point(float x, float y, int size, string color);
	Point(float x, float y,string color);
	Point(float x,float y);
	void setPositionXY(float x,float y);
	void xAdd();
	void yAdd();
	void xSub();
	void ySub();
	void hide();
	float getX() const;
	float getY() const;

	friend class Monster;
	friend class SpaceShip;
};
#endif