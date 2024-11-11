#include "Point.hpp"

Point::Point()
{
    this->x = -1;
    this->y = -1;
    this->color = "Invisible";
}

Point::Point(float x, float y, int size, string color) : sf::RectangleShape(sf::Vector2f(1, 1))
{
    this->x = x;
    this->y = y;
    this->size = size;
    this->color = color;

    this->setFillColor(sf::Color::Black);
    this->setPosition(x, y);
}

void Point::xAdd()
{
    this->x++;
    this->setPosition(x, y);
}
void Point::yAdd()
{
    this->y++;
    this->setPosition(x, y);
}
void Point::xSub()
{
    this->x--;
    this->setPosition(x, y);
}
void Point::ySub()
{
    this->y--;
    this->setPosition(x, y);
}
void Point::hide()
{
    this->color = "Invisible";
    this->setFillColor(sf::Color::Transparent);
}

float Point::getX()
{
    return (this->x);
}
float Point::getY()
{
    return (this->y);
}

