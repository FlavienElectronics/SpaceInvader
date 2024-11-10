#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
using namespace std;

class SpaceShip;
class Point;

class Point : public sf::RectangleShape
{
private:
	float x, y;
	int size;
	string color;

public:
	Point()
	{
		this->x = -1;
		this->y = -1;
		this->color = "Invisible";
	}

	Point(float x, float y, int size, string color) : sf::RectangleShape(sf::Vector2f(1, 1))
	{
		this->x = x;
		this->y = y;
		this->size = size;
		this->color = color;

		this->setFillColor(sf::Color::Black);
		this->setPosition(x, y);
	}

	void xAdd()
	{
		this->x++;
		this->setPosition(x, y);
	}
	void yAdd()
	{
		this->y++;
		this->setPosition(x, y);
	}
	void xSub()
	{
		this->x--;
		this->setPosition(x, y);
	}
	void ySub()
	{
		this->y--;
		this->setPosition(x, y);
	}
};

/* Projectile généralisable avec SpaceShip ???*/
class Projectile : public sf::Drawable
{
private:
	Point *pt[2];
	float x, y;

public:
	Projectile(float x_pos, float y_pos, string color) : x(x_pos), y(y_pos)
	{
		pt[0] = new Point(x + 0, y + 0, 1, color);
		pt[1] = new Point(x + 0, y + 1, 1, color);
	}

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override
	{
		for (int i = 0; i < 2; i++)
		{
			target.draw(*pt[i], states);
		}
	}

    void ySub()
    {
        this->y--;
        pt[0]->ySub(); 
        pt[1]->ySub(); 
    }
};

class SpaceShip : public sf::Drawable
{
private:
	sf::RenderWindow *window;
	Point *pt[11];
	Projectile *pjt[50];
	float x, y;

	void correctPosition()
	{
		/*
				if (this->x < 0)
			this->x = 0;
		if (this->x > windowWidth - 2 * point.getRadius())
			this->x = windowWidth - 2 * point.getRadius();
		if (this->y < 0)
			this->y = 0;
		if (this->y > windowHeight - 2 * this->getRadius())
			this->y = windowHeight - 2 * point.getRadius();
			*/
	}

public:
	SpaceShip(sf::RenderWindow *win, float x_pos, float y_pos, string color) : x(x_pos), y(y_pos)
	{
		pt[0] = new Point(x + 2, y + 0, 1, color);
		pt[1] = new Point(x + 1, y + 1, 1, color);
		pt[2] = new Point(x + 2, y + 1, 1, color);
		pt[3] = new Point(x + 3, y + 1, 1, color);
		pt[4] = new Point(x + 0, y + 2, 1, color);
		pt[5] = new Point(x + 1, y + 2, 1, color);
		pt[6] = new Point(x + 2, y + 2, 1, color);
		pt[7] = new Point(x + 3, y + 2, 1, color);
		pt[8] = new Point(x + 4, y + 2, 1, color);
		pt[9] = new Point(x + 1, y + 3, 1, color);
		pt[10] = new Point(x + 3, y + 3, 1, color);
		this->window = win;
		for (int i = 0; i < 50; ++i)
		{
			pjt[i] = NULL;
		}
	}

	void shoot()
	{
		// Chercher un emplacement libre dans le tableau de projectiles
		for (int i = 0; i < 50; ++i)
		{
			if (pjt[i] == nullptr) // Si l'emplacement est libre
			{
				pjt[i] = new Projectile(this->x + 2, this->y - 5, "col");
				break;
			}
		}
	}

	void updateProjectiles()
	{
		// Déplacer tous les projectiles existants
		for (int i = 0; i < 50; ++i)
		{
			if (pjt[i] != nullptr)
			{
				// Déplacer le projectile (par exemple, le faire se déplacer vers le haut)
				pjt[i]->ySub(); // Vous pouvez ajouter une méthode de déplacement pour le projectile
			}
		}
	}

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override
	{
		// Dessiner tous les points du vaisseau
		for (int i = 0; i < 11; i++)
		{
			target.draw(*pt[i], states);
		}

		// Dessiner tous les projectiles
		for (int i = 0; i < 50; ++i)
		{
			if (pjt[i] != nullptr)
			{
				target.draw(*pjt[i], states);
			}
		}
	}

	void xAdd()
	{
		this->x++;
		for (int i = 0; i < 11; i++)
		{
			pt[i]->xAdd();
		}
	}
	void yAdd()
	{
		this->y++;
		for (int i = 0; i < 11; i++)
		{
			pt[i]->yAdd();
		}
	}
	void xSub()
	{
		this->x--;
		for (int i = 0; i < 11; i++)
		{
			pt[i]->xSub();
		}
	}
	void ySub()
	{
		this->y--;
		for (int i = 0; i < 11; i++)
		{
			pt[i]->ySub();
		}
	}

	~SpaceShip()
	{
		for (int i = 0; i < 11; i++)
		{
			delete pt[i]; // Libérer la mémoire allouée pour chaque Point
		}
	}
};

int main()
{
	const string gameName = "SpaceInvader";
	const float windowWidth = 1000;
	const float windowHeight = 562;

	// Création de la fenêtre SFML
	cout << "Window creation" << endl;
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), gameName);

	sf::CircleShape point(2);			// Point avec un rayon de 2 pixels
	point.setFillColor(sf::Color::Red); // Couleur du point

	float x = windowWidth / 2, y = windowHeight / 2; // Position initiale du point
	point.setPosition(x, y);

	Point p2(100, 100, 1, "Vert");
	SpaceShip ship(&window, 200, 100, "Green");
	sf::Clock clock;
	sf::Time delay = sf::milliseconds(20);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (clock.getElapsedTime() >= delay)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				ship.xAdd();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				ship.xSub();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				ship.yAdd();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				ship.ySub();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				ship.shoot();

			clock.restart(); // Redémarre l'horloge pour le prochain intervalle
		}

		// Empêcher le point de sortir des bords de la fenêtre

		// Mise à jour de la position du point
		point.setPosition(x, y);

		// Efface l'écran en blanc
		window.clear(sf::Color::White);

		window.draw(ship);
		ship.updateProjectiles();

		// Affiche la mise à jour de la fenêtre
		window.display();
	}
	cout << "Window closed" << endl;

	return 0;
}
