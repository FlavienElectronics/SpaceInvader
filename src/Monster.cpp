#include "Monster.hpp"
#include "Explosion.hpp"

Monster::Monster(sf::RenderWindow *win, float windowHeight, float windowWidth, float x_pos, float y_pos, string color)
{
    srand(time(0));
    this->alive = true;
    this->explo = new Explosion;
    this->direction = rand() % 2;

    this->x = x_pos;
    this->y = y_pos;
    this->numberOfPixels = 10;
    this->numberOfProjectiles = 10;
    this->xSize = 5;
    this->ySize = 4;
    this->stat = 0;

    pt = new Point *[numberOfPixels];
    pjt = new Projectile *[numberOfProjectiles];

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
    for (int i = 0; i < numberOfProjectiles; i++)
    {
        this->pjt[i] = nullptr;
    }
#ifdef VERBOSE_MONSTER
    cout << "Creation monster nb pixels " << numberOfPixels << " Sens : " << this->direction << endl;
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
    this->alive = false;
    if (explo != nullptr && stat < 3)
    {
        this->stat = explo->grow(*this);
#ifdef VERBOSE_MONSTER
        cout << "Status " << stat << endl;

#endif
    }
}

void Monster::updateParticule()
{
    if (this->alive == false && this->stat < 3)
    {
        this->hide();
        this->explode();
    }
}

bool Monster::isAlive()
{
    return(this->alive);
}

Monster::~Monster()
{
#ifdef VERBOSE_MONSTER
    cout << typeid(this).name() << " Nombre de pixels monstre " << numberOfPixels << endl;
    cout << typeid(this).name() << " Nombre de projectile monstre " << numberOfProjectiles << endl;
    cout << "Fin destructeur monster " << endl;
#endif
    delete explo;
}