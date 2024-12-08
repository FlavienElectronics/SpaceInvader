/**
 * @file Explosion.hpp
 * @brief Declaration of the Explosion class, simulating the explosion effect in the game.
 * 
 * This file contains the definition of the `Explosion` class, which is responsible for simulating the
 * explosion effect of a monster when it is destroyed. The explosion grows in size over time, starting
 * with a single pixel and expanding into multiple pixels as the explosion progresses. The class manages
 * the state of the explosion through a status attribute, and it is linked to the `Monster` class to track
 * the position and size of the explosion relative to the monster. The explosion can grow through different
 * stages, representing different phases of the explosion's visual effect.
 * 
 * @version 1.0
 * @date 2024-12-08
 */

#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Monster.hpp"

class Monster;

using namespace std;

class Explosion : public SpaceShip
{
protected:
	int status; //-1 = starting | 0 = explosion range 1| 1 = explosion range 2 | 2 = monster has exploded
	void clearPoints();

public:
	/**
	 * @brief Default constructor for the Explosion class.
	 *
	 * Initializes all attributes to their default values. Sets `pt` to `nullptr`,
	 * `numberOfPixels` and `numberOfProjectiles` to 0, and `status` to -1.
	 */
	Explosion();

	/**
	 * @brief Simulates the growth of the explosion by modifying the points based on the explosion's status.
	 *
	 * @param monstr Reference to a Monster object used to determine the explosion's position and size.
	 *
	 * @return The current status of the explosion after the growth phase.
	 *
	 * - **Status -1:** Initializes the explosion with one pixel.
	 * - **Status 0:** Expands the explosion to three pixels.
	 * - **Status 1:** Further expands the explosion to seven pixels.
	 * - **Status 2:** Clears all points, ending the explosion.
	 */
	virtual int grow(const Monster &monstr);
	friend Monster;
};
#endif