#include "SpaceShip.hpp"

SpaceShip::Exept::Exept(std::string mes)
{
    this->message = mes;
}

SpaceShip::SpaceShip() : x(0), y(0), numberOfPixels(11) {}

SpaceShip::SpaceShip(sf::RenderWindow *win, float windowHeight, float windowWidth, float x_pos, float y_pos, string color) : x(x_pos), y(y_pos), numberOfPixels(11), numberOfProjectiles(50), xSize(5), ySize(4)
{
#ifdef VERBOSE
    cout << "Creation ship nb pixels " << numberOfPixels << endl;
#endif
    pt = new Point *[numberOfPixels];
    pjt = new Projectile *[numberOfProjectiles];
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
    this->winHeight = windowHeight;
    this->winWidth = windowWidth;
    for (int i = 0; i < numberOfProjectiles; i++)
    {
        this->pjt[i] = nullptr;
    }
}

void SpaceShip::shoot()
{
    // Chercher un emplacement libre dans le tableau de projectiles
    for (int i = 0; i < numberOfProjectiles; ++i)
    {
        if (pjt[i] == nullptr) // Si l'emplacement est libre
        {
            pjt[i] = new Projectile(this->x + 2, this->y - 2, "col");
#ifdef VERBOSE
            cout << "Lancement projectile " << i << endl;
#endif
            break;
        }
    }
}

void SpaceShip::updateProjectiles()
{
    for (int i = 0; i < numberOfProjectiles; ++i)
    {
        if (pjt[i] != nullptr)
        {
            // Déplacer le projectile vers le haut
            pjt[i]->ySub();

            // Vérifier si le projectile est en dehors de l'écran
            if (pjt[i]->isOutOfBounds(this->winHeight))
            {
                // Libérer la mémoire du projectile
                delete pjt[i];
                pjt[i] = nullptr;
#ifdef VERBOSE
                cout << "Destruction projectile " << i << endl;
#endif
            }
        }
    }
}

void SpaceShip::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // Dessiner tous les points du vaisseau
    for (int i = 0; i < numberOfPixels; i++)
    {
        target.draw(*pt[i], states);
    }

    // Dessiner tous les projectiles
    for (int i = 0; i < numberOfProjectiles; ++i)
    {
        if (pjt[i] != nullptr)
        {
            target.draw(*pjt[i], states);
        }
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
#ifdef VERBOSE
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
#ifdef VERBOSE
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
#ifdef VERBOSE
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
#ifdef VERBOSE
        cout << "New pos : " << this->x << ";" << this->y << endl;
#endif
    }
}

SpaceShip::~SpaceShip()
{
#ifdef VERBOSE
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
#ifdef VERBOSE
                cout << "Destruction point vaisseau " << i << endl;
#endif
            }
        }
        delete[] pt;
        pt = nullptr;
    }
#ifdef VERBOSE
    cout << "Allons détruire les projectiles du vaisseau" << endl;
#endif
    if (pjt != nullptr)
    {
        for (int i = 0; i < numberOfProjectiles; i++)
        {
            if (pjt[i] != nullptr)
            {
                delete pjt[i]; // Libérer chaque projectile si il est alloué
#ifdef VERBOSE
                cout << "Destruction point vaisseau " << i << endl;
#endif
            }
        }
        delete[] pjt;
        pjt = nullptr;
    }
}

float SpaceShip::getX()
{
    return (this->x);
}
float SpaceShip::getY()
{
    return (this->y);
}
