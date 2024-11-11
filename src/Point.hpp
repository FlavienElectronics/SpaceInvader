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
	void xAdd();
	void yAdd();
	void xSub();
	void ySub();
	void hide();
};
#endif