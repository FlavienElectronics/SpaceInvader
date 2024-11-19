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
    sf::Color localColor;
    if (color == "B")
    {
        localColor = sf::Color::Black;
        this->color == "B";
    }
    else if (color == "W")
    {
        localColor = sf::Color::White;
        this->color == "W";
    }
    else
    {
        localColor = sf::Color::Black; 
    }
    this->setFillColor(localColor);
    this->setPosition(x, y);
}

Point::Point(float x, float y) : sf::RectangleShape(sf::Vector2f(1, 1))
{
    this->x = x;
    this->y = y;
    this->color == "B";
    this->setFillColor(sf::Color::Black);
    this->setPosition(x, y);
}

Point::Point(float x, float y, string color) : sf::RectangleShape(sf::Vector2f(1, 1))
{
    this->x = x;
    this->y = y;
    sf::Color localColor;
    if (color == "B")
    {
        localColor = sf::Color::Black;
        this->color == "B";
    }
    else if (color == "W")
    {
        localColor = sf::Color::White;
        this->color == "W";
    }
    else
    {
        localColor = sf::Color::Black;
    }
    this->setFillColor(localColor);
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

float Point::getX() const
{
    return (this->x);
}
float Point::getY() const
{
    return (this->y);
}
