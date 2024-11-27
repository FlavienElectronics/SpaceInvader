#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Projectile.hpp"
class Monster;
class MonsterLine;

// #define VERBOSE_SHIP

using namespace std;

/*Faire une classe Player*/

class SpaceShip : public sf::Drawable
{
private:
    int life;

protected:
    float x, y;
    Point **pt;
    Projectile **pjt; /*Utilisation de la STL pour les projectile (vector)*/
    int hitBox_x;
    int hitBox_y;
    int numberOfPixels;
    int numberOfProjectiles;
    int xSize;
    int ySize;

    bool alive;

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
    virtual void shoot();
    void updateProjectiles();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void xAdd();
    void yAdd();
    void xSub();
    void ySub();
    ~SpaceShip();
    float getX() const;
    float getY() const;
    void hidePixel(int x, int y);

    void goTo(float xValue);

    void correctCoordinates(int& xToCorrect, int& yToCorrect);

    bool detectImpact(MonsterLine **monsterLine, int numberOfLine);

    bool isAlive();
    void die();

    friend class Explosion;
    friend class Monster;
};

#endif