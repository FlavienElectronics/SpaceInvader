#include "SpaceShip.hpp"
#include "MonsterLine.hpp"

SpaceShip::Exept::Exept(std::string mes)
{
    this->message = mes;
}

SpaceShip::SpaceShip() : x(0), y(0), numberOfPixels(11) {}

SpaceShip::SpaceShip(sf::RenderWindow *win, float windowHeight, float windowWidth, float x_pos, float y_pos, string color) : x(x_pos), y(y_pos), numberOfPixels(11), numberOfProjectiles(50), xSize(5), ySize(4)
{
#ifdef VERBOSE_SHIP
    cout << "Creation ship nb pixels " << numberOfPixels << endl;
#endif
    pt = new Point *[numberOfPixels];
    pjt = std::vector<Projectile *>();
    pt[0] = new Point(x + 0, y + 2, 1, color);
    pt[1] = new Point(x + 1, y + 1, 1, color);
    pt[2] = new Point(x + 1, y + 2, 1, color);
    pt[3] = new Point(x + 1, y + 3, 1, color);
    pt[4] = new Point(x + 2, y + 0, 1, color);
    pt[5] = new Point(x + 2, y + 1, 1, color);
    pt[6] = new Point(x + 2, y + 2, 1, color);
    pt[7] = new Point(x + 3, y + 1, 1, color);
    pt[8] = new Point(x + 3, y + 2, 1, color);
    pt[9] = new Point(x + 3, y + 3, 1, color);
    pt[10] = new Point(x + 4, y + 2, 1, color);
    this->life = 6;
    this->alive = true;
    this->window = win;
    this->winHeight = windowHeight;
    this->winWidth = windowWidth;
    this->hitBox_x = 4;
    this->hitBox_y = 3;
}

void SpaceShip::shoot()
{
    // Chercher un emplacement libre dans le tableau de projectiles
    for (int i = 0; i < numberOfProjectiles; ++i)
    {
        pjt.push_back(new Projectile(this->x + 2, this->y - 2, "col"));
        cout << "Lancement projectile, nombre total : " << pjt.size() << endl;
    }
}

void SpaceShip::correctCoordinates(int &xToCorrect, int &yToCorrect)
{
    int *yVector = new int[this->numberOfPixels];
    cout << "xToCorrect" << xToCorrect << endl;
    int ySmaller = this->hitBox_y; // Max on y axis
    for (int i = 0; i < this->numberOfPixels; i++)
    {
        yVector[i] = this->hitBox_y; // Max on y axis
        // cout <<this->pt[i]->color <<endl;
        cout << (int)this->pt[i]->getX() - (int)this->getX() << endl;
        if (((int)this->pt[i]->getX() - (int)this->getX()) == xToCorrect && this->pt[i]->color != "Invisible")
        {
            yVector[i] = ((int)this->pt[i]->getY() - (int)this->getY());
            cout << "Adding new value" << ((int)this->pt[i]->getY() - (int)this->getY()) << endl;
        }
    }
    for (int i = 0; i < this->numberOfPixels; i++)
    {
        if (ySmaller > yVector[i])
            ySmaller = yVector[i];
    }
    yToCorrect = ySmaller;
    delete[] yVector;
}

void SpaceShip::hidePixel(int xTH, int yTH)
{
    for (int i = 0; i < this->numberOfPixels; i++)
    {
        int xtemp = ((int)this->pt[i]->getX() - (int)this->getX());
        int ytemp = ((int)this->pt[i]->getY() - (int)this->getY());
        if (xtemp == xTH && ytemp == yTH)
        {
            // cout << (int)this->pt[i]->getX() - (int)this->getX() << "x-x " <<  (int)this->pt[i]->getY() - (int)this->getY() << "y-y" << endl;
            this->pt[i]->hide();
            cout << "Hiding pixel " << i << endl;
        }
    }
}

void SpaceShip::updateProjectiles()
{
    for (size_t i = 0; i < pjt.size();)
    {
        pjt[i]->ySub();                             // Déplacer le projectile
        if (pjt[i]->isOutOfBounds(this->winHeight)) // Si hors écran
        {
            delete pjt[i];
            pjt.erase(pjt.begin() + i); // Supprimer du vecteur
#ifdef VERBOSE_SHIP
            cout << "Destruction projectile, reste : " << pjt.size() << endl;
#endif
        }
        else
        {
            ++i; // Avancer seulement si aucun élément n'a été supprimé
        }
    }
}

void SpaceShip::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
// Dessiner tous les points du vaisseau
#ifdef VERBOSE_SHIP
    cout << "Nombre de pixels " << numberOfPixels << " " << pt << endl;
#endif
    if (pt != nullptr)
    {
        for (int i = 0; i < numberOfPixels; i++)
        {
            if (pt[i] != nullptr)
            {
                target.draw(*pt[i], states);
            }
        }

        // Dessiner tous les projectiles
        for (const auto &projectile : pjt)
        {
            target.draw(*projectile, states);
        }
    }
    else
    {
#ifdef VERBOSE_SHIP
        cout << typeid(this).name() << endl;
#endif
    }
}

void SpaceShip::xAdd()
{
    this->x++;
    if (this->x > winWidth - this->xSize)
    {
        this->x = winWidth - this->xSize;
        throw(Exept("x out of bound > width"));
    }
    else
    {
        for (int i = 0; i < numberOfPixels; i++)
        {
            pt[i]->xAdd();
        }
#ifdef VERBOSE_SHIP
        cout << "New pos : " << this->x << ";" << this->y << endl;
#endif
    }
}
void SpaceShip::yAdd()
{
    this->y++;
    if (this->y > winHeight - this->ySize)
    {
        this->y = winHeight - this->ySize;
        throw(Exept("y out of bound y > height"));
    }
    else
    {
        for (int i = 0; i < numberOfPixels; i++)
        {
            pt[i]->yAdd();
        }
#ifdef VERBOSE_SHIP
        cout << "New pos : " << this->x << ";" << this->y << endl;
#endif
    }
}
void SpaceShip::xSub()
{
    this->x--;
    if (this->x < 0)
    {
        this->x = 0;
        throw(Exept("x out of bound < 0"));
    }
    else
    {
        for (int i = 0; i < numberOfPixels; i++)
        {
            pt[i]->xSub();
        }
#ifdef VERBOSE_SHIP
        cout << "New pos : " << this->x << ";" << this->y << endl;
#endif
    }
}
void SpaceShip::ySub()
{
    this->y--;
    if (this->y < 0)
    {
        this->y = 0;
        throw(Exept("y out of bound y < 0"));
    }
    else
    {
        for (int i = 0; i < numberOfPixels; i++)
        {
            pt[i]->ySub();
        }
#ifdef VERBOSE_SHIP
        cout << "New pos : " << this->x << ";" << this->y << endl;
#endif
    }
}

void SpaceShip::goTo(float xValue)
{
    int delta = (int)xValue - (int)this->x;
    if (delta > 0)
    {
        try
        {
            this->xAdd();
        }
        catch (SpaceShip::Exept exp)
        {
            // cout << exp.message << endl;
        }
    }
    else if (delta < 0)
    {
        try
        {
            this->xSub();
        }
        catch (SpaceShip::Exept exp)
        {
            // cout << exp.message << endl;
        }
    }
    // cout << "x ship = " << this->x << " y ship =  " << this->y << endl;
}

SpaceShip::~SpaceShip()
{
#ifdef VERBOSE_SHIP
    cout << typeid(this).name() << " Nombre de pixels vaisseau " << numberOfPixels << endl;
    cout << typeid(this).name() << " Nombre de projectile vaisseau " << numberOfProjectiles << endl;
#endif
    if (pt != nullptr)
    {
        for (int i = 0; i < numberOfPixels; i++)
        {
            if (pt[i] != nullptr)
            {
                delete pt[i]; // Libérer la mémoire allouée pour chaque Point
#ifdef VERBOSE_SHIP
                cout << "Destruction point vaisseau " << i << endl;
#endif
            }
        }
        delete[] pt;
        pt = nullptr;
    }
#ifdef VERBOSE_SHIP
    cout << "Allons détruire les projectiles du vaisseau" << endl;
#endif
    for (auto &projectile : pjt)
    {
        delete projectile;
    }
    pjt.clear();
}

float SpaceShip::getX() const
{
    return (this->x);
}
float SpaceShip::getY() const
{
    return (this->y);
}

bool SpaceShip::detectImpact(MonsterLine **monsterLine, int numberOfLine)
{
    for (int j = 0; j < numberOfLine; j++)
    {
        if (monsterLine != nullptr)
        {
            MonsterLine *tempMonsterLine = monsterLine[j];
            for (int i = 0; i < tempMonsterLine->getNumberOfMonster(); i++)
            {

                Monster &tempMonster = (*monsterLine[j])[i];

                for (auto &monsterProjectile : tempMonster.pjt)
                {
                    if (monsterProjectile != nullptr)
                    {
                        /* Check if the position of the projectile is in the hitbox of the ship */
                        if ((int)monsterProjectile->getY() == (int)this->getY() &&
                            (int)monsterProjectile->getX() >= (int)this->getX() &&
                            (int)monsterProjectile->getX() < (int)this->getX() + (int)this->hitBox_x)
                        {
                            int xToDestroy = (int)monsterProjectile->getX() - (int)(this->getX());
                            int yToDestroy = (int)monsterProjectile->getY() + 1 - (int)(this->getY());

                            // Corriger les coordonnées avant de cacher le pixel
                            this->correctCoordinates(xToDestroy, yToDestroy);
                            this->hidePixel(xToDestroy, yToDestroy);

                            this->life--;
                            if (this->life == 0)
                            {
                                return true; // Détection d'impact fatal
                            }
                        }
                    }
                }
            }
        }
    }
    return (false);
}

bool SpaceShip::isAlive()
{
    return (this->alive);
}

void SpaceShip::die()
{
    this->alive = false;
}