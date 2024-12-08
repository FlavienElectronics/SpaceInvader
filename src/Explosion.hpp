/*Ajouter des entête sous chaque fichier*/

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