#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Point.hpp"

#define VERBOSE

using namespace std;

/* Projectile généralisable avec SpaceShip et Monster???*/
class Projectile : public sf::Drawable
{
private:
	int numberOfPixels;
	Point *pt[2];
	float x, y;

public:
	Projectile(float x_pos, float y_pos, string color);
	void ySub();
	bool isOutOfBounds(float windowHeight);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	float getY() const;
	~Projectile();
};
#endif