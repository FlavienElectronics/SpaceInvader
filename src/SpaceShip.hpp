#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Point.hpp"
#include "Projectile.hpp"

#define VERBOSE

using namespace std;

/*Faire une classe Player*/

class SpaceShip : public sf::Drawable
{
protected:
    float x, y;
    Point **pt;
    Projectile **pjt; /*Utilisation de la STL pour les projectile (vector)*/
    int numberOfPixels;
    int numberOfProjectiles;
    int xSize;
    int ySize;

    sf::RenderWindow *window;
    float winHeight;
    float winWidth;

public:
    class Exept
    {
    public:
        std::string message;
        Exept(std::string mes);
    };

    SpaceShip();
    SpaceShip(sf::RenderWindow *win, float windowHeight, float windowWidth, float x_pos, float y_pos, string color);
    void shoot();
    void updateProjectiles();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void xAdd();
    void yAdd();
    void xSub();
    void ySub();
    ~SpaceShip();
    float getX();
    float getY();
};

#endif