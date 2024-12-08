/**
 * @file MonsterLine.cpp
 * @brief Implementation of the MonsterLine class, responsible for managing a group of monsters in the game.
 *
 * This class defines the behavior of a line of monsters, including managing their movement, drawing,
 * handling collisions, explosions, and direction changes. It also handles communication with individual
 * monsters within the line and provides various methods for game logic related to monster groups.
 *
 * @version 1.0
 * @date 2024-12-08
 */

#ifndef MONSTER_LINE_HPP
#define MONSTER_LINE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Monster.hpp"
#include "SpaceShip.hpp"

class MonsterLine
{
private:
	int direction;
	Monster **block;
	int numberOfMonster;
	float spacing;

	sf::RenderWindow *window;
	float winHeight;
	float winWidth;

public:
	/**
	 * @brief Constructor for the MonsterLine class.
	 *
	 * Initializes a new line of monsters at specified position, with a random direction and the given number of monsters.
	 * Each monster is allocated dynamically and placed with a certain spacing between them.
	 *
	 * @param win Pointer to the SFML window used for rendering the game.
	 * @param windowHeight The height of the game window.
	 * @param windowWidth The width of the game window.
	 * @param x_pos The initial x-coordinate of the first monster in the line.
	 * @param y_pos The initial y-coordinate of the monsters in the line.
	 * @param numberOfMonster The total number of monsters in the line.
	 * @param color The color used for the monsters (currently unused in the constructor).
	 */
	MonsterLine(sf::RenderWindow *win, float windowHeight, float windowWidth, float x_pos, float y_pos, int numberOfMonster, string color);
	/**
	 * @brief Overloaded index operator to access monsters in the line.
	 *
	 * Allows direct access to a specific monster in the line using the array index.
	 *
	 * @param location The index of the monster to be accessed.
	 * @return A reference to the monster at the specified location.
	 */
	Monster &operator[](int location);

	/**
	 * @brief Checks if all monsters in the line are destroyed.
	 *
	 * This method checks if all monsters have been destroyed and the line is empty.
	 *
	 * @return True if all monsters are destroyed, false otherwise.
	 */
	bool isLineDestoyed();
	/**
	 * @brief Draws the monsters in the line on the target.
	 *
	 * Loops through all monsters in the line and draws them to the screen.
	 *
	 * @param target The target to draw on (typically the game window).
	 * @param states Render states for drawing.
	 */
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	/**
	 * @brief Checks if a monster at the given location is currently exploding.
	 *
	 * @param location The index of the monster in the line.
	 * @return True if the monster is exploding, false otherwise.
	 */
	bool isExplosing(int location);
	/**
	 * @brief Updates the explosion particles of a specific monster in the line.
	 *
	 * This method updates the explosion effect if the monster is exploding.
	 *
	 * @param location The index of the monster to update.
	 */
	void updateParticule(int location);

	/**
	 * @brief Triggers the explosion of a specific monster in the line.
	 *
	 * This method simulates the explosion of a monster when it is destroyed.
	 *
	 * @param location The index of the monster to explode.
	 */
	void explode(int location);

	/**
	 * @brief Checks if a specific monster is alive.
	 *
	 * This method returns whether the monster at the given location is still alive.
	 *
	 * @param location The index of the monster to check.
	 * @return True if the monster is alive, false otherwise.
	 */
	bool isAlive(int location);

	/**
	 * @brief Changes the direction of the entire monster line.
	 *
	 * This method flips the direction of the whole line of monsters, causing them to
	 * move in the opposite direction.
	 */
	void changeDirection();

	/**
	 * @brief Checks for collisions between the spaceship and the monsters.
	 *
	 * This method updates a boolean array indicating whether a collision has occurred
	 * for each monster in the line.
	 *
	 * @param ship The spaceship object to check for collisions.
	 * @param vectorBool Pointer to a boolean array to store the collision status.
	 */
	void updateCollision(const SpaceShip &ship, bool **vectorBool);

	/**
	 * @brief Moves all monsters in the line to the left.
	 *
	 * This method shifts the position of each monster in the line by a fixed amount.
	 */
	void xSub();

	/**
	 * @brief Moves all monsters in the line to the right.
	 *
	 * This method shifts the position of each monster in the line by a fixed amount to the right.
	 */
	void xAdd();
	/**
	 * @brief Gets the direction of the monster line.
	 *
	 * @return The current direction of the line (1 for right, 0 for left).
	 */
	int getDirection();

	/**
	 * @brief Gets the total number of monsters in the line.
	 *
	 * @return The number of monsters in the line.
	 */
	int getNumberOfMonster();

	/**
	 * @brief Gets the number of monsters that are still alive in the line.
	 *
	 * This method counts how many monsters in the line are still alive.
	 *
	 * @return The number of alive monsters.
	 */
	int getNumberOfMonsterAlive();

	/**
	 * @brief Destructor for the MonsterLine class.
	 *
	 * Cleans up the dynamically allocated memory for the monsters in the line.
	 */
	~MonsterLine();
};

#endif