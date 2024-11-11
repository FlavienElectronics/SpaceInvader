#include "Projectile.hpp"

Projectile::Projectile(float x_pos, float y_pos, string color) : x(x_pos), y(y_pos), numberOfPixels(2)
{
    this->pt[0] = new Point(this->x + 0, this->y + 0, 1, color);
    this->pt[1] = new Point(this->x + 0, this->y + 1, 1, color);
}

void Projectile::ySub()
{
    this->y--;
    pt[0]->ySub();
    pt[1]->ySub();
}

// Vérifie si le projectile est en dehors de la fenêtre
bool Projectile::isOutOfBounds(float windowHeight)
{
    return this->y < 0; // Un projectile est hors de l'écran si sa position Y est inférieure à 0
}

void Projectile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (int i = 0; i < 2; i++)
    {
        target.draw(*pt[i], states);
    }
}

float Projectile::getY() const
{
    return y;
}

Projectile::~Projectile()
{
    for (int i = 0; i < numberOfPixels; i++)
    {
        if (pt[i] != nullptr)
        {
#ifdef VERBOSE
            cout << "Destruction point " << i << " projectile" << endl;
#endif
        }
    }
}