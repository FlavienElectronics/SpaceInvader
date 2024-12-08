/**
 * @file SpaceShip.cpp
 * @brief Implementation of the SpaceShip class, representing the player's spaceship in the game.
 *
 * The SpaceShip class manages the ship's position, movement, shooting, and interactions with other objects in the game.
 * It handles its pixels (points), projectiles, and the detection of impacts with enemies.
 * The class also manages the life of the spaceship and the corresponding behaviors when it's hit.
 *
 * @version 1.0
 * @date 2024-12-08
 */

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

using namespace std;

class SpaceShip : public sf::Drawable
{
private:
    int life;
    int max_life;

protected:
    float x, y;
    Point **pt;
    std::vector<Projectile *> pjt; /*Utilisation de la STL pour les projectile (vector)*/
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
    /**
     * @brief Exception constructor for the SpaceShip class.
     *
     * Used to throw custom exceptions with an error message.
     *
     * @param mes The message describing the exception.
     */
    class Exept
    {
    public:
        std::string message;
        Exept(std::string mes);
    };

    /**
     * @brief Default constructor for the SpaceShip class.
     *
     * Initializes the spaceship's position to (0, 0) and sets the number of pixels to 11.
     */
    SpaceShip();

    /**
     * @brief Constructor for the SpaceShip class with window parameters and position.
     *
     * Initializes the spaceship with specific position and color, creates points to represent the ship's pixels,
     * and initializes various properties such as the number of projectiles, ship size, and life.
     *
     * @param win The render window for the game.
     * @param windowHeight The height of the game window.
     * @param windowWidth The width of the game window.
     * @param x_pos The x-coordinate of the spaceship's starting position.
     * @param y_pos The y-coordinate of the spaceship's starting position.
     * @param color The color of the spaceship.
     */
    SpaceShip(sf::RenderWindow *win, float windowHeight, float windowWidth, float x_pos, float y_pos, string color);
    /**
     * @brief Shoots a projectile from the spaceship.
     *
     * Creates a new projectile and adds it to the projectile list, initializing its position above the spaceship.
     */
    virtual void shoot();
    /**
     * @brief Updates the state of all projectiles by moving them and removing any that are out of bounds.
     */
    void updateProjectiles();

    /**
     * @brief Draws the spaceship and all its projectiles on the screen.
     *
     * This method iterates through all the spaceship's points and its projectiles,
     * drawing them on the target window.
     *
     * @param target The render target where the spaceship and projectiles are drawn.
     * @param states The render states used for drawing.
     */
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    /**
     * @brief Moves the spaceship one unit to the right.
     *
     * Updates the x-coordinate of the spaceship, checking bounds. If out of bounds, throws an exception.
     */
    void xAdd();

    /**
     * @brief Moves the spaceship one unit downward.
     *
     * Updates the y-coordinate of the spaceship, checking bounds. If out of bounds, throws an exception.
     */
    void yAdd();

    /**
     * @brief Moves the spaceship one unit to the left.
     *
     * Updates the x-coordinate of the spaceship, checking bounds. If out of bounds, throws an exception.
     */
    void xSub();

    /**
     * @brief Moves the spaceship one unit upward.
     *
     * Updates the y-coordinate of the spaceship, checking bounds. If out of bounds, throws an exception.
     */
    void ySub();

    /**
     * @brief Destructor for the SpaceShip class.
     *
     * Frees the memory allocated for the spaceship's points and projectiles.
     * Ensures no memory leaks occur when the spaceship object is destroyed.
     */
    ~SpaceShip();
    /**
     * @brief Gets the x-coordinate of the spaceship.
     *
     * This function returns the current x-coordinate of the spaceship in the game world.
     *
     * @return The x-coordinate of the spaceship.
     */
    float getX() const;

    /**
     * @brief Gets the y-coordinate of the spaceship.
     *
     * This function returns the current y-coordinate of the spaceship in the game world.
     *
     * @return The y-coordinate of the spaceship.
     */
    float getY() const;
    /**
     * @brief Hides a specific pixel of the spaceship.
     *
     * Given a specific x and y coordinate, the corresponding pixel is hidden from view.
     *
     * @param xTH The x-coordinate of the pixel to hide.
     * @param yTH The y-coordinate of the pixel to hide.
     */
    void hidePixel(int x, int y);

    /**
     * @brief Moves the spaceship to a specified x-coordinate.
     *
     * Moves the spaceship towards the target x-coordinate, adjusting its position accordingly.
     *
     * @param xValue The x-coordinate to move the spaceship to.
     */
    void goTo(float xValue);

    /**
     * @brief Corrects the y-coordinate to avoid overlap with other ship's pixels.
     *
     * Iterates over all the ship's pixels and adjusts the `yToCorrect` variable to avoid conflicts.
     *
     * @param xToCorrect The x-coordinate to be corrected.
     * @param yToCorrect The y-coordinate to be corrected.
     */
    void correctCoordinates(int &xToCorrect, int &yToCorrect);

    /**
     * @brief Detects if the spaceship has collided with any monsters.
     *
     * This function checks for any impact between the spaceship and the monsters, based on the given
     * monster lines in the game. If an impact is detected, the spaceship is marked as damaged or destroyed.
     *
     * @param monsterLine A pointer to the array of monster lines.
     * @param numberOfLine The number of lines containing monsters.
     *
     * @return true if the spaceship has collided with a monster, false otherwise.
     */
    bool detectImpact(MonsterLine **monsterLine, int numberOfLine);
    /**
     * @brief Checks if the spaceship is still alive.
     *
     * This function determines if the spaceship is still alive based on its current health.
     * If the life count is greater than 0, the spaceship is considered alive.
     *
     * @return true if the spaceship is alive, false otherwise.
     */
    bool isAlive();

    /**
     * @brief Kills the spaceship, marking it as not alive.
     *
     * This function handles the death of the spaceship, which includes marking the spaceship as dead,
     * resetting its life to 0, and triggering any necessary game over or destruction processes.
     */
    void die();

    friend class Explosion;
    friend class Monster;
};

#endif