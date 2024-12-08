/**
 * @file Monster.hpp
 * @brief Declaration of the Monster class, representing an enemy spaceship in the game.
 * 
 * This file contains the definition of the `Monster` class, which inherits from the `SpaceShip` class.
 * The `Monster` class is responsible for managing an enemy spaceship's properties and behavior in the game.
 * It includes functionalities such as controlling the monster's movement, direction, collision detection, 
 * and handling projectiles and explosions. Monsters can shoot projectiles, change direction, and trigger 
 * explosion effects upon being destroyed. The class interacts with the `Explosion` class for visual effects 
 * and uses `sf::Clock` to manage timing for explosions.
 * 
 * @version 1.0
 * @date 2024-12-08
 */

#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "SpaceShip.hpp"

class Explosion;

using namespace std;

class Monster : public SpaceShip
{

protected:
	int direction; // 0 -> goes left | 1 -> goes right
	int stat;
	Explosion *explo; // Circular inclusion
	sf::Clock *clockExplosion;

public:
	/**
	 * @brief Constructor for the Monster class.
	 *
	 * Initializes the monster's properties, including position, size, and projectiles.
	 *
	 * @param win The render window for drawing the monster.
	 * @param windowHeight The height of the window.
	 * @param windowWidth The width of the window.
	 * @param x_pos The x-coordinate of the monster's initial position.
	 * @param y_pos The y-coordinate of the monster's initial position.
	 * @param direction The initial direction of the monster.
	 * @param color The color of the monster's pixels.
	 */
	Monster(sf::RenderWindow *win, float windowHeight, float windowWidth, float x_pos, float y_pos, int direction, string color);
	/**
	 * @brief Draws the monster, its projectiles, and explosion particles onto the screen.
	 *
	 * @param target The target to draw on.
	 * @param states The render states for drawing.
	 */
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	/**
	 * @brief Returns the current direction of the monster.
	 *
	 * @return The direction of the monster (1 for right, 0 for left).
	 */
	int getDirection();

	/**
	 * @brief Changes the direction of the monster.
	 *
	 * If the direction is 1 (right), it changes to 0 (left), and vice versa.
	 */
	void changeDirection();

	/**
	 * @brief Hides the monster by hiding its pixels.
	 */
	void hide();

	/**
	 * @brief Handles the explosion of the monster when it is destroyed.
	 *
	 * Changes the monster's state to "exploding" and triggers the explosion effect.
	 */
	void explode();

	/**
	 * @brief Destructor for the Monster class.
	 *
	 * Frees the memory allocated for the monster's explosion and projectile objects.
	 */
	~Monster();
	/**
	 * @brief Checks if the monster is currently exploding.
	 *
	 * @return True if the monster is exploding, false otherwise.
	 */
	bool isExplosing();
	/**
	 * @brief Returns the x-coordinate of the monster.
	 *
	 * @return The x-coordinate of the monster.
	 */
	float getX() const;
	/**
	 * @brief Returns the y-coordinate of the monster.
	 *
	 * @return The y-coordinate of the monster.
	 */
	float getY() const;

	/**
	 * @brief Updates the movement of the monster's projectiles.
	 *
	 * This function is called each frame to move the projectiles and check if they are out of bounds.
	 */
	void updateProjectiles();
	/**
	 * @brief Checks for collisions between the monster and the spaceship's projectiles.
	 *
	 * @param ship The spaceship object to check for collisions.
	 * @return True if a collision is detected, false otherwise.
	 */
	bool updateCollision(const SpaceShip &ship); // For projectile throw by player
	/**
	 * @brief Updates the monster's explosion effect.
	 *
	 * This function is called each frame to check if the monster is exploding.
	 */
	void updateParticule();

	/**
	 * @brief Shoots a projectile from the monster.
	 *
	 * The projectile is created at the monster's position and added to the list of projectiles.
	 */
	void shoot();

	/**
	 * @brief Returns the elapsed time from the monster's explosion clock.
	 *
	 * @return The elapsed time since the explosion was triggered.
	 */
	sf::Time getElapsedTimeClockExplosion();

	/**
	 * @brief Resets the explosion clock to restart the timer.
	 */
	void resetClockExplosion();

	friend class Explosion;
	friend class MonsterLine;
};
#endif