/**
 * @file Point.cpp
 * @brief Implementation of the Point class, representing a point in the game world.
 *
 * The Point class provides basic functionality for managing a point's position
 * (x, y) and color. It supports operations like moving the point along the x or
 * y axis, hiding the point, and accessing its position and color. This class
 * extends SFML's RectangleShape to render the point visually.
 *
 * @version 1.0
 * @date 2024-12-08
 */

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

public:
	/**
	 * @brief Default constructor for the Point class.
	 *
	 * Initializes the point with default values: position set to (-1, -1) and
	 * color set to "Invisible".
	 */
	Point();
	/**
	 * @brief Constructor for the Point class with specified position, size, and color.
	 *
	 * Initializes a point at the specified (x, y) coordinates with the given size
	 * and color. This constructor also sets up the fill color for the rectangle
	 * shape based on the specified color string.
	 *
	 * @param x The x-coordinate of the point.
	 * @param y The y-coordinate of the point.
	 * @param size The size of the point (not currently used but stored).
	 * @param color The color of the point, represented by a string ("B" for black, "W" for white).
	 */
	Point(float x, float y, int size, string color);

	/**
	 * @brief Constructor for the Point class with specified position and color.
	 *
	 * Initializes a point at the specified (x, y) coordinates and sets the color
	 * based on the provided string ("B" for black, "W" for white).
	 *
	 * @param x The x-coordinate of the point.
	 * @param y The y-coordinate of the point.
	 * @param color The color of the point, represented by a string ("B" for black, "W" for white).
	 */
	Point(float x, float y, string color);
	/**
	 * @brief Constructor for the Point class with specified position.
	 *
	 * Initializes a point at the specified (x, y) coordinates and sets the color
	 * to black by default.
	 *
	 * @param x The x-coordinate of the point.
	 * @param y The y-coordinate of the point.
	 */
	Point(float x, float y);

	/**
	 * @brief Moves the point one unit to the right (positive x-direction).
	 *
	 * This method increments the x-coordinate of the point by 1 and updates the
	 * position of the point in the SFML window.
	 */
	void xAdd();

	/**
	 * @brief Moves the point one unit upwards (positive y-direction).
	 *
	 * This method increments the y-coordinate of the point by 1 and updates the
	 * position of the point in the SFML window.
	 */
	void yAdd();

	/**
	 * @brief Moves the point one unit to the left (negative x-direction).
	 *
	 * This method decrements the x-coordinate of the point by 1 and updates the
	 * position of the point in the SFML window.
	 */
	void xSub();

	/**
	 * @brief Moves the point one unit downwards (negative y-direction).
	 *
	 * This method decrements the y-coordinate of the point by 1 and updates the
	 * position of the point in the SFML window.
	 */
	void ySub();

	/**
	 * @brief Hides the point by making it invisible.
	 *
	 * This method sets the color of the point to "Invisible" and makes the fill
	 * color transparent, effectively hiding the point from the display.
	 */
	void hide();

	/**
	 * @brief Gets the x-coordinate of the point.
	 *
	 * @return The current x-coordinate of the point.
	 */
	float getX() const;

	/**
	 * @brief Gets the y-coordinate of the point.
	 *
	 * @return The current y-coordinate of the point.
	 */
	float getY() const;

	friend class Monster;
	friend class SpaceShip;
};
#endif