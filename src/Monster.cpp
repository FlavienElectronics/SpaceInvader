#include "Monster.hpp"
#include "Explosion.hpp"

Monster::Monster(sf::RenderWindow *win, float windowHeight, float windowWidth, float x_pos, float y_pos, int direction, string color)
{
    // Initialisation classique
    this->alive = true;
    this->explo = new Explosion;
    this->direction = direction;
    this->x = x_pos;
    this->y = y_pos;
    this->numberOfPixels = 10;
    this->numberOfProjectiles = 10;
    this->xSize = 5;
    this->ySize = 4;
    this->stat = -1;
    this->clockExplosion = new sf::Clock;
    
    pt = new Point *[numberOfPixels];
    pjt.resize(numberOfProjectiles, nullptr); // Remplacer l'allocation dynamique par un vecteur

    // Initialisation des points
    pt[0] = new Point(x + 1, y + 0, 1, color);
    pt[1] = new Point(x + 3, y + 0, 1, color);
    pt[2] = new Point(x + 0, y + 1, 1, color);
    pt[3] = new Point(x + 2, y + 1, 1, color);
    pt[4] = new Point(x + 4, y + 1, 1, color);
    pt[5] = new Point(x + 1, y + 2, 1, color);
    pt[6] = new Point(x + 2, y + 2, 1, color);
    pt[7] = new Point(x + 3, y + 2, 1, color);
    pt[8] = new Point(x + 1, y + 3, 1, color);
    pt[9] = new Point(x + 3, y + 3, 1, color);

    this->window = win;
    this->winHeight = windowHeight;
    this->winWidth = windowWidth;
    this->hitBox_x = 4;
    this->hitBox_y = 3;
    
#ifdef VERBOSE_MONSTER
    cout << "Creation monster nb pixels " << numberOfPixels << endl;
#endif
}


void Monster::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // Dessiner tous les points du vaisseau
    for (int i = 0; i < this->numberOfPixels; i++)
    {
        target.draw(*this->pt[i], states);
    }

    // Dessiner tous les projectiles
    for (int i = 0; i < this->numberOfProjectiles; i++)
    {
        if (this->pjt[i] != nullptr)
        {
            target.draw(*this->pjt[i], states);
        }
    }

    for (int i = 0; i < this->explo->numberOfPixels; i++)
    {
        if (this->explo->pt[i] != nullptr)
        {
            target.draw(*this->explo->pt[i], states);
        }
    }
}

int Monster::getDirection()
{
    return (this->direction);
}

void Monster::changeDirection()
{
    if (this->direction == 1)
    {
        this->direction = 0;
    }
    else
    {
        this->direction = 1;
    }
}

void Monster::hide()
{
    if (this->pt != nullptr)
    {
        for (int i = 0; i < this->numberOfPixels; i++)
        {
            if (this->pt[i] != nullptr)
            {
                this->pt[i]->hide();
            }
        }
    }
}

void Monster::explode()
{
    this->hide();
    this->alive = false;
    if (this->explo != nullptr && stat < 3)
    {
        this->stat = this->explo->grow(*this);
#ifdef VERBOSE_MONSTER
        cout << "Status " << stat << endl;
#endif
    }
}

void Monster::updateParticule()
{
    if (this->alive == false && this->stat < 3)
    {
        if (this->stat > -1)
        {
            this->explode();
        }
    }
}

bool Monster::isExplosing()
{
    // cout << "Helo"<< endl;
    if (this->stat >= 0 && this->stat < 3)
    {
        return (true);
    }
    return (false);
}

float Monster::getX() const
{
    return (this->x);
}
float Monster::getY() const
{
    return (this->y);
}

bool Monster::updateCollision(const SpaceShip &ship)
{
    for (int i = 0; i < this->numberOfPixels; i++)
    {
        for (size_t j = 0; j < ship.pjt.size(); j++) // Utilisation du vecteur
        {
            if (ship.pjt[j] != nullptr && this->pt[i] != nullptr)
            {
                if ((int)ship.pjt[j]->x == (int)this->pt[i]->x && (int)ship.pjt[j]->y == (int)this->pt[i]->y)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

sf::Time Monster::getElapsedTimeClockExplosion()
{
    //cout << this->clockExplosion << endl;
    //cout << this->clockExplosion->getElapsedTime().asMilliseconds() << endl;
    return (this->clockExplosion->getElapsedTime());
}

void Monster::resetClockExplosion()
{
    this->clockExplosion->restart();
}

void Monster::shoot()
{
    for (size_t i = 0; i < pjt.size(); ++i)
    {
        if (pjt[i] == nullptr) // Si l'emplacement est libre
        {
            pjt[i] = new Projectile(this->x + 2, this->y - 2, "col");
            break;
        }
    }
}


void Monster::updateProjectiles()
{
    for (size_t i = 0; i < pjt.size(); i++) // Utilisation du vecteur
    {
        if (pjt[i] != nullptr)
        {
            // Déplacer le projectile vers le haut
            pjt[i]->yAdd();

            // Vérifier si le projectile est en dehors de l'écran
            if (pjt[i]->isOutOfBounds(this->winHeight))
            {
                // Libérer la mémoire du projectile
                delete pjt[i];
                pjt[i] = nullptr;
            }
        }
    }
}



Monster::~Monster()
{
#ifdef VERBOSE_MONSTER
    cout << typeid(this).name() << " Nombre de pixels monstre " << numberOfPixels << endl;
    cout << typeid(this).name() << " Nombre de projectile monstre " << numberOfProjectiles << endl;
    cout << "Fin destructeur monster " << endl;
#endif

    delete clockExplosion;
    delete explo;
}
