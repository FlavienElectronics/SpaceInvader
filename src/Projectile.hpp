/**
 * @file Projectile.cpp
 * @brief Implementation of the Projectile class, representing a projectile in the game.
 *
 * The Projectile class handles the creation, movement, and rendering of projectiles
 * in the game. It supports operations like moving the projectile vertically,
 * checking if it is out of bounds, and drawing it on the screen. Each projectile
 * is represented by two points that form a vertical line on the screen.
 *
 * @version 1.0
 * @date 2024-12-08
 */

#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Point.hpp"


using namespace std;

class Projectile : public sf::Drawable
{
private:
	int numberOfPixels;
	Point *pt[2];
	float x, y;

public:
	/**
	 * @brief Constructor for the Projectile class.
	 *
	 * Initializes the projectile with a specified position and color. The projectile
	 * is represented by two points, one for each part of the projectile. These points
	 * are initialized at the provided coordinates.
	 *
	 * @param x_pos The x-coordinate of the projectile's starting position.
	 * @param y_pos The y-coordinate of the projectile's starting position.
	 * @param color The color of the projectile, represented as a string.
	 */
	Projectile(float x_pos, float y_pos, string color);

	/**
	 * @brief Moves the projectile one unit upwards (negative y-direction).
	 *
	 * This method decrements the y-coordinate of the projectile by 1, and updates
	 * the y-coordinate of both points representing the projectile.
	 */
	void ySub();

	/**
	 * @brief Moves the projectile one unit downwards (positive y-direction).
	 *
	 * This method increments the y-coordinate of the projectile by 1, and updates
	 * the y-coordinate of both points representing the projectile.
	 */
	void yAdd();

	/**
	 * @brief Checks if the projectile is out of bounds of the game window.
	 *
	 * This method checks if the projectile has gone beyond the top or bottom edge
	 * of the window, returning `true` if it is out of bounds and `false` otherwise.
	 *
	 * @param windowHeight The height of the game window.
	 * @return `true` if the projectile is out of bounds, `false` otherwise.
	 */
	bool isOutOfBounds(float windowHeight);

	/**
	 * @brief Draws the projectile on the screen.
	 *
	 * This method draws both points representing the projectile on the target window.
	 *
	 * @param target The render target where the projectile is to be drawn.
	 * @param states The render states used for drawing.
	 */
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	/**
	 * @brief Gets the y-coordinate of the projectile.
	 *
	 * @return The current y-coordinate of the projectile.
	 */
	float getY() const;

	/**
	 * @brief Gets the x-coordinate of the projectile.
	 *
	 * @return The current x-coordinate of the projectile.
	 */
	float getX() const;

	/**
	 * @brief Destructor for the Projectile class.
	 *
	 * Cleans up the memory allocated for the points representing the projectile.
	 * This destructor ensures that the points are properly destroyed when the
	 * projectile object is destroyed.
	 */
	~Projectile();

	friend class Monster;
};
#endif